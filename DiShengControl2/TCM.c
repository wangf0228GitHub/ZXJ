#include "HardwareProfile.h"
#include "TCM.h"

_TCM_Flags TCM_Flags;
unsigned char TCM_RxList[MAX_TCM_RX];
unsigned char TCM_RxCount;
unsigned char TCM_NeedRxCount;
void TCM_EndProcCommand(void)
{
	TCM_Flags.bRx=0;
	TCM_NeedRxCount=0xff;
	TCM_RxCount=0;
}
void TCM_ProcRx(unsigned char rx)
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
	else if(TCM_RxCount==4)//判断地址
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
void __attribute__((__interrupt__,auto_psv)) _U1RXInterrupt(void)
{	
	unsigned char rx;
	_U1RXIF=0;
	while(U1STAbits.URXDA)
	{		
 		rx=(unsigned char)U1RXREG;
		//NMEA0183_RxProc(rx);
 		TCM_ProcRx(rx);
	}	
}

void TCM_SendData( void )
{
	TCM_EndProcCommand();
	TCM_TxByte(0x00);
	TCM_TxByte(0x05);
	TCM_TxByte(0x04);
	TCM_TxByte(0xBF);
	TCM_TxByte(0x71);
}

// void ProcCommandFromPC( void )
// {
// 	unsigned char sum,Command,tx[10],ret;
// 	uint crc;
// 	crc.u16=GetVerify_CRC16(TCM_RxList,TCM_NeedRxCount-2);
// 	if(crc.u8H!=TCM_RxList[TCM_NeedRxCount-2] || crc.u8L!=TCM_RxList[TCM_NeedRxCount-1])
// 	{
// 		TCM_EndProcCommand();
// 		return;
// 	}
// 	Command=TCM_RxList[pCP1616_CommandIndex];
// 	switch(Command)
// 	{
// 	case 1://电源开关控制
// 		PowerControl();		
// 		
// 		TCM_SendOK(Command);
// 		break;
// 	case 2://		
// 		TCM_EndProcCommand();
// 		ret= ModbusRTU_Master_ProcCommand03(0x0006,2);
// 		if(ret==0)
// 			TCM_SendError(Command);
// 		else
// 		{
// 			TCM_SendData(Command,ModbusRTU_Master_RxList+3,4);
// 		}
// 		break;
// 	case 3://
// 		TCM_EndProcCommand();
// 		break;
// 	case 4://
// 		TCM_EndProcCommand();
// 		break;
// 	case 5://漏水检测
// 		TCM_EndProcCommand();
// 		if(LouShui1_R==1)
// 			tx[0]=0xff;
// 		else
// 			tx[0]=0;
// 		if(LouShui2_R==1)
// 			tx[1]=0xff;
// 		else
// 			tx[1]=0;
// 		TCM_SendData(Command,tx,2);
// 		break;
// 	case 6://
// 		TCM_EndProcCommand();
// 		break;
// 	case 100://		
// 		TCM_EndProcCommand();
// 		break;
// 	default:
// 		TCM_EndProcCommand();
// 	}
// }


