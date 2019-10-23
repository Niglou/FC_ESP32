#ifndef H_NONOS_RMT
#define H_NONOS_RMT

#include "ESP32/registers/struct/rmt_struct.h"

typedef enum { CHANNEL_0, CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_5, CHANNEL_6, CHANNEL_7 } rmt_ch_t;
typedef enum { TRANSMITTER, RECEIVER } rmt_mode_t;
typedef enum { REF_TICK, APB_CLK } rmt_clk_t;
typedef enum { RMT_DIS, RMT_EN } rmt_bool_t;

class RMTPeriph {
  public:
    RMTPeriph();
    RMTPeriph(rmt_ch_t _ch);
    void attach(rmt_ch_t);
    void mode(rmt_mode_t mode) const;
    void clock(rmt_clk_t clk) const;
    void divider(unsigned int div) const;
    void conti_mode(rmt_bool_t mode) const;
    void carrier(rmt_bool_t state) const;
    void idle_en(rmt_bool_t en) const;
    void idle_lvl(rmt_bool_t high) const;
    void data(unsigned int sel, unsigned int data) const;
    void rst_pos_trans() const;
    void rst_pos_receiv() const;
    void start() const;

  private:
    rmt_ch_t ch;

};

#endif
