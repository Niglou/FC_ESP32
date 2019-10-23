#ifndef H_SPI_FLASH
#define H_SPI_FLASH

#include "spi.h"

class intFlashClass {
public:
  intFlashClass(SPIPeriph *spi);
  void spi_bus_init() const;
  void spi_init() const;
  unsigned int id() const;
  void write(unsigned int address, unsigned char data) const;
  unsigned int* read(unsigned int address) const;

private:
  SPIPeriph *_spi;

};

void spi_flash_bus_init();
void spi_flash_init(SPIPeriph *spi);
void spi_flash_en(SPIPeriph *spi);
void spi_flash_id(SPIPeriph *spi);

#endif
