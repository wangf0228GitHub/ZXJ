#ifndef __TCM_h__
#define __TCM_h__

typedef union   
{
	struct
	{
		unsigned bRx:1;
	};
	unsigned char AllFlag;
} _TCM_Flags;        // general flags

#define TCM_TxByte(x) Uart1_PutChar(x)

#define pTCMData 4

#ifndef MAX_TCM_RX
#define MAX_TCM_RX 50
#endif

extern _TCM_Flags TCM_Flags;
extern unsigned char TCM_RxList[MAX_TCM_RX];
extern unsigned char TCM_RxCount;
extern unsigned char TCM_NeedRxCount;


void TCM_EndProcCommand(void);
void TCM_ProcRx(unsigned char rx);
void TCM_SendData(void);


#endif


