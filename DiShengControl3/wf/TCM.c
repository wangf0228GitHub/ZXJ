#include "TCM.h"
#include "Variables.h"

_TCM_Flags TCM_Flags;
uint8_t TCM_RxList[MAX_TCM_RX];
uint8_t TCM_RxCount;
uint8_t TCM_NeedRxCount;
uint8_t TCM_Rx;
void TCM_EndProcCommand(void)
{
	TCM_Flags.bRx=0;
	TCM_NeedRxCount=0xff;
	TCM_RxCount=0;
}
void TCM_ProcRx(uint8_t rx)
{
	if(TCM_Flags.bRx==1)
		return;
	TCM_RxList[TCM_RxCount++]=rx;
	if(TCM_RxCount>pTCMData)
	{
		if(TCM_RxCount==TCM_NeedRxCount)
		{			
			TCM_Flags.bRx=1;			
		}
		else if(TCM_RxCount>TCM_NeedRxCount)
		{
			TCM_RxCount=0;
			TCM_NeedRxCount=0xff;
		}
		else if(TCM_RxCount>MAX_TCM_RX)
		{
			TCM_RxCount=0;
			TCM_NeedRxCount=0xff;				
		}
	}
	else if(TCM_RxCount==4)//≈–∂œµÿ÷∑
	{
		TCM_NeedRxCount=6+(rx*5);
	}
	else if(TCM_RxCount==3)
	{
		if(rx!=0x05)
		{
			TCM_RxCount=0;
		}
	}
	else if(TCM_RxCount==2)
	{
		if(rx!=0x15)
		{
			TCM_RxCount=0;
		}
	}
	else if(TCM_RxCount==1)
	{
		if(rx!=0x00)
		{
			TCM_RxCount=0;
		}
	}	
}
void TCM_SendData( void )
{
	TCM_EndProcCommand();	
	uint8_t tx[5]={0x00,0x05,0x04,0xbf,0x71};
	HAL_UART_Transmit(&TCMUart,tx,5,1000);
}
