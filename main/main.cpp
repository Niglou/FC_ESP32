#include <ESP32/include/init.h>
#include <ESP32/include/rom/ets_sys.h>

#include <ESP32/registers/dport_reg.h>

/* Internal periph */
#include <ESP32/include/intr.h>
#include <ESP32/include/timer.h>
#include <ESP32/include/spi.h>
#include <ESP32/include/rmt.h>
#include <ESP32/include/gpio.h>
#include <ESP32/include/i2c.h>

/* External periph */
#include "drivers/imu/mpu9250.h"
#include "drivers/esc/esc.h"
#include "drivers/led/ws2812b.h"

#include "gpio/gpio.h"

#include "config.h"

#include <ESP32/registers/struct/gpio_struct.h>

#include <math.h>
#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f


#define reg(r) *(volatile unsigned int*)(r)

extern "C" {

	void main_cpu0();
	void main_cpu1();

	extern volatile unsigned int channel_1;

}


void main_cpu0() {

	init_esp32();
	ets_install_uart_printf();
	ets_update_cpu_frequency_rom(80);

	/* ********* SETUP *********** */

	TIMPeriph Timer(GROUP0, TIMER0);

	SPIPeriph HSPI(SPI2_PERIPH);
	SPIPeriph VSPI(SPI3_PERIPH);

  RMTPeriph RMT_0(CHANNEL_0);
  RMTPeriph RMT_1(CHANNEL_1);
  RMTPeriph RMT_2(CHANNEL_2);
  RMTPeriph RMT_3(CHANNEL_3);

	RMTPeriph RMT_4(CHANNEL_4);


	MPU9250 imu(&HSPI);

	ESC motor_1(&RMT_0);
	ESC motor_2(&RMT_1);
	ESC motor_3(&RMT_2);
	ESC motor_4(&RMT_3);

  WS2812B led(&RMT_4);

	Timer.divider(80);
	Timer.enable();

	imu.init_spi();
	motor_1.mode(ESC_MODE);
	motor_2.mode(ESC_MODE);
	motor_3.mode(ESC_MODE);
	motor_4.mode(ESC_MODE);

	/* Interrupt matrix */
	reg(DPORT_PRO_GPIO_INTERRUPT_NMI_MAP_REG) = 26; // gpio -> level 5(26)

	init_gpio();

  IOMUX.GPIO2.reg = 0;
	IOMUX.GPIO2.func_drv = 2;
	GPIO.func_out_sel_cfg[2].reg = 91;

/*
	if(imu.check() != WHOAMI) {
		ets_printf("[ERROR] mpu not found");
		while(1);
	}
*/
	//intr_enable( 1<<26 );

	reg(DPORT_PERIP_RST_EN_REG) |= (1<<7);
	reg(DPORT_PERIP_CLK_EN_REG) |= (1<<7);
	reg(DPORT_PERIP_RST_EN_REG) &= ~(1<<7);

	ets_delay_us(2000000);

	if(imu.check())
		ets_printf("MPU9250 : detected ! \n");
	else
		ets_printf("MPU9250 : not found ! \n");

  int angle_x = 0;
  int angle_y = 0;
  int angle_z = 0;

	/* ************ LOOP ************ */
  int test_time = 0;
	while(true) {

		// 2500 (400Hz)
		while( Timer.counter_l() < 100000 );
		Timer.counter_l(0);

/*
		imu.get_acc();
		uint16_t test = reg(0x3FF64080);

		ets_printf("%d\n", tmp);
*/
/*
		motor_1.set(1000);
		motor_1.write();

*/
/*
		RMT_4.rst_pos_trans();
		RMT_4.start();

*/

		int gaz = (channel_1-1000) * 2;
		if(gaz > 20) gaz += 48;
		else gaz = 48;

		if(test_time == 7000) {
			motor_1.set(3,1);
			motor_2.set(3,1);
			motor_3.set(3,1);
			motor_4.set(3,1);

		}
		else {
			test_time++;
			motor_1.set(0);
			motor_2.set(0);
			motor_3.set(0);
			motor_4.set(0);
		}

		motor_1.write();
		motor_2.write();
		motor_3.write();
		motor_4.write();


		imu.get_all();

		short *sensors;
		sensors = HSPI.buffer();

		float acc_x = sensors[1] / ACC_SENS_2G;
		float acc_y = sensors[0] / ACC_SENS_2G;
		float acc_z = sensors[3] / ACC_SENS_2G;

    float gyro_x = sensors[5] / GYRO_SENS_250DPS;
    float gyro_y = sensors[4] / GYRO_SENS_250DPS;
    float gyro_z = sensors[7] / GYRO_SENS_250DPS;

		float temp = (sensors[2] / 321.0 + 21) * 10;
/*
    angle_x += gyro_x;
    angle_y += gyro_y;
    angle_z += gyro_z;
*/

    angle_x = atan2(acc_x, acc_z) * RAD_TO_DEG;
    angle_y = atan2(acc_y, acc_z) * RAD_TO_DEG;
    angle_z += gyro_z / 10;

		ets_printf("AngleX : %d° AngleY : %d° AngleZ : %d° Temp : %d°C \n", (int)angle_x, (int)angle_y, (int)angle_z, (int)temp);




	}

}
