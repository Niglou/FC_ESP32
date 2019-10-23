#ifndef H_NONOS_IOMUX_STRUCT
#define H_NONOS_IOMUX_STRUCT

const unsigned int esp32_gpioMux[]={
    0x44,
    0x88,
    0x40,
    0x84,
    0x48,
    0x6c,
    0x60,
    0x64,
    0x68,
    0x54,
    0x58,
    0x5c,
    0x34,
    0x38,
    0x30,
    0x3c,
    0x4c,
    0x50,
    0x70,
    0x74,
    0x78,
    0x7c,
    0x80,
    0x8c,
    0,
    0x24,
    0x28,
    0x2c,
    0,
    0,
    0,
    0,
    0x1c,
    0x20,
    0x14,
    0x18,
    0x04,
    0x08,
    0x0c,
    0x10,
};

union iomux_pad_t {
    struct {
        unsigned int mcu_oe     :   1;
        unsigned int slp_sel    :   1;
        unsigned int mcu_wpd    :   1;
        unsigned int mcu_wpu    :   1;
        unsigned int mcu_ie     :   1;
        unsigned int mcu_drv    :   2;
        unsigned int func_wpd   :   1;
        unsigned int func_wpu   :   1;
        unsigned int func_ie    :   1;
        unsigned int func_drv   :   2;
        unsigned int mcu_sel    :   3;
        unsigned int reserved   :  17;
    };
    unsigned int reg;
};

typedef volatile struct {

    union {
        struct {
            unsigned int clk1 :  4;
            unsigned int clk2 :  4;
            unsigned int clk3 :  4;
            unsigned int      : 20;
        };
        unsigned int reg;
    } pin_ctrl;

    union iomux_pad_t GPIO36;
    union iomux_pad_t GPIO37;
    union iomux_pad_t GPIO38;
    union iomux_pad_t GPIO39;
    union iomux_pad_t GPIO34;
    union iomux_pad_t GPIO35;
    union iomux_pad_t GPIO32;
    union iomux_pad_t GPIO33;
    union iomux_pad_t GPIO25;
    union iomux_pad_t GPIO26;
    union iomux_pad_t GPIO27;
    union { union iomux_pad_t MTMS;     union iomux_pad_t HSPICLK;  union iomux_pad_t GPIO14; };
    union { union iomux_pad_t MTDI;     union iomux_pad_t HSPIQ;    union iomux_pad_t GPIO12; };
    union { union iomux_pad_t MTCK;     union iomux_pad_t HSPID;    union iomux_pad_t GPIO13; };
    union { union iomux_pad_t MTDO;     union iomux_pad_t HSPICS0;  union iomux_pad_t GPIO15; };
    union iomux_pad_t GPIO2;
    union iomux_pad_t GPIO0;
    union iomux_pad_t GPIO4;
    union iomux_pad_t GPIO16;
    union iomux_pad_t GPIO17;
    union { union iomux_pad_t SD_DATA2; union iomux_pad_t GPIO9; };
    union { union iomux_pad_t SD_DATA3; union iomux_pad_t GPIO10; };
    union { union iomux_pad_t SD_CMD;   union iomux_pad_t GPIO11; };
    union { union iomux_pad_t SD_CLK;   union iomux_pad_t GPIO6; };
    union { union iomux_pad_t SD_DATA0; union iomux_pad_t GPIO7; };
    union { union iomux_pad_t SD_DATA1; union iomux_pad_t GPIO8; };
    union iomux_pad_t GPIO5;
    union { union iomux_pad_t GPIO18;   union iomux_pad_t VSPICLK; };
    union { union iomux_pad_t GPIO19;   union iomux_pad_t VSPIQ; };
    union iomux_pad_t GPIO20;
    union { union iomux_pad_t GPIO21;   union iomux_pad_t VSPIHD; };
    union { union iomux_pad_t GPIO22;   union iomux_pad_t VSPIWP; };
    union iomux_pad_t U0RXD;
    union iomux_pad_t U0TXD;
    union { union iomux_pad_t GPIO23;   union iomux_pad_t VSPID; };
    union iomux_pad_t GPIO24;

} iomux_dev_t;

#define IOMUX (*(iomux_dev_t*)(0x3FF49000))

#endif
