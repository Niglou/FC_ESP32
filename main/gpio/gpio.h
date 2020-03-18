#ifndef H_GPIO
#define H_GPIO

#include <registers/struct/iomux_struct.h>

/*
#define IOMUX_CONF2(a) IOMUX.GPIO##a
#define IOMUX_CONF(a) IOMUX_CONF2(a)
*/

#define IOMUX_CONF(a) (*(iomux_pad_t*)(0x3FF49000+esp32_gpioMux[a]))

void init_gpio();

void init_i2c_gpio();
void init_spi_gpio();
void init_input_gpio();

#endif
