# **FC_ESP32**

- **ESP32-PICO-D4** (default) / **ESP32** (modify makefile)
- **MODE** : Gyro
- **INPUT** : PWM
- **IMU** : MPU9250 + BMP280 ( not implemented )
- **OSD** : MAX7456
- **ESC** : PWM / ONESHOT125 / ONESHOT45 / MULTISHOT  
    DSHOT150 / DSHOT300 / DSHOT600 / DSHOT1200
- **SDCARD** ( not implemented )

----

## Components  

###### LED State
  * GPIO 2

###### MPU9250
  * HSPI ( direct / bypass GPIO Matrix )

###### BMP280
  * AUX_I2C from MPU9250

###### MAX7456
  * VSPI ( direct / bypass GPIO Matrix ) CS1 : SD_DATA_3 ( GPIO 10 )

###### SDCARD
  * VSPI ( direct / bypass GPIO Matrix )
