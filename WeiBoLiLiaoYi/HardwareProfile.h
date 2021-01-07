#ifndef __STDAFX_H__
#define __STDAFX_H__

#include <htc.h>
#define _XTAL_FREQ 4000000
#include <afx.h>
#include "wfDefine.h"
#include "TypeDefine.h"
#include "FlagDefine.h"

#define T1_100ms 53036

GFlags gFlags;
unsigned int SystemTick;
unsigned int BeepTick;
unsigned int KeyTick;

unsigned char MCTime_M;//介入时间
unsigned char MCTime_S;//介入时间
unsigned char MCLevel;//介入周期
unsigned char T2Times;

#define KEY_S1 0x0004 //时间-
#define KEY_S2 0x0040 //暂停/复位
#define KEY_S3 0x0400 //脉冲/持续
#define KEY_S4 0x0002 //时间+
#define KEY_S5 0x0020 //启动
#define KEY_S6 0x0200 //功率-
#define KEY_S7 0x0001 //功率+


#define TM1638_STB_IO TRISB5  //片选
#define TM1638_CLK_IO TRISB4      //时钟
#define TM1638_DIO_IO TRISB3   //数据输入/输出
 
#define TM1638_STB RB5
#define TM1638_CLK RB4
#define TM1638_DIO RB3 
#include "TM1638.h"
#include "LED.h"



#define TLV56XX_CLK_W	RD1  
#define TLV56XX_DIO_W	RD0 
#define TLV56XX_CS_W	RD2

#define TLV56XX_CLK_DIR TRISD1
#define TLV56XX_DIO_DIR TRISD0  
#define TLV56XX_CS_DIR  TRISD2
#include "TLV56XX.h"


#define U5_8_ON()	RC6=0
#define U5_8_OFF()	RC6=1
#define U5_8_W		RC6
#define U5_8_DIR	TRISC6

#define U1_1_R		RA4
#define U1_1_DIR	TRISA4

#define RUNLed_OFF()	RE2=1
#define RUNLed_ON()	RE2=0
#define RUNLed_W	RE2
#define RUNLed_DIR	TRISE2

// #define PLed_ON()	RC2=1
// #define CLed_ON()	RC2=0
// #define PCLed_DIR	TRISC2
// 
// #define SLed_Toggle()	RC3=!RC3
// #define SLed_ON()	RC3=0
// //#define RUNLed_W	RE2
// #define SLed_DIR	TRISC2


#define BZ_ON()	RA5=1
#define BZ_OFF()	RA5=0
#define BZ_W	RA5
#define BZ_DIR	TRISA5

#define Beep() BeepTick=SystemTick;BZ_ON()//;__delay_ms(100)//HT162X_Setting(HT162X_TONE_ON);gFlags.Bits.bBeep=1;BeepTick=SystemTick
#define DAOut() TLV56XX_WriteData((5+MCLevel*9)<<2)
#define DAStop() TLV56XX_WriteData(0);

void KeyProc(void);
void InitSystem( void );
#endif
