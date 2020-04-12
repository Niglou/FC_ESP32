#include "init.h"
#include "rom/ets_sys.h"

#include <registers/dport_reg.h>

// Internal periph ESP32 NONOS
#include "intr.h"
#include "timer.h"
#include "spi.h"
#include "rmt.h"
#include "gpio.h"
#include "adc.h"

// External periph FC ESP32
#include "drivers/led/ws2812b.h"
#include "drivers/imu/mpu9250.h"
#include "drivers/esc/esc.h"
#include "drivers/osd/max7456.h"
#include "rx/pwm.h"
#include "rx/rx.h"
#include "gpio/gpio.h"

#include "imu/kalman.h"
#include "imu/pid.h"

#include "config.h"

#include <registers/struct/gpio_struct.h>

#include <math.h>

// Attribute for APP CPU section
#define IRAM_APP_CPU __attribute__((section(".app_text")))
#define DRAM_APP_CPU __attribute__((section(".app_data")))

extern "C" {
  void main_cpu0();
  void IRAM_APP_CPU main_cpu1();
}

int DRAM_APP_CPU app_cpu_status = 0;

extern volatile int rx_channel_[NUM_CHANNEL];

const float _gyro_sens  = 1 / GYRO_SENS_2000DPS;
const float _acc_sens   = 1 / ACC_SENS_8G;

// R1 = 30000 R2 = 1000  Ub = Uadc * (R2/(R1+R2))
const float battery_pont = 34.1;

// Global objects store like static, not heap or stack for better performances

// Internal periph
TIMPeriph Timer;
SPIPeriph SPI;
SPIPeriph HSPI;
SPIPeriph VSPI;
RMTPeriph RMT_[5];
ADCPeriph ADC1;

// External periph
MPU9250 imu;
MAX7456 osd;
ESC motor_[4];

// Variables
int offset_gyro[3] = {0};
int offset_acc[3] = {0};

float prev_gyro[3][2] = {0};

float acc_x, acc_y, acc_z;
float gyro_x, gyro_y, gyro_z;

Kalman kalman_pro;
Kalman DRAM_APP_CPU kalman_app;
float angle_est_x, angle_est_y, angle_est_z;
float rate_est_x, rate_est_y;

PID pid_pitch, pid_roll, pid_yaw;
PID pid_acc_p, pid_acc_r;

short output_motor_[4];

uint32_t battery_voltage = 0;

// APP CPU Function
void main_cpu1() {

  // Change stack space (32KB banks) for dual core
  asm(
    "movsp sp, %0;"
    "mov.n a7, sp"
    ::"a"(0x3FFE8000)
  );

  while(1) {
    while(!app_cpu_status);

    if(app_cpu_status == 1) {

      // Calcul kalman
      kalman_app.update(&rate_est_y, &angle_est_y, gyro_y, acc_x);

    }

    app_cpu_status = 0;
  }
}

// PRO CPU Function
void main_cpu0() {

  // Change stack space (32KB banks) for dual core
  asm(
    "movsp sp, %0;"
    "mov.n a7, sp"
    ::"a"(0x3FFF0000)
  );

  init_esp32();
  ets_install_uart_printf();
  ets_update_cpu_frequency_rom(80);

  /* ********* SETUP *********** */

  Timer.attach(GROUP0, TIMER0);

   SPI.attach(SPI1_PERIPH);
  HSPI.attach(SPI2_PERIPH);
  VSPI.attach(SPI3_PERIPH);

  /* Attach RMT object to each channel */
  RMT_[0].attach(CHANNEL_0);
  RMT_[1].attach(CHANNEL_1);
  RMT_[2].attach(CHANNEL_2);
  RMT_[3].attach(CHANNEL_3);

  ADC1.attach(RTC_ADC_1);

  imu.attach(&HSPI);

  for(int i=0; i<4; i++)
    motor_[i].attach(&RMT_[i]);

  osd.attach(&VSPI);

  // Set PID value
  pid_pitch.K ( 1.3f  , 0.0035f  , 5.0f );
  pid_roll.K  ( 1.3f  , 0.0035f  , 5.0f );
  pid_yaw.K   ( 1.4f  , 0.0050f  , 0.0f );

  pid_acc_p.K ( 0.4f  , 0.0f  , 0.0f );
  pid_acc_r.K ( 0.4f  , 0.0f  , 0.0f );

  // Initialize input
  init_input_pwm();

  // Initialize spi controller
  imu.spi_init();

  // Config and start Timer
  Timer.divider(80);
  Timer.enable();

  // Initialize spi controller
  osd.spi_init();

  for(int i=0; i<4; i++)
    motor_[i].mode(ESC_MODE);

  ADC1.set_width(ADC_WIDTH_BIT_12);
  ADC1.set_channel_atten(ADC_CHANNEL_0, ADC_ATTEN_DB_0);
  ADC1.start_async(ADC_CHANNEL_0);

  // Initialize gpio for sensors, esc, input, etc
  init_gpio();

  // Led GPIO
  IOMUX.GPIO2.reg = 0;
  IOMUX.GPIO2.func_drv = 1;
  GPIO.func_out_sel_cfg[2].reg = 91;

  // Check mpu
  if(imu.check()) ets_printf("MPU9250 : detected ! \n");
  else {
    ets_printf("MPU9250 : not found ! \n");
    while(1);
  }

  // Initialize mpu and use the 20Mhz clock
  imu.mpu_init();
  imu.clk_20Mhz();

  // Calcul gyro offset
  imu.config_get_gyro();
  struct esp32_mpu_gyro *gyro = (esp32_mpu_gyro*)imu.buffer();
  for(int i=0; i<500; i++) {
    imu.get();
    offset_gyro[0] += gyro->gyroX;
    offset_gyro[1] += gyro->gyroY;
    offset_gyro[2] += gyro->gyroZ;
    while( Timer.counter_l() < 250 );
    Timer.counter_l(0);
  }
  for(int i=0; i<3; i++)
    offset_gyro[i] /= 500;


  // Calcul accelerometer offset
/*
  imu.config_get_acc();
  struct esp32_mpu_gyro *acc = (esp32_mpu_gyro*)imu.buffer();
  for(int i=0; i<500; i++) {
    Timer.counter_l(0);
    imu.get();
    offset_acc[0] += acc->gyroX;
    offset_acc[1] += acc->gyroY;
    offset_acc[2] += acc->gyroZ;
    while( Timer.counter_l() < 500 );
  }

  for(int i=0; i<3; i++)
    offset_acc[i] /= 500;

  ets_printf("X: %d\nY: %d\nZ: %d\n", (int)offset_acc[0], (int)offset_acc[1], (int)offset_acc[2]);
*/

  // Set accelerometer offsets
  offset_acc[0] = -120;
  offset_acc[1] = 75;
  offset_acc[2] = 84;

  // Wait 1sec
  ets_delay_us(1000000);

  // Initialize kalman variables
  kalman_pro.init();
  kalman_app.init();

  // Set kalman dt (loop time unit=sec)
  kalman_pro.set_dt(0.00025f);
  kalman_app.set_dt(0.00025f);

  // Initialize MAX7456
  osd.init();

  // Config imu object to get all sensors values
  imu.config_get_all();

  float RC = 1 / ( 2 * M_PI * 75.0f);
  float K_GYRO = 0.00025f / (RC + 0.00025f);

  // Start APP_CPU
  *(unsigned int*)(DPORT_APPCPU_CTRL_D_REG) = (unsigned int)&main_cpu1; // Address function
  *(unsigned int*)(DPORT_APPCPU_CTRL_A_REG) = 1; // Set reset
  *(unsigned int*)(DPORT_APPCPU_CTRL_B_REG) = 1; // Set clock
  *(unsigned int*)(DPORT_APPCPU_CTRL_A_REG) = 0; // Clear reset

  // Interrupt matrix
  // RX input pwm
  *(unsigned int*)(DPORT_PRO_GPIO_INTERRUPT_NMI_MAP_REG) = 26; // gpio -> level 5(26)
  intr_enable( 1<<26 ); // Enable interrupt 26 (LVL5)

  /* ************ LOOP ************ */
  int test_time = 0;
  while(1) {

    // 500 (2KHz)
    // Use Low address counter (32bit)
    // No need High address (64bit)
    while( Timer.counter_l() < 250 );
    Timer.counter_l(0);

    // Get sensors values from SPI buffer
    struct esp32_mpu_all *sensors_raw;
    sensors_raw = (struct esp32_mpu_all*)imu.buffer(); // imu buffer (SPI)

    struct esp32_mpu_all sensors;
    sensors.accX = sensors_raw->accX - offset_acc[0];
    sensors.accY = sensors_raw->accY - offset_acc[1];
    sensors.accZ = sensors_raw->accZ - offset_acc[2];

    sensors.gyroX = sensors_raw->gyroX - offset_gyro[0];
    sensors.gyroY = sensors_raw->gyroY - offset_gyro[1];
    sensors.gyroZ = sensors_raw->gyroZ - offset_gyro[2];

    sensors.temp = sensors_raw->temp;

    // Start SPI transfer while calcul
    imu.get_async();

    // Correct the direction
    sensors.gyroX *= -1;
    sensors.gyroY *= -1;
    sensors.gyroZ *= -1;

    sensors.accX *= -1;

    // Convert to g
    acc_x = sensors.accX * _acc_sens;
    acc_y = sensors.accY * _acc_sens;
    acc_z = sensors.accZ * _acc_sens;

    // Convert to °/s
    gyro_x = sensors.gyroX * _gyro_sens;
    gyro_y = sensors.gyroY * _gyro_sens;
    gyro_z = sensors.gyroZ * _gyro_sens;

/*
    // Average of 2 values
    gyro_x = (gyro_x + prev_gyro[0][0]) * 0.5f;
    gyro_y = (gyro_y + prev_gyro[1][0]) * 0.5f;
    gyro_z = (gyro_z + prev_gyro[2][0]) * 0.5f;

    prev_gyro[0][0] = gyro_x;
    prev_gyro[1][0] = gyro_y;
    prev_gyro[2][0] = gyro_z;
*/

    // PT1 Filter
    prev_gyro[0][0] = prev_gyro[0][0] + K_GYRO * (gyro_x - prev_gyro[0][0]);
    prev_gyro[1][0] = prev_gyro[1][0] + K_GYRO * (gyro_y - prev_gyro[1][0]);
    prev_gyro[2][0] = prev_gyro[2][0] + K_GYRO * (gyro_z - prev_gyro[2][0]);

    gyro_x = prev_gyro[0][0];
    gyro_y = prev_gyro[1][0];
    gyro_z = prev_gyro[2][0];


    // float temp = (sensors.temp / 321.0 + 21) * 10;


    // Start kalman calcul on APP_CPU
    app_cpu_status = 1;

    // Get battery voltage
    battery_voltage = ADC1.get_voltage_async();
    float real_voltage = battery_voltage * battery_pont - 3200;

    // Convert voltage to XX.XX array for MAX7456
    int real_voltage_int = real_voltage;
    char array_real_voltage[5];
    for(int i=4; i>=0; i--) {
      array_real_voltage[i] = real_voltage_int % 10;
      real_voltage_int /= 10;
    }
    array_real_voltage[4] = array_real_voltage[3];
    array_real_voltage[3] = array_real_voltage[2];
    array_real_voltage[2] = 65; // 65 = '.'

    // Print to screen
    osd.print(13, 12, array_real_voltage, 5);

    // Start adc convert
    ADC1.start_async(ADC_CHANNEL_0);

    // Get input from interrupt variables
    float throttle_ch = rx_channel_[0];
    float pitch_ch    = rx_channel_[2];
    float roll_ch     = rx_channel_[1];
    float yaw_ch      = rx_channel_[3];
    float aux_1       = rx_channel_[4];
    float aux_2       = rx_channel_[5];

    // Input Margin
    if(pitch_ch > 1510.0f)     pitch_ch  -= 1510.0f;
    else if(pitch_ch < 1490.0f)pitch_ch  -= 1490.0f;
    else pitch_ch = 0.0f;

    if(roll_ch > 1510.0f)      roll_ch   -= 1510.0f;
    else if(roll_ch < 1490.0f) roll_ch   -= 1490.0f;
    else roll_ch = 0.0f;

    if(yaw_ch > 1510.0f)       yaw_ch    -= 1510.0f;
    else if(yaw_ch < 1490.0f)  yaw_ch    -= 1490.0f;
    else yaw_ch = 0.0f;

    // Input max value
    if(pitch_ch < -500.0f) pitch_ch  = -500.0f;
    if(roll_ch  < -500.0f) roll_ch   = -500.0f;
    if(yaw_ch   < -500.0f) yaw_ch    = -500.0f;

    if(pitch_ch > 500.0f) pitch_ch = 500.0f;
    if(roll_ch  > 500.0f) roll_ch  = 500.0f;
    if(yaw_ch   > 500.0f) yaw_ch   = 500.0f;

    pitch_ch  = apply_rc_expo(pitch_ch);
    roll_ch   = apply_rc_expo(roll_ch);
    yaw_ch    = apply_rc_expo(yaw_ch);


    // Kalman calcul on PRO_CPU
    kalman_pro.update(&rate_est_x, &angle_est_x, gyro_x, acc_y);

    // Wait calcul of APP_CPU
    while(app_cpu_status);

    // x°*10 -> 50° max (command_max = 500)
    angle_est_x *= 10.0f;
    angle_est_y *= 10.0f;

    // Calcul PID
    float Pitch, Roll, Yaw;
    // If switch STABLE MODE (AUX 2)
    if( aux_2 > 1500.0f ) {
      pitch_ch = pid_acc_p.calcul(pitch_ch, angle_est_y);
      roll_ch  = pid_acc_r.calcul(roll_ch, angle_est_x);
    }
    Pitch = pid_pitch.calcul(pitch_ch, gyro_y);
    Roll  = pid_roll.calcul(roll_ch, gyro_x);
    Yaw = pid_yaw.calcul(yaw_ch, gyro_z);

    // Throttle 0 - 1000
    throttle_ch -= 1000.0f;

    // If Throttle 0 - 1000, convert to 0 - 2000 for dshot
    if(ESC_MODE >= DSHOT150) throttle_ch *= 2.0f;

    // Limit value of throttle
    if(throttle_ch < 0.0f) throttle_ch = 0.0f;
    if(throttle_ch > 1500.0f) throttle_ch = 1500.0f;

    // Mix motor
    output_motor_[0] = throttle_ch - Pitch - Roll + Yaw;
		output_motor_[1] = throttle_ch - Pitch + Roll - Yaw;
		output_motor_[2] = throttle_ch + Pitch + Roll + Yaw;
		output_motor_[3] = throttle_ch + Pitch - Roll - Yaw;

    // If ARM (AUX 1)
    if(aux_1 > 1500.0f) {

      for(int i=0; i<4; i++) {
        if(output_motor_[i] > 1500) output_motor_[i] = 1500;
        else if(output_motor_[i] < 25) output_motor_[i] = 25;
      }

      // Set buffer motor (rmt buffer)
      for(int i=0; i<4; i++)
          motor_[i].set(output_motor_[i] + 48); // DSHOT +48

    }
    // If NOT ARM
    else {

      // Reset PID sum
      pid_pitch.reset_i_sum();
      pid_roll.reset_i_sum();
      pid_yaw.reset_i_sum();

      pid_acc_p.reset_i_sum();
      pid_acc_r.reset_i_sum();

      // Set buffer motor (rmt buffer)
      for(int i=0; i<4; i++)
        motor_[i].set(0);

    }

    // Send motor buffer to ESC
    for(int i=0; i<4; i++)
      motor_[i].write();

    // Loop time
    //int looptime = Timer.counter_l();
    //ets_printf("t:%d us \n", looptime);


  }

}
