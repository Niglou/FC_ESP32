
#ifndef H_NONOS_RMT_STRUCT
#define H_NONOS_RMT_STRUCT

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct {
    unsigned int fifo_ch[8];                                /*The R/W ram address for channel0-7 by apb fifo access.
                                                        Note that in some circumstances, data read from the FIFO may get lost. As RMT memory area accesses using the RMTMEM method do not have this issue
                                                        and provide all the functionality that the FIFO register has, it is encouraged to use that instead.*/
    struct{
        union {
            struct {
                unsigned int div_cnt:        8;             /*This register is used to configure the  frequency divider's factor in channel0-7.*/
                unsigned int idle_thres:    16;             /*In receive mode when no edge is detected on the input signal for longer than reg_idle_thres_ch0 then the receive process is done.*/
                unsigned int mem_size:       4;             /*This register is used to configure the the amount of memory blocks allocated to channel0-7.*/
                unsigned int carrier_en:     1;             /*This is the carrier modulation enable control bit for channel0-7.*/
                unsigned int carrier_out_lv: 1;             /*This bit is used to configure the way carrier wave is modulated for  channel0-7.1'b1:transmit on low output level  1'b0:transmit  on high output level.*/
                unsigned int mem_pd:         1;             /*This bit is used to reduce power consumed by memory. 1:memory is in low power state.*/
                unsigned int clk_en:         1;             /*This bit  is used  to control clock.when software configure RMT internal registers  it controls the register clock.*/
            };
            unsigned int val;
        } conf0;
        union {
            struct {
                unsigned int tx_start:        1;            /*Set this bit to start sending data for channel0-7.*/
                unsigned int rx_en:           1;            /*Set this bit to enable receiving data for channel0-7.*/
                unsigned int mem_wr_rst:      1;            /*Set this bit to reset write ram address for channel0-7 by receiver access.*/
                unsigned int mem_rd_rst:      1;            /*Set this bit to reset read ram address for channel0-7 by transmitter access.*/
                unsigned int apb_mem_rst:     1;            /*Set this bit to reset W/R ram address for channel0-7 by apb fifo access (using fifo is discouraged, please see the note above at data_ch[] item)*/
                unsigned int mem_owner:       1;            /*This is the mark of channel0-7's ram usage right.1'b1：receiver uses the ram  0：transmitter uses the ram*/
                unsigned int tx_conti_mode:   1;            /*Set this bit to continue sending  from the first data to the last data in channel0-7 again and again.*/
                unsigned int rx_filter_en:    1;            /*This is the receive filter enable bit for channel0-7.*/
                unsigned int rx_filter_thres: 8;            /*in receive mode  channel0-7 ignore input pulse when the pulse width is smaller then this value.*/
                unsigned int ref_cnt_rst:     1;            /*This bit is used to reset divider in channel0-7.*/
                unsigned int ref_always_on:   1;            /*This bit is used to select base clock. 1'b1:clk_apb  1'b0:clk_ref*/
                unsigned int idle_out_lv:     1;            /*This bit configures the output signal's level for channel0-7 in IDLE state.*/
                unsigned int idle_out_en:     1;            /*This is the output enable control bit for channel0-7 in IDLE state.*/
                unsigned int reserved20:     12;
            };
            unsigned int reg;
        } conf1;
    } conf_ch[8];
    unsigned int status_ch[8];                              /*The status for channel0-7*/
    unsigned int apb_mem_addr_ch[8];                        /*The ram relative address in channel0-7 by apb fifo access (using fifo is discouraged, please see the note above at data_ch[] item)*/
    union {
        struct {
            unsigned int ch0_tx_end:       1;               /*The interrupt raw bit for channel 0 turns to high level when the transmit process is done.*/
            unsigned int ch0_rx_end:       1;               /*The interrupt raw bit for channel 0 turns to high level when the receive process is done.*/
            unsigned int ch0_err:          1;               /*The interrupt raw bit for channel 0 turns to high level when channel 0 detects some errors.*/
            unsigned int ch1_tx_end:       1;               /*The interrupt raw bit for channel 1 turns to high level when the transmit process is done.*/
            unsigned int ch1_rx_end:       1;               /*The interrupt raw bit for channel 1 turns to high level when the receive process is done.*/
            unsigned int ch1_err:          1;               /*The interrupt raw bit for channel 1 turns to high level when channel 1 detects some errors.*/
            unsigned int ch2_tx_end:       1;               /*The interrupt raw bit for channel 2 turns to high level when the transmit process is done.*/
            unsigned int ch2_rx_end:       1;               /*The interrupt raw bit for channel 2 turns to high level when the receive process is done.*/
            unsigned int ch2_err:          1;               /*The interrupt raw bit for channel 2 turns to high level when channel 2 detects some errors.*/
            unsigned int ch3_tx_end:       1;               /*The interrupt raw bit for channel 3 turns to high level when the transmit process is done.*/
            unsigned int ch3_rx_end:       1;               /*The interrupt raw bit for channel 3 turns to high level when the receive process is done.*/
            unsigned int ch3_err:          1;               /*The interrupt raw bit for channel 3 turns to high level when channel 3 detects some errors.*/
            unsigned int ch4_tx_end:       1;               /*The interrupt raw bit for channel 4 turns to high level when the transmit process is done.*/
            unsigned int ch4_rx_end:       1;               /*The interrupt raw bit for channel 4 turns to high level when the receive process is done.*/
            unsigned int ch4_err:          1;               /*The interrupt raw bit for channel 4 turns to high level when channel 4 detects some errors.*/
            unsigned int ch5_tx_end:       1;               /*The interrupt raw bit for channel 5 turns to high level when the transmit process is done.*/
            unsigned int ch5_rx_end:       1;               /*The interrupt raw bit for channel 5 turns to high level when the receive process is done.*/
            unsigned int ch5_err:          1;               /*The interrupt raw bit for channel 5 turns to high level when channel 5 detects some errors.*/
            unsigned int ch6_tx_end:       1;               /*The interrupt raw bit for channel 6 turns to high level when the transmit process is done.*/
            unsigned int ch6_rx_end:       1;               /*The interrupt raw bit for channel 6 turns to high level when the receive process is done.*/
            unsigned int ch6_err:          1;               /*The interrupt raw bit for channel 6 turns to high level when channel 6 detects some errors.*/
            unsigned int ch7_tx_end:       1;               /*The interrupt raw bit for channel 7 turns to high level when the transmit process is done.*/
            unsigned int ch7_rx_end:       1;               /*The interrupt raw bit for channel 7 turns to high level when the receive process is done.*/
            unsigned int ch7_err:          1;               /*The interrupt raw bit for channel 7 turns to high level when channel 7 detects some errors.*/
            unsigned int ch0_tx_thr_event: 1;               /*The interrupt raw bit for channel 0 turns to high level when transmitter in channel0  have send data more than  reg_rmt_tx_lim_ch0  after detecting this interrupt  software can updata the old data with new data.*/
            unsigned int ch1_tx_thr_event: 1;               /*The interrupt raw bit for channel 1 turns to high level when transmitter in channel1  have send data more than  reg_rmt_tx_lim_ch1  after detecting this interrupt  software can updata the old data with new data.*/
            unsigned int ch2_tx_thr_event: 1;               /*The interrupt raw bit for channel 2 turns to high level when transmitter in channel2  have send data more than  reg_rmt_tx_lim_ch2  after detecting this interrupt  software can updata the old data with new data.*/
            unsigned int ch3_tx_thr_event: 1;               /*The interrupt raw bit for channel 3 turns to high level when transmitter in channel3  have send data more than  reg_rmt_tx_lim_ch3  after detecting this interrupt  software can updata the old data with new data.*/
            unsigned int ch4_tx_thr_event: 1;               /*The interrupt raw bit for channel 4 turns to high level when transmitter in channel4  have send data more than  reg_rmt_tx_lim_ch4  after detecting this interrupt  software can updata the old data with new data.*/
            unsigned int ch5_tx_thr_event: 1;               /*The interrupt raw bit for channel 5 turns to high level when transmitter in channel5  have send data more than  reg_rmt_tx_lim_ch5  after detecting this interrupt  software can updata the old data with new data.*/
            unsigned int ch6_tx_thr_event: 1;               /*The interrupt raw bit for channel 6 turns to high level when transmitter in channel6  have send data more than  reg_rmt_tx_lim_ch6  after detecting this interrupt  software can updata the old data with new data.*/
            unsigned int ch7_tx_thr_event: 1;               /*The interrupt raw bit for channel 7 turns to high level when transmitter in channel7  have send data more than  reg_rmt_tx_lim_ch7  after detecting this interrupt  software can updata the old data with new data.*/
        };
        unsigned int reg;
    } int_raw;
    union {
        struct {
            unsigned int ch0_tx_end:       1;                /*The interrupt  state bit for channel 0's mt_ch0_tx_end_int_raw when mt_ch0_tx_end_int_ena is set to 0.*/
            unsigned int ch0_rx_end:       1;                /*The interrupt  state bit for channel 0's rmt_ch0_rx_end_int_raw when  rmt_ch0_rx_end_int_ena is set to 0.*/
            unsigned int ch0_err:          1;                /*The interrupt  state bit for channel 0's rmt_ch0_err_int_raw when  rmt_ch0_err_int_ena is set to 0.*/
            unsigned int ch1_tx_end:       1;                /*The interrupt  state bit for channel 1's mt_ch1_tx_end_int_raw when mt_ch1_tx_end_int_ena is set to 1.*/
            unsigned int ch1_rx_end:       1;                /*The interrupt  state bit for channel 1's rmt_ch1_rx_end_int_raw when  rmt_ch1_rx_end_int_ena is set to 1.*/
            unsigned int ch1_err:          1;                /*The interrupt  state bit for channel 1's rmt_ch1_err_int_raw when  rmt_ch1_err_int_ena is set to 1.*/
            unsigned int ch2_tx_end:       1;                /*The interrupt  state bit for channel 2's mt_ch2_tx_end_int_raw when mt_ch2_tx_end_int_ena is set to 1.*/
            unsigned int ch2_rx_end:       1;                /*The interrupt  state bit for channel 2's rmt_ch2_rx_end_int_raw when  rmt_ch2_rx_end_int_ena is set to 1.*/
            unsigned int ch2_err:          1;                /*The interrupt  state bit for channel 2's rmt_ch2_err_int_raw when  rmt_ch2_err_int_ena is set to 1.*/
            unsigned int ch3_tx_end:       1;                /*The interrupt  state bit for channel 3's mt_ch3_tx_end_int_raw when mt_ch3_tx_end_int_ena is set to 1.*/
            unsigned int ch3_rx_end:       1;                /*The interrupt  state bit for channel 3's rmt_ch3_rx_end_int_raw when  rmt_ch3_rx_end_int_ena is set to 1.*/
            unsigned int ch3_err:          1;                /*The interrupt  state bit for channel 3's rmt_ch3_err_int_raw when  rmt_ch3_err_int_ena is set to 1.*/
            unsigned int ch4_tx_end:       1;                /*The interrupt  state bit for channel 4's mt_ch4_tx_end_int_raw when mt_ch4_tx_end_int_ena is set to 1.*/
            unsigned int ch4_rx_end:       1;                /*The interrupt  state bit for channel 4's rmt_ch4_rx_end_int_raw when  rmt_ch4_rx_end_int_ena is set to 1.*/
            unsigned int ch4_err:          1;                /*The interrupt  state bit for channel 4's rmt_ch4_err_int_raw when  rmt_ch4_err_int_ena is set to 1.*/
            unsigned int ch5_tx_end:       1;                /*The interrupt  state bit for channel 5's mt_ch5_tx_end_int_raw when mt_ch5_tx_end_int_ena is set to 1.*/
            unsigned int ch5_rx_end:       1;                /*The interrupt  state bit for channel 5's rmt_ch5_rx_end_int_raw when  rmt_ch5_rx_end_int_ena is set to 1.*/
            unsigned int ch5_err:          1;                /*The interrupt  state bit for channel 5's rmt_ch5_err_int_raw when  rmt_ch5_err_int_ena is set to 1.*/
            unsigned int ch6_tx_end:       1;                /*The interrupt  state bit for channel 6's mt_ch6_tx_end_int_raw when mt_ch6_tx_end_int_ena is set to 1.*/
            unsigned int ch6_rx_end:       1;                /*The interrupt  state bit for channel 6's rmt_ch6_rx_end_int_raw when  rmt_ch6_rx_end_int_ena is set to 1.*/
            unsigned int ch6_err:          1;                /*The interrupt  state bit for channel 6's rmt_ch6_err_int_raw when  rmt_ch6_err_int_ena is set to 1.*/
            unsigned int ch7_tx_end:       1;                /*The interrupt  state bit for channel 7's mt_ch7_tx_end_int_raw when mt_ch7_tx_end_int_ena is set to 1.*/
            unsigned int ch7_rx_end:       1;                /*The interrupt  state bit for channel 7's rmt_ch7_rx_end_int_raw when  rmt_ch7_rx_end_int_ena is set to 1.*/
            unsigned int ch7_err:          1;                /*The interrupt  state bit for channel 7's rmt_ch7_err_int_raw when  rmt_ch7_err_int_ena is set to 1.*/
            unsigned int ch0_tx_thr_event: 1;                /*The interrupt state bit  for channel 0's rmt_ch0_tx_thr_event_int_raw when mt_ch0_tx_thr_event_int_ena is set to 1.*/
            unsigned int ch1_tx_thr_event: 1;                /*The interrupt state bit  for channel 1's rmt_ch1_tx_thr_event_int_raw when mt_ch1_tx_thr_event_int_ena is set to 1.*/
            unsigned int ch2_tx_thr_event: 1;                /*The interrupt state bit  for channel 2's rmt_ch2_tx_thr_event_int_raw when mt_ch2_tx_thr_event_int_ena is set to 1.*/
            unsigned int ch3_tx_thr_event: 1;                /*The interrupt state bit  for channel 3's rmt_ch3_tx_thr_event_int_raw when mt_ch3_tx_thr_event_int_ena is set to 1.*/
            unsigned int ch4_tx_thr_event: 1;                /*The interrupt state bit  for channel 4's rmt_ch4_tx_thr_event_int_raw when mt_ch4_tx_thr_event_int_ena is set to 1.*/
            unsigned int ch5_tx_thr_event: 1;                /*The interrupt state bit  for channel 5's rmt_ch5_tx_thr_event_int_raw when mt_ch5_tx_thr_event_int_ena is set to 1.*/
            unsigned int ch6_tx_thr_event: 1;                /*The interrupt state bit  for channel 6's rmt_ch6_tx_thr_event_int_raw when mt_ch6_tx_thr_event_int_ena is set to 1.*/
            unsigned int ch7_tx_thr_event: 1;                /*The interrupt state bit  for channel 7's rmt_ch7_tx_thr_event_int_raw when mt_ch7_tx_thr_event_int_ena is set to 1.*/
        };
        unsigned int reg;
    } int_st;
    union {
        struct {
            unsigned int ch0_tx_end:       1;               /*Set this bit to enable rmt_ch0_tx_end_int_st.*/
            unsigned int ch0_rx_end:       1;               /*Set this bit to enable rmt_ch0_rx_end_int_st.*/
            unsigned int ch0_err:          1;               /*Set this bit to enable rmt_ch0_err_int_st.*/
            unsigned int ch1_tx_end:       1;               /*Set this bit to enable rmt_ch1_tx_end_int_st.*/
            unsigned int ch1_rx_end:       1;               /*Set this bit to enable rmt_ch1_rx_end_int_st.*/
            unsigned int ch1_err:          1;               /*Set this bit to enable rmt_ch1_err_int_st.*/
            unsigned int ch2_tx_end:       1;               /*Set this bit to enable rmt_ch2_tx_end_int_st.*/
            unsigned int ch2_rx_end:       1;               /*Set this bit to enable rmt_ch2_rx_end_int_st.*/
            unsigned int ch2_err:          1;               /*Set this bit to enable rmt_ch2_err_int_st.*/
            unsigned int ch3_tx_end:       1;               /*Set this bit to enable rmt_ch3_tx_end_int_st.*/
            unsigned int ch3_rx_end:       1;               /*Set this bit to enable rmt_ch3_rx_end_int_st.*/
            unsigned int ch3_err:          1;               /*Set this bit to enable rmt_ch3_err_int_st.*/
            unsigned int ch4_tx_end:       1;               /*Set this bit to enable rmt_ch4_tx_end_int_st.*/
            unsigned int ch4_rx_end:       1;               /*Set this bit to enable rmt_ch4_rx_end_int_st.*/
            unsigned int ch4_err:          1;               /*Set this bit to enable rmt_ch4_err_int_st.*/
            unsigned int ch5_tx_end:       1;               /*Set this bit to enable rmt_ch5_tx_end_int_st.*/
            unsigned int ch5_rx_end:       1;               /*Set this bit to enable rmt_ch5_rx_end_int_st.*/
            unsigned int ch5_err:          1;               /*Set this bit to enable rmt_ch5_err_int_st.*/
            unsigned int ch6_tx_end:       1;               /*Set this bit to enable rmt_ch6_tx_end_int_st.*/
            unsigned int ch6_rx_end:       1;               /*Set this bit to enable rmt_ch6_rx_end_int_st.*/
            unsigned int ch6_err:          1;               /*Set this bit to enable rmt_ch6_err_int_st.*/
            unsigned int ch7_tx_end:       1;               /*Set this bit to enable rmt_ch7_tx_end_int_st.*/
            unsigned int ch7_rx_end:       1;               /*Set this bit to enable rmt_ch7_rx_end_int_st.*/
            unsigned int ch7_err:          1;               /*Set this bit to enable rmt_ch7_err_int_st.*/
            unsigned int ch0_tx_thr_event: 1;               /*Set this bit to enable rmt_ch0_tx_thr_event_int_st.*/
            unsigned int ch1_tx_thr_event: 1;               /*Set this bit to enable rmt_ch1_tx_thr_event_int_st.*/
            unsigned int ch2_tx_thr_event: 1;               /*Set this bit to enable rmt_ch2_tx_thr_event_int_st.*/
            unsigned int ch3_tx_thr_event: 1;               /*Set this bit to enable rmt_ch3_tx_thr_event_int_st.*/
            unsigned int ch4_tx_thr_event: 1;               /*Set this bit to enable rmt_ch4_tx_thr_event_int_st.*/
            unsigned int ch5_tx_thr_event: 1;               /*Set this bit to enable rmt_ch5_tx_thr_event_int_st.*/
            unsigned int ch6_tx_thr_event: 1;               /*Set this bit to enable rmt_ch6_tx_thr_event_int_st.*/
            unsigned int ch7_tx_thr_event: 1;               /*Set this bit to enable rmt_ch7_tx_thr_event_int_st.*/
        };
        unsigned int reg;
    } int_ena;
    union {
        struct {
            unsigned int ch0_tx_end:       1;               /*Set this bit to clear the rmt_ch0_rx_end_int_raw..*/
            unsigned int ch0_rx_end:       1;               /*Set this bit to clear the rmt_ch0_tx_end_int_raw.*/
            unsigned int ch0_err:          1;               /*Set this bit to clear the  rmt_ch0_err_int_raw.*/
            unsigned int ch1_tx_end:       1;               /*Set this bit to clear the rmt_ch1_rx_end_int_raw..*/
            unsigned int ch1_rx_end:       1;               /*Set this bit to clear the rmt_ch1_tx_end_int_raw.*/
            unsigned int ch1_err:          1;               /*Set this bit to clear the  rmt_ch1_err_int_raw.*/
            unsigned int ch2_tx_end:       1;               /*Set this bit to clear the rmt_ch2_rx_end_int_raw..*/
            unsigned int ch2_rx_end:       1;               /*Set this bit to clear the rmt_ch2_tx_end_int_raw.*/
            unsigned int ch2_err:          1;               /*Set this bit to clear the  rmt_ch2_err_int_raw.*/
            unsigned int ch3_tx_end:       1;               /*Set this bit to clear the rmt_ch3_rx_end_int_raw..*/
            unsigned int ch3_rx_end:       1;               /*Set this bit to clear the rmt_ch3_tx_end_int_raw.*/
            unsigned int ch3_err:          1;               /*Set this bit to clear the  rmt_ch3_err_int_raw.*/
            unsigned int ch4_tx_end:       1;               /*Set this bit to clear the rmt_ch4_rx_end_int_raw..*/
            unsigned int ch4_rx_end:       1;               /*Set this bit to clear the rmt_ch4_tx_end_int_raw.*/
            unsigned int ch4_err:          1;               /*Set this bit to clear the  rmt_ch4_err_int_raw.*/
            unsigned int ch5_tx_end:       1;               /*Set this bit to clear the rmt_ch5_rx_end_int_raw..*/
            unsigned int ch5_rx_end:       1;               /*Set this bit to clear the rmt_ch5_tx_end_int_raw.*/
            unsigned int ch5_err:          1;               /*Set this bit to clear the  rmt_ch5_err_int_raw.*/
            unsigned int ch6_tx_end:       1;               /*Set this bit to clear the rmt_ch6_rx_end_int_raw..*/
            unsigned int ch6_rx_end:       1;               /*Set this bit to clear the rmt_ch6_tx_end_int_raw.*/
            unsigned int ch6_err:          1;               /*Set this bit to clear the  rmt_ch6_err_int_raw.*/
            unsigned int ch7_tx_end:       1;               /*Set this bit to clear the rmt_ch7_rx_end_int_raw..*/
            unsigned int ch7_rx_end:       1;               /*Set this bit to clear the rmt_ch7_tx_end_int_raw.*/
            unsigned int ch7_err:          1;               /*Set this bit to clear the  rmt_ch7_err_int_raw.*/
            unsigned int ch0_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch0_tx_thr_event_int_raw interrupt.*/
            unsigned int ch1_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch1_tx_thr_event_int_raw interrupt.*/
            unsigned int ch2_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch2_tx_thr_event_int_raw interrupt.*/
            unsigned int ch3_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch3_tx_thr_event_int_raw interrupt.*/
            unsigned int ch4_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch4_tx_thr_event_int_raw interrupt.*/
            unsigned int ch5_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch5_tx_thr_event_int_raw interrupt.*/
            unsigned int ch6_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch6_tx_thr_event_int_raw interrupt.*/
            unsigned int ch7_tx_thr_event: 1;               /*Set this bit to clear the  rmt_ch7_tx_thr_event_int_raw interrupt.*/
        };
        unsigned int reg;
    } int_clr;
    union {
        struct {
            unsigned int low: 16;                           /*This register is used to configure carrier wave's low level value for channel0-7.*/
            unsigned int high:16;                           /*This register is used to configure carrier wave's high level value for channel0-7.*/
        };
        unsigned int reg;
    } carrier_duty_ch[8];
    union {
        struct {
            unsigned int limit: 9;                          /*When channel0-7 sends more than reg_rmt_tx_lim_ch0 data then channel0-7 produce the relative interrupt.*/
            unsigned int reserved9: 23;
        };
        unsigned int reg;
    } tx_lim_ch[8];
    union {
        struct {
            unsigned int mem_access_en:  1;                     /*Set this bit to enable RMTMEM and disable apb fifo access (using fifo is discouraged, please see the note above at data_ch[] item)*/
            unsigned int mem_tx_wrap_en: 1;                 /*when data need to be send is more than channel's mem can store  then set this bit to enable reuse of mem this bit is used together with reg_rmt_tx_lim_chn.*/
            unsigned int reserved2:     30;
        };
        unsigned int reg;
    } apb_conf;
    unsigned int reserved_f4;
    unsigned int reserved_f8;
    unsigned int date;                                      /*This is the version register.*/
} rmt;


typedef volatile struct {
    struct {
        union {
            struct {
                unsigned int duration0 :15;
                unsigned int level0 :1;
                unsigned int duration1 :15;
                unsigned int level1 :1;
            };
            unsigned int reg;
        } data[64];
    } ch[8];
} rmt_ram;

extern rmt RMT; /* PROVIDE( RMT = 0x3ff56000); in esp32.peripherals.ld */
extern rmt_ram RMTMEM; /* PROVIDE( RMT = 0x3FF56800); in esp32.peripherals.ld */

#ifdef __cplusplus
}
#endif

#endif  /* H_NONOS_RMT_STRUCT */
