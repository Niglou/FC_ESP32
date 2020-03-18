#include "esc.h"

ESC::ESC(RMTPeriph *rmt) {
  _rmt = rmt;
  _rmt->mode(TRANSMITTER);
  _rmt->carrier(RMT_DIS);
  _rmt->idle_en(RMT_EN);
  _rmt->idle_lvl(RMT_DIS);
  _rmt->conti_mode(RMT_DIS);
  _rmt->divider(1);
  pSet = 0;
}

void ESC::mode(esc_mode_t mode) {
  switch (mode) {

    /* TICK clock 1MHz ( 1us ) */

    case PWM: pSet = &ESC::set_pwm;
              _rmt->clock(REF_TICK);
              break;

    /* APB clock 80MHz ( 12.5ns ) */

    case ONESHOT125:  pSet = &ESC::set_oneshot125;
                      _rmt->clock(APB_CLK);
                      break;
    case ONESHOT42:   pSet = &ESC::set_oneshot42;
                      _rmt->clock(APB_CLK);
                      break;
    case MULTISHOT:   pSet = &ESC::set_multishot;
                      _rmt->clock(APB_CLK);
                      break;

    case DSHOT150:    pSet = &ESC::set_dshot150;
                      _rmt->clock(APB_CLK);
                      break;
    case DSHOT300:    pSet = &ESC::set_dshot300;
                      _rmt->clock(APB_CLK);
                      break;
    case DSHOT600:    pSet = &ESC::set_dshot600;
                      _rmt->clock(APB_CLK);
                      break;
    case DSHOT1200:    pSet = &ESC::set_dshot1200;
                      _rmt->clock(APB_CLK);
                      break;
  }
}

void ESC::set(unsigned int value, bool telemetry) {
  (this->*pSet)(value, telemetry);
}

void ESC::write() {
  _rmt->rst_pos_trans();
  _rmt->start();
}

void ESC::set_pwm(unsigned int value, bool) {
  _rmt->data(0, (1<<15) | value );
}
void ESC::set_oneshot125(unsigned int value, bool) {
  _rmt->data(0, (1<<15) | (value*10) );
}
void ESC::set_oneshot42(unsigned int value, bool) {
  _rmt->data(0, (1<<15) | (value*336/100) );
}
void ESC::set_multishot(unsigned int value, bool) {
  _rmt->data(0, (1<<15) | (((value-1000)*16/10) + 400) );
}

void ESC::set_dshot150(unsigned int value, bool telemetry) {
  unsigned int frame = ( value << 1) | telemetry; // requestTelemetry (0)
  unsigned int checksum = dshotChecksum(frame);
  frame = ( frame << 4) | checksum;
  for (int i = 0; i < 16; i++) {
    unsigned int bit = (frame >> (15-i)) & 0x1;
    if(bit) _rmt->data(i, ( 135 <<16) | (1<<15) | 400 );
    else _rmt->data(i, ( 335 <<16) | (1<<15) | 200 ); }
}
void ESC::set_dshot300(unsigned int value, bool telemetry) {
  unsigned int frame = ( value << 1) | telemetry; // requestTelemetry (0)
  unsigned int checksum = dshotChecksum(frame);
  frame = ( frame << 4) | checksum;
  for (int i = 0; i < 16; i++) {
    unsigned int bit = (frame >> (15-i)) & 0x1;
    if(bit) _rmt->data(i, ( 66 <<16) | (1<<15) | 200 );
    else _rmt->data(i, ( 166 <<16) | (1<<15) | 100 ); }
}
void ESC::set_dshot600(unsigned int value, bool telemetry) {
  unsigned int frame = ( value << 1) | telemetry; // requestTelemetry (0)
  unsigned int checksum = dshotChecksum(frame);
  frame = ( frame << 4) | checksum;
  for (int i = 0; i < 16; i++) {
    unsigned int bit = (frame >> (15-i)) & 0x1;
    if(bit) _rmt->data(i, ( 34 <<16) | (1<<15) | 98 );
    else _rmt->data(i, ( 84 <<16) | (1<<15) | 48 ); }
}
void ESC::set_dshot1200(unsigned int value, bool telemetry) {
  unsigned int frame = ( value << 1) | telemetry; // requestTelemetry (0)
  unsigned int checksum = dshotChecksum(frame);
  frame = ( frame << 4) | checksum;
  for (int i = 0; i < 16; i++) {
    unsigned int bit = (frame >> (15-i)) & 0x1;
    if(bit) _rmt->data(i, ( 17 <<16) | (1<<15) | 50 );
    else _rmt->data(i, ( 42 <<16) | (1<<15) | 25 ); }
}

unsigned int ESC::dshotChecksum(unsigned int packet) {
  int csum = 0;
  int csum_data = packet;
  for(int i=0; i<3; i++) {
    csum ^= csum_data;
    csum_data >>=4;
  }
  csum &= 0xf;
  return csum;
}
