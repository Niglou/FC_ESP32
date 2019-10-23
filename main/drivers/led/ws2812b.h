#ifndef H_WS2812B
#define H_WS2812B

#include <ESP32/include/rmt.h>

class WS2812B {
  public:
    WS2812B(RMTPeriph *rmt);
    void green(unsigned char value);
    void red(unsigned char value);
    void blue(unsigned char value);
    void color(unsigned char green, unsigned char red, unsigned char blue);
    void write();

  private:
    RMTPeriph *_rmt;

};

#endif
