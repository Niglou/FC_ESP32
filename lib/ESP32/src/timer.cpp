#include "ESP32/include/timer.h"

TIMPeriph::TIMPeriph() {}

TIMPeriph::TIMPeriph(timer_group_t group, timer_num_t timer) {
  if(group == GROUP0) timg = &TIMERG0;
  else if(group == GROUP1) timg = &TIMERG1;
  t_num = timer;
}

void TIMPeriph::attach(timer_group_t group, timer_num_t timer) {
  if(group == GROUP0) timg = &TIMERG0;
  else if(group == GROUP1) timg = &TIMERG1;
  t_num = timer;
}

void TIMPeriph::enable() const {
  timg->hw_timer[t_num].config.enable = 1;
}

void TIMPeriph::disable() const {
  timg->hw_timer[t_num].config.enable = 0;
}

void TIMPeriph::alarm_en(bool value) const {
  timg->hw_timer[t_num].config.alarm_en = value;
}

void TIMPeriph::divider(unsigned int div) const {
  timg->hw_timer[t_num].config.divider = div;
}

void TIMPeriph::dir(timer_dir_t dir) const {
  timg->hw_timer[t_num].config.increase = dir;
}

void TIMPeriph::alarm(unsigned long long value) const {
  timg->hw_timer[t_num].alarm_low = value;
  timg->hw_timer[t_num].alarm_high = (value >> 32);
}

void TIMPeriph::alarm_l(unsigned int value) const {
  timg->hw_timer[t_num].alarm_low = value;
}

void TIMPeriph::alarm_h(unsigned int value) const {
  timg->hw_timer[t_num].alarm_high = value;
}

void TIMPeriph::counter(unsigned long long value) const {
    timg->hw_timer[t_num].load_low = value;
    timg->hw_timer[t_num].load_high = (value >> 32);
    timg->hw_timer[t_num].reload = 1;
}

void TIMPeriph::counter_l(unsigned int value) const {
    timg->hw_timer[t_num].load_low = value;
    timg->hw_timer[t_num].reload = 1;
}

void TIMPeriph::counter_h(unsigned int value) const {
    timg->hw_timer[t_num].load_high = value;
    timg->hw_timer[t_num].reload = 1;
}

unsigned long long TIMPeriph::alarm() const {
  unsigned long long low_reg = timg->hw_timer[t_num].alarm_low;
  unsigned long long high_reg = timg->hw_timer[t_num].alarm_low;
  return ( (high_reg << 32) | low_reg );
}

unsigned int TIMPeriph::alarm_l() const {
  return timg->hw_timer[t_num].alarm_low;
}

unsigned int TIMPeriph::alarm_h() const {
  return timg->hw_timer[t_num].alarm_high;
}

unsigned long long TIMPeriph::counter() const {
  timg->hw_timer[t_num].update = 1;
  unsigned long long low_reg = timg->hw_timer[t_num].cnt_low;
  unsigned long long high_reg = timg->hw_timer[t_num].cnt_high;
  return ( (high_reg << 32) | low_reg );
}

unsigned int TIMPeriph::counter_l() const {
  timg->hw_timer[t_num].update = 1;
  unsigned int low_reg = timg->hw_timer[t_num].cnt_low;
  return ( low_reg );
}

unsigned int TIMPeriph::counter_h() const {
  timg->hw_timer[t_num].update = 1;
  unsigned int low_reg = timg->hw_timer[t_num].cnt_high;
  return ( low_reg );
}
