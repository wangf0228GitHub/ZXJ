#ifndef __RIO_h__
#define __RIO_h__

#include "stdint.h"
#include "usart.h"

#define pRIOData 8

#ifndef MAX_RIO_RX
#define MAX_RIO_RX 50
#endif

extern uint32_t bRIORx;
extern uint32_t bRIORead;
extern uint8_t RIO_Rx;
extern uint8_t RIO_RxList[MAX_RIO_RX];
extern uint8_t RIO_RxCount;
extern uint8_t RIO_NeedRxCount;
extern uint16_t RIOCur;
extern uint8_t RIO_0E[6];

void RIO_EndProcCommand(void);
void RIO_ProcRx(unsigned char rx);
uint32_t RIO_OpenSerial( void );
uint32_t RIO_CloseSerial( void );
uint32_t RIO_ReadCommand(uint8_t CMDID);
uint32_t RIO_Write_0x27(uint16_t current);

#endif


