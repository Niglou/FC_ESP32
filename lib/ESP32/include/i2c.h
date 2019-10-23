#ifndef H_NONOS_I2C
#define H_NONOS_I2C

#include "ESP32/registers/struct/i2c_struct.h"

typedef enum { I2C_SLAVE, I2C_MASTER } i2c_mode_t;
typedef enum { I2C0_PERIPH, I2C1_PERIPH } i2c_num_t;
typedef enum { I2C_MSB_FIRST, I2C_LSB_FIRST, SAMPLE_SCL_HIGH=0, SAMPLE_SCL_LOW } i2c_data_t;
typedef enum { DIRECT, OPEN_DRAIN } i2c_pin_t;
typedef enum { I2C_START, I2C_WRITE, I2C_READ, I2C_STOP, I2C_END } i2c_cmd_t;

class I2CPeriph {
    public:
        I2CPeriph(i2c_num_t _num);

        void mode(i2c_mode_t mode) const;
        void data_mode(i2c_data_t sample_scl_level, i2c_data_t rx, i2c_data_t tx) const;
        void pin_mode(i2c_pin_t scl, i2c_pin_t sda) const;

        void period(int low_period, int high_period) const;
        void data_timing(int sample_time, int hold_time) const;
        void start_timing(int setup_time, int hold_time) const;
        void stop_timing(int setup_time, int hold_time) const;

        void cmd(int index, i2c_cmd_t cmd, int byte_num, bool check=0, bool ack_value=0) const;
        void data(int data) const;
        int data() const;

        void trans_start() const;
        int  trans_check() const;

    private:
        i2c_dev_t *i2c;
};

#endif