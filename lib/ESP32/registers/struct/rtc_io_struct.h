#ifndef H_NONOS_RTC_IO_STRUCT
#define H_NONOS_RTC_IO_STRUCT

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct {
    union {
        struct {
            unsigned int reserved0:        14;
            unsigned int data:18;              /*GPIO0~17 output value*/
        };
        unsigned int reg;
    } out;
    union {
        struct {
            unsigned int reserved0:             14;
            unsigned int w1ts:18;         /*GPIO0~17 output value write 1 to set*/
        };
        unsigned int reg;
    } out_w1ts;
    union {
        struct {
            unsigned int reserved0:             14;
            unsigned int w1tc:18;         /*GPIO0~17 output value write 1 to clear*/
        };
        unsigned int reg;
    } out_w1tc;
    union {
        struct {
            unsigned int reserved0:      14;
            unsigned int enable:18;                /*GPIO0~17 output enable*/
        };
        unsigned int reg;
    } enable;
    union {
        struct {
            unsigned int reserved0:           14;
            unsigned int w1ts:18;           /*GPIO0~17 output enable write 1 to set*/
        };
        unsigned int reg;
    } enable_w1ts;
    union {
        struct {
            unsigned int reserved0:           14;
            unsigned int w1tc:18;           /*GPIO0~17 output enable write 1 to clear*/
        };
        unsigned int reg;
    } enable_w1tc;
    union {
        struct {
            unsigned int reserved0:          14;
            unsigned int status:18;            /*GPIO0~17 interrupt status*/
        };
        unsigned int reg;
    } status;
    union {
        struct {
            unsigned int reserved0:               14;
            unsigned int w1ts:18;       /*GPIO0~17 interrupt status write 1 to set*/
        };
        unsigned int reg;
    } status_w1ts;
    union {
        struct {
            unsigned int reserved0:               14;
            unsigned int w1tc:18;       /*GPIO0~17 interrupt status write 1 to clear*/
        };
        unsigned int reg;
    } status_w1tc;
    union {
        struct {
            unsigned int reserved0:       14;
            unsigned int in:18;               /*GPIO0~17 input value*/
        };
        unsigned int reg;
    } in_val;
    union {
        struct {
            unsigned int reserved0:                   2;
            unsigned int pad_driver:    1;    /*if set to 0: normal output  if set to 1: open drain*/
            unsigned int reserved3:                   4;
            unsigned int int_type:      3;    /*if set to 0: GPIO interrupt disable  if set to 1: rising edge trigger  if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger  if set to 5: high level trigger*/
            unsigned int wakeup_enable: 1;    /*GPIO wake up enable  only available in light sleep*/
            unsigned int reserved11:                 21;
        };
        unsigned int reg;
    } pin[18];
    union {
        struct {
            unsigned int sel0:          5;
            unsigned int sel1:          5;
            unsigned int sel2:          5;
            unsigned int sel3:          5;
            unsigned int sel4:          5;
            unsigned int no_gating_12m: 1;
            unsigned int reserved26:              6;
        };
        unsigned int reg;
    } debug_sel;
    unsigned int dig_pad_hold;                              /*select the digital pad hold value.*/
    union {
        struct {
            unsigned int reserved0: 30;
            unsigned int hall_phase: 1;                     /*Reverse phase of hall sensor*/
            unsigned int xpd_hall:   1;                     /*Power on hall sensor and connect to VP and VN*/
        };
        unsigned int reg;
    } hall_sens;
    union {
        struct {
            unsigned int reserved0:      4;
            unsigned int sense4_fun_ie:  1;                 /*the input enable of the pad*/
            unsigned int sense4_slp_ie:  1;                 /*the input enable of the pad in sleep status*/
            unsigned int sense4_slp_sel: 1;                 /*the sleep status selection signal of the pad*/
            unsigned int sense4_fun_sel: 2;                 /*the functional selection signal of the pad*/
            unsigned int sense3_fun_ie:  1;                 /*the input enable of the pad*/
            unsigned int sense3_slp_ie:  1;                 /*the input enable of the pad in sleep status*/
            unsigned int sense3_slp_sel: 1;                 /*the sleep status selection signal of the pad*/
            unsigned int sense3_fun_sel: 2;                 /*the functional selection signal of the pad*/
            unsigned int sense2_fun_ie:  1;                 /*the input enable of the pad*/
            unsigned int sense2_slp_ie:  1;                 /*the input enable of the pad in sleep status*/
            unsigned int sense2_slp_sel: 1;                 /*the sleep status selection signal of the pad*/
            unsigned int sense2_fun_sel: 2;                 /*the functional selection signal of the pad*/
            unsigned int sense1_fun_ie:  1;                 /*the input enable of the pad*/
            unsigned int sense1_slp_ie:  1;                 /*the input enable of the pad in sleep status*/
            unsigned int sense1_slp_sel: 1;                 /*the sleep status selection signal of the pad*/
            unsigned int sense1_fun_sel: 2;                 /*the functional selection signal of the pad*/
            unsigned int sense4_mux_sel: 1;                 /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int sense3_mux_sel: 1;                 /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int sense2_mux_sel: 1;                 /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int sense1_mux_sel: 1;                 /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int sense4_hold:    1;                 /*hold the current value of the output when setting the hold to �1�*/
            unsigned int sense3_hold:    1;                 /*hold the current value of the output when setting the hold to �1�*/
            unsigned int sense2_hold:    1;                 /*hold the current value of the output when setting the hold to �1�*/
            unsigned int sense1_hold:    1;                 /*hold the current value of the output when setting the hold to �1�*/
        };
        unsigned int reg;
    } sensor_pads;
    union {
        struct {
            unsigned int reserved0:   18;
            unsigned int adc2_fun_ie:  1;                   /*the input enable of the pad*/
            unsigned int adc2_slp_ie:  1;                   /*the input enable of the pad in sleep status*/
            unsigned int adc2_slp_sel: 1;                   /*the sleep status selection signal of the pad*/
            unsigned int adc2_fun_sel: 2;                   /*the functional selection signal of the pad*/
            unsigned int adc1_fun_ie:  1;                   /*the input enable of the pad*/
            unsigned int adc1_slp_ie:  1;                   /*the input enable of the pad in sleep status*/
            unsigned int adc1_slp_sel: 1;                   /*the sleep status selection signal of the pad*/
            unsigned int adc1_fun_sel: 2;                   /*the functional selection signal of the pad*/
            unsigned int adc2_mux_sel: 1;                   /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int adc1_mux_sel: 1;                   /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int adc2_hold:    1;                   /*hold the current value of the output when setting the hold to �1�*/
            unsigned int adc1_hold:    1;                   /*hold the current value of the output when setting the hold to �1�*/
        };
        unsigned int reg;
    } adc_pad;
    union {
        struct {
            unsigned int reserved0:          10;
            unsigned int dac_xpd_force: 1;            /*Power on DAC1. Usually  we need to tristate PDAC1 if we power on the DAC  i.e. IE=0  OE=0  RDE=0  RUE=0*/
            unsigned int fun_ie:        1;            /*the input enable of the pad*/
            unsigned int slp_oe:        1;            /*the output enable of the pad in sleep status*/
            unsigned int slp_ie:        1;            /*the input enable of the pad in sleep status*/
            unsigned int slp_sel:       1;            /*the sleep status selection signal of the pad*/
            unsigned int fun_sel:       2;            /*the functional selection signal of the pad*/
            unsigned int mux_sel:       1;            /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int xpd_dac:       1;            /*Power on DAC1. Usually  we need to tristate PDAC1 if we power on the DAC  i.e. IE=0  OE=0  RDE=0  RUE=0*/
            unsigned int dac:           8;            /*PAD DAC1 control code.*/
            unsigned int rue:           1;            /*the pull up enable of the pad*/
            unsigned int rde:           1;            /*the pull down enable of the pad*/
            unsigned int hold:          1;            /*hold the current value of the output when setting the hold to �1�*/
            unsigned int drv:           2;            /*the driver strength of the pad*/
        };
        unsigned int reg;
    } pad_dac[2];
    union {
        struct {
            unsigned int reserved0:      1;
            unsigned int dbias_xtal_32k: 2;                 /*32K XTAL self-bias reference control.*/
            unsigned int dres_xtal_32k:  2;                 /*32K XTAL resistor bias control.*/
            unsigned int x32p_fun_ie:    1;                 /*the input enable of the pad*/
            unsigned int x32p_slp_oe:    1;                 /*the output enable of the pad in sleep status*/
            unsigned int x32p_slp_ie:    1;                 /*the input enable of the pad in sleep status*/
            unsigned int x32p_slp_sel:   1;                 /*the sleep status selection signal of the pad*/
            unsigned int x32p_fun_sel:   2;                 /*the functional selection signal of the pad*/
            unsigned int x32n_fun_ie:    1;                 /*the input enable of the pad*/
            unsigned int x32n_slp_oe:    1;                 /*the output enable of the pad in sleep status*/
            unsigned int x32n_slp_ie:    1;                 /*the input enable of the pad in sleep status*/
            unsigned int x32n_slp_sel:   1;                 /*the sleep status selection signal of the pad*/
            unsigned int x32n_fun_sel:   2;                 /*the functional selection signal of the pad*/
            unsigned int x32p_mux_sel:   1;                 /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int x32n_mux_sel:   1;                 /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int xpd_xtal_32k:   1;                 /*Power up 32kHz crystal oscillator*/
            unsigned int dac_xtal_32k:   2;                 /*32K XTAL bias current DAC.*/
            unsigned int x32p_rue:       1;                 /*the pull up enable of the pad*/
            unsigned int x32p_rde:       1;                 /*the pull down enable of the pad*/
            unsigned int x32p_hold:      1;                 /*hold the current value of the output when setting the hold to �1�*/
            unsigned int x32p_drv:       2;                 /*the driver strength of the pad*/
            unsigned int x32n_rue:       1;                 /*the pull up enable of the pad*/
            unsigned int x32n_rde:       1;                 /*the pull down enable of the pad*/
            unsigned int x32n_hold:      1;                 /*hold the current value of the output when setting the hold to �1�*/
            unsigned int x32n_drv:       2;                 /*the driver strength of the pad*/
        };
        unsigned int reg;
    } xtal_32k_pad;
    union {
        struct {
            unsigned int reserved0:     23;
            unsigned int dcur:     2;                 /*touch sensor bias current. Should have option to tie with BIAS_SLEEP(When BIAS_SLEEP  this setting is available*/
            unsigned int drange:   2;                 /*touch sensor saw wave voltage range.*/
            unsigned int drefl:    2;                 /*touch sensor saw wave bottom voltage.*/
            unsigned int drefh:    2;                 /*touch sensor saw wave top voltage.*/
            unsigned int xpd_bias: 1;                 /*touch sensor bias power on.*/
        };
        unsigned int reg;
    } touch_cfg;
    union {
        struct {
            unsigned int reserved0:         12;
            unsigned int to_gpio: 1;             /*connect the rtc pad input to digital pad input �0� is availbale GPIO4*/
            unsigned int fun_ie:  1;             /*the input enable of the pad*/
            unsigned int slp_oe:  1;             /*the output enable of the pad in sleep status*/
            unsigned int slp_ie:  1;             /*the input enable of the pad in sleep status*/
            unsigned int slp_sel: 1;             /*the sleep status selection signal of the pad*/
            unsigned int fun_sel: 2;             /*the functional selection signal of the pad*/
            unsigned int mux_sel: 1;             /*�1� select the digital function  �0�slection the rtc function*/
            unsigned int xpd:     1;             /*touch sensor power on.*/
            unsigned int tie_opt: 1;             /*default touch sensor tie option. 0: tie low  1: tie high.*/
            unsigned int start:   1;             /*start touch sensor.*/
            unsigned int dac:     3;             /*touch sensor slope control. 3-bit for each touch panel  default 100.*/
            unsigned int reserved26:         1;
            unsigned int rue:     1;             /*the pull up enable of the pad*/
            unsigned int rde:     1;             /*the pull down enable of the pad*/
            unsigned int drv:     2;             /*the driver strength of the pad*/
            unsigned int hold:    1;             /*hold the current value of the output when setting the hold to �1�*/
        };
        unsigned int reg;
    } touch_pad[10];
    union {
        struct {
            unsigned int reserved0:      27;
            unsigned int sel: 5;                /*select the wakeup source �0� select GPIO0 �1� select GPIO2 ...�17� select GPIO17*/
        };
        unsigned int reg;
    } ext_wakeup0;
    union {
        struct {
            unsigned int reserved0:      27;
            unsigned int sel: 5;                /*select the external xtl power source �0� select GPIO0 �1� select GPIO2 ...�17� select GPIO17*/
        };
        unsigned int reg;
    } xtl_ext_ctr;
    union {
        struct {
            unsigned int reserved0:        23;
            unsigned int debug_bit_sel: 5;
            unsigned int scl_sel:   2;              /*�0� using TOUCH_PAD[0] as i2c clk �1� using TOUCH_PAD[2] as i2c clk*/
            unsigned int sda_sel:   2;              /*�0� using TOUCH_PAD[1] as i2c sda �1� using TOUCH_PAD[3] as i2c sda*/
        };
        unsigned int reg;
    } sar_i2c_io;
    union {
        struct {
            unsigned int date:      28;                     /*date*/
            unsigned int reserved28: 4;
        };
        unsigned int reg;
    } date;
} rtc_io_dev_t;

extern rtc_io_dev_t RTCIO;

#ifdef __cplusplus
}
#endif

#endif