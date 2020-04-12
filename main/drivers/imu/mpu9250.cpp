#include "mpu9250.h"

MPU9250::MPU9250() {}

MPU9250::MPU9250(SPIPeriph *spi) {
  _spi = spi;
}

void MPU9250::attach(SPIPeriph *spi) {
  _spi = spi;
}

void MPU9250::spi_init() const {
  _spi->mode(MASTER);
  _spi->bit_order(MSB_FIRST, MSB_FIRST);
  _spi->byte_order(SPI_LITTE_ENDIAN, SPI_BIG_ENDIAN);
  _spi->full_duplex(NORMAL);
  _spi->phase( SPI_ADDR | SPI_MOSI );
  _spi->cmd_len(0);
  _spi->addr_len(7); /* 7 + 1 = 8 bits */
  _spi->mosi_len(7); /* 7 + 1 = 8 bits */
  _spi->miso_len(0);
  _spi->clk_sys(0);
  _spi->pre_div(19);
  _spi->clkcnt(3);
  _spi->clk_edge_idle(HIGH);
  _spi->addr_h(0);
  _spi->clk_miso_delay(2, 0);
  _spi->clear_all_buffer();
}

void MPU9250::clk_1Mhz() const {
  _spi->pre_div(19);
}

void MPU9250::clk_20Mhz() const {
  _spi->pre_div(0);
}

/*
  ****** IC2 MPU9250 SETTINGS*****

  I2CPeriph I2C_0(I2C0_PERIPH);
	I2C_0.mode(I2C_MASTER);
	I2C_0.data_mode(SAMPLE_SCL_HIGH, I2C_MSB_FIRST, I2C_MSB_FIRST);
	I2C_0.pin_mode(OPEN_DRAIN, OPEN_DRAIN);
	I2C_0.period(200, 200);
	I2C_0.start_timing(100, 100);
	I2C_0.data_timing(50,50);
	I2C_0.stop_timing(100,100);

  ****** READ REGISTER *******

  I2C_0.cmd(0, I2C_START, 1);
	I2C_0.cmd(1, I2C_WRITE, 2, 1);
	I2C_0.cmd(2, I2C_START, 1);
	I2C_0.cmd(3, I2C_WRITE, 1, 1);
	I2C_0.cmd(4, I2C_READ, 1, 0, 0);
	I2C_0.cmd(5, I2C_READ, 1, 0, 1);
	I2C_0.cmd(6, I2C_STOP, 1);

	I2C_0.data( (0x68<<1) );
	I2C_0.data( 0x3b );
	I2C_0.data( (0x68<<1 | 1) );

	I2C_0.trans_start();
	ets_printf("Start ... \n");
	while(I2C0.status_reg.bus_busy);
	//ets_delay_us(1000000);

	uint8_t acc_h = I2C_0.data();
	uint8_t acc_l = I2C_0.data();

	uint16_t acc = (acc_h<<8) | acc_l;
*/

unsigned int* MPU9250::buffer() const {
  return _spi->buffer();
}

int MPU9250::check() const {
  return ( RRegister(WHOAMI_ADDR) == WHOAMI );
}

void MPU9250::mpu_init() const {

  WRegister( CONFIG , GYRO_BW_3600 );
  WRegister( GYRO_CONFIG , GYRO_2000DPS | GYRO_8K_1KHZ );
  WRegister( ACCEL_CONFIG , ACCEL_8G );
  WRegister( ACCEL_CONFIG_2 , ACCEL_4KHZ );

  _spi->phase( SPI_ADDR | SPI_MISO );
  _spi->miso_len(111);
  _spi->addr_h( ( 0x80 | ACCEL_XOUT_H ) << 24 );
}

void MPU9250::config_get_all() const {
  _spi->phase( SPI_ADDR | SPI_MISO );
  _spi->miso_len(111);
  _spi->addr_h( ( 0x80 | ACCEL_XOUT_H ) << 24 );
}

void MPU9250::config_get_acc() const {
  _spi->phase( SPI_ADDR | SPI_MISO );
  _spi->miso_len(47);
  _spi->addr_h( ( 0x80 | ACCEL_XOUT_H ) << 24 );
}

void MPU9250::config_get_gyro() const {
  _spi->phase( SPI_ADDR | SPI_MISO );
  _spi->miso_len(47);
  _spi->addr_h( ( 0x80 | GYRO_XOUT_H ) << 24 );
}

void MPU9250::config_get_temp() const {
  _spi->phase( SPI_ADDR | SPI_MISO );
  _spi->miso_len(15);
  _spi->addr_h( ( 0x80 | TEMP_OUT_H ) << 24 );
}
void MPU9250::WRegister(unsigned char address, unsigned char data) const {
  _spi->phase( SPI_ADDR | SPI_MOSI );
  _spi->addr_h(( address ) << 24);
  _spi->mosi_len(7);
  _spi->buffer(0, data);
  _spi->transfer();
  while(_spi->transfer_status());
}

unsigned char MPU9250::RRegister(unsigned char address) const {
  _spi->phase( SPI_ADDR | SPI_MISO );
  _spi->addr_h(( 0x80 | address ) << (32-8));
  _spi->miso_len(7);
  _spi->transfer();
  while(_spi->transfer_status());
  return (_spi->buffer(0) >> 24);
}

unsigned int MPU9250::test() const {
  return RRegister(116);
}
