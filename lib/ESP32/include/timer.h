#ifndef H_NONOS_TIMER
#define H_NONOS_TIMER

#include "ESP32/registers/struct/timer_struct.h"

typedef enum { GROUP0, GROUP1 } timer_group_t;
typedef enum { TIMER0, TIMER1 } timer_num_t;
typedef enum { DECREASE, INCREASE } timer_dir_t;

class TIMPeriph {
  public:
    TIMPeriph();
    TIMPeriph(timer_group_t group, timer_num_t timer);
    void attach(timer_group_t group, timer_num_t timer);
    void enable() const;
    void disable() const;
    void alarm_en(bool value) const;
    void divider(unsigned int div) const;
    void dir(timer_dir_t dir) const;
    void alarm(unsigned long long value) const;
    void alarm_l(unsigned int value) const;
    void alarm_h(unsigned int value) const;
    void counter(unsigned long long value) const;
    void counter_l(unsigned int value) const;
    void counter_h(unsigned int value) const;

    unsigned long long alarm() const;
    unsigned int alarm_l() const;
    unsigned int alarm_h() const;
    unsigned long long counter() const;
    unsigned int counter_l() const;
    unsigned int counter_h() const;


  private:
    timg_dev_t *timg;
    timer_num_t t_num;

};

#endif /* H_NONOS_TIMER */
