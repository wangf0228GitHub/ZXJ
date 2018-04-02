#include "HardwareProfile.h"
#include "CP1616_NoAddr.h"
uint8_t CP1616_NoAddr_RxList[MAX_CP1616_NoAddr_RX];
uint16_t CP1616_NoAddr_RxCount;
uint16_t CP1616_NoAddr_NeedRxCount;
uint CP1616_NoAddr_Addr;
uint8_t CP1616_NoAddr_TxList[MAX_CP1616_NoAddr_RX];
uint16_t CP1616_NoAddr_TxCount;
uint8_t CP1616_NoAddr_NeedCommand;
void CP1616_NoAddr_Init(void)
{
	CP1616_NoAddr_NeedCommand=0xff;
	CP1616_NoAddr_EndProcCommand();
}
void CP1616_NoAddr_EndProcCommand(void)
{
	CP1616_NoAddr_NeedRxCount=0xffff;
	CP1616_NoAddr_RxCount=0;
}
uint8_t CP1616_NoAddr_DataProc(uint8_t rx)
{
	CP1616_NoAddr_RxList[CP1616_NoAddr_RxCount++]=rx;
	if(CP1616_NoAddr_RxCount>pCP1616_NoAddr_Data)
	{
		if(rx==0x0d && CP1616_NoAddr_RxCount==CP1616_NoAddr_NeedRxCount)
		{			
			return 1;			
		}
		else if(CP1616_NoAddr_RxCount>CP1616_NoAddr_NeedRxCount)
		{
			CP1616_NoAddr_RxCount=0;
			CP1616_NoAddr_NeedRxCount=0xffff;
		}
		else if(CP1616_NoAddr_RxCount>MAX_CP1616_NoAddr_RX)
		{
			CP1616_NoAddr_RxCount=0;
			CP1616_NoAddr_NeedRxCount=0xffff;				
		}
	}
	else if(CP1616_NoAddr_RxCount==pCP1616_NoAddr_Data)
	{
		CP1616_NoAddr_NeedRxCount=MAKE_INT(CP1616_NoAddr_RxList[3],CP1616_NoAddr_RxList[4])+pCP1616_NoAddr_Data+2;
	}
	else if(CP1616_NoAddr_RxCount==3)
	{
		if(CP1616_NoAddr_NeedCommand!=0xff)
		{
			if(CP1616_NoAddr_NeedCommand!=rx)
				CP1616_NoAddr_RxCount=0;
		}
	}
	else if(CP1616_NoAddr_RxCount==2)
	{
		if(rx!=0x16)
		{
			CP1616_NoAddr_RxCount=0;
		}
	}
	else if(CP1616_NoAddr_RxCount==1)
	{
		if(rx!=0x16)
		{
			CP1616_NoAddr_RxCount=0;
		}
	}	
	return 0;
}


