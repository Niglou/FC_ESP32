# **FC_ESP32**

## **Features**

- **ESP32-PICO-D4**
- **MODE** : Gyro   
- **INPUT** : PWM
- **IMU** : MPU9250 + BMP280 ( not implemented )
- **OSD** : MAX7456
- **ESC** : analog : PWM / ONESHOT125 / ONESHOT45 / MULTISHOT  
    &emsp; &emsp; digital : DSHOT150 / DSHOT300 / DSHOT600 / DSHOT1200
- **SDCARD** ( not implemented )

## **Prerequies**

- You'll need [**esp32-nonos**](https://github.com/Niglou/esp32-nonos)

- Change esp32-nonos path in *Makefile*

- For ESP32-PICO-D4 flash with this :  
  `esptool.py -c esp32 write_flash -sc 6,17,8,11,16 0x1000 FC_ESP32.bin`  
  ( If you use ESP32 no need "-sc" option but the pins of the internal flash are not the same, so you may need to change pins )

- Use "config.h" to set pins for RX and ESC.

## **Pins**

**Available**
  * IO : &ensp; 4, 9, 21, 22, 25, 26, 27, 32, 33 ( input/output )
  * I &ensp; : &ensp; 34, 35, 37, 38, 39 ( input only )


**LED State**
  * GPIO 2

**MPU9250**
  * HSPI ( direct / bypass GPIO Matrix )

**BMP280**
  * AUX_I2C from MPU9250

**MAX7456**
  * VSPI ( direct / bypass GPIO Matrix ) CS1 : SD_DATA_3 ( GPIO 10 )

**SDCARD**
  * VSPI ( direct / bypass GPIO Matrix )
