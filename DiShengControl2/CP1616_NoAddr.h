#ifndef __CP1616_NoAddr_h__
#define __CP1616_NoAddr_h__

#include <stdint.h>



#define pCP1616_NoAddr_Data 5
#define pCP1616_NoAddr_CommandIndex 2


#ifndef MAX_CP1616_NoAddr_RX
#define MAX_CP1616_NoAddr_RX 50
#endif

#ifndef MAX_CP1616_NoAddr_TX
#define MAX_CP1616_NoAddr_TX 50
#endif

extern uint8_t CP1616_NoAddr_RxList[MAX_CP1616_NoAddr_RX];
extern uint16_t CP1616_NoAddr_RxCount;
extern uint16_t CP1616_NoAddr_NeedRxCount;
extern uint8_t CP1616_NoAddr_NeedCommand;

extern uint8_t CP1616_NoAddr_TxList[MAX_CP1616_NoAddr_TX];
extern uint16_t CP1616_NoAddr_TxCount;

void CP1616_NoAddr_Init(void);
void CP1616_NoAddr_EndProcCommand(void);
uint8_t CP1616_NoAddr_DataProc(uint8_t rx);



#endif


