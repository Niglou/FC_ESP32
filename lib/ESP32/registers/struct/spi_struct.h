#ifndef H_NONOS_SPI_STRUCT
#define H_NONOS_SPI_STRUCT

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct spi_dev_s {
    union {
        struct {
            unsigned int reserved0: 16;                         /*reserved*/
            unsigned int flash_per:  1;                         /*program erase resume bit  program erase suspend operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_pes:  1;                         /*program erase suspend bit  program erase suspend operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int usr:        1;                         /*User define command enable.  An operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_hpm:  1;                         /*Drive Flash into high performance mode.  The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_res:  1;                         /*This bit combined with reg_resandres bit releases Flash from the power-down state or high performance mode and obtains the devices ID. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_dp:   1;                         /*Drive Flash into power down.  An operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_ce:   1;                         /*Chip erase enable. Chip erase operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_be:   1;                         /*Block erase enable(32KB) .  Block erase operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_se:   1;                         /*Sector erase enable(4KB). Sector erase operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_pp:   1;                         /*Page program enable(1 byte ~256 bytes data to be programmed). Page program operation  will be triggered when the bit is set. The bit will be cleared once the operation done .1: enable 0: disable.*/
            unsigned int flash_wrsr: 1;                         /*Write status register enable.   Write status operation  will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_rdsr: 1;                         /*Read status register-1.  Read status operation will be triggered when the bit is set. The bit will be cleared once the operation done.1: enable 0: disable.*/
            unsigned int flash_rdid: 1;                         /*Read JEDEC ID . Read ID command will be sent when the bit is set. The bit will be cleared once the operation done. 1: enable 0: disable.*/
            unsigned int flash_wrdi: 1;                         /*Write flash disable. Write disable command will be sent when the bit is set. The bit will be cleared once the operation done. 1: enable 0: disable.*/
            unsigned int flash_wren: 1;                         /*Write flash enable.  Write enable command will be sent when the bit is set. The bit will be cleared once the operation done. 1: enable 0: disable.*/
            unsigned int flash_read: 1;                         /*Read flash enable. Read flash operation will be triggered when the bit is set. The bit will be cleared once the operation done. 1: enable 0: disable.*/
        };
        unsigned int reg;
    } cmd;
    unsigned int addr;                                          /*addr to slave / from master. SPI transfer from the MSB to the LSB. If length > 32 bits, then address continues from MSB of slv_wr_status.*/
    union {
        struct {
            unsigned int reserved0:         10;                 /*reserved*/
            unsigned int fcs_crc_en:         1;                 /*For SPI1  initialize crc32 module before writing encrypted data to flash. Active low.*/
            unsigned int tx_crc_en:          1;                 /*For SPI1  enable crc32 when writing encrypted data to flash. 1: enable  0:disable*/
            unsigned int wait_flash_idle_en: 1;                 /*wait flash idle when program flash or erase flash. 1: enable 0: disable.*/
            unsigned int fastrd_mode:        1;                 /*This bit enable the bits: spi_fread_qio  spi_fread_dio  spi_fread_qout and spi_fread_dout. 1: enable 0: disable.*/
            unsigned int fread_dual:         1;                 /*In the read operations  read-data phase apply 2 signals. 1: enable 0: disable.*/
            unsigned int resandres:          1;                 /*The Device ID is read out to SPI_RD_STATUS register, this bit combine with spi_flash_res bit. 1: enable 0: disable.*/
            unsigned int reserved16:         4;                 /*reserved*/
            unsigned int fread_quad:         1;                 /*In the read operations read-data phase apply 4 signals. 1: enable 0: disable.*/
            unsigned int wp:                 1;                 /*Write protect signal output when SPI is idle.  1: output high  0: output low.*/
            unsigned int wrsr_2b:            1;                 /*two bytes data will be written to status register when it is set. 1: enable 0: disable.*/
            unsigned int fread_dio:          1;                 /*In the read operations address phase and read-data phase apply 2 signals. 1: enable 0: disable.*/
            unsigned int fread_qio:          1;                 /*In the read operations address phase and read-data phase apply 4 signals. 1: enable 0: disable.*/
            unsigned int rd_bit_order:       1;                 /*In read-data (MISO) phase 1: LSB first 0: MSB first*/
            unsigned int wr_bit_order:       1;                 /*In command address write-data (MOSI) phases 1: LSB firs 0: MSB first*/
            unsigned int reserved27:         5;                 /*reserved*/
        };
        unsigned int reg;
    } ctrl;
    union {
        struct {
            unsigned int reserved0:        16;                  /*reserved*/
            unsigned int cs_hold_delay_res:12;                  /*Delay cycles of resume Flash when resume Flash is enable by spi clock.*/
            unsigned int cs_hold_delay:     4;                  /*SPI cs signal is delayed by spi clock cycles*/
        };
        unsigned int reg;
    } ctrl1;
    union {
        struct {
            unsigned int status:    16;                         /*In the slave mode, it is the status for master to read out.*/
            unsigned int wb_mode:    8;                         /*Mode bits in the flash fast read mode, it is combined with spi_fastrd_mode bit.*/
            unsigned int status_ext: 8;                         /*In the slave mode,it is the status for master to read out.*/
        };
        unsigned int reg;
    } rd_status;
    union {
        struct {
            unsigned int setup_time:       4;                   /*(cycles-1) of ,prepare, phase by spi clock, this bits combined with spi_cs_setup bit.*/
            unsigned int hold_time:        4;                   /*delay cycles of cs pin by spi clock, this bits combined with spi_cs_hold bit.*/
            unsigned int ck_out_low_mode:  4;                   /*modify spi clock duty ratio when the value is lager than 8, the bits are combined with spi_clkcnt_N bits and spi_clkcnt_L bits.*/
            unsigned int ck_out_high_mode: 4;                   /*modify spi clock duty ratio when the value is lager than 8, the bits are combined with spi_clkcnt_N bits and spi_clkcnt_H bits.*/
            unsigned int miso_delay_mode:  2;                   /*MISO signals are delayed by spi_clk. 0: zero  1: if spi_ck_out_edge or spi_ck_i_edge is set 1  delayed by half cycle    else delayed by one cycle  2: if spi_ck_out_edge or spi_ck_i_edge is set 1  delayed by one cycle  else delayed by half cycle  3: delayed one cycle*/
            unsigned int miso_delay_num:   3;                   /*MISO signals are delayed by system clock cycles*/
            unsigned int mosi_delay_mode:  2;                   /*MOSI signals are delayed by spi_clk. 0: zero  1: if spi_ck_out_edge or spi_ck_i_edge is set 1  delayed by half cycle    else delayed by one cycle  2: if spi_ck_out_edge or spi_ck_i_edge is set 1  delayed by one cycle  else delayed by half cycle  3: delayed one cycle*/
            unsigned int mosi_delay_num:   3;                   /*MOSI signals are delayed by system clock cycles*/
            unsigned int cs_delay_mode:    2;                   /*spi_cs signal is delayed by spi_clk . 0: zero  1: if spi_ck_out_edge or spi_ck_i_edge is set 1  delayed by half cycle    else delayed by one cycle  2: if spi_ck_out_edge or spi_ck_i_edge is set 1  delayed by one cycle   else delayed by half cycle  3: delayed one cycle*/
            unsigned int cs_delay_num:     4;                   /*spi_cs signal is delayed by system clock cycles*/
        };
        unsigned int reg;
    } ctrl2;
    union {
        struct {
            unsigned int clkcnt_l:       6;                     /*In the master mode it must be equal to spi_clkcnt_N. In the slave mode it must be 0.*/
            unsigned int clkcnt_h:       6;                     /*In the master mode it must be floor((spi_clkcnt_N+1)/2-1). In the slave mode it must be 0.*/
            unsigned int clkcnt_n:       6;                     /*In the master mode it is the divider of spi_clk. So spi_clk frequency is system/(spi_clkdiv_pre+1)/(spi_clkcnt_N+1)*/
            unsigned int clkdiv_pre:    13;                     /*In the master mode it is pre-divider of spi_clk.*/
            unsigned int clk_equ_sysclk: 1;                     /*In the master mode 1: spi_clk is eqaul to system 0: spi_clk is divided from system clock.*/
        };
        unsigned int reg;
    } clock;
    union {
        struct {
            unsigned int doutdin:           1;                  /*Set the bit to enable full duplex communication. 1: enable 0: disable.*/
            unsigned int reserved1:         3;                  /*reserved*/
            unsigned int cs_hold:           1;                  /*spi cs keep low when spi is in ,done, phase. 1: enable 0: disable.*/
            unsigned int cs_setup:          1;                  /*spi cs is enable when spi is in ,prepare, phase. 1: enable 0: disable.*/
            unsigned int ck_i_edge:         1;                  /*In the slave mode  the bit is same as spi_ck_out_edge in master mode. It is combined with  spi_miso_delay_mode bits.*/
            unsigned int ck_out_edge:       1;                  /*the bit combined with spi_mosi_delay_mode bits to set mosi signal delay mode.*/
            unsigned int reserved8:         2;                  /*reserved*/
            unsigned int rd_byte_order:     1;                  /*In read-data (MISO) phase 1: big-endian 0: little_endian*/
            unsigned int wr_byte_order:     1;                  /*In command address write-data (MOSI) phases 1: big-endian 0: litte_endian*/
            unsigned int fwrite_dual:       1;                  /*In the write operations read-data phase apply 2 signals*/
            unsigned int fwrite_quad:       1;                  /*In the write operations read-data phase apply 4 signals*/
            unsigned int fwrite_dio:        1;                  /*In the write operations address phase and read-data phase apply 2 signals.*/
            unsigned int fwrite_qio:        1;                  /*In the write operations address phase and read-data phase apply 4 signals.*/
            unsigned int sio:               1;                  /*Set the bit to enable 3-line half duplex communication  mosi and miso signals share the same pin. 1: enable 0: disable.*/
            unsigned int usr_hold_pol:      1;                  /*It is combined with hold bits to set the polarity of spi hold line  1: spi will be held when spi hold line is high  0: spi will be held when spi hold line is low*/
            unsigned int usr_dout_hold:     1;                  /*spi is hold at data out state  the bit combined with spi_usr_hold_pol bit.*/
            unsigned int usr_din_hold:      1;                  /*spi is hold at data in state  the bit combined with spi_usr_hold_pol bit.*/
            unsigned int usr_dummy_hold:    1;                  /*spi is hold at dummy state  the bit combined with spi_usr_hold_pol bit.*/
            unsigned int usr_addr_hold:     1;                  /*spi is hold at address state  the bit combined with spi_usr_hold_pol bit.*/
            unsigned int usr_cmd_hold:      1;                  /*spi is hold at command state  the bit combined with spi_usr_hold_pol bit.*/
            unsigned int usr_prep_hold:     1;                  /*spi is hold at prepare state  the bit combined with spi_usr_hold_pol bit.*/
            unsigned int usr_miso_highpart: 1;                  /*read-data phase only access to high-part of the buffer spi_w8~spi_w15. 1: enable 0: disable.*/
            unsigned int usr_mosi_highpart: 1;                  /*write-data phase only access to high-part of the buffer spi_w8~spi_w15. 1: enable 0: disable.*/
            unsigned int usr_dummy_idle:    1;                  /*spi clock is disable in dummy phase when the bit is enable.*/
            unsigned int usr_mosi:          1;                  /*This bit enable the write-data phase of an operation.*/
            unsigned int usr_miso:          1;                  /*This bit enable the read-data phase of an operation.*/
            unsigned int usr_dummy:         1;                  /*This bit enable the dummy phase of an operation.*/
            unsigned int usr_addr:          1;                  /*This bit enable the address phase of an operation.*/
            unsigned int usr_command:       1;                  /*This bit enable the command phase of an operation.*/
        };
        unsigned int reg;
    } user;
    union {
        struct {
            unsigned int usr_dummy_cyclelen: 8;                 /*The length in spi_clk cycles of dummy phase. The register value shall be (cycle_num-1).*/
            unsigned int reserved8:         18;                 /*reserved*/
            unsigned int usr_addr_bitlen:    6;                 /*The length in bits of address phase. The register value shall be (bit_num-1).*/
        };
        unsigned int reg;
    } user1;
    union {
        struct {
            unsigned int usr_command_value: 16;                 /*The value of  command. Output sequence: bit 7-0 and then 15-8.*/
            unsigned int reserved16:        12;                 /*reserved*/
            unsigned int usr_command_bitlen: 4;                 /*The length in bits of command phase. The register value shall be (bit_num-1)*/
        };
        unsigned int reg;
    } user2;
    union {
        struct {
            unsigned int usr_mosi_dbitlen:24;                   /*The length in bits of write-data. The register value shall be (bit_num-1).*/
            unsigned int reserved24:       8;                   /*reserved*/
        };
        unsigned int reg;
    } mosi_dlen;
    union {
        struct {
            unsigned int usr_miso_dbitlen:24;                   /*The length in bits of  read-data. The register value shall be (bit_num-1).*/
            unsigned int reserved24:       8;                   /*reserved*/
        };
        unsigned int reg;
    } miso_dlen;
    unsigned int slv_wr_status;                                 /*In the slave mode this register are the status register for the master to write into. In the master mode this register are the higher 32bits in the 64 bits address condition.*/
    union {
        struct {
            unsigned int cs0_dis:        1;                     /*SPI CS0 pin enable, 1: disable CS0, 0: spi_cs0 signal is from/to CS0 pin*/
            unsigned int cs1_dis:        1;                     /*SPI CS1 pin enable, 1: disable CS1, 0: spi_cs1 signal is from/to CS1 pin*/
            unsigned int cs2_dis:        1;                     /*SPI CS2 pin enable, 1: disable CS2, 0: spi_cs2 signal is from/to CS2 pin*/
            unsigned int reserved3:      2;                     /*reserved*/
            unsigned int ck_dis:         1;                     /*1: spi clk out disable  0: spi clk out enable*/
            unsigned int master_cs_pol:  3;                     /*In the master mode  the bits are the polarity of spi cs line  the value is equivalent to spi_cs ^ spi_master_cs_pol.*/
            unsigned int reserved9:      2;                     /*reserved*/
            unsigned int master_ck_sel:  3;                     /*In the master mode  spi cs line is enable as spi clk  it is combined with spi_cs0_dis spi_cs1_dis spi_cs2_dis.*/
            unsigned int reserved14:    15;                     /*reserved*/
            unsigned int ck_idle_edge:   1;                     /*1: spi clk line is high when idle     0: spi clk line is low when idle*/
            unsigned int cs_keep_active: 1;                     /*spi cs line keep low when the bit is set.*/
            unsigned int reserved31:     1;                     /*reserved*/
        };
        unsigned int reg;
    } pin;
    union {
        struct {
            unsigned int rd_buf_done:  1;                       /*The interrupt raw bit for the completion of read-buffer operation in the slave mode.*/
            unsigned int wr_buf_done:  1;                       /*The interrupt raw bit for the completion of write-buffer operation in the slave mode.*/
            unsigned int rd_sta_done:  1;                       /*The interrupt raw bit for the completion of read-status operation in the slave mode.*/
            unsigned int wr_sta_done:  1;                       /*The interrupt raw bit for the completion of write-status operation in the slave mode.*/
            unsigned int trans_done:   1;                       /*The interrupt raw bit for the completion of any operation in both the master mode and the slave mode.*/
            unsigned int rd_buf_inten: 1;                       /*The interrupt enable bit for the completion of read-buffer operation in the slave mode.*/
            unsigned int wr_buf_inten: 1;                       /*The interrupt enable bit for the completion of write-buffer operation in the slave mode.*/
            unsigned int rd_sta_inten: 1;                       /*The interrupt enable bit for the completion of read-status operation in the slave mode.*/
            unsigned int wr_sta_inten: 1;                       /*The interrupt enable bit for the completion of write-status operation in the slave mode.*/
            unsigned int trans_inten:  1;                       /*The interrupt enable bit for the completion of any operation in both the master mode and the slave mode.*/
            unsigned int cs_i_mode:    2;                       /*In the slave mode  this bits used to synchronize the input spi cs signal and eliminate spi cs  jitter.*/
            unsigned int reserved12:   5;                       /*reserved*/
            unsigned int last_command: 3;                       /*In the slave mode it is the value of command.*/
            unsigned int last_state:   3;                       /*In the slave mode it is the state of spi state machine.*/
            unsigned int trans_cnt:    4;                       /*The operations counter in both the master mode and the slave mode. 4: read-status*/
            unsigned int cmd_define:   1;                       /*1: slave mode commands are defined in SPI_SLAVE3.  0: slave mode commands are fixed as: 1: write-status 2: write-buffer and 3: read-buffer.*/
            unsigned int wr_rd_sta_en: 1;                       /*write and read status enable  in the slave mode*/
            unsigned int wr_rd_buf_en: 1;                       /*write and read buffer enable in the slave mode*/
            unsigned int slave_mode:   1;                       /*1: slave mode 0: master mode.*/
            unsigned int sync_reset:   1;                       /*Software reset enable, reset the spi clock line cs line and data lines.*/
        };
        unsigned int reg;
    } slave;
    union {
        struct {
            unsigned int rdbuf_dummy_en:  1;                    /*In the slave mode it is the enable bit of dummy phase for read-buffer operations.*/
            unsigned int wrbuf_dummy_en:  1;                    /*In the slave mode it is the enable bit of dummy phase for write-buffer operations.*/
            unsigned int rdsta_dummy_en:  1;                    /*In the slave mode it is the enable bit of dummy phase for read-status operations.*/
            unsigned int wrsta_dummy_en:  1;                    /*In the slave mode it is the enable bit of dummy phase for write-status operations.*/
            unsigned int wr_addr_bitlen:  6;                    /*In the slave mode it is the address length in bits for write-buffer operation. The register value shall be (bit_num-1).*/
            unsigned int rd_addr_bitlen:  6;                    /*In the slave mode it is the address length in bits for read-buffer operation. The register value shall be (bit_num-1).*/
            unsigned int reserved16:      9;                    /*reserved*/
            unsigned int status_readback: 1;                    /*In the slave mode  1:read register of SPI_SLV_WR_STATUS  0: read register of SPI_RD_STATUS.*/
            unsigned int status_fast_en:  1;                    /*In the slave mode enable fast read status.*/
            unsigned int status_bitlen:   5;                    /*In the slave mode it is the length of status bit.*/
        };
        unsigned int reg;
    } slave1;
    union {
        struct {
            unsigned int rdsta_dummy_cyclelen: 8;               /*In the slave mode it is the length in spi_clk cycles of dummy phase for read-status operations. The register value shall be (cycle_num-1).*/
            unsigned int wrsta_dummy_cyclelen: 8;               /*In the slave mode it is the length in spi_clk cycles of dummy phase for write-status operations. The register value shall be (cycle_num-1).*/
            unsigned int rdbuf_dummy_cyclelen: 8;               /*In the slave mode it is the length in spi_clk cycles of dummy phase for read-buffer operations. The register value shall be (cycle_num-1).*/
            unsigned int wrbuf_dummy_cyclelen: 8;               /*In the slave mode it is the length in spi_clk cycles of dummy phase for write-buffer operations. The register value shall be (cycle_num-1).*/
        };
        unsigned int reg;
    } slave2;
    union {
        struct {
            unsigned int rdbuf_cmd_value: 8;                    /*In the slave mode it is the value of read-buffer command.*/
            unsigned int wrbuf_cmd_value: 8;                    /*In the slave mode it is the value of write-buffer command.*/
            unsigned int rdsta_cmd_value: 8;                    /*In the slave mode it is the value of read-status command.*/
            unsigned int wrsta_cmd_value: 8;                    /*In the slave mode it is the value of write-status command.*/
        };
        unsigned int reg;
    } slave3;
    union {
        struct {
            unsigned int bit_len:    24;                        /*In the slave mode it is the length in bits for write-buffer operations. The register value shall be (bit_num-1).*/
            unsigned int reserved24:  8;                        /*reserved*/
        };
        unsigned int reg;
    } slv_wrbuf_dlen;
    union {
        struct {
            unsigned int bit_len:    24;                        /*In the slave mode it is the length in bits for read-buffer operations. The register value shall be (bit_num-1).*/
            unsigned int reserved24:  8;                        /*reserved*/
        };
        unsigned int reg;
    } slv_rdbuf_dlen;
    union {
        struct {
            unsigned int req_en:        1;                      /*For SPI0  Cache access enable  1: enable  0:disable.*/
            unsigned int usr_cmd_4byte: 1;                      /*For SPI0  cache  read flash with 4 bytes command  1: enable  0:disable.*/
            unsigned int flash_usr_cmd: 1;                      /*For SPI0  cache  read flash for user define command  1: enable  0:disable.*/
            unsigned int flash_pes_en:  1;                      /*For SPI0  spi1 send suspend command before cache read flash  1: enable  0:disable.*/
            unsigned int reserved4:    28;                      /*reserved*/
        };
        unsigned int reg;
    } cache_fctrl;
    union {
        struct {
            unsigned int reserved0:           1;                /*reserved*/
            unsigned int usr_sram_dio:        1;                /*For SPI0  In the spi sram mode  spi dual I/O mode enable  1: enable  0:disable*/
            unsigned int usr_sram_qio:        1;                /*For SPI0  In the spi sram mode  spi quad I/O mode enable  1: enable  0:disable*/
            unsigned int usr_wr_sram_dummy:   1;                /*For SPI0  In the spi sram mode  it is the enable bit of dummy phase for write operations.*/
            unsigned int usr_rd_sram_dummy:   1;                /*For SPI0  In the spi sram mode  it is the enable bit of dummy phase for read operations.*/
            unsigned int cache_sram_usr_rcmd: 1;                /*For SPI0  In the spi sram mode cache read sram for user define command.*/
            unsigned int sram_bytes_len:      8;                /*For SPI0  In the sram mode  it is the byte length of spi read sram data.*/
            unsigned int sram_dummy_cyclelen: 8;                /*For SPI0  In the sram mode  it is the length in bits of address phase. The register value shall be (bit_num-1).*/
            unsigned int sram_addr_bitlen:    6;                /*For SPI0  In the sram mode  it is the length in bits of address phase. The register value shall be (bit_num-1).*/
            unsigned int cache_sram_usr_wcmd: 1;                /*For SPI0  In the spi sram mode cache write sram for user define command*/
            unsigned int reserved29:          3;                /*reserved*/
        };
        unsigned int reg;
    } cache_sctrl;
    union {
        struct {
            unsigned int dio:       1;                          /*For SPI0 SRAM DIO mode enable .  SRAM DIO enable command will be send when the bit is set. The bit will be cleared once the operation done.*/
            unsigned int qio:       1;                          /*For SPI0 SRAM QIO mode enable .  SRAM QIO enable command will be send when the bit is set. The bit will be cleared once the operation done.*/
            unsigned int reserved2: 2;                          /*For SPI0 SRAM write enable . SRAM write operation will be triggered when the bit is set. The bit will be cleared once the operation done.*/
            unsigned int rst_io:    1;                          /*For SPI0 SRAM IO mode reset enable. SRAM IO mode reset operation will be triggered when the bit is set. The bit will be cleared once the operation done*/
            unsigned int reserved5:27;                          /*reserved*/
        };
        unsigned int reg;
    } sram_cmd;
    union {
        struct {
            unsigned int usr_rd_cmd_value:   16;                /*For SPI0 When cache mode is enable it is the read command value of command phase for SRAM.*/
            unsigned int reserved16:         12;                /*reserved*/
            unsigned int usr_rd_cmd_bitlen:   4;                /*For SPI0 When cache mode is enable it is the length in bits of command phase for SRAM. The register value shall be (bit_num-1).*/
        };
        unsigned int reg;
    } sram_drd_cmd;
    union {
        struct {
            unsigned int usr_wr_cmd_value: 16;                  /*For SPI0 When cache mode is enable it is the write command value of command phase for SRAM.*/
            unsigned int reserved16:       12;                  /*reserved*/
            unsigned int usr_wr_cmd_bitlen: 4;                  /*For SPI0 When cache mode is enable it is the in bits of command phase  for SRAM. The register value shall be (bit_num-1).*/
        };
        unsigned int reg;
    } sram_dwr_cmd;
    union {
        struct {
            unsigned int slv_rdata_bit:24;                      /*In the slave mode it is the bit length of read data. The value is the length - 1.*/
            unsigned int reserved24:    8;                      /*reserved*/
        };
        unsigned int reg;
    } slv_rd_bit;
    unsigned int reserved_68;
    unsigned int reserved_6c;
    unsigned int reserved_70;
    unsigned int reserved_74;
    unsigned int reserved_78;
    unsigned int reserved_7c;
    unsigned int data_buf[16];                                  /*data buffer*/
    unsigned int tx_crc;                                        /*For SPI1  the value of crc32 for 256 bits data.*/
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
    union {
        struct {
            unsigned int t_pp_time: 12;                         /*page program delay time  by system clock.*/
            unsigned int reserved12: 4;                         /*reserved*/
            unsigned int t_pp_shift: 4;                         /*page program delay time shift .*/
            unsigned int reserved20:11;                         /*reserved*/
            unsigned int t_pp_ena:   1;                         /*page program delay enable.*/
        };
        unsigned int reg;
    } ext0;
    union {
        struct {
            unsigned int t_erase_time: 12;                      /*erase flash delay time by system clock.*/
            unsigned int reserved12:    4;                      /*reserved*/
            unsigned int t_erase_shift: 4;                      /*erase flash delay time shift.*/
            unsigned int reserved20:   11;                      /*reserved*/
            unsigned int t_erase_ena:   1;                      /*erase flash delay enable.*/
        };
        unsigned int reg;
    } ext1;
    union {
        struct {
            unsigned int st:         3;                         /*The status of spi state machine .*/
            unsigned int reserved3: 29;                         /*reserved*/
        };
        unsigned int reg;
    } ext2;
    union {
        struct {
            unsigned int int_hold_ena: 2;                       /*This register is for two SPI masters to share the same cs clock and data signals. The bits of one SPI are set  if the other SPI is busy  the SPI will be hold. 1(3): hold at ,idle, phase 2: hold at ,prepare, phase.*/
            unsigned int reserved2:   30;                       /*reserved*/
        };
        unsigned int reg;
    } ext3;
    union {
        struct {
            unsigned int reserved0:         2;                  /*reserved*/
            unsigned int in_rst:            1;                  /*The bit is used to reset in dma fsm and in data fifo pointer.*/
            unsigned int out_rst:           1;                  /*The bit is used to reset out dma fsm and out data fifo pointer.*/
            unsigned int ahbm_fifo_rst:     1;                  /*reset spi dma ahb master fifo pointer.*/
            unsigned int ahbm_rst:          1;                  /*reset spi dma ahb master.*/
            unsigned int in_loop_test:      1;                  /*Set bit to test in link.*/
            unsigned int out_loop_test:     1;                  /*Set bit to test out link.*/
            unsigned int out_auto_wrback:   1;                  /*when the link is empty   jump to next automatically.*/
            unsigned int out_eof_mode:      1;                  /*out eof flag generation mode . 1: when dma pop all data from fifo  0:when ahb push all data to fifo.*/
            unsigned int outdscr_burst_en:  1;                  /*read descriptor use burst mode when read data for memory.*/
            unsigned int indscr_burst_en:   1;                  /*read descriptor use burst mode when write data to memory.*/
            unsigned int out_data_burst_en: 1;                  /*spi dma read data from memory in burst mode.*/
            unsigned int reserved13:        1;                  /*reserved*/
            unsigned int dma_rx_stop:       1;                  /*spi dma read data stop  when in continue tx/rx mode.*/
            unsigned int dma_tx_stop:       1;                  /*spi dma write data stop when in continue tx/rx mode.*/
            unsigned int dma_continue:      1;                  /*spi dma continue tx/rx data.*/
            unsigned int reserved17:       15;                  /*reserved*/
        };
        unsigned int reg;
    } dma_conf;
    union {
        struct {
            unsigned int addr:        20;                       /*The address of the first outlink descriptor.*/
            unsigned int reserved20:   8;                       /*reserved*/
            unsigned int stop:         1;                       /*Set the bit to stop to use outlink descriptor.*/
            unsigned int start:        1;                       /*Set the bit to start to use outlink descriptor.*/
            unsigned int restart:      1;                       /*Set the bit to mount on new outlink descriptors.*/
            unsigned int reserved31:   1;                       /*reserved*/
        };
        unsigned int reg;
    } dma_out_link;
    union {
        struct {
            unsigned int addr:       20;                        /*The address of the first inlink descriptor.*/
            unsigned int auto_ret:    1;                        /*when the bit is set  inlink descriptor returns to the next descriptor while a packet is wrong*/
            unsigned int reserved21:  7;                        /*reserved*/
            unsigned int stop:        1;                        /*Set the bit to stop to use inlink descriptor.*/
            unsigned int start:       1;                        /*Set the bit to start to use inlink descriptor.*/
            unsigned int restart:     1;                        /*Set the bit to mount on new inlink descriptors.*/
            unsigned int reserved31:  1;                        /*reserved*/
        };
        unsigned int reg;
    } dma_in_link;
    union {
        struct {
            unsigned int rx_en:      1;                         /*spi dma read data status bit.*/
            unsigned int tx_en:      1;                         /*spi dma write data status bit.*/
            unsigned int reserved2: 30;                         /*spi dma read data from memory count.*/
        };
        unsigned int reg;
    } dma_status;
    union {
        struct {
            unsigned int inlink_dscr_empty:  1;                 /*The enable bit for lack of enough inlink descriptors.*/
            unsigned int outlink_dscr_error: 1;                 /*The enable bit for outlink descriptor error.*/
            unsigned int inlink_dscr_error:  1;                 /*The enable bit for inlink descriptor error.*/
            unsigned int in_done:            1;                 /*The enable bit for completing usage of a inlink descriptor.*/
            unsigned int in_err_eof:         1;                 /*The enable bit for receiving error.*/
            unsigned int in_suc_eof:         1;                 /*The enable bit for completing receiving all the packets from host.*/
            unsigned int out_done:           1;                 /*The enable bit for completing usage of a outlink descriptor .*/
            unsigned int out_eof:            1;                 /*The enable bit for sending a packet to host done.*/
            unsigned int out_total_eof:      1;                 /*The enable bit for sending all the packets to host done.*/
            unsigned int reserved9:         23;                 /*reserved*/
        };
        unsigned int reg;
    } dma_int_ena;
    union {
        struct {
            unsigned int inlink_dscr_empty:  1;                 /*The raw bit for lack of enough inlink descriptors.*/
            unsigned int outlink_dscr_error: 1;                 /*The raw bit for outlink descriptor error.*/
            unsigned int inlink_dscr_error:  1;                 /*The raw bit for inlink descriptor error.*/
            unsigned int in_done:            1;                 /*The raw bit for completing usage of a inlink descriptor.*/
            unsigned int in_err_eof:         1;                 /*The raw bit for receiving error.*/
            unsigned int in_suc_eof:         1;                 /*The raw bit for completing receiving all the packets from host.*/
            unsigned int out_done:           1;                 /*The raw bit for completing usage of a outlink descriptor.*/
            unsigned int out_eof:            1;                 /*The raw bit for sending a packet to host done.*/
            unsigned int out_total_eof:      1;                 /*The raw bit for sending all the packets to host done.*/
            unsigned int reserved9:         23;                 /*reserved*/
        };
        unsigned int reg;
    } dma_int_raw;
    union {
        struct {
            unsigned int inlink_dscr_empty:  1;                  /*The status bit for lack of enough inlink descriptors.*/
            unsigned int outlink_dscr_error: 1;                  /*The status bit for outlink descriptor error.*/
            unsigned int inlink_dscr_error:  1;                  /*The status bit for inlink descriptor error.*/
            unsigned int in_done:            1;                  /*The status bit for completing usage of a inlink descriptor.*/
            unsigned int in_err_eof:         1;                  /*The status bit for receiving error.*/
            unsigned int in_suc_eof:         1;                  /*The status bit for completing receiving all the packets from host.*/
            unsigned int out_done:           1;                  /*The status bit for completing usage of a outlink descriptor.*/
            unsigned int out_eof:            1;                  /*The status bit for sending a packet to host done.*/
            unsigned int out_total_eof:      1;                  /*The status bit for sending all the packets to host done.*/
            unsigned int reserved9:         23;                  /*reserved*/
        };
        unsigned int reg;
    } dma_int_st;
    union {
        struct {
            unsigned int inlink_dscr_empty:  1;                 /*The clear bit for lack of enough inlink descriptors.*/
            unsigned int outlink_dscr_error: 1;                 /*The clear bit for outlink descriptor error.*/
            unsigned int inlink_dscr_error:  1;                 /*The clear bit for inlink descriptor error.*/
            unsigned int in_done:            1;                 /*The clear bit for completing usage of a inlink descriptor.*/
            unsigned int in_err_eof:         1;                 /*The clear bit for receiving error.*/
            unsigned int in_suc_eof:         1;                 /*The clear bit for completing receiving all the packets from host.*/
            unsigned int out_done:           1;                 /*The clear bit for completing usage of a outlink descriptor.*/
            unsigned int out_eof:            1;                 /*The clear bit for sending a packet to host done.*/
            unsigned int out_total_eof:      1;                 /*The clear bit for sending all the packets to host done.*/
            unsigned int reserved9:         23;                 /*reserved*/
        };
        unsigned int reg;
    } dma_int_clr;
    unsigned int dma_in_err_eof_des_addr;                       /*The inlink descriptor address when spi dma produce receiving error.*/
    unsigned int dma_in_suc_eof_des_addr;                       /*The last inlink descriptor address when spi dma produce from_suc_eof.*/
    unsigned int dma_inlink_dscr;                               /*The content of current in descriptor pointer.*/
    unsigned int dma_inlink_dscr_bf0;                           /*The content of next in descriptor pointer.*/
    unsigned int dma_inlink_dscr_bf1;                           /*The content of current in descriptor data buffer pointer.*/
    unsigned int dma_out_eof_bfr_des_addr;                      /*The address of buffer relative to the outlink descriptor that produce eof.*/
    unsigned int dma_out_eof_des_addr;                          /*The last outlink descriptor address when spi dma produce to_eof.*/
    unsigned int dma_outlink_dscr;                              /*The content of current out descriptor pointer.*/
    unsigned int dma_outlink_dscr_bf0;                          /*The content of next out descriptor pointer.*/
    unsigned int dma_outlink_dscr_bf1;                          /*The content of current out descriptor data buffer pointer.*/
    unsigned int dma_rx_status;                                 /*spi dma read data from memory status.*/
    unsigned int dma_tx_status;                                 /*spi dma write data to memory status.*/
    unsigned int reserved_150;
    unsigned int reserved_154;
    unsigned int reserved_158;
    unsigned int reserved_15c;
    unsigned int reserved_160;
    unsigned int reserved_164;
    unsigned int reserved_168;
    unsigned int reserved_16c;
    unsigned int reserved_170;
    unsigned int reserved_174;
    unsigned int reserved_178;
    unsigned int reserved_17c;
    unsigned int reserved_180;
    unsigned int reserved_184;
    unsigned int reserved_188;
    unsigned int reserved_18c;
    unsigned int reserved_190;
    unsigned int reserved_194;
    unsigned int reserved_198;
    unsigned int reserved_19c;
    unsigned int reserved_1a0;
    unsigned int reserved_1a4;
    unsigned int reserved_1a8;
    unsigned int reserved_1ac;
    unsigned int reserved_1b0;
    unsigned int reserved_1b4;
    unsigned int reserved_1b8;
    unsigned int reserved_1bc;
    unsigned int reserved_1c0;
    unsigned int reserved_1c4;
    unsigned int reserved_1c8;
    unsigned int reserved_1cc;
    unsigned int reserved_1d0;
    unsigned int reserved_1d4;
    unsigned int reserved_1d8;
    unsigned int reserved_1dc;
    unsigned int reserved_1e0;
    unsigned int reserved_1e4;
    unsigned int reserved_1e8;
    unsigned int reserved_1ec;
    unsigned int reserved_1f0;
    unsigned int reserved_1f4;
    unsigned int reserved_1f8;
    unsigned int reserved_1fc;
    unsigned int reserved_200;
    unsigned int reserved_204;
    unsigned int reserved_208;
    unsigned int reserved_20c;
    unsigned int reserved_210;
    unsigned int reserved_214;
    unsigned int reserved_218;
    unsigned int reserved_21c;
    unsigned int reserved_220;
    unsigned int reserved_224;
    unsigned int reserved_228;
    unsigned int reserved_22c;
    unsigned int reserved_230;
    unsigned int reserved_234;
    unsigned int reserved_238;
    unsigned int reserved_23c;
    unsigned int reserved_240;
    unsigned int reserved_244;
    unsigned int reserved_248;
    unsigned int reserved_24c;
    unsigned int reserved_250;
    unsigned int reserved_254;
    unsigned int reserved_258;
    unsigned int reserved_25c;
    unsigned int reserved_260;
    unsigned int reserved_264;
    unsigned int reserved_268;
    unsigned int reserved_26c;
    unsigned int reserved_270;
    unsigned int reserved_274;
    unsigned int reserved_278;
    unsigned int reserved_27c;
    unsigned int reserved_280;
    unsigned int reserved_284;
    unsigned int reserved_288;
    unsigned int reserved_28c;
    unsigned int reserved_290;
    unsigned int reserved_294;
    unsigned int reserved_298;
    unsigned int reserved_29c;
    unsigned int reserved_2a0;
    unsigned int reserved_2a4;
    unsigned int reserved_2a8;
    unsigned int reserved_2ac;
    unsigned int reserved_2b0;
    unsigned int reserved_2b4;
    unsigned int reserved_2b8;
    unsigned int reserved_2bc;
    unsigned int reserved_2c0;
    unsigned int reserved_2c4;
    unsigned int reserved_2c8;
    unsigned int reserved_2cc;
    unsigned int reserved_2d0;
    unsigned int reserved_2d4;
    unsigned int reserved_2d8;
    unsigned int reserved_2dc;
    unsigned int reserved_2e0;
    unsigned int reserved_2e4;
    unsigned int reserved_2e8;
    unsigned int reserved_2ec;
    unsigned int reserved_2f0;
    unsigned int reserved_2f4;
    unsigned int reserved_2f8;
    unsigned int reserved_2fc;
    unsigned int reserved_300;
    unsigned int reserved_304;
    unsigned int reserved_308;
    unsigned int reserved_30c;
    unsigned int reserved_310;
    unsigned int reserved_314;
    unsigned int reserved_318;
    unsigned int reserved_31c;
    unsigned int reserved_320;
    unsigned int reserved_324;
    unsigned int reserved_328;
    unsigned int reserved_32c;
    unsigned int reserved_330;
    unsigned int reserved_334;
    unsigned int reserved_338;
    unsigned int reserved_33c;
    unsigned int reserved_340;
    unsigned int reserved_344;
    unsigned int reserved_348;
    unsigned int reserved_34c;
    unsigned int reserved_350;
    unsigned int reserved_354;
    unsigned int reserved_358;
    unsigned int reserved_35c;
    unsigned int reserved_360;
    unsigned int reserved_364;
    unsigned int reserved_368;
    unsigned int reserved_36c;
    unsigned int reserved_370;
    unsigned int reserved_374;
    unsigned int reserved_378;
    unsigned int reserved_37c;
    unsigned int reserved_380;
    unsigned int reserved_384;
    unsigned int reserved_388;
    unsigned int reserved_38c;
    unsigned int reserved_390;
    unsigned int reserved_394;
    unsigned int reserved_398;
    unsigned int reserved_39c;
    unsigned int reserved_3a0;
    unsigned int reserved_3a4;
    unsigned int reserved_3a8;
    unsigned int reserved_3ac;
    unsigned int reserved_3b0;
    unsigned int reserved_3b4;
    unsigned int reserved_3b8;
    unsigned int reserved_3bc;
    unsigned int reserved_3c0;
    unsigned int reserved_3c4;
    unsigned int reserved_3c8;
    unsigned int reserved_3cc;
    unsigned int reserved_3d0;
    unsigned int reserved_3d4;
    unsigned int reserved_3d8;
    unsigned int reserved_3dc;
    unsigned int reserved_3e0;
    unsigned int reserved_3e4;
    unsigned int reserved_3e8;
    unsigned int reserved_3ec;
    unsigned int reserved_3f0;
    unsigned int reserved_3f4;
    unsigned int reserved_3f8;
    union {
        struct {
            unsigned int date:      28;                         /*SPI register version.*/
            unsigned int reserved28: 4;                         /*reserved*/
        };
        unsigned int reg;
    } date;
} spi_dev_t;

extern spi_dev_t SPI0;
extern spi_dev_t SPI1;
extern spi_dev_t SPI2;
extern spi_dev_t SPI3;

#ifdef __cplusplus
}
#endif

#endif
