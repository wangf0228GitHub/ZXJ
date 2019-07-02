#include "HardwareProfile.h"
#include <stdio.h>
#include "stdlib.h"
#include "Function.h"
#include "..\..\..\WF_Device\CP1616_Master.h"
#include "..\..\..\WF_Device\CP1616_Client.h"

uint8_t FastModeData[256];
uint16_t FastModeDataIndex;
void Measurement(void)
{
	uint8_t x[2];
	uint16_t da;
	x[1]=FastModeDataIndex;
	da=FastModeDataIndex;
	da=da<<2;
	VOutput(da);
	__delay_ms(10);
	ShowAD_I();
	if(KEY_FS_R)//快速模式
	{
		FastModeData[FastModeDataIndex]=IValue>>1;
	}
	else//慢速模式
	{
		//送数据给2520
		x[0]=IValue>>1;
		CP1616_MasterWaitClientData(2,&x,2);
	}
}
void AutoMode_Init(void)
{
	/************************************************************************/
	/* TMR2为1ms定时器                                                      */
	/************************************************************************/
	TMR2IF=0;
	TMR2IE=0;
	PR2=50;
	T2CON=0b00100011;//5*16/4=20us
	Nms=0;
	TMR2IF=0;
	TMR2IE=1;
	TMR2ON=1;

	gFlags.bPause=0;
	FastModeDataIndex=0;
	if(KEY_FS_R)//快速模式
	{
		gFlags.bOldAutoMode=1;
	}
	else
	{
		gFlags.bOldAutoMode=0;
	}
	Measurement();
}

void AutoModeProc(void)
{	
	while(1)
	{
		if(KEY_FS_R)//快速模式
		{
			if(gFlags.bOldAutoMode==0)//之前是慢扫
			{
				gFlags.bPause=0;
				FastModeDataIndex=0;
				gFlags.bOldAutoMode=1;
			}
			if(gFlags.bPause)//循环采集暂停2s
			{
				if(Nms>2000)
				{
					Nms=0;
					gFlags.bPause=0;
					FastModeDataIndex=0;
					Measurement();
				}
			}
			else
			{
				if(Nms>39)
				{
					Nms=0;
					if(FastModeDataIndex==256)//采集一圈
					{
						FastModeDataIndex=0;
						gFlags.bPause=1;						
						//送数据给2520
						CP1616_MasterWaitClientData(1,FastModeData,256);
						Measurement();
					}
					else
					{
						FastModeDataIndex++;
						Measurement();
					}
				}
			}		
		}
		else//慢速模式
		{
			if(gFlags.bOldAutoMode==1)//之前是快扫
			{
				gFlags.bPause=0;
				FastModeDataIndex=0;
				gFlags.bOldAutoMode=0;		
				Measurement();
			}
			if(gFlags.bPause)//循环采集暂停50s
			{
				if(Nms>50000)
				{
					Nms=0;
					gFlags.bPause=0;
					FastModeDataIndex=0;			
					Measurement();
				}
				else
				{
					if(Nms%100==0)
					{
						Measurement();
						__delay_20ms(5);
					}
				}
			}
			else
			{
				if(Nms>781)
				{
					Nms=0;
					if(FastModeDataIndex==255)//采集一圈
					{
						FastModeDataIndex=0;
						gFlags.bPause=1;			
						Measurement();
					}
					else
					{						
						Measurement();
						FastModeDataIndex++;
					}
				}
			}	
		}
		if(OERR1)
		{
			CREN1=0;
			NOP();
			CREN1=1;
		}
		if(OERR2)
		{
			CREN2=0;
			NOP();
			CREN2=1;
		}
		if(CP1616_Client_Flags.Bits.bRx)
		{			
			CP1616_Client_SendError(CP1616_Client_RxList[pCP1616_Client_CommandIndex],0x10);
			CP1616_Client_EndProcCommand();		
		}
		if(KEY_Mode_R)//手动模式,退出自动模式
			return;
	}
}
