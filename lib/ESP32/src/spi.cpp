#include "ESP32/include/spi.h"

SPIPeriph::SPIPeriph(spi_periph_t _spi) {
  if(_spi == SPI0_PERIPH) spi = &SPI0;
  else if(_spi == SPI1_PERIPH) spi = &SPI1;
  else if(_spi == SPI2_PERIPH) spi = &SPI2;
  else if(_spi == SPI3_PERIPH) spi = &SPI3;
  else spi = &SPI2;
}
void SPIPeriph::mode(spi_mode_t mode) const { (*spi).slave.slave_mode = mode; }
void SPIPeriph::bit_order(spi_bit_order_t write, spi_bit_order_t read ) const {
    (*spi).ctrl.wr_bit_order = write;
    (*spi).ctrl.rd_bit_order = read;
}
void SPIPeriph::byte_order(spi_byte_order_t write, spi_byte_order_t read ) const {
    (*spi).user.wr_byte_order = write;
    (*spi).user.rd_byte_order = read;
}
void SPIPeriph::phase(spi_bool_t cmd, spi_bool_t addr, spi_bool_t dummy, spi_bool_t mosi, spi_bool_t miso) const {
    (*spi).user.usr_command = cmd;
    (*spi).user.usr_dummy = dummy;
    (*spi).user.usr_addr = addr;
    (*spi).user.usr_mosi = mosi;
    (*spi).user.usr_miso = miso;
}
void SPIPeriph::keep_cs(spi_bool_t value) const {
  (*spi).pin.cs_keep_active = value;
}
void SPIPeriph::cmd(unsigned int cmd) const { (*spi).user2.usr_command_value = cmd; }
void SPIPeriph::addr(unsigned int addr) const { (*spi).addr = addr; }
void SPIPeriph::cmd_len(unsigned int len) const { (*spi).user2.usr_command_bitlen = len; }
void SPIPeriph::dummy_len(unsigned int len) const { (*spi).user1.usr_dummy_cyclelen = len; }
void SPIPeriph::addr_len(unsigned int len) const { (*spi).user1.usr_addr_bitlen = len; }
void SPIPeriph::mosi_len(unsigned int len) const { (*spi).mosi_dlen.usr_mosi_dbitlen = len; }
void SPIPeriph::miso_len(unsigned int len) const { (*spi).miso_dlen.usr_miso_dbitlen = len; }
void SPIPeriph::read_mode(spi_read_t mode) const {
  (*spi).ctrl.reg &= 0x6202000;
  switch (mode) {
    case SPI_READ_SLOW:
      (*spi).ctrl.fastrd_mode = 0; break;
    case SPI_READ_FAST:
      break;
    case SPI_READ_QIO:
      (*spi).ctrl.fread_qio = 1;
      break;
    case SPI_READ_DIO:
      (*spi).ctrl.fread_dio = 1;
      break;
    case SPI_READ_QUAD:
      (*spi).ctrl.fread_quad = 1;
      break;
    case SPI_READ_DUAL:
      (*spi).ctrl.fread_dual = 1;
      break;
  }
}
void SPIPeriph::full_duplex(spi_com_t full_duplex) const { (*spi).user.doutdin = full_duplex; }
void SPIPeriph::clk_sys(spi_bool_t sys) const { (*spi).clock.clk_equ_sysclk = sys; }
void SPIPeriph::pre_div(unsigned int div) const { (*spi).clock.clkdiv_pre = div; }
void SPIPeriph::clkcnt(unsigned int cnt) const {
  if(mode()) {
    (*spi).clock.clkcnt_n = cnt;
    (*spi).clock.clkcnt_l = 0;
    (*spi).clock.clkcnt_h = 0;
  }
  else {
    (*spi).clock.clkcnt_n = cnt;
    (*spi).clock.clkcnt_l = cnt;
    (*spi).clock.clkcnt_h = ((cnt+1)/2-1);
  }
}
void SPIPeriph::clkcnt(unsigned int cnt, unsigned int cnt_l, unsigned int cnt_h) const {
  if(mode()) {
    (*spi).clock.clkcnt_n = cnt;
    (*spi).clock.clkcnt_l = 0;
    (*spi).clock.clkcnt_h = 0;
  }
  else {
    (*spi).clock.clkcnt_n = cnt;
    (*spi).clock.clkcnt_l = cnt_l;
    (*spi).clock.clkcnt_h = cnt_h;
  }
}
void SPIPeriph::clk_edge_idle(spi_edge_t edge) const { (*spi).pin.ck_idle_edge = edge; }
void SPIPeriph::clk_miso_delay(unsigned int mode, unsigned int num) const {
  (*spi).ctrl2.miso_delay_mode = mode;
  (*spi).ctrl2.miso_delay_num = num;
}
void SPIPeriph::clk_mosi_delay(unsigned int mode, unsigned int num) const {
  (*spi).ctrl2.mosi_delay_mode = mode;
  (*spi).ctrl2.mosi_delay_num = num;
}
void SPIPeriph::cs_setup(bool en, unsigned int value) const {
  (*spi).user.cs_setup = en;
  (*spi).ctrl2.setup_time = value;
}
void SPIPeriph::cs_hold(bool en, unsigned int value) const {
  (*spi).user.cs_hold = en;
  (*spi).ctrl2.hold_time = value;
}
void SPIPeriph::buf_highpart(spi_buf_t highpart) const {
  if(highpart == MOSI) {
    (*spi).user.usr_mosi_highpart = 1;
    (*spi).user.usr_miso_highpart = 0;
  }
  else if(highpart == MISO) {
    (*spi).user.usr_mosi_highpart = 0;
    (*spi).user.usr_miso_highpart = 1;
  }
  else {
    (*spi).user.usr_mosi_highpart = 0;
    (*spi).user.usr_miso_highpart = 0;
  }
}
void SPIPeriph::buffer(unsigned int index, unsigned int data) const { (*spi).data_buf[(index & 0xF)] = data; }
void SPIPeriph::clear_all_buffer() const { for(int i = 0; i < 16; i++) (*spi).data_buf[i] = 0; }
void SPIPeriph::transfer() const { (*spi).cmd.usr = 1; }


unsigned int SPIPeriph::mode() const { return (*spi).slave.slave_mode; }
unsigned int SPIPeriph::addr() const { return (*spi).addr; }
unsigned int* SPIPeriph::buffer() const { return (unsigned int*)&((*spi).data_buf); }
unsigned int SPIPeriph::buffer(unsigned int read) const { return (*spi).data_buf[(read & 0xF)]; }
unsigned int SPIPeriph::transfer_st() const { return (*spi).cmd.usr; }
