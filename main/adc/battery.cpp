#include "battery.h"

#include <ESP32/registers/struct/rtc_io_struct.h>
#include <ESP32/registers/struct/sens_struct.h>
#include <ESP32/registers/struct/apb_ctrl_struct.h>

void adc_battery_init() {

  SENS.sar_start_force.sar1_bit_width = 3;
  SENS.sar_read_ctrl.sar1_sample_bit = 3;

  SENS.sar_read_ctrl.sar1_data_inv = 1;

  RTCIO.sensor_pads.sense1_mux_sel = 1;
  RTCIO.sensor_pads.sense1_fun_sel = 0;

  RTCIO.enable_w1ts.w1ts = 0;
  RTCIO.enable_w1tc.w1tc = 1;

  RTCIO.sensor_pads.sense1_fun_ie = 0;

  SENS.sar_atten1 = 0;

  SENS.sar_read_ctrl.sar1_dig_force = 0;

  SENS.sar_meas_wait2.force_xpd_sar = 3;

  RTCIO.hall_sens.xpd_hall = 0;

  SENS.sar_meas_wait2.force_xpd_amp = 2; // xpd_amp 2:off
  SENS.sar_meas_ctrl.amp_rst_fb_fsm = 0;
  SENS.sar_meas_ctrl.amp_short_ref_fsm = 0;
  SENS.sar_meas_ctrl.amp_short_ref_gnd_fsm = 0;
  SENS.sar_meas_wait1.sar_amp_wait1 = 1;
  SENS.sar_meas_wait1.sar_amp_wait2 = 1;
  SENS.sar_meas_wait2.sar_amp_wait3 = 1;

  SENS.sar_read_ctrl.sar1_dig_force = false;      //RTC controller controls the ADC, not digital controller
  SENS.sar_meas_start1.meas1_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
  SENS.sar_meas_start1.sar1_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
  SENS.sar_touch_ctrl1.xpd_hall_force = true;     // RTC controller controls the hall sensor power,not ulp coprocessor
  SENS.sar_touch_ctrl1.hall_phase_force = true;   // RTC controller controls the hall sensor phase,not ulp coprocessor


}

int  get_battery_voltage() {

  unsigned short adc_value;

  SENS.sar_meas_start1.sar1_en_pad = (1 << 0); //only one channel is selected.
  SENS.sar_meas_start1.meas1_start_sar = 0;
  SENS.sar_meas_start1.meas1_start_sar = 1;
  while (SENS.sar_meas_start1.meas1_done_sar == 0);
  adc_value = SENS.sar_meas_start1.meas1_data_sar;

  return adc_value;
}
