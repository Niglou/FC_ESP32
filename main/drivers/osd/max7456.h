#ifndef H_MAX7456
#define H_MAX7456

#include <ESP32/include/spi.h>

// Write Register
#define W_VM0   0x00
#define W_VM1   0x01
#define W_HOS   0x02
#define W_VOS   0x03
#define W_DMM   0x04
#define W_DMAH  0x05
#define W_DMAL  0x06
#define W_DMDI  0x07
#define W_CMM   0x08
#define W_CMAH  0x09
#define W_CMAL  0x0A
#define W_CMDI  0x0B
#define W_OSDM  0x0C
#define W_RB0   0x10
#define W_RB1   0x11
#define W_RB2   0x12
#define W_RB3   0x13
#define W_RB4   0x14
#define W_RB5   0x15
#define W_RB6   0x16
#define W_RB7   0x17
#define W_RB8   0x18
#define W_RB9   0x19
#define W_RB10  0x1A
#define W_RB11  0x1B
#define W_RB12  0x1C
#define W_RB13  0x1D
#define W_RB14  0x1E
#define W_RB15  0x1F
#define W_OSDBL 0x6C

// Read REGISTER
#define R_VM0   0x80
#define R_VM1   0x81
#define R_HOS   0x82
#define R_VOS   0x83
#define R_DMM   0x84
#define R_DMAH  0x85
#define R_DMAL  0x86
#define R_DMDI  0x87
#define R_CMM   0x88
#define R_CMAH  0x89
#define R_CMAL  0x8A
#define R_CMDI  0x8B
#define R_OSDM  0x8C
#define R_RB0   0x90
#define R_RB1   0x91
#define R_RB2   0x92
#define R_RB3   0x93
#define R_RB4   0x94
#define R_RB5   0x95
#define R_RB6   0x96
#define R_RB7   0x97
#define R_RB8   0x98
#define R_RB9   0x99
#define R_RB10  0x9A
#define R_RB11  0x9B
#define R_RB12  0x9C
#define R_RB13  0x9D
#define R_RB14  0x9E
#define R_RB15  0x9F
#define R_OSDBL 0x6C
#define R_STAT  0xA0
#define R_DMDO  0xB0
#define R_CMDO  0xC0


class MAX7456 {
public:
  MAX7456(SPIPeriph *spi);
  void spi_init() const;
  void init() const;
  int check() const;
  char stat() const;
  void print(char *value, char x, char y);

private:
  void WRegister(unsigned char addr, unsigned char data) const;
  unsigned char RRegister(unsigned char addr) const;
  SPIPeriph *_spi;

};

#endif
