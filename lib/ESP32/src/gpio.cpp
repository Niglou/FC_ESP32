#include "ESP32/registers/gpio_sig_map.h"
#include "ESP32/registers/io_mux_reg.h"

#include "ESP32/include/gpio.h"

void gpio_init() {

    GPIO.enable_w1ts = ( 1 << 2 );
    GPIO.func_out_sel_cfg[2].func_sel = RMT_SIG_OUT0_IDX;

/*
    IOMUX.GPIO13.reg = 0;
    IOMUX.GPIO13.mcu_sel = 2;
    GPIO.func_out_sel_cfg[13].func_sel = HSPICLK_OUT_IDX;

    IOMUX.GPIO12.reg = 0;
    IOMUX.GPIO12.mcu_sel = 2;
    GPIO.func_out_sel_cfg[12].func_sel = HSPID_OUT_IDX;

    IOMUX.GPIO14.reg = 0;
    IOMUX.GPIO14.mcu_sel = 2;
    GPIO.func_out_sel_cfg[14].func_sel = HSPIQ_IN_IDX;

    IOMUX.GPIO27.reg = 0;
    IOMUX.GPIO27.mcu_sel = 2;
    GPIO.func_out_sel_cfg[27].func_sel = HSPICS0_OUT_IDX;

    GPIO.enable_w1ts = ( 1<<13 | 1<<12 | 1<<27 );
*/
/*
    IOMUX.GPIO13.reg = 0;
    IOMUX.GPIO14.reg = 0;
    IOMUX.GPIO15.reg = 0;
    IOMUX.GPIO12.reg = 0;

    IOMUX.GPIO13.mcu_sel = 1; // GPIO13 MOSI
    IOMUX.GPIO14.mcu_sel = 1; // GPIO14 CLK
    IOMUX.GPIO15.mcu_sel = 1; // GPIO15 CS
    IOMUX.GPIO12.mcu_sel = 1; // GPIO12 MISO
    GPIO.enable_w1ts = ( 1<<13 | 1<<14 | 1<<15 );
*/

    IOMUX.GPIO15.reg = 0;
    IOMUX.GPIO14.reg = 0;
    IOMUX.GPIO12.reg = 0;
    IOMUX.GPIO13.reg = 0;

    IOMUX.GPIO13.mcu_sel = 1; // GPIO13 MOSI
    IOMUX.GPIO14.mcu_sel = 1; // GPIO14 CLK
    IOMUX.GPIO15.mcu_sel = 1; // GPIO15 CS
    IOMUX.GPIO12.mcu_sel = 1; // GPIO12 MISO

    /*
    WRITE_PERI_REG (GPIO_ENABLE_REG, (1<<5));
    WRITE_PERI_REG (GPIO_FUNC5_OUT_SEL_CFG_REG, (1<<10)|73);
    WRITE_PERI_REG (PERIPHS_IO_MUX_GPIO5_U, (3<<10)|(1<<8));
    */

}
