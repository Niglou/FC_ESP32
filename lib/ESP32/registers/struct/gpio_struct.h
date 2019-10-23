#ifndef H_NONOS_GPIO_STRUCT
#define H_NONOS_GPIO_STRUCT

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct {
    unsigned int bt_select;                             /*NA*/
    unsigned int out;                                   /*GPIO0~31 output value*/
    unsigned int out_w1ts;                              /*GPIO0~31 output value write 1 to set*/
    unsigned int out_w1tc;                              /*GPIO0~31 output value write 1 to clear*/
    union {
        struct {
            unsigned int data:       8;                 /*GPIO32~39 output value*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } out1;
    union {
        struct {
            unsigned int data:       8;                 /*GPIO32~39 output value write 1 to set*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } out1_w1ts;
    union {
        struct {
            unsigned int data:       8;                 /*GPIO32~39 output value write 1 to clear*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } out1_w1tc;
    union {
        struct {
            unsigned int sel:        8;                 /*SDIO PADS on/off control from outside*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } sdio_select;
    unsigned int enable;                                /*GPIO0~31 output enable*/
    unsigned int enable_w1ts;                           /*GPIO0~31 output enable write 1 to set*/
    unsigned int enable_w1tc;                           /*GPIO0~31 output enable write 1 to clear*/
    union {
        struct {
            unsigned int data:        8;                /*GPIO32~39 output enable*/
            unsigned int reserved8:  24;
        };
        unsigned int reg;
    } enable1;
    union {
        struct {
            unsigned int data:        8;                /*GPIO32~39 output enable write 1 to set*/
            unsigned int reserved8:  24;
        };
        unsigned int reg;
    } enable1_w1ts;
    union {
        struct {
            unsigned int data:        8;                /*GPIO32~39 output enable write 1 to clear*/
            unsigned int reserved8:  24;
        };
        unsigned int reg;
    } enable1_w1tc;
    union {
        struct {
            unsigned int strapping: 16;                 /*GPIO strapping results: {2'd0  boot_sel_dig[7:1]  vsdio_boot_sel  boot_sel_chip[5:0]} .   Boot_sel_dig[7:1]: {U0RXD  SD_CLK  SD_CMD  SD_DATA0  SD_DATA1  SD_DATA2  SD_DATA3} .  vsdio_boot_sel: MTDI. boot_sel_chip[5:0]: {GPIO0  U0TXD  GPIO2  GPIO4  MTDO  GPIO5} */
            unsigned int reserved16:16;
        };
        unsigned int reg;
    } strap;
    unsigned int in;                                    /*GPIO0~31 input value*/
    union {
        struct {
            unsigned int data:       8;                 /*GPIO32~39 input value*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } in1;
    unsigned int status;                                /*GPIO0~31 interrupt status*/
    unsigned int status_w1ts;                           /*GPIO0~31 interrupt status write 1 to set*/
    unsigned int status_w1tc;                           /*GPIO0~31 interrupt status write 1 to clear*/
    union {
        struct {
            unsigned int intr_st:    8;                 /*GPIO32~39 interrupt status*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } status1;
    union {
        struct {
            unsigned int intr_st:    8;                 /*GPIO32~39 interrupt status write 1 to set*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } status1_w1ts;
    union {
        struct {
            unsigned int intr_st:    8;                 /*GPIO32~39 interrupt status write 1 to clear*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } status1_w1tc;
    unsigned int reserved_5c;
    unsigned int acpu_int;                              /*GPIO0~31 APP CPU interrupt status*/
    unsigned int acpu_nmi_int;                          /*GPIO0~31 APP CPU non-maskable interrupt status*/
    unsigned int pcpu_int;                              /*GPIO0~31 PRO CPU interrupt status*/
    unsigned int pcpu_nmi_int;                          /*GPIO0~31 PRO CPU non-maskable interrupt status*/
    unsigned int cpusdio_int;                           /*SDIO's extent GPIO0~31 interrupt*/
    union {
        struct {
            unsigned int intr:       8;                 /*GPIO32~39 APP CPU interrupt status*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } acpu_int1;
    union {
        struct {
            unsigned int intr:       8;                 /*GPIO32~39 APP CPU non-maskable interrupt status*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } acpu_nmi_int1;
    union {
        struct {
            unsigned int intr:       8;                 /*GPIO32~39 PRO CPU interrupt status*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } pcpu_int1;
    union {
        struct {
            unsigned int intr:       8;                 /*GPIO32~39 PRO CPU non-maskable interrupt status*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } pcpu_nmi_int1;
    union {
        struct {
            unsigned int intr:       8;                 /*SDIO's extent GPIO32~39 interrupt*/
            unsigned int reserved8: 24;
        };
        unsigned int reg;
    } cpusdio_int1;
    union {
        struct {
            unsigned int reserved0:     2;
            unsigned int pad_driver:    1;              /*if set to 0: normal output  if set to 1: open drain*/
            unsigned int reserved3:     4;
            unsigned int int_type:      3;              /*if set to 0: GPIO interrupt disable  if set to 1: rising edge trigger  if set to 2: falling edge trigger  if set to 3: any edge trigger  if set to 4: low level trigger  if set to 5: high level trigger*/
            unsigned int wakeup_enable: 1;              /*GPIO wake up enable  only available in light sleep*/
            unsigned int config:        2;              /*NA*/
            unsigned int int_ena:       5;              /*bit0: APP CPU interrupt enable  bit1: APP CPU non-maskable interrupt enable  bit3: PRO CPU interrupt enable  bit4:  PRO CPU non-maskable interrupt enable  bit5: SDIO's extent interrupt enable*/
            unsigned int reserved18:   14;
        };
        unsigned int reg;
    } pin[40];
    union {
        struct {
            unsigned int rtc_max:     10;
            unsigned int reserved10:  21;
            unsigned int start:        1;
        };
        unsigned int reg;
    } cali_conf;
    union {
        struct {
            unsigned int value_sync2: 20;
            unsigned int reserved20:  10;
            unsigned int rdy_real:     1;
            unsigned int rdy_sync2:    1;
        };
        unsigned int reg;
    } cali_data;
    union {
        struct {
            unsigned int func_sel:    6;                /*select one of the 256 inputs*/
            unsigned int sig_in_inv:  1;                /*revert the value of the input if you want to revert  please set the value to 1*/
            unsigned int sig_in_sel:  1;                /*if the slow signal bypass the io matrix or not if you want  setting the value to 1*/
            unsigned int reserved8:  24;                /*The 256 registers below are selection control for 256 input signals connected to GPIO matrix's 40 GPIO input  if GPIO_FUNCx_IN_SEL is set to n(0<=n<40): it means GPIOn input is used for input signal x  if GPIO_FUNCx_IN_SEL is set to 0x38: the input signal x is set to 1   if GPIO_FUNCx_IN_SEL is set to 0x30: the input signal x is set to 0*/
        };
        unsigned int reg;
    } func_in_sel_cfg[256];
    union {
        struct {
            unsigned int func_sel:     9;               /*select one of the 256 output to 40 GPIO*/
            unsigned int inv_sel:      1;               /*invert the output value  if you want to revert the output value  setting the value to 1*/
            unsigned int oen_sel:      1;               /*weather using the logical oen signal or not using the value setting by the register*/
            unsigned int oen_inv_sel:  1;               /*invert the output enable value  if you want to revert the output enable value  setting the value to 1*/
            unsigned int reserved12:  20;               /*The 40 registers below are selection control for 40 GPIO output  if GPIO_FUNCx_OUT_SEL is set to n(0<=n<256): it means GPIOn input is used for output signal x  if GPIO_FUNCx_OUT_INV_SEL is set to 1  the output signal x is set to ~value.  if GPIO_FUNC0_OUT_SEL is 256 or GPIO_FUNC0_OEN_SEL is 1 using GPIO_ENABLE_DATA[x] for the enable value else using the signal enable*/
        };
        unsigned int reg;
    } func_out_sel_cfg[40];
} gpio_dev_t;

extern gpio_dev_t GPIO;


#ifdef __cplusplus
}
#endif

#endif
