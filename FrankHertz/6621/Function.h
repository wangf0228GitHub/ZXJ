#ifndef   __Function_h__
#define   __Function_h__

#include "HardwareProfile.h"



void TLC5615_WriteData(uint16_t d);
void Display_Init(void);
void VOutput(uint16_t da);
void ReadAD_RP(void);
void ShowAD_I(void);
#endif

