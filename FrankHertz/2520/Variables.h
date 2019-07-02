#ifndef   __Variables_h__
#define   __Variables_h__

#include <stdint.h>
#include "FlagDefine.h"
extern volatile uint16_t SystemTick;
extern volatile uint16_t TBTick;
extern volatile GFlags gFlags;
extern volatile uint8_t gTemp1;
extern volatile uint8_t gTemp2;
extern volatile uint8_t FastModeData[256];
#endif

