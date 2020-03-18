#ifndef H_ESC
#define H_ESC

#include "rmt.h"

typedef enum { PWM, ONESHOT125, ONESHOT42, MULTISHOT, DSHOT150, DSHOT300, DSHOT600, DSHOT1200 } esc_mode_t;

class ESC {
  public:
    ESC(RMTPeriph *rmt);
    void mode(esc_mode_t mode);
    void set(unsigned int value, bool telemetry = 0);
    void write();

  private:
    void set_pwm(unsigned int value, bool);
    void set_oneshot125(unsigned int value, bool);
    void set_oneshot42(unsigned int value, bool);
    void set_multishot(unsigned int value, bool);
    void set_dshot150(unsigned int value, bool telemetry);
    void set_dshot300(unsigned int value, bool telemetry);
    void set_dshot600(unsigned int value, bool telemetry);
    void set_dshot1200(unsigned int value, bool telemetry);
    void (ESC::*pSet)(unsigned int, bool);
    unsigned int dshotChecksum(unsigned int packet);
    RMTPeriph *_rmt;

};

#endif /* H_ESC */
