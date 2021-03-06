#ifndef H_MPU9250
#define H_MPU9250

#include "spi.h"

#define REG(_r) *(volatile unsigned int*)_r

#define WHOAMI_ADDR         0x75
#define WHOAMI              0x71

#define USER_CTRL           0x6A

#define CONFIG              0x1A
#define GYRO_BW_3600        0x07
#define GYRO_BW_250         0x00

#define GYRO_CONFIG         0x1B
#define GYRO_250DPS         0x00
#define GYRO_500DPS         0x08
#define GYRO_1000DPS        0x10
#define GYRO_2000DPS        0x18
#define GYRO_8K_1KHZ        0x00
#define GYRO_L_32KHZ        0x02 /* Bandwidth 3600Hz */
#define GYRO_F_32KHZ        0x03 /* Bandwidth 8800Hz */

#define GYRO_SENS_250DPS    131.0f
#define GYRO_SENS_500DPS    65.5f
#define GYRO_SENS_1000DPS   32.8f
#define GYRO_SENS_2000DPS   16.4f

#define ACCEL_CONFIG        0x1C
#define ACCEL_2G            0x00
#define ACCEL_4G            0x08
#define ACCEL_8G            0x10
#define ACCEL_16G           0x18

#define ACC_SENS_2G         16384.0
#define ACC_SENS_4G         8162.0f
#define ACC_SENS_8G         4096.0f
#define ACC_SENS_16G        2048.0f

#define ACCEL_CONFIG_2      0x1D
#define ACCEL_4KHZ          0x08

#define ACCEL_XOUT_H        0x3B
#define ACCEL_XOUT_L        0x3C
#define ACCEL_YOUT_H        0x3D
#define ACCEL_YOUT_L        0x3E
#define ACCEL_ZOUT_H        0x3F
#define ACCEL_ZOUT_L        0x40
#define TEMP_OUT_H          0x41
#define TEMP_OUT_L          0x42
#define GYRO_XOUT_H         0x43
#define GYRO_XOUT_L         0x44
#define GYRO_YOUT_H         0x45
#define GYRO_YOUT_L         0x46
#define GYRO_ZOUT_H         0x47
#define GYRO_ZOUT_L         0x48

struct esp32_mpu_all {
  short accY;
  short accX;
  short temp;
  short accZ;
  short gyroY;
  short gyroX;
  short empty;
  short gyroZ;
};

struct esp32_mpu_gyro {
  short gyroY;
  short gyroX;
  short empty;
  short gyroZ;
};

class MPU9250 {
  public:
    MPU9250();
    MPU9250(SPIPeriph *spi);
    void attach(SPIPeriph *spi);
    void spi_init() const;
    void mpu_init() const;
    int check() const;
    unsigned int* buffer() const;
    void config_get_all() const;
    void config_get_acc() const;
    void config_get_gyro() const;
    void config_get_temp() const;
    void get() const;
    void get_async() const;
    void clk_20Mhz() const;
    void clk_1Mhz() const;
    unsigned int test() const;

  private:
    void WRegister(unsigned char address, unsigned char data) const;
    unsigned char RRegister(unsigned char address) const;

    SPIPeriph *_spi;

};

inline void MPU9250::get() const {
  _spi->transfer();
  while(_spi->transfer_status());
}

inline void MPU9250::get_async() const {
  while(_spi->transfer_status());
  _spi->transfer();
}



#endif /* H_MPU9250 */
