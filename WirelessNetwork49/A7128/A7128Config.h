#include "HardwareProfile.h"
const uint8_t A7128Config[]=
{
	0x00, //0x00,    MODE register,		only reset, not use on config
	0x62, //0x01,    MODE CTRL register,
	0x00, //0x02,    CALIBRATION register,
	0x3F, //0x03,    FIFO1 register,
	0x00, //0x04,    FIFO2 register,
	0x00, //0x05,    FIFO register,		for fifo read/write
	0x00, //0x06,    IDDATA register,	for idcode
	0x00, //0x07,    RCOSC1 register,
	0x00, //0x08,    RCOSC2 register,
	0x00, //0x09,    RCOSC3 register,
	0x00, //0x0a,    CKO register,
	0x01, //0x0b,    GPIO1 register
	0x19, //0x0c,    GPIO2 register,
	0xDF, //0x0d,    DATARATECLK register,
	0x3C, //0x0e,    PLL1 register,
	0x0E, //0x0f,    PLL2 register, 		RFbase 900.001MHz
	0x70, //0x10,    PLL3 register,
	0x80, //0x11,    PLL4 register,
	0x08, //0x12,    PLL5 register,
	0x28, //0x13,    chanel group I,
	0x50, //0x14,    chanel group II,
	0x2F, //0x15,    TX1 register,
	0x40, //0x16,    TX2 register,
	0x12, //0x17,    DELAY1 register,
	0x42, //0x18,    DELAY2 register,
	0xe0, //0x19,    RX register,
	0x1F, //0x1a,    RXGAIN1 register,
	0xEC, //0x1b,    RXGAIN2 register,
	0x00, //0x1c,    RXGAIN3 register,
	0x56, //0x1d,    RXGAIN4 register,
	0x00, //0x1e,    RSSI register,
	0xD2, //0x1f,    ADC register,
	0x17, //0x20,    CODE1 register,
	0xC6, //0x21,    CODE2 register,
	0x2A, //0x22,    CODE3 register,
	0x00, //0x23,    IFCAL1 register,
	0x7F, //0x24,    IFCAL2 register,
	0x00, //0x25,    VCOCCAL register,
	0xC0, //0x26,    VCOCAL1 register,
	0x80, //0x27,    VCOCAL2 register,
	0x70, //0x28,    VCO DEV Cal. I register,
	0x00, //0x29,    VCO DEV Cal. II register,
	0x80, //0x2a,    VCO DEV Cal. III register,
	0xE0, //0x2b,    VCO Mod. delay register,
	0x7A, //0x2c,    BATTERY register,
	0x7f, //0x2d,    TXTEST register,
	0x47, //0x2e,    RXDEM1 register,
	0x80, //0x2f,    RXDEM2 register,
	0xF4, //0x30,    CPC1 register,
	0x7A, //0x31,    CPC2 register,
	0x34, //0x32,    CRYSTAL register,
	0x51, //0x33,    PLLTEST register,
	0x10, //0x34,    VCOTEST register,
	0x08, //0x35,    RF Analog Test
	0xFD, //0x36,    IFAT register,
	0x77, //0x37,    Channel select register,
	0x00, //0x38,    VRB register,
	0x00, //0x39,    Data rate register,
	0x00, //0x3a,    FCR register,
	0x00, //0x3b,    ARD register,
	0x00, //0x3c,    AFEP register,
	0x00, //0x3d,    WMUX register,
	0x00, //0x3e,    FCF register,
	0x00, //0x3f,    USID register,
};