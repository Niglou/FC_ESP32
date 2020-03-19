#include "init.h"
#include "rom/ets_sys.h"

#include <registers/dport_reg.h>

/* Internal periph */
#include "intr.h"
#include "timer.h"
#include "spi.h"
#include "spi_flash.h"
#include "rmt.h"
#include "gpio.h"
#include "i2c.h"

/* External periph */
#include "drivers/led/ws2812b.h"
#include "drivers/imu/mpu9250.h"
#include "drivers/esc/esc.h"
#include "drivers/osd/max7456.h"

#include "rx/pwm.h"

#include "gpio/gpio.h"

#include "imu/kalman.h"
#include "imu/pid.h"

#include "config.h"

#include <registers/struct/gpio_struct.h>

#include "adc/battery.h"


#include <math.h>
#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f

#define reg(r) *(volatile unsigned int*)(r)

extern "C" {

  void main_cpu0();
  void main_cpu1();

}

extern volatile int channel_[NUM_CHANNEL];

const float _gyro_sens  = 1 / GYRO_SENS_2000DPS;
const float _acc_sens   = 1 / ACC_SENS_8G;
const float _battery_conv = 1.0f / 4096.0f * 31.0f;

PID pid_pitch, pid_roll, pid_yaw;

int offset_gyro[3] = {0};
float prev_gyro[3] = {0};

short output_motor_1, output_motor_2, output_motor_3, output_motor_4;

void main_cpu0() {

  init_esp32();
  ets_install_uart_printf();
  ets_update_cpu_frequency_rom(80);

  /* ********* SETUP *********** */

  TIMPeriph Timer(GROUP0, TIMER0);

  SPIPeriph SPI(SPI1_PERIPH);
  SPIPeriph HSPI(SPI2_PERIPH);
  SPIPeriph VSPI(SPI3_PERIPH);

  RMTPeriph RMT_0(CHANNEL_0);
  RMTPeriph RMT_1(CHANNEL_1);
  RMTPeriph RMT_2(CHANNEL_2);
  RMTPeriph RMT_3(CHANNEL_3);

  RMTPeriph RMT_4(CHANNEL_4);

  pid_pitch.K ( 2.2f , 0.006f , 3.0f );
  pid_roll.K  ( 2.2f , 0.006f , 3.0f );
  pid_yaw.K   ( 4.75f , 0.018f , 0.0f );

  intFlashClass FLASH(&SPI);

  MPU9250 imu(&HSPI);
  MAX7456 osd(&VSPI);

  init_input_pwm();

  ESC motor_1(&RMT_0);
  ESC motor_2(&RMT_1);
  ESC motor_3(&RMT_2);
  ESC motor_4(&RMT_3);

  WS2812B led(&RMT_4);

  Kalman kalman_x, kalman_y;

  Timer.divider(80);
  Timer.enable();

  FLASH.spi_init();

  imu.init_spi();
  osd.spi_init();

  motor_1.mode(ESC_MODE);
  motor_2.mode(ESC_MODE);
  motor_3.mode(ESC_MODE);
  motor_4.mode(ESC_MODE);

  adc_battery_init();

  FLASH.spi_bus_init();
  init_gpio();

  //FLASH.write(0x10002, 0x3F);

  // Led GPIO
  IOMUX.GPIO2.reg = 0;
  IOMUX.GPIO2.func_drv = 1;
  GPIO.func_out_sel_cfg[2].reg = 91;

  if(imu.check())
    ets_printf("MPU9250 : detected ! \n");
  else
    ets_printf("MPU9250 : not found ! \n");

  imu.init();
  imu.clk_20Mhz();

  struct esp32_mpu_gyro *gyro = (esp32_mpu_gyro*)imu.buffer();
  for(int i=0; i<500; i++) {
    imu.get_gyro();
    offset_gyro[0] += gyro->gyroX;
    offset_gyro[1] += gyro->gyroY;
    offset_gyro[2] += gyro->gyroZ;
    while( Timer.counter_l() < 500 );
    Timer.counter_l(0);
  }
  offset_gyro[0] /= 500;
  offset_gyro[1] /= 500;
  offset_gyro[2] /= 500;

  ets_delay_us(2000000);

  osd.init();

  led.color(120, 0, 0);

  //int throttle_ch, pitch_ch, roll_ch, yaw_ch, aux_1;

  /* Interrupt matrix */
  reg(DPORT_PRO_GPIO_INTERRUPT_NMI_MAP_REG) = 26; // gpio -> level 5(26)
  intr_enable( 1<<26 );


  /* ************ LOOP ************ */
  int test_time = 0;
  while(true) {

    // 2500 (400Hz)
    while( Timer.counter_l() < 500 );
    Timer.counter_l(0);

    float adc_reading = 0.0f;
    for(int i=0; i<5; i++) adc_reading += get_battery_voltage();
    adc_reading *= 0.2f;

    float adc_value = adc_reading * _battery_conv * 1000;
    int adc_integer = adc_value;

    char array[5];
    for (int i = 4; i >= 0; i--) {
      array[i] = adc_integer % 10;
      if(array[i] == 0) array[i] = 0x0A;
      adc_integer /= 10;
    }

    osd.print(array, 13, 12); // 300us

/*
    ets_printf("%d \n", adc_integer);
*/

    //led.write();

    // Get sensors values from SPI buffer
    struct esp32_mpu_all *sensors_raw;
    sensors_raw = (struct esp32_mpu_all*)imu.buffer();

    struct esp32_mpu_all sensors;
    sensors.accX = sensors_raw->accX;
    sensors.accY = sensors_raw->accY;
    sensors.accZ = sensors_raw->accZ;

    sensors.gyroX = sensors_raw->gyroX - offset_gyro[0];
    sensors.gyroY = sensors_raw->gyroY - offset_gyro[1];
    sensors.gyroZ = sensors_raw->gyroZ - offset_gyro[2];

    sensors.temp = sensors_raw->temp;

    // Get sensors values in SPI buffer while calcul
    imu.get_all_async();

    // Correct the direction
    sensors.gyroX *= -1;
    sensors.gyroY *= -1;
    sensors.gyroZ *= -1;

    sensors.accX *= -1;

    float acc_x = sensors.accX * _acc_sens;
    float acc_y = sensors.accY * _acc_sens;
    float acc_z = sensors.accZ * _acc_sens;

    float gyro_x = sensors.gyroX * _gyro_sens;
    float gyro_y = sensors.gyroY * _gyro_sens;
    float gyro_z = sensors.gyroZ * _gyro_sens;

    gyro_x = (gyro_x + prev_gyro[0]) * 0.5;
    gyro_y = (gyro_y + prev_gyro[1]) * 0.5;
    gyro_z = (gyro_z + prev_gyro[2]) * 0.5;

    prev_gyro[0] = gyro_x;
    prev_gyro[1] = gyro_y;
    prev_gyro[2] = gyro_z;

    //float temp = (sensors.temp / 321.0 + 21) * 10;
/*
    ets_printf("gyroX:%d gyroY:%d gyroZ:%d \n", (int)gyro_x, (int)gyro_y, (int)gyro_z);
*/
    int throttle_ch = channel_[0];
    int pitch_ch    = channel_[2];
    int roll_ch     = channel_[1];
    int yaw_ch      = channel_[3];
    int aux_1       = channel_[4];
/*
    ets_printf("ch1:%d ch2:%d ch3:%d ch4:%d ch5:%d \n", throttle_ch, pitch_ch, roll_ch, yaw_ch, aux_1);
*/
    if(pitch_ch > 1510)     pitch_ch  -= 1510;
    else if(pitch_ch < 1490)pitch_ch  -= 1490;
    else pitch_ch = 0;

    if(roll_ch > 1510)      roll_ch   -= 1510;
    else if(roll_ch < 1490) roll_ch   -= 1490;
    else roll_ch = 0;

    if(yaw_ch > 1510)       yaw_ch    -= 1510;
    else if(yaw_ch < 1490)  yaw_ch    -= 1490;
    else yaw_ch = 0;


    if(pitch_ch < -500) pitch_ch  = -500;
    if(roll_ch  < -500) roll_ch   = -500;
    if(yaw_ch   < -500) yaw_ch    = -500;

    if(pitch_ch > 500) pitch_ch = 500;
    if(roll_ch  > 500) roll_ch  = 500;
    if(yaw_ch   > 500) yaw_ch   = 500;

/*
    ets_printf("ch1:%d ch2:%d ch3:%d ch4:%d ch5:%d \n", (int)throttle_ch, (int)pitch_ch, (int)roll_ch, (int)yaw_ch, (int)aux_1);
*/

    float rate_est_x, rate_est_y;
    float angle_est_x, angle_est_y;

    kalman_x.update(&rate_est_x, &angle_est_x, gyro_x, acc_y);
    kalman_y.update(&rate_est_y, &angle_est_y, gyro_y, acc_x);
/*
    ets_printf("KangleX:%d KangleY:%d \n", (int)angle_est_x, (int)angle_est_y);
*/
    float Pitch = pid_pitch.calcul(pitch_ch, gyro_y);
    float Roll  = pid_roll.calcul(roll_ch, gyro_x);
    float Yaw   = pid_yaw.calcul(yaw_ch, gyro_z);
/*
    ets_printf("pitch:%d roll:%d, yaw:%d \n", (int)Pitch , (int)Roll, (int)Yaw);
*/

    throttle_ch -= 1000;
    if(ESC_MODE >= DSHOT150) throttle_ch *= 2;

    if(throttle_ch < 0) throttle_ch = 0;
    if(throttle_ch > 1500) throttle_ch = 1500;

/*
    ets_printf("%d \n", throttle_ch);
*/
    output_motor_1 = throttle_ch - Pitch - Roll + Yaw;
		output_motor_2 = throttle_ch - Pitch + Roll - Yaw;
		output_motor_3 = throttle_ch + Pitch + Roll + Yaw;
		output_motor_4 = throttle_ch + Pitch - Roll - Yaw;
/*
    ets_printf("1:%d 2:%d 3:%d 4:%d \n", output_motor_1, output_motor_2, output_motor_3, output_motor_4);
*/
    if(aux_1 > 1500) {

      if(output_motor_1 > 1500) output_motor_1 = 1500;
      else if(output_motor_1 < 25) output_motor_1 = 25;

      if(output_motor_2 > 1500) output_motor_2 = 1500;
      else if(output_motor_2 < 25) output_motor_2 = 25;

      if(output_motor_3 > 1500) output_motor_3 = 1500;
      else if(output_motor_3 < 25) output_motor_3 = 25;

      if(output_motor_4 > 1500) output_motor_4 = 1500;
      else if(output_motor_4 < 25) output_motor_4 = 25;
/*
      ets_printf("out1:%d \n", output_motor_1);
*/
      // dshot (+48)
      motor_1.set(output_motor_1 + 48);
      motor_2.set(output_motor_2 + 48);
      motor_3.set(output_motor_3 + 48);
      motor_4.set(output_motor_4 + 48);
    }
    else {

      pid_pitch.reset_i_sum();
      pid_roll.reset_i_sum();
      pid_yaw.reset_i_sum();

      motor_1.set(0);
      motor_2.set(0);
      motor_3.set(0);
      motor_4.set(0);
    }

    ets_printf("%d \n", throttle_ch);

    motor_1.write();
    motor_2.write();
    motor_3.write();
    motor_4.write();

    // ets_printf("t:%d us \n", Timer.counter_l());

  }

}
