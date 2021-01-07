#ifndef ADS131M06_h__
#define ADS131M06_h__

#include "gpio.h"
#define FrameLen 3*8
/************************************************************************/
/* 采样率宏定义                                                         */
/************************************************************************/
//500SPS
#define OSR500 4  //2048
#define myOSR500 1

#define OSR200 2 //512	
#define myOSR200 10 

#define OSR100 3 //1024
#define myOSR100 10

extern uint8_t  spiRxList[FrameLen];
extern uint32_t SPS;
extern uint32_t myOSR;
extern uint32_t myOSRMax;
void ADS131_ReadADC(void);
void ADS131_Init(void);
void ADS131_ReadReg(uint16_t addr);
void ADS131_SetSPS(void);
void ADS131_WriteCMD(uint16_t cmd);
void ADS131_WriteReg(uint16_t addr, uint16_t data);
#endif // ADS131M06_h__
