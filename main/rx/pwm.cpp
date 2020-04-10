
#include <registers/struct/gpio_struct.h>

#include "main/config.h"

#include "timer.h"
#include "pwm.h"

extern "C" {
  void ISR_LVL5();
}

extern unsigned int channel_gpio_[];

volatile unsigned int prev_state, prev_state1;

volatile int rx_channel_[NUM_CHANNEL] = {0};
volatile unsigned long long start_channel_[NUM_CHANNEL] = {0};
volatile int failsafe = 0;

TIMPeriph inputTimer;

void init_input_pwm()
{
  inputTimer.attach(GROUP0, TIMER1);
  inputTimer.divider(80);
  //inputTimer.intr_type(LEVEL);
  //inputTimer.intr_enable(1);
  inputTimer.enable();
}

void ISR_LVL5()
{

  unsigned int gpio_in = GPIO.in;
  unsigned int gpio_in1 = GPIO.in1.data;
/*
  TIMPeriph *pInputTimer = &inputTimer;
  unsigned long long ccount = pInputTimer->counter();
*/

  TIMERG0.hw_timer[1].update = 1;
  unsigned long long low_reg = TIMERG0.hw_timer[1].cnt_low;
  unsigned long long high_reg = TIMERG0.hw_timer[1].cnt_high;
  unsigned long long ccount = (high_reg << 32) | low_reg ;


  unsigned int intr_status = GPIO.status;
  unsigned int intr_status1 = GPIO.status1.intr_st;
  GPIO.status_w1tc = intr_status;
  GPIO.status1_w1tc.intr_st = intr_status1;

  unsigned int change = prev_state ^ gpio_in;
  unsigned int change1 = prev_state1 ^ gpio_in1;

  prev_state = gpio_in;
  prev_state1 = gpio_in1;

  for(int i=0; i<NUM_CHANNEL; i++) {
    if(channel_gpio_[i] < 32) {
      if(0x1 & change >> channel_gpio_[i]) {
    		if(0x1 & gpio_in >> channel_gpio_[i]) {
    			start_channel_[i] = ccount;
    		}
    		else {
    			rx_channel_[i] = (ccount - start_channel_[i]);
          if(rx_channel_[i] < 0) rx_channel_[i] += 0xFFFFFFFFFFFFFFFF;
    		}
      }
    }
    else {
      if(0x1 & change1 >> (channel_gpio_[i]-32)) {
    		if(0x1 & gpio_in1 >> (channel_gpio_[i]-32)) {
    			start_channel_[i] = ccount;
    		}
    		else {
    			rx_channel_[i] = (ccount - start_channel_[i]);
          if(rx_channel_[i] < 0) rx_channel_[i] += 0xFFFFFFFFFFFFFFFF;
    		}
      }
    }
  }

  //inputTimer.alarm( ccount + FAILSAFE_LIMIT );

}
