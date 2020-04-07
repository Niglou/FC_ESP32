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
  _spi->phase( SPI_ADDR | SPI_MOSI );
  _spi->addr_len(7);
  _spi->mosi_len(7);
  _spi->miso_len(7);
  _spi->clk_sys(0);
  _spi->pre_div(1);
  _spi->clkcnt(3);
  _spi->clk_edge_idle(LOW);
  _spi->addr_h(0);
  _spi->clk_miso_delay(2, 0);
  _spi->clear_all_buffer();
}

void MAX7456::turnOff() const {
  WRegister(VM0,  0x01);
}

void MAX7456::init() const {
  WRegister(VM0,  0x6C);
  WRegister(OSDM, 0x00); // Insertion Mux
  WRegister(VOS,  0b11111); // Vertical Offset
}

int MAX7456::check() const {
  return RRegister(0x80);
}

char MAX7456::stat() const {
  return RRegister(R_STAT); // Status register
}

void MAX7456::print(char x, char y, char *value, char length) {
  unsigned int addr = 30*y+x;
  char addrH = addr >> 8;
  char addrL = addr;

  // 31 character max
  length &= 0x1F;

  // Use CMD, ADDR and MOSI phases
  _spi->phase( SPI_CMD | SPI_ADDR | SPI_MOSI );

  // Use INCREMENT MODE
  _spi->cmd_len(15);
  _spi->cmd( (DMM << 8) | 0x01 );

  // Set start ADDR DISPLAY
  _spi->addr_len(31);
  _spi->addr_h( (DMAH << 24) | (addrH << 16) | (DMAL << 8) | addrL );

  // Number of bits
  _spi->mosi_len( 16*length -1);

  // If one character
  if( length == 1 ) {
    _spi->buffer(0, (DMDI << 8) | value[0]);
  }
  // If number of characters impair
  else if( length%2 ) {
    int len = length / 2;
    for(int i=0; i<len; i++) {
      int val = i * 2;
      _spi->buffer(i, (DMDI << 24) | (value[val]<<16) | (DMDI << 8) | value[val+1]);
    }
    _spi->buffer(len, (DMDI << 24) | (value[length-1]<<16) | (DMDI << 8) | 0xFF);
  }
  // If number of characters pair
  else {
    int len = length / 2;
    for(int i=0; i<len; i++) {
      int val = i * 2;
      _spi->buffer(i, (DMDI << 24) | (value[val]<<16) | (DMDI << 8) | value[val+1]);
    }
    _spi->buffer(len, (DMDI << 8) | 0xFF);
  }

}

void MAX7456::WRegister(unsigned char addr, unsigned char data) const {
  _spi->phase( SPI_ADDR | SPI_MOSI );
  _spi->addr_h(addr << 24);
  _spi->buffer(0, data);
  _spi->mosi_len(7);
  _spi->transfer();
  while(_spi->transfer_status());
}

unsigned char MAX7456::RRegister(unsigned char addr) const {
  _spi->phase( SPI_ADDR | SPI_MISO );
  _spi->addr_h( ( 0x80 | addr ) << 24);
  _spi->miso_len(7);
  _spi->transfer();
  while(_spi->transfer_status());
  return (_spi->buffer(0));
}
