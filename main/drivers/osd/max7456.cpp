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

void MAX7456::init() const
{
  WRegister(VM0,  0x6C);
  WRegister(OSDM, 0x00); // Insertion Mux
  WRegister(VOS,  0b11111); // Vertical Offset

  unsigned int addr = 30*4+13;
  char addrH = addr >> 8;
  char addrL = addr;

  WRegister(DMM, 0x0);
  WRegister(DMAH, addrH);
  WRegister(DMAL, addrL);

  WRegister(DMDI, 1);

}

int MAX7456::check() const {
  return RRegister(0x80);
}

char MAX7456::stat() const {
  return RRegister(R_STAT); // Status register
}

void MAX7456::print(unsigned char x, unsigned char y, char *value, unsigned char length) const {
  unsigned int addr = 30*y+x;
  char addrH = addr >> 8;
  char addrL = addr;

  // 31 character max
  length &= 0x1F;

  // Wait if SPI is already use
  while(_spi->transfer_status());

  // Use ADDR and MOSI phases
  _spi->phase( SPI_ADDR | SPI_MOSI );

  // Set INCREMENT MODE
  // Set start ADDR DISPLAY
  _spi->addr_len(47);
  _spi->addr_l( (DMM << 24) | (0x01 << 16) );
  _spi->addr_h( (DMAH << 24) | (addrH << 16) | (DMAL << 8) | addrL );

  // Number of bits (+1 byte for end character)
  _spi->mosi_len( 16*(length+1) -1);

  // If one character
  if( length == 1 ) {
    _spi->buffer(0, (0xFF << 24) | (DMDI << 16) | (value[0] << 8) | DMDI );
  }
  // If number of characters impair
  else if( length%2 ) {
    int len = length / 2;
    for(int i=0; i<len; i++) {
      int val = i * 2;
      _spi->buffer(i, (value[val+1] << 24) | (DMDI<<16) | (value[val] << 8) | DMDI);
    }
    _spi->buffer(len, (0xFF << 24) | (DMDI<<16) | (value[length-1] << 8) | DMDI);
  }
  // If number of characters pair
  else {
    int len = length / 2;
    for(int i=0; i<len; i++) {
      int val = i * 2;
      _spi->buffer(i, (value[val+1] << 24) | (DMDI<<16) | (value[val] << 8) | DMDI);
    }
    _spi->buffer(len, (0xFF << 8) | DMDI);
  }

  // Start SPI transmission
  _spi->transfer();

}

void MAX7456::WRegister(unsigned char addr, unsigned char data) const {
  _spi->phase( SPI_ADDR | SPI_MOSI );
<<<<<<< HEAD
  _spi->addr_h(addr << 24);
  _spi->buffer(0, data);
=======
  _spi->addr_len(7);
  _spi->addr_h(addr << 24);
>>>>>>> osd
  _spi->mosi_len(7);
  _spi->buffer(0, data);
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
