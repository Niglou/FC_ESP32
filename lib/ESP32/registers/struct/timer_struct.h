#ifndef H_NONOS_TIMER_STRUCT
#define H_NONOS_TIMER_STRUCT

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct timg_dev_s {
    struct{
        union {
            struct {
                unsigned int reserved0:   10;
                unsigned int alarm_en:     1;             /*When set  alarm is enabled*/
                unsigned int level_int_en: 1;             /*When set  level type interrupt will be generated during alarm*/
                unsigned int edge_int_en:  1;             /*When set  edge type interrupt will be generated during alarm*/
                unsigned int divider:     16;             /*Timer clock (T0/1_clk) pre-scale value.*/
                unsigned int autoreload:   1;             /*When set  timer 0/1 auto-reload at alarming is enabled*/
                unsigned int increase:     1;             /*When set  timer 0/1 time-base counter increment. When cleared timer 0 time-base counter decrement.*/
                unsigned int enable:       1;             /*When set  timer 0/1 time-base counter is enabled*/
            };
            unsigned int reg;
        } config;
        unsigned int cnt_low;                             /*Register to store timer 0/1 time-base counter current value lower 32 bits.*/
        unsigned int cnt_high;                            /*Register to store timer 0 time-base counter current value higher 32 bits.*/
        unsigned int update;                              /*Write any value will trigger a timer 0 time-base counter value update (timer 0 current value will be stored in registers above)*/
        unsigned int alarm_low;                           /*Timer 0 time-base counter value lower 32 bits that will trigger the alarm*/
        unsigned int alarm_high;                          /*Timer 0 time-base counter value higher 32 bits that will trigger the alarm*/
        unsigned int load_low;                            /*Lower 32 bits of the value that will load into timer 0 time-base counter*/
        unsigned int load_high;                           /*higher 32 bits of the value that will load into timer 0 time-base counter*/
        unsigned int reload;                              /*Write any value will trigger timer 0 time-base counter reload*/
    } hw_timer[2];
    union {
        struct {
            unsigned int reserved0:       14;
            unsigned int flashboot_mod_en: 1;             /*When set  flash boot protection is enabled*/
            unsigned int sys_reset_length: 3;             /*length of system reset selection. 0: 100ns  1: 200ns  2: 300ns  3: 400ns  4: 500ns  5: 800ns  6: 1.6us  7: 3.2us*/
            unsigned int cpu_reset_length: 3;             /*length of CPU reset selection. 0: 100ns  1: 200ns  2: 300ns  3: 400ns  4: 500ns  5: 800ns  6: 1.6us  7: 3.2us*/
            unsigned int level_int_en:     1;             /*When set  level type interrupt generation is enabled*/
            unsigned int edge_int_en:      1;             /*When set  edge type interrupt generation is enabled*/
            unsigned int stg3:             2;             /*Stage 3 configuration. 0: off  1: interrupt  2: reset CPU  3: reset system*/
            unsigned int stg2:             2;             /*Stage 2 configuration. 0: off  1: interrupt  2: reset CPU  3: reset system*/
            unsigned int stg1:             2;             /*Stage 1 configuration. 0: off  1: interrupt  2: reset CPU  3: reset system*/
            unsigned int stg0:             2;             /*Stage 0 configuration. 0: off  1: interrupt  2: reset CPU  3: reset system*/
            unsigned int en:               1;             /*When set  SWDT is enabled*/
        };
        unsigned int reg;
    } wdt_config0;
    union {
        struct {
            unsigned int reserved0:       16;
            unsigned int clk_prescale:16;             /*SWDT clock prescale value. Period = 12.5ns * value stored in this register*/
        };
        unsigned int reg;
    } wdt_config1;
    unsigned int wdt_config2;                             /*Stage 0 timeout value in SWDT clock cycles*/
    unsigned int wdt_config3;                             /*Stage 1 timeout value in SWDT clock cycles*/
    unsigned int wdt_config4;                             /*Stage 2 timeout value in SWDT clock cycles*/
    unsigned int wdt_config5;                             /*Stage 3 timeout value in SWDT clock cycles*/
    unsigned int wdt_feed;                                /*Write any value will feed SWDT*/
    unsigned int wdt_wprotect;                            /*If change its value from default  then write protection is on.*/
    union {
        struct {
            unsigned int reserved0:             12;
            unsigned int start_cycling: 1;
            unsigned int clk_sel:       2;
            unsigned int rdy:           1;
            unsigned int max:          15;
            unsigned int start:         1;
        };
        unsigned int reg;
    } rtc_cali_cfg;
    union {
        struct {
            unsigned int reserved0:      7;
            unsigned int value:25;
        };
        unsigned int reg;
    } rtc_cali_cfg1;
    union {
        struct {
            unsigned int reserved0:         7;
            unsigned int rtc_only:     1;
            unsigned int cpst_en:      1;
            unsigned int lac_en:       1;
            unsigned int alarm_en:     1;
            unsigned int level_int_en: 1;
            unsigned int edge_int_en:  1;
            unsigned int divider:     16;
            unsigned int autoreload:   1;
            unsigned int increase:     1;
            unsigned int en:           1;
        };
        unsigned int reg;
    } lactconfig;
    union {
        struct {
            unsigned int reserved0:         6;
            unsigned int step_len:26;
        };
        unsigned int reg;
    } lactrtc;
    unsigned int lactlo;                                  /**/
    unsigned int lacthi;                                  /**/
    unsigned int lactupdate;                              /**/
    unsigned int lactalarmlo;                             /**/
    unsigned int lactalarmhi;                             /**/
    unsigned int lactloadlo;                              /**/
    unsigned int lactloadhi;                              /**/
    unsigned int lactload;                                /**/
    union {
        struct {
            unsigned int t0:         1;                   /*interrupt when timer0 alarm*/
            unsigned int t1:         1;                   /*interrupt when timer1 alarm*/
            unsigned int wdt:        1;                   /*Interrupt when an interrupt stage timeout*/
            unsigned int lact:       1;
            unsigned int reserved4: 28;
        };
        unsigned int reg;
    } int_ena;
    union {
        struct {
            unsigned int t0:        1;                    /*interrupt when timer0 alarm*/
            unsigned int t1:        1;                    /*interrupt when timer1 alarm*/
            unsigned int wdt:       1;                    /*Interrupt when an interrupt stage timeout*/
            unsigned int lact:      1;
            unsigned int reserved4:28;
        };
        unsigned int reg;
    } int_raw;
    union {
        struct {
            unsigned int t0:         1;                   /*interrupt when timer0 alarm*/
            unsigned int t1:         1;                   /*interrupt when timer1 alarm*/
            unsigned int wdt:        1;                   /*Interrupt when an interrupt stage timeout*/
            unsigned int lact:       1;
            unsigned int reserved4: 28;
        };
        unsigned int reg;
    } int_st_timers;
    union {
        struct {
            unsigned int t0:         1;                   /*interrupt when timer0 alarm*/
            unsigned int t1:         1;                   /*interrupt when timer1 alarm*/
            unsigned int wdt:        1;                   /*Interrupt when an interrupt stage timeout*/
            unsigned int lact:       1;
            unsigned int reserved4: 28;
        };
        unsigned int reg;
    } int_clr_timers;
    unsigned int reserved_a8;
    unsigned int reserved_ac;
    unsigned int reserved_b0;
    unsigned int reserved_b4;
    unsigned int reserved_b8;
    unsigned int reserved_bc;
    unsigned int reserved_c0;
    unsigned int reserved_c4;
    unsigned int reserved_c8;
    unsigned int reserved_cc;
    unsigned int reserved_d0;
    unsigned int reserved_d4;
    unsigned int reserved_d8;
    unsigned int reserved_dc;
    unsigned int reserved_e0;
    unsigned int reserved_e4;
    unsigned int reserved_e8;
    unsigned int reserved_ec;
    unsigned int reserved_f0;
    unsigned int reserved_f4;
    union {
        struct {
            unsigned int date:28;                         /*Version of this regfile*/
            unsigned int reserved28:   4;
        };
        unsigned int reg;
    } timg_date;
    union {
        struct {
            unsigned int reserved0: 31;
            unsigned int en:     1;                   /*Force clock enable for this regfile*/
        };
        unsigned int reg;
    } clk;
} timg_dev_t;

extern timg_dev_t TIMERG0;
extern timg_dev_t TIMERG1;

#ifdef __cplusplus
}
#endif

#endif  /* H_NONOS_TIMER_STRUCT */
