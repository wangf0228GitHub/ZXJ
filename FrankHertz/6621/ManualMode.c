#include "HardwareProfile.h"
#include <stdio.h>
#include "stdlib.h"
#include "Function.h"
#include "..\..\..\WF_Device\CP1616_Client.h"
#include "..\..\..\WF_Device\Verify.h"
#include "..\..\..\WF_Device\wfDefine.h"


void ManualMode_Init(void)
{
	ManualMeasTick=SystemTick-100;
}
void PCModeProc(void)
{
	uint8_t txI[2];
	while(1)
	{
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
			switch(CP1616_Client_RxList[pCP1616_Client_CommandIndex])
			{
			case 1://连接
				CP1616_Client_SendOK(CP1616_Client_RxList[pCP1616_Client_CommandIndex]);
				CP1616_Client_EndProcCommand();
				break;
			case 2://断开
				CP1616_Client_SendOK(CP1616_Client_RxList[pCP1616_Client_CommandIndex]);
				CP1616_Client_EndProcCommand();
				return;
			case 3://采集
				VOutput(MAKE_SHORT(CP1616_Client_RxList[pCP1616_ClientData],CP1616_Client_RxList[pCP1616_ClientData+1]));
				__delay_20ms(1);
				ShowAD_I();
				txI[0]=HIGH_BYTE(IValue);
				txI[1]=LOW_BYTE(IValue);
				CP1616_Client_SendData(CP1616_Client_RxList[pCP1616_Client_CommandIndex],txI,2);
				CP1616_Client_EndProcCommand();
				break;
			default:
				CP1616_Client_SendError(CP1616_Client_RxList[pCP1616_Client_CommandIndex],0x02);
				CP1616_Client_EndProcCommand();
				break;
			}		
		}
		if(KEY_Mode_R==0)//自动模式,退出手动模式
			return;		
	}
}
void ManualModeProc(void)
{	
	uint8_t i;
	uint16_t ad;
	while(1)
	{	
		//CP1616_Client_TxByte(0x55);
		ad=SystemTick;
		ad=ad-ManualMeasTick;
		//if(ad>10)
		{
			ManualMeasTick=SystemTick;
			ReadAD_RP();
			VOutput(RPValue);
			__delay_20ms(1);
			ShowAD_I();
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
			switch(CP1616_Client_RxList[pCP1616_Client_CommandIndex])
			{
			case 1://连接
				CP1616_Client_SendOK(CP1616_Client_RxList[pCP1616_Client_CommandIndex]);
				CP1616_Client_EndProcCommand();
				PCModeProc();
				break;
			default:
				CP1616_Client_SendError(CP1616_Client_RxList[pCP1616_Client_CommandIndex],0x02);
				CP1616_Client_EndProcCommand();
				break;
			}		
		}
		if(KEY_Mode_R==0)//自动模式,退出手动模式
			return;
		if(KEY_C0_R==0)//清零按钮
		{
			__delay_20ms(1);
			if(KEY_C0_R==0)
			{
				ADCON0=0x05;//通道1
				__delay_ms(1);
				ad=0;
				for(i=0;i<8;i++)
				{
					GODONE=1;
					while(GODONE);
					ad+=MAKE_SHORT(ADRESH,ADRESL);
				}
			}
			RomParams.AD0=ad>>3;
			SaveRomData();
			while(KEY_C0_R==0);
		}
	}
}
