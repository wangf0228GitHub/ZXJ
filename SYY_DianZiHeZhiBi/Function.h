#ifndef   __Function_h__
#define   __Function_h__

#include "HardwareProfile.h"

void Display_Init(void);
void Display_ShowSet(uint8_t who);
void Display_ShowIa(void);
void DASet(uint8_t who);
void Display_ShowFlash(uint8_t who);
void __delay_20ms(uint16_t x);
void FlashTick(void);
#endif

