#include "RIO.h"
#include "Variables.h"
#include "..\..\..\WF_Device\stm32\wfSys.h"
#include "..\..\..\WF_Device\Verify.h"
#include "..\..\..\WF_Device\wfDefine.h"

uint32_t bRIORx;
uint32_t bRIORead;
uint8_t RIO_RxList[MAX_RIO_RX];
uint8_t RIO_RxCount;
uint8_t RIO_NeedRxCount;
uint8_t RIO_Rx;
uint32_t RIOTick;
uint8_t RIO_PKGID;
uint16_t RIOCur;
uint8_t RIO_0E[6];
void RIO_EndProcCommand(void)
{
	bRIORx=0;
	RIO_NeedRxCount=0xff;
	RIO_RxCount=0;
}
void RIO_ProcRx(uint8_t rx)
{
	if(bRIORx!=0)
		return;
	RIO_RxList[RIO_RxCount++]=rx;
	if(RIO_RxCount>pRIOData)
	{
		if(RIO_RxCount==RIO_NeedRxCount && rx==0xa5)
		{			
			bRIORx=1;			
		}
		else if(RIO_RxCount>RIO_NeedRxCount)
		{
			RIO_RxCount=0;
			RIO_NeedRxCount=0xff;
		}
		else if(RIO_RxCount>MAX_RIO_RX)
		{
			RIO_RxCount=0;
			RIO_NeedRxCount=0xff;				
		}
	}
	else if(RIO_RxCount==3)//LEN
	{
		RIO_NeedRxCount=rx+2;
	}
// 	else if(RIO_RxCount==2)//PKT ID
// 	{
// 		if(rx!=0x15)
// 		{
// 			RIO_RxCount=0;
// 		}
// 	}
	else if(RIO_RxCount==1)//HDR
	{
		if(rx!=0xa9)
		{
			RIO_RxCount=0;
		}
	}	
}
uint32_t RIO_OpenSerial( void )
{	
	RIO_EndProcCommand();
	//RIOErr++;
	uint8_t tx[9]={0xA9,0x00,0x07,0x00,0xFF,0x02,0x24,0x2b,0xA5};
	tx[1]=RIO_PKGID++;
	tx[7]=GetVerify_Sum(tx,7);
	tx[7]=0xff-tx[7];
	tx[7]=tx[7]+1;
	HAL_UART_Transmit(&RIOUart,tx,9,1000);
	RIOTick=HAL_GetTick();
	while(1)
	{
		if(bRIORx!=0)
		{
			if(RIO_RxList[0x06]==0)//status
				return 1;
			else
				return 0;
		}
		if(GetDeltaTick(RIOTick)>50)
			return 0;
	}
}
uint32_t RIO_CloseSerial( void )
{	
	RIO_EndProcCommand();
	//RIOErr++;
	uint8_t tx[9]={0xA9,0x00,0x07,0x00,0xFF,0x02,0x25,0xED,0xA5};
	tx[1]=RIO_PKGID++;
	tx[7]=GetVerify_Sum(tx,7);
	tx[7]=0xff-tx[7];
	tx[7]=tx[7]+1;
	HAL_UART_Transmit(&RIOUart,tx,9,1000);
	RIOTick=HAL_GetTick();
	while(1)
	{
		if(bRIORx!=0)
		{
			if(RIO_RxList[0x06]==0)//status
				return 1;
			else
				return 0;
		}
		if(GetDeltaTick(RIOTick)>50)
			return 0;
	}
}
uint32_t RIO_ReadCommand(uint8_t CMDID)
{
	if(RIO_OpenSerial()==0)
		return 0;
	RIO_EndProcCommand();
	//RIOErr++;
	uint8_t tx[9]={0xA9,0x00,0x07,0x00,0xFF,0x01,0x0e,0x2b,0xA5};
	tx[1]=RIO_PKGID++;
	tx[6]=CMDID;
	tx[7]=GetVerify_Sum(tx,7);
	tx[7]=0xff-tx[7];
	tx[7]=tx[7]+1;
	HAL_UART_Transmit(&RIOUart,tx,9,1000);
	RIOTick=HAL_GetTick();
	while(1)
	{
		if(bRIORx!=0)
		{
			if(RIO_RxList[0x06]==0)//status
				return 1;
			else
				return 0;
		}
		if(GetDeltaTick(RIOTick)>50)
			return 0;
	}
	if(RIO_CloseSerial()==0)
		return 0;
}
uint32_t RIO_Write_0x27(uint16_t current)
{
	if(RIO_OpenSerial()==0)
		return 0;
	RIO_EndProcCommand();
	//RIOErr++;
	uint8_t tx[11]={0xA9,0x00,0x09,0x00,0xFF,0x02,0x27,0xaa,0x55,0x2b,0xA5};
	tx[1]=RIO_PKGID++;
	tx[7]=HIGH_BYTE(current);
	tx[8]=LOW_BYTE(current);
	tx[9]=GetVerify_Sum(tx,9);
	tx[9]=0xff-tx[9];
	tx[9]=tx[9]+1;
	HAL_UART_Transmit(&RIOUart,tx,11,1000);
	RIOTick=HAL_GetTick();
	while(1)
	{
		if(bRIORx!=0)
		{
			if(RIO_RxList[0x06]==0)//status
				return 1;
			else
				return 0;
		}
		if(GetDeltaTick(RIOTick)>50)
			return 0;
	}
	if(RIO_CloseSerial()==0)
		return 0;
}
