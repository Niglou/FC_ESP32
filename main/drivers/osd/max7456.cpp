#include <cstdio>
#include "max7456.h"

MAX7456::MAX7456() {}

MAX7456::MAX7456(SPIPeriph *spi) {
  _spi = spi;
}

void MAX7456::attach(SPIPeriph *spi) {
  _spi = spi;
}

void MAX7456::spi_init() const {
  _spi->mode(MASTER);
  _spi->bit_order(MSB_FIRST, MSB_FIRST);
  _spi->byte_order(SPI_LITTE_ENDIAN, SPI_LITTE_ENDIAN);
  _spi->full_duplex(NORMAL);
  _spi->phase(SPI_DIS, SPI_DIS, SPI_DIS, SPI_EN, SPI_DIS);
  _spi->addr_len(7);
  _spi->mosi_len(7);
  _spi->miso_len(7);
  _spi->clk_sys(SPI_DIS);
  _spi->pre_div(1);
  _spi->clkcnt(3);
  _spi->clk_edge_idle(LOW);
  _spi->addr(0);
  _spi->clk_miso_delay(2, 0);
  _spi->clear_all_buffer();
}

void MAX7456::init() const {
  WRegister(W_VM0,  0x6C);
  WRegister(W_OSDM, 0x00); // Insertion Mux
  WRegister(W_VOS,  0b11111); // Vertical Offset


  unsigned int addr = 30*2+15;
  char addrH = addr >> 8;
  char addrL = addr;

  WRegister(W_DMM,  0x00);
  WRegister(W_DMAH, addrH);
  WRegister(W_DMAL, addrL);

  WRegister(W_DMDI, 0x01);

}

int MAX7456::check() const {
  return RRegister(0x80);
}

char MAX7456::stat() const {
  return RRegister(0xA0);
}

void MAX7456::print(char *value, char x, char y) {
  unsigned int addr = 30*y+x;
  char addrH = addr >> 8;
  char addrL = addr;

  _spi->keep_cs(SPI_EN);

  WRegister(W_DMM, 0x01);
  WRegister(W_DMAH, addrH);
  WRegister(W_DMAL, addrL);

  for (int i = 0; i < 5; i++) {
      WRegister(W_DMDI, value[i]);
  }

  WRegister(W_DMDI, 0xFF);

  _spi->keep_cs(SPI_DIS);


/*
  for(int i=0; i<5; i++) {
    WRegister(W_DMAL, addrL);
    WRegister(W_DMDI, value[i]);
    addrL++;
  }
*/

}

void MAX7456::WRegister(unsigned char addr, unsigned char data) const {
  _spi->phase(SPI_DIS, SPI_EN, SPI_DIS, SPI_EN, SPI_DIS);
  _spi->addr(addr << 24);
  _spi->addr_len(7);
  _spi->buffer(0, data);
  _spi->mosi_len(7);
  _spi->transfer();
  while(_spi->transfer_st());
}

unsigned char MAX7456::RRegister(unsigned char addr) const {
  _spi->phase(SPI_DIS, SPI_EN, SPI_DIS, SPI_DIS, SPI_EN);
  _spi->addr(addr << 24);
  _spi->addr_len(7);
  _spi->miso_len(7);
  _spi->transfer();
  while(_spi->transfer_st());
  return (_spi->buffer(0));
}
