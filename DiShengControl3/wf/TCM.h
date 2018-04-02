#ifndef __TCM_h__
#define __TCM_h__

#include "stdint.h"
#include "usart.h"

#define TCMUart huart3

typedef union   
{
	struct
	{
		unsigned bRx:1;
	};
	uint8_t AllFlag;
} _TCM_Flags;        // general flags

#define pTCMData 4

#ifndef MAX_TCM_RX
#define MAX_TCM_RX 50
#endif

extern _TCM_Flags TCM_Flags;
extern uint8_t TCM_Rx;
extern uint8_t TCM_RxList[MAX_TCM_RX];
extern uint8_t TCM_RxCount;
extern uint8_t TCM_NeedRxCount;

void TCM_EndProcCommand(void);
void TCM_ProcRx(unsigned char rx);
void TCM_SendData(void);

#endif


