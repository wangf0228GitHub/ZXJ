#ifndef __STDAFX_H__
#define __STDAFX_H__

//#define Proteus

#include <htc.h>
#include "stdint.h"
#define _XTAL_FREQ 16000000

#include "FlagDefine.h"

#define GetDeltaTick(a) (SystemTick-a)
#define wfDelay_ms(x) __delay_ms(x)

//TMR0的定时周期为100ms,1:8
#define SetTMR0() TMR0H=0x3c;TMR0L=0xb0

//励磁电流显示
#define SimI2C
#define SimI2C_Delay_Ex
#define SimI2C_Delay() __delay_us(50);
#define SimI2C_CLK_IO TRISF0
#define SimI2C_DATA_IO TRISF1
#define SimI2C_CLK_W LATF0
#define SimI2C_DATA_W LATF1
#define SimI2C_DATA_R RF1

#define SIMI2C_SCL_High()	SimI2C_CLK_W=1
#define SIMI2C_SCL_Low()	SimI2C_CLK_W=0

#define SIMI2C_SDA_IN()	SimI2C_DATA_IO=1
#define SIMI2C_SDA_OUT()  SimI2C_DATA_IO=0
#define SIMI2C_SDA_High() SimI2C_DATA_W=1
#define SIMI2C_SDA_Low()	SimI2C_DATA_W=0
#define SIMI2C_SDA_Read() SimI2C_DATA_R
//灯丝电流显示
#define SimI2C_2
#define SimI2C_2_Delay_Ex
#define SimI2C_2_Delay() __delay_us(50);
#define SimI2C_2_CLK_IO TRISF2
#define SimI2C_2_DATA_IO TRISF3
#define SimI2C_2_CLK_W LATF2
#define SimI2C_2_DATA_W LATF3
#define SimI2C_2_DATA_R RF3

#define SimI2C_2_SCL_High() SimI2C_2_CLK_W=1
#define SimI2C_2_SCL_Low()	SimI2C_2_CLK_W=0

#define SimI2C_2_SDA_IN()	SimI2C_2_DATA_IO=1
#define SimI2C_2_SDA_OUT()  SimI2C_2_DATA_IO=0
#define SimI2C_2_SDA_High() SimI2C_2_DATA_W=1
#define SimI2C_2_SDA_Low()	SimI2C_2_DATA_W=0
#define SimI2C_2_SDA_Read() SimI2C_2_DATA_R

//阳极电压显示
#define SimI2C_3
#define SimI2C_3_Delay_Ex
#define SimI2C_3_Delay() __delay_us(50);
#define SimI2C_3_CLK_IO TRISF4
#define SimI2C_3_DATA_IO TRISF5
#define SimI2C_3_CLK_W LATF4
#define SimI2C_3_DATA_W LATF5
#define SimI2C_3_DATA_R RF5

#define SimI2C_3_SCL_High() SimI2C_3_CLK_W=1
#define SimI2C_3_SCL_Low()	SimI2C_3_CLK_W=0

#define SimI2C_3_SDA_IN()	SimI2C_3_DATA_IO=1
#define SimI2C_3_SDA_OUT()  SimI2C_3_DATA_IO=0
#define SimI2C_3_SDA_High() SimI2C_3_DATA_W=1
#define SimI2C_3_SDA_Low()	SimI2C_3_DATA_W=0
#define SimI2C_3_SDA_Read() SimI2C_3_DATA_R

//阳极电流显示
#define SimI2C_4
#define SimI2C_4_Delay_Ex
#define SimI2C_4_Delay() __delay_us(50);
#define SimI2C_4_CLK_IO TRISF6
#define SimI2C_4_DATA_IO TRISF7
#define SimI2C_4_CLK_W LATF6
#define SimI2C_4_DATA_W LATF7
#define SimI2C_4_DATA_R RF7

#define SimI2C_4_SCL_High() SimI2C_4_CLK_W=1
#define SimI2C_4_SCL_Low()	SimI2C_4_CLK_W=0

#define SimI2C_4_SDA_IN()	SimI2C_4_DATA_IO=1
#define SimI2C_4_SDA_OUT()  SimI2C_4_DATA_IO=0
#define SimI2C_4_SDA_High() SimI2C_4_DATA_W=1
#define SimI2C_4_SDA_Low()	SimI2C_4_DATA_W=0
#define SimI2C_4_SDA_Read() SimI2C_4_DATA_R

#include "SimI2C.h"
#define TM1650_2
#define TM1650_3
#define TM1650_4
#include "TM1650.h"



//阳极电压控制
#define DAC8830_CS_SetOut() TRISE2=0
#define DAC8830_SCLK_SetOut() TRISE1=0
#define DAC8830_SDI_SetOut() TRISE0=0

#define DAC8830_CS_SetHigh() LATE2=1;__delay_us(1000);
#define DAC8830_CS_SetLow() LATE2=0;__delay_us(1000);
#define DAC8830_SCLK_SetLow() LATE1=0;__delay_us(1000);
#define DAC8830_SCLK_SetHigh() LATE1=1;__delay_us(1000);
#define DAC8830_SDI_SetHigh() LATE0=1;__delay_us(1000);
#define DAC8830_SDI_SetLow() LATE0=0;__delay_us(1000);
//灯丝电压控制
#define DAC8830_2
#define DAC8830_2_CS_SetOut() TRISD4=0
#define DAC8830_2_SCLK_SetOut() TRISD5=0
#define DAC8830_2_SDI_SetOut() TRISD6=0

#define DAC8830_2_CS_SetHigh() LATD4=1
#define DAC8830_2_CS_SetLow() LATD4=0
#define DAC8830_2_SCLK_SetLow() LATD5=0
#define DAC8830_2_SCLK_SetHigh() LATD5=1
#define DAC8830_2_SDI_SetHigh() LATD6=1
#define DAC8830_2_SDI_SetLow() LATD6=0
//励磁电流控制
#define DAC8830_3
#define DAC8830_3_CS_SetOut() TRISD0=0
#define DAC8830_3_SCLK_SetOut() TRISD1=0
#define DAC8830_3_SDI_SetOut() TRISD2=0

#define DAC8830_3_CS_SetHigh() LATD0=1
#define DAC8830_3_CS_SetLow() LATD0=0
#define DAC8830_3_SCLK_SetLow() LATD1=0
#define DAC8830_3_SCLK_SetHigh() LATD1=1
#define DAC8830_3_SDI_SetHigh() LATD2=1
#define DAC8830_3_SDI_SetLow() LATD2=0
#include "DAC8830.h"


#define MCP3201_CS_SetOut() TRISE6=0
#define MCP3201_CLK_SetOut() TRISE4=0
#define MCP3201_Dout_SetIn() TRISE5=1

#define MCP3201_CS_SetHigh() LATE6=1;__delay_us(1000);
#define MCP3201_CS_SetLow() LATE6=0;__delay_us(1000);
#define MCP3201_CLK_SetLow() LATE4=0;__delay_us(1000);
#define MCP3201_CLK_SetHigh() LATE4=1;__delay_us(1000);
#define MCP3201_Dout_Read() RE5
#include "MCP3201.h"


#define Beep_W LATC4
#define Beep_DIR TRISC4
/************************************************************************/
/* 按键                                                                 */
/************************************************************************/
#define K1_R RA0
#define K2_R RA1
#define K3_R RA2
#define K4_R RA3

#define K1_B_R RB0
#define K1_A_R RB4
#define K2_B_R RB2
#define K2_A_R RB3
#define K3_B_R RB1
#define K3_A_R RB5

#define K1_Value 0x0e //励磁
#define K2_Value 0x0d //灯丝
#define K3_Value 0x0b //高压、阳极
#define K4_Value 0x07 //清零
#define KeyCheck_NoKey 0x0f
#define KeyCheck_ReadKey(key) key=PORTA&0x0f
#include "KeyCheck.h"

volatile uint16_t SystemTick;
uint16_t IaTick;
uint16_t FlashTick_If;
uint16_t FlashTick_Ic;
uint16_t FlashTick_U;
uint16_t SetTick_If;
uint16_t SetTick_Ic;
uint16_t SetTick_U;
volatile _KnobFlags knobFlags;
_gFlags gFlags;
uint16_t Ifset;
uint16_t Icset;
uint16_t Uset;
uint8_t T2Times;
uint16_t  If; //灯丝电流If ：0-0.850A
uint16_t  Ic;//励磁电流Ic ：0 - 0.450A
uint16_t  U;//阳极电压U：0-150.0V
//uint16_t  Ia;//阳极电流Ia：0-1000uA
uint16_t  Ia0;//阳极电流零点偏置
void InitMCU(void);
void InitSystem(void);

#endif
