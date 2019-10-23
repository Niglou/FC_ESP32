#include "ESP32/include/spi_flash.h"
#include "ESP32/registers/struct/iomux_struct.h"
#include "ESP32/registers/struct/gpio_struct.h"

intFlashClass::intFlashClass(SPIPeriph *spi) {
  _spi = spi;
}
void intFlashClass::spi_bus_init() const {
  /*
  IOMUX.GPIO6.reg = 0x1A00;
  IOMUX.GPIO7.reg = 0x1A00;
  IOMUX.GPIO8.reg = 0x1A00;
  IOMUX.GPIO9.reg = 0x1A00;
  IOMUX.GPIO10.reg = 0x1A00;
  IOMUX.GPIO11.reg = 0x1A00;
  */


  IOMUX.GPIO6.reg = 0x2A00;
  //IOMUX.GPIO7.reg = 0x2A00;
  IOMUX.GPIO8.reg = 0x2A00;
  //IOMUX.GPIO11.reg = 0x2A00;
  IOMUX.GPIO16.reg = 0x2A00;
  IOMUX.GPIO17.reg = 0x2A00;

  GPIO.func_out_sel_cfg[6].func_sel = 0;
  //GPIO.func_out_sel_cfg[7].func_sel = 4;
  GPIO.func_out_sel_cfg[8].func_sel = 2;
  //GPIO.func_out_sel_cfg[11].func_sel = 3;
  GPIO.func_out_sel_cfg[16].func_sel = 5;
  GPIO.func_out_sel_cfg[17].func_sel = 1;

}
void intFlashClass::spi_init() const {
  _spi->mode(MASTER);
  //_spi->clk_sys(SPI_EN);
  _spi->clk_sys(SPI_DIS);
  _spi->pre_div(1);
  _spi->clkcnt(1);
  _spi->clear_all_buffer();
}
unsigned int intFlashClass::id() const {
  _spi->read_mode(SPI_READ_FAST);
  _spi->phase(SPI_EN, SPI_DIS, SPI_DIS, SPI_DIS, SPI_EN);
  _spi->cmd(0x9F);
  _spi->cmd_len(7);
  _spi->miso_len(23);
  _spi->transfer();
  while(_spi->transfer_st());

  unsigned char *raw_id = (unsigned char*)_spi->buffer();
  return (raw_id[0] << 16) | (raw_id[1] << 8) | raw_id[2];
}
void intFlashClass::write(unsigned int address, unsigned char data) const {
  // Write enable
  _spi->read_mode(SPI_READ_FAST);
  _spi->phase(SPI_EN, SPI_DIS, SPI_DIS, SPI_DIS, SPI_DIS);
  _spi->cmd(0x06);
  _spi->cmd_len(7);
  _spi->transfer();
  while(_spi->transfer_st());

  // Page program
  _spi->phase(SPI_EN, SPI_EN, SPI_DIS, SPI_EN, SPI_DIS);
  _spi->cmd(0x02);
  _spi->cmd_len(7);
  _spi->addr(address << 8);
  _spi->addr_len(23);
  _spi->mosi_len(7);
  _spi->buffer(0, data);
  _spi->transfer();
  while(_spi->transfer_st());
}
unsigned int* intFlashClass::read(unsigned int address) const {
  _spi->read_mode(SPI_READ_DIO);
  _spi->phase(SPI_EN, SPI_EN, SPI_DIS, SPI_DIS, SPI_EN);
  _spi->cmd(0xBB);
  _spi->cmd_len(7);
  _spi->addr(address << 8);
  _spi->addr_len(31);
  _spi->miso_len(7);
  _spi->transfer();
  while(_spi->transfer_st());
  return _spi->buffer();
}
