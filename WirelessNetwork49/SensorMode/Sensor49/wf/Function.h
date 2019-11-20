#ifndef   __Function_h__
#define   __Function_h__

#include <stdint.h>
#include "main.h"

//uint32_t CheckRxPacket(void);
void A7128_SetTx(void);
void A7128_SetRx(void);
void MCUSleep(void);
void ADCBAT(void);
void InitTimeIndex(void);
void TxADCDataProc(uint32_t FrameIndex);
#endif
