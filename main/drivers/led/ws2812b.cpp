#include "ws2812b.h"

WS2812B::WS2812B(RMTPeriph *rmt) {
  _rmt = rmt;
  _rmt->mode(TRANSMITTER);
	_rmt->clock(APB_CLK);
	_rmt->divider(2);
	_rmt->carrier(RMT_DIS);
	_rmt->idle_en(RMT_EN);
	_rmt->idle_lvl(RMT_DIS);
	_rmt->conti_mode(RMT_DIS);
  _rmt->data(24, 2000);
}

void WS2812B::green(unsigned char value) {
  for(int i = 0; i<8; i++) {
    int bit = (value >> (7-i)) & 0x01;
    if(bit) _rmt->data(i+8, (16<<16) | (1<<15) | (32));
		else    _rmt->data(i+8, (32<<16) | (1<<15) | (16));
	}
}

void WS2812B::red(unsigned char value) {
  for(int i = 0; i<8; i++) {
    int bit = (value >> (7-i)) & 0x01;
    if(bit) _rmt->data(i, (16<<16) | (1<<15) | (32));
		else    _rmt->data(i, (32<<16) | (1<<15) | (16));
	}
}

void WS2812B::blue(unsigned char value) {
  for(int i = 0; i<8; i++) {
    int bit = (value >> (7-i)) & 0x01;
    if(bit) _rmt->data(i+16, (16<<16) | (1<<15) | (32));
		else    _rmt->data(i+16, (32<<16) | (1<<15) | (16));
	}
}

void WS2812B::color(unsigned char red, unsigned char green, unsigned char blue) {
  this->red(red);
  this->green(green);
  this->blue(blue);
}

void WS2812B::write() {
  _rmt->rst_pos_trans();
  _rmt->start();
}
