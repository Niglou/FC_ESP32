

#include <registers/struct/gpio_struct.h>
#include <registers/gpio_sig_map.h>


#include "config.h"
#include "gpio.h"
#include "rx/pwm.h"


unsigned int channel_gpio_[] = CHANNEL_GPIO;

void init_gpio() {

    init_spi_gpio();

    init_input_gpio();

    /* SET RMT GPIO OUTPUT */
    GPIO.enable = 1<<MOTOR_1_GPIO | 1<<MOTOR_2_GPIO | 1<<MOTOR_3_GPIO | 1<<MOTOR_4_GPIO;

    /* OUTPUT GPIO conf */
    /*
        strenght : 3 (0-3)
        input : disable
        pull-up : disable
        pull-down : disable
    */
    IOMUX_CONF(MOTOR_1_GPIO).reg = 0x2C00;
    IOMUX_CONF(MOTOR_2_GPIO).reg = 0x2C00;
    IOMUX_CONF(MOTOR_3_GPIO).reg = 0x2C00;
    IOMUX_CONF(MOTOR_4_GPIO).reg = 0x2C00;

    /* Attach RMT to GPIO */
    GPIO.func_out_sel_cfg[MOTOR_1_GPIO].reg = 0;
    GPIO.func_out_sel_cfg[MOTOR_2_GPIO].reg = 0;
    GPIO.func_out_sel_cfg[MOTOR_3_GPIO].reg = 0;
    GPIO.func_out_sel_cfg[MOTOR_4_GPIO].reg = 0;

    GPIO.func_out_sel_cfg[MOTOR_1_GPIO].func_sel = RMT_SIG_OUT0_IDX;
    GPIO.func_out_sel_cfg[MOTOR_2_GPIO].func_sel = RMT_SIG_OUT1_IDX;
    GPIO.func_out_sel_cfg[MOTOR_3_GPIO].func_sel = RMT_SIG_OUT2_IDX;
    GPIO.func_out_sel_cfg[MOTOR_4_GPIO].func_sel = RMT_SIG_OUT3_IDX;

}

void init_i2c_gpio() {

  GPIO.enable = (1<<25) | (1<<26);
	GPIO.out = (1<<25) | (1<<26);

	/* open drain */
	GPIO.pin[25].pad_driver = 1;
	GPIO.pin[26].pad_driver = 1;

    /*
        function gpio
        drive strenght
        enable input
        enable pull-up
    */
	IOMUX.GPIO25.reg = 0;
	IOMUX.GPIO25.mcu_sel = 2;
	IOMUX.GPIO25.func_drv = 2;
	IOMUX.GPIO25.func_ie = 1;
	IOMUX.GPIO25.func_wpu = 1;

	IOMUX.GPIO26.reg = 0;
	IOMUX.GPIO26.mcu_sel = 2;
	IOMUX.GPIO26.func_drv = 2;
	IOMUX.GPIO26.func_ie = 1;
	IOMUX.GPIO26.func_wpu = 1;

    /*
        i2c0 signal SCL:29 SDA:30
        i2c1 signal SCL:95 SDA:96
    */
	/* output */
	GPIO.func_out_sel_cfg[25].reg = 0;
	GPIO.func_out_sel_cfg[25].func_sel = 29;

	GPIO.func_out_sel_cfg[26].reg = 0;
	GPIO.func_out_sel_cfg[26].func_sel = 30;
	/* input */
	GPIO.func_in_sel_cfg[29].func_sel = 25;
	GPIO.func_in_sel_cfg[29].sig_in_sel = 1;

	GPIO.func_in_sel_cfg[30].func_sel = 26;
	GPIO.func_in_sel_cfg[30].sig_in_sel = 1;

}

void init_spi_gpio() {

    /*
      HSPI
    */

    IOMUX.GPIO12.reg = 0x1A00;

    IOMUX.GPIO13.reg = 0x1800;

    IOMUX.GPIO14.reg = 0x1800;

    IOMUX.GPIO15.reg = 0x1800;

    GPIO.func_in_sel_cfg[9].sig_in_sel = 0;

    /*
      VSPI
    */

    IOMUX.GPIO19.reg = 0x1A00;

    IOMUX.GPIO18.reg = 0x1800;

    IOMUX.GPIO23.reg = 0x1800;

    IOMUX.GPIO10.reg =  0x2800;

    GPIO.func_in_sel_cfg[64].sig_in_sel = 0;

    GPIO.func_out_sel_cfg[10].func_sel = 68;


/*
    IOMUX.GPIO12.reg = 0;
    IOMUX.GPIO12.mcu_sel = 2;
    IOMUX.GPIO12.func_drv = 2;

    IOMUX.GPIO13.reg = 0;
    IOMUX.GPIO13.mcu_sel = 2;
    IOMUX.GPIO13.func_drv = 2;

    IOMUX.GPIO14.reg = 0;
    IOMUX.GPIO14.mcu_sel = 2;
    IOMUX.GPIO14.func_drv = 2;
    IOMUX.GPIO14.func_ie = 1;

    IOMUX.GPIO27.reg = 0;
    IOMUX.GPIO27.mcu_sel = 2;
    IOMUX.GPIO27.mcu_drv = 2;


    GPIO.func_out_sel_cfg[12].reg = 0;
    GPIO.func_out_sel_cfg[12].func_sel = 10;

    GPIO.func_out_sel_cfg[13].reg = 0;
    GPIO.func_out_sel_cfg[13].func_sel = 8;

    GPIO.func_out_sel_cfg[27].reg = 0;
    GPIO.func_out_sel_cfg[27].func_sel = 11;

    GPIO.func_in_sel_cfg[9].func_sel = 14;
    GPIO.func_in_sel_cfg[9].sig_in_sel = 1;
*/

}

void init_input_gpio() {

    /* INPUT PWM GPIO conf */
    /*
        function : GPIO
        input : enable
        pull-up : disable
        pull-down : enable if possible (remove parasites)
    */
    for(int i=0; i<NUM_CHANNEL_GPIO; i++) {
      // IOMUX_CONF(channel_gpio_[i]).reg = 0x2280;
      IOMUX_CONF(channel_gpio_[i]).reg = 0x2280;
    }

    /* Enable interrupt (INPUT PWM) */
    /*
        PRO CPU Interrupt
        Any edge trigger
    */
    for(int i=0; i<NUM_CHANNEL_GPIO; i++) {
      GPIO.pin[channel_gpio_[i]].reg = 0x10180;
    }



}
