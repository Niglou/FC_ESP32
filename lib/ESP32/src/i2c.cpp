#include "ESP32/include/i2c.h"

I2CPeriph::I2CPeriph(i2c_num_t _num) {
    if(_num == I2C0_PERIPH) i2c = &I2C0;
    else if(_num == I2C1_PERIPH) i2c = &I2C1;
    else i2c = &I2C0; 
    (*i2c).ctr.val = 0;
    (*i2c).ctr.clk_en = 1;
    (*i2c).timeout.tout = 400000; }

void I2CPeriph::mode(i2c_mode_t mode) const {
    (*i2c).ctr.ms_mode = mode; }
void I2CPeriph::data_mode(i2c_data_t sample_scl_level, i2c_data_t rx, i2c_data_t tx) const {
    (*i2c).ctr.sample_scl_level = sample_scl_level;
    (*i2c).ctr.rx_lsb_first = rx;
    (*i2c).ctr.tx_lsb_first = tx; }
void I2CPeriph::pin_mode(i2c_pin_t scl, i2c_pin_t sda) const {
    (*i2c).ctr.scl_force_out = scl;
    (*i2c).ctr.sda_force_out = sda; }

void I2CPeriph::period(int low_period, int high_period) const {
    (*i2c).scl_low_period.period = low_period;
    (*i2c).scl_high_period.period = high_period; }

void I2CPeriph::data_timing(int sample_time, int hold_time) const {
    (*i2c).sda_sample.time = sample_time;
    (*i2c).sda_hold.time = hold_time; }
void I2CPeriph::start_timing(int setup_time, int hold_time) const {
    (*i2c).scl_rstart_setup.time = setup_time;
    (*i2c).scl_start_hold.time = hold_time; }
void I2CPeriph::stop_timing(int setup_time, int hold_time) const {
    (*i2c).scl_stop_setup.time = setup_time;
    (*i2c).scl_stop_hold.time = hold_time; }
void I2CPeriph::cmd(int index, i2c_cmd_t cmd, int byte_num, bool check, bool ack_value) const {
    (*i2c).command[index].byte_num = byte_num; 
    (*i2c).command[index].ack_en = check; 
    (*i2c).command[index].ack_exp = 0;
    (*i2c).command[index].ack_val = ack_value;
    (*i2c).command[index].op_code = cmd; }
void I2CPeriph::data(int data) const {
    (*i2c).fifo_data.data = data; }
int  I2CPeriph::data() const {
    return (*i2c).fifo_data.data; }

void I2CPeriph::trans_start() const {
    (*i2c).ctr.trans_start = 1; }

int  I2CPeriph::trans_check() const {
    return (*i2c).ctr.trans_start; }
