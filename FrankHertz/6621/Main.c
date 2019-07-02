//Build F:\work_tfs\MCU\WYP\Saving2\Saving2 for device 18F6621
//Using driver C:\Program Files\HI-TECH Software\PICC-18\PRO\9.63\bin\picc18.exe
#include "HardwareProfile.h"
#include <stdio.h>
#include <stdlib.h>
#include "CP1616_Client.h"
#include "..\..\..\WF_Device\CP1616_Master.h"
#include "Function.h"
__CONFIG(1,OSCSDIS&HSHW);
__CONFIG(2,PWRTEN&BOREN&BORV42&WDTPS32K&WDTDIS);//看门狗2s复位
__CONFIG(3,MCLREN&CCP2RC1);
__CONFIG(4,STVREN&LVPDIS);
void AutoMode_Init(void);
void AutoModeProc(void);
void ManualMode_Init(void);
void ManualModeProc(void);
void main()
{	
	unsigned char i;
	unsigned int ix,iy;
	__delay_ms(5);	
	InitSystem();
	__delay_ms(5);
	while(1)
	{
		if(KEY_Mode_R)//手动模式
		{
			ManualMode_Init();
			ManualModeProc();
		}
		else//自动模式
		{
			AutoMode_Init();
			AutoModeProc();
		}			
	}		
}
void interrupt low_priority lowISR(void)
{
	unsigned char rx;
	
	if(RC2IE&&RC2IF)
	{
		RC2IF=0;
		rx=RCREG2;
		CP1616_Master_ProcRx(rx);
	}
	if(TMR0IE&&TMR0IF)
	{		
		CLRWDT();
		TMR0IF=0;
		SetTMR0();
		SystemTick++;
	}
	if(TMR2IE&&TMR2IF)
	{
		TMR2IF=0;
		Nms++;
	}
	if(RC1IE&&RC1IF)
	{
		RC1IF=0;
		rx=RCREG1;
		CP1616_Client_ProcRx(rx);
	}
}

