//Build F:\work_tfs\MCU\WYP\Saving2\Saving2 for device 18F6621
//Using driver C:\Program Files\HI-TECH Software\PICC-18\PRO\9.63\bin\picc18.exe
#include "HardwareProfile.h"
#include <stdio.h>
#include <stdlib.h>
#include "CP1616_Client.h"
#include "Function.h"
__CONFIG(1,IESOEN&HSPLL);
__CONFIG(2,PWRTEN&BOREN&BORV42&WDTPS32K&WDTEN);//看门狗2s复位
__CONFIG(3,MCLREN&CCP2RC1);
__CONFIG(4,STVREN&LVPDIS);
void InitSystem( void );
void main()
{	
	unsigned char i,sum;
	unsigned int ix,iy;
	__delay_ms(5);	
	InitSystem();
	__delay_ms(5);	
	while(1)
	{
		if(gFlags.bFastMode)
		{
			FastModeOut();
		}
		if(gFlags.bTB)
		{
			if((SystemTick-TBTick)>50)
			{
				gFlags.bTB=0;
				TB_W=0;
			}
		}
		if(CP1616_Client_Flags.Bits.bRx)
		{			
			sum=GetVerify_Sum(CP1616_Client_RxList,CP1616_Client_NeedRxCount-2);
			if(sum==CP1616_Client_RxList[CP1616_Client_NeedRxCount-2])	
			{
				switch(CP1616_Client_RxList[pCP1616_Client_CommandIndex])
				{
				case 1://快扫模式					
					gFlags.bFastMode=1;
					for(ix=0;ix<256;ix++)
					{
						FastModeData[ix]=CP1616_Client_RxList[pCP1616_ClientData+ix];
					}
					break;
				case 2://慢扫
					gFlags.bFastMode=0;
					DAC0832_WriteData(CP1616_Client_RxList[pCP1616_ClientData]);
					if(CP1616_Client_RxList[pCP1616_ClientData+1]==1)
					{
						TB_W=1;
						gFlags.bTB=1;
						TBTick=SystemTick;
					}					
					if(CP1616_Client_RxList[pCP1616_ClientData+1]==255)
					{
						TB_W=1;
						gFlags.bTB=1;
						TBTick=SystemTick;
					}
					break;
				}
				CP1616_Client_SendOK(CP1616_Client_RxList[pCP1616_Client_CommandIndex]);
			}
			CP1616_Client_EndProcCommand();
		}
		if(OERR)
		{
			CREN=0;
			NOP();
			CREN=1;
		}
	}		
}
void interrupt low_priority lowISR(void)
{
	unsigned char rx;	
	if(TMR0IE&&TMR0IF)
	{		
		CLRWDT();
		TMR0IF=0;
		SetTMR0();
		SystemTick++;
	}
	if(RCIE&&RCIF)
	{
		RCIF=0;
		rx=RCREG;
		CP1616_Client_ProcRx(rx);		
	}
}

