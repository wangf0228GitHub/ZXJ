#include "HardwareProfile.h"
void PowerControl(void);
void __attribute__((__interrupt__,auto_psv)) _U1RXInterrupt(void)
{	
	unsigned char rx;
	_U1RXIF=0;
	while(U1STAbits.URXDA)
	{
		rx=(unsigned char)U1RXREG;
		//CP1616_Client_ProcRx(rx);
	}	
}
//void ProcCommandFromPC( void )
//{
//	unsigned char sum,Command,tx[10],ret;
//	sum=GetVerify_Sum(CP1616_Client_RxList,CP1616_Client_NeedRxCount-2);
//	if(sum!=CP1616_Client_RxList[CP1616_Client_NeedRxCount-2])
//	{
//		CP1616_Client_EndProcCommand();
//		return;
//	}
//	Command=CP1616_Client_RxList[pCP1616_CommandIndex];
//	switch(Command)
//	{
//	case 1://电源开关控制
//		PowerControl();		
//		
//		CP1616_Client_SendOK(Command);
//		break;
//	case 2://		
//		CP1616_Client_EndProcCommand();
//		ret= ModbusRTU_Master_ProcCommand03(0x0006,2);
//		if(ret==0)
//			CP1616_Client_SendError(Command);
//		else
//		{
//			CP1616_Client_SendData(Command,ModbusRTU_Master_RxList+3,4);
//		}
//		break;
//	case 3://
//		CP1616_Client_EndProcCommand();
//		break;
//	case 4://
//		CP1616_Client_EndProcCommand();
//		break;
//	case 5://漏水检测
//		CP1616_Client_EndProcCommand();
//		if(LouShui1_R==1)
//			tx[0]=0xff;
//		else
//			tx[0]=0;
//		if(LouShui2_R==1)
//			tx[1]=0xff;
//		else
//			tx[1]=0;
//		CP1616_Client_SendData(Command,tx,2);
//		break;
//	case 6://
//		CP1616_Client_EndProcCommand();
//		break;
//	case 100://		
//		CP1616_Client_EndProcCommand();
//		break;
//	default:
//		CP1616_Client_EndProcCommand();
//	}
//}


