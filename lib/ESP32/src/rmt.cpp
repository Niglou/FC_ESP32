#include "ESP32/registers/dport_reg.h"
#include "ESP32/registers/rmt_reg.h"

#include "ESP32/include/rmt.h"

RMTPeriph::RMTPeriph() {}

RMTPeriph::RMTPeriph(rmt_ch_t _ch) {
  //  Enable RMT clock
  *(volatile uint32_t*)DPORT_PERIP_CLK_EN_REG |= DPORT_RMT_CLK_EN;

  //  Disable RMT reset
  *(volatile uint32_t*)DPORT_PERIP_RST_EN_REG &= ~DPORT_RMT_RST;

  RMT.apb_conf.mem_access_en = 1;
  ch = _ch;
  for(int i = 0; i < 64; i++) RMTMEM.ch[ch].data[i].reg = 0;
}

void RMTPeriph::attach(rmt_ch_t _ch) {
  //  Enable RMT clock
  *(volatile uint32_t*)DPORT_PERIP_CLK_EN_REG |= DPORT_RMT_CLK_EN;

  //  Disable RMT reset
  *(volatile uint32_t*)DPORT_PERIP_RST_EN_REG &= ~DPORT_RMT_RST;

  RMT.apb_conf.mem_access_en = 1;
  ch = _ch;
  for(int i = 0; i < 64; i++) RMTMEM.ch[ch].data[i].reg = 0;

}

void RMTPeriph::mode(rmt_mode_t mode) const {
  RMT.conf_ch[ch].conf1.mem_owner = mode;
}

void RMTPeriph::clock(rmt_clk_t clk) const {
  RMT.conf_ch[ch].conf1.ref_always_on = clk;
}

void RMTPeriph::divider(unsigned int div) const {
  RMT.conf_ch[ch].conf0.div_cnt = div;
}

void RMTPeriph::conti_mode(rmt_bool_t mode) const {
  RMT.conf_ch[ch].conf1.tx_conti_mode = mode;
}

void RMTPeriph::carrier(rmt_bool_t state) const {
  RMT.conf_ch[ch].conf0.carrier_en = state;
}

void RMTPeriph::idle_en(rmt_bool_t en) const {
  RMT.conf_ch[ch].conf1.idle_out_en = en;
}

void RMTPeriph::idle_lvl(rmt_bool_t high) const {
  RMT.conf_ch[ch].conf1.idle_out_lv = high;
}

void RMTPeriph::data(unsigned int sel, unsigned int data) const {
  RMTMEM.ch[ch].data[sel].reg = data;
}

void RMTPeriph::rst_pos_trans() const {
  RMT.conf_ch[ch].conf1.mem_rd_rst = 1;
  RMT.conf_ch[ch].conf1.mem_rd_rst = 0;
}

void RMTPeriph::rst_pos_receiv() const {
  RMT.conf_ch[ch].conf1.mem_wr_rst = 1;
  RMT.conf_ch[ch].conf1.mem_wr_rst = 0;
}

void RMTPeriph::start() const {
  RMT.conf_ch[ch].conf1.tx_start = 1;
}
