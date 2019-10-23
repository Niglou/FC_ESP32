
#include <ESP32/registers/struct/gpio_struct.h>

#include "config.h"

#include <ESP32/include/timer.h>
#include "pwm.h"

extern "C" {

  void ISR_LVL5();

}

extern unsigned int channel_gpio_[];

volatile unsigned int prev_state, prev_state1;

volatile int channel_[NUM_CHANNEL] = {0};
volatile unsigned long long start_channel_[NUM_CHANNEL] = {0};

TIMPeriph inputTimer;

void init_input_pwm() {
  inputTimer.attach(GROUP0, TIMER1);
  inputTimer.divider(80);
  inputTimer.enable();
}

void ISR_LVL5() {

  unsigned int gpio_in = GPIO.in;
  unsigned int gpio_in1 = GPIO.in1.data;

  TIMERG0.hw_timer[1].update = 1;
  unsigned long long ccount_l = TIMERG0.hw_timer[1].cnt_low;
  unsigned long long ccount_h = TIMERG0.hw_timer[1].cnt_high;
  unsigned long long ccount = (ccount_h << 32) | ccount_l;

  unsigned int intr_status = GPIO.status;
  unsigned int intr_status1 = GPIO.status1.intr_st;
  GPIO.status_w1tc = intr_status;
  GPIO.status1_w1tc.intr_st = intr_status1;

  unsigned int change = prev_state ^ gpio_in;
  unsigned int change1 = prev_state1 ^ gpio_in1;

  for(int i=0; i<NUM_CHANNEL; i++) {
    if(channel_gpio_[i] < 32) {
      if(0x1 & change >> channel_gpio_[i]) {
    		if(0x1 & gpio_in >> channel_gpio_[i]) {
    			start_channel_[i] = ccount;
    		}
    		else {
    			channel_[i] = (ccount - start_channel_[i]);
          if(channel_[i] < 0) channel_[i] += 0xFFFFFFFFFFFFFFFF;
    		}
      }
    }
    else {
      if(0x1 & change1 >> (channel_gpio_[i]-32)) {
    		if(0x1 & gpio_in1 >> (channel_gpio_[i]-32)) {
    			start_channel_[i] = ccount;
    		}
    		else {
    			channel_[i] = (ccount - start_channel_[i]);
          if(channel_[i] < 0) channel_[i] += 0xFFFFFFFFFFFFFFFF;
    		}
      }
    }
  }

  prev_state = gpio_in;
  prev_state1 = gpio_in1;

}
