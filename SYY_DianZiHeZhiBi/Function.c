#include "HardwareProfile.h"
#include "Function.h"
unsigned char DisplayLine_If[10];
unsigned char DisplayLine_Ic[10];
unsigned char DisplayLine_U[10];
unsigned char DisplayLine_Ia[10];
#include <stdio.h>

#define TM1650_LEDNumCode_Sub 0x40
#define TM1650_LEDNumCode_P 0x73
#define TM1650_LEDNumCode_Off 0x17
#define TM1650_LEDNumCode_L 0x38
#define TM1650_LEDNumCode_H 0x76
#define Display_LED_Off 0x00
#define Display_SetDP(x) x=x|0x80

const unsigned char Display_LEDAddr[4]={0x68,0x6a,0x6c,0x6e};//从左至右
void __delay_20ms(uint16_t x)
{
	while (x--)
	{
		__delay_ms(20);
	}
}
void Display_Init(void)
{
	TM1650_Init();
	while(TM1650_WriteData(0x48,0x11)==0);
	TM1650_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[0] | 0x80);
	TM1650_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[1]);
	TM1650_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[2]);
	TM1650_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[3]);

	TM1650_2_Init();
	while(TM1650_2_WriteData(0x48,0x11)==0);
	TM1650_2_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[0] | 0x80);
	TM1650_2_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[1]);
	TM1650_2_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[2]);
	TM1650_2_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[3]);

	TM1650_3_Init();
	while (TM1650_3_WriteData(0x48, 0x11) == 0);
 	TM1650_3_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[0]);
 	TM1650_3_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[1]);
 	TM1650_3_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[2] | 0x80);
 	TM1650_3_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[3]);

	TM1650_4_Init();
	while (TM1650_4_WriteData(0x48, 0x11) == 0);
	TM1650_4_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[0]);
	TM1650_4_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[1]);
	TM1650_4_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[2]);
	TM1650_4_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[3]);
}
void Display_ShowIa(void)
{
	//I=AD*2.048/4096*1000/2=AD/4
	uint8_t i;
	int Ia;
	uint16_t AD=0;
	for (i = 0; i < 4; i++)
	{
		AD += MCP3201_ReadAD();
	}
	AD = AD / 4;
	Ia = AD / 4;
	Ia = Ia - Ia0;
	int len = sprintf(DisplayLine_Ia, "%+d", Ia);
	for (i = 0; i < (len - 1); i++)
	{
		TM1650_4_WriteData(Display_LEDAddr[3 - i], TM1650_LEDNumCode[DisplayLine_Ia[len - 1 - i] - '0']);
		if (i == 3)
			break;
	}
	if(len<4)
	{
		for (i = 0; i < (5 - len); i++)
		{
			TM1650_4_WriteData(Display_LEDAddr[i], 0);
		}
	}
	if (Ia < 0)
	{
		if(len<5)
			TM1650_4_WriteData(Display_LEDAddr[4 - len], TM1650_LEDNumCode_Sub);
		else
			TM1650_4_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[DisplayLine_Ia[len - 4] - '0'] | TM1650_LEDNumCode_Sub);
	}
}
void DASet(uint8_t who)
{
	uint32_t x;
	if ((who & 0x01) != 0)
	{
		//灯丝电流If ：0-0.850A
		//DA=If*(1.024/850)*65536/2.048=If*32
		x = (uint32_t)If;
		x = x << 15;
		x = x / 850;
		DAC8830_2_Setting((uint16_t)x);
	}
	if ((who & 0x02) != 0)
	{
		//励磁电流IC ：0 - 0.450A
		//DA=IC*(1.024/450)*65536/2.048=If*32
		x = (uint32_t)Ic;
		x = x << 15;
		x = x / 450;
		DAC8830_3_Setting((uint16_t)x);
	}
	if ((who & 0x04) != 0)
	{
		//阳极电压U：0-150.0V
		//DA=U*(1.5/1500)*65536/2.048=U*32
		DAC8830_Setting((uint16_t)(U << 5));		
	}
}
void Display_ShowSet(uint8_t who)
{
	uint32_t x;
	if((who&0x01)!=0)
	{
		//灯丝电流If ：0-0.850A
		//DA=If*(1.024/850)*65536/2.048=If*32
		sprintf(DisplayLine_If, "%03d", If);
		TM1650_2_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[0] | 0x80);
		TM1650_2_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_If[0] - '0']);
		TM1650_2_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[DisplayLine_If[1] - '0']);
		TM1650_2_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[0]);
	}
	if ((who & 0x02) != 0)
	{
		//励磁电流IC ：0 - 0.450A
		//DA=IC*(1.024/450)*65536/2.048=If*32
		sprintf(DisplayLine_Ic, "%03d", Ic);
		TM1650_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[0] | 0x80);
		TM1650_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_Ic[0] - '0']);
		TM1650_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[DisplayLine_Ic[1] - '0']);
		TM1650_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[DisplayLine_Ic[2] - '0']);
	}
	if ((who & 0x04) != 0)
	{
		//阳极电压U：0-150.0V
		//DA=U*(1.5/1500)*65536/2.048=U*32
		sprintf(DisplayLine_U, "%04d", U);
// 		if (DisplayLine_U[0] == '0')
// 		{
// 			TM1650_3_WriteData(Display_LEDAddr[0], 0);
// 			if (DisplayLine_U[1] == '0')
// 				TM1650_3_WriteData(Display_LEDAddr[1], 0);
// 			else
// 				TM1650_3_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_U[1] - '0']);
// 		}
// 		else
// 		{
// 			TM1650_3_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[DisplayLine_U[0] - '0']);
// 			TM1650_3_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_U[1] - '0']);
// 		}
		TM1650_3_WriteData(Display_LEDAddr[0], TM1650_LEDNumCode[DisplayLine_U[0] - '0']);
		TM1650_3_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_U[1] - '0']);
		TM1650_3_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[DisplayLine_U[2] - '0'] | 0x80);
		TM1650_3_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[DisplayLine_U[3] - '0']);
	}
}
void Display_ShowFlash(uint8_t who)
{
	uint32_t x;
	if ((who & 0x01) != 0)
	{
		//灯丝电流If ：0-0.850A
		//DA=If*(1.024/850)*65536/2.048=If*32
		FlashTick_If = SystemTick;
		if (Ifset == 10)
		{
			if (gFlags.bSetIf_Show)
			{
				TM1650_2_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[DisplayLine_If[1] - '0']);
			}
			else
			{
				TM1650_2_WriteData(Display_LEDAddr[2], 0);
			}
		}
		if (Ifset == 100)
		{
			if (gFlags.bSetIf_Show)
			{
				TM1650_2_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_If[0] - '0']);
			}
			else
			{
				TM1650_2_WriteData(Display_LEDAddr[1], 0);
			}
		}
		gFlags.bSetIf_Show = !gFlags.bSetIf_Show;
	}
	if ((who & 0x02) != 0)
	{
		//励磁电流IC ：0 - 0.450A
		//DA=IC*(1.024/450)*65536/2.048=If*32
		FlashTick_Ic = SystemTick;
		if (Icset == 1)
		{
			if (gFlags.bSetIc_Show)
			{
				TM1650_WriteData(Display_LEDAddr[3], TM1650_LEDNumCode[DisplayLine_Ic[2] - '0']);
			}
			else
			{
				TM1650_WriteData(Display_LEDAddr[3], 0);
			}
		}
		if (Icset == 10)
		{
			if (gFlags.bSetIc_Show)
			{
				TM1650_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[DisplayLine_Ic[1] - '0']);
			}
			else
			{
				TM1650_WriteData(Display_LEDAddr[2], 0);
			}
		}
		if (Icset == 100)
		{
			if (gFlags.bSetIc_Show)
			{
				TM1650_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_Ic[0] - '0']);
			}
			else
			{
				TM1650_WriteData(Display_LEDAddr[1], 0);
			}
		}
		gFlags.bSetIc_Show = !gFlags.bSetIc_Show;
	}
	if ((who & 0x04) != 0)
	{
		//阳极电压U：0-150.0V
		//DA=U*(1.5/1500)*65536/2.048=U*32
		FlashTick_U = SystemTick;
		if (Uset == 100)
		{
			if (gFlags.bSetU_Show)
			{
				TM1650_3_WriteData(Display_LEDAddr[1], TM1650_LEDNumCode[DisplayLine_U[1] - '0']);
			}
			else
			{
				TM1650_3_WriteData(Display_LEDAddr[1], 0);
			}
		}
		if (Uset == 10)
		{
			if (gFlags.bSetU_Show)
			{
				TM1650_3_WriteData(Display_LEDAddr[2], TM1650_LEDNumCode[DisplayLine_U[2] - '0'] | 0x80);
			}
			else
			{
				TM1650_3_WriteData(Display_LEDAddr[2], 0);
			}
		}
		gFlags.bSetU_Show = !gFlags.bSetU_Show;
	}
}
void FlashTick(void)
{
	
	if (gFlags.bSetIf==1 && GetDeltaTick(FlashTick_If)>3)
	{
		Display_ShowFlash(0x01);
		FlashTick_If = SystemTick;
	}
	if (gFlags.bSetIc == 1 && GetDeltaTick(FlashTick_Ic)>3)
	{
		Display_ShowFlash(0x02);
		FlashTick_Ic = SystemTick;
	}
	if (gFlags.bSetU == 1 && GetDeltaTick(FlashTick_U)>3)
	{
		Display_ShowFlash(0x04);
		FlashTick_U = SystemTick;
	}
	if (gFlags.bSetIf == 1 && GetDeltaTick(SetTick_If) > 30)
	{
		gFlags.bSetIf_Show = 1;
		Display_ShowFlash(0x01);
		gFlags.bSetIf = 0;
	}
	if (gFlags.bSetIc == 1 && GetDeltaTick(SetTick_Ic) > 30)
	{
		gFlags.bSetIc_Show = 1;
		Display_ShowFlash(0x02);
		gFlags.bSetIc = 0;
	}
	if (gFlags.bSetU == 1 && GetDeltaTick(SetTick_U) > 30)
	{
		gFlags.bSetU_Show = 1;
		Display_ShowFlash(0x04);
		gFlags.bSetU = 0;
	}
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
// void VOutput(uint16_t da)
// {
// 	uint8_t x;
// 	float v=da*0.082;//ad/1024*2.048*2*20.5
// // 	uint16_t v;
// // 	v=da<<3;//乘8，ad/1024*2.048*2*100*20,1mV
// 	sprintf(DisplayLine,"%04.1f",v);
// 	x=TM1650_LEDNumCode[DisplayLine[1]-'0'];
// 	Display_SetDP(x);
// 	Display_WriteData_2(Display_LEDAddr[0],Display_LED_Off); 
// 	if(DisplayLine[0]=='0')
// 		Display_WriteData_2(Display_LEDAddr[1],Display_LED_Off);
// 	else
// 		Display_WriteData_2(Display_LEDAddr[1],TM1650_LEDNumCode[DisplayLine[0]-'0']);
// 	Display_WriteData_2(Display_LEDAddr[2],x);
// 	Display_WriteData_2(Display_LEDAddr[3],TM1650_LEDNumCode[DisplayLine[3]-'0']);
// 	da=da<<2;
// 	da=da&0x0ffc;
// 	TLC5615_WriteData(da);
// }
// void ReadAD_RP(void)
// {
// 	uint8_t i;
// 	uint16_t ad;
// 	ADCON0=0x01;//通道0
// 	__delay_ms(1);
// 	ad=0;
// 	for(i=0;i<4;i++)
// 	{
// 		GODONE=1;
// 		while(GODONE);
// 		ad+=MAKE_SHORT(ADRESH,ADRESL);
// 	}
// 	RPValue=ad>>2;
// }
// 
// void ShowAD_I(void)
// {
// 	uint8_t i;
// 	uint16_t ad;
// 	ADCON0=0x05;//通道1
// 	__delay_ms(1);
// 	ad=0;
// 	for(i=0;i<8;i++)
// 	{
// 		GODONE=1;
// 		while(GODONE);
// 		ad+=MAKE_SHORT(ADRESH,ADRESL);
// 	}
// 	IValue=ad>>3;
// 	if(IValue<RomParams.AD0)
// 	{
// 		IValue=RomParams.AD0-IValue;
// 		IValue=IValue>>1;
// 		if(IValue==0)
// 		{
// 			Display_WriteData(Display_LEDAddr[0],Display_LED_Off); 
// 		}
// 		else
// 		{
// 			Display_WriteData(Display_LEDAddr[0],TM1650_LEDNumCode[0x10]); 
// 		}		
// 	}
// 	else
// 	{
// 		IValue=IValue-RomParams.AD0;
// 		Display_WriteData(Display_LEDAddr[0],Display_LED_Off); 
// 		IValue=IValue>>1;		
// 	}
// 	
// 	
// 	sprintf(DisplayLine,"%03d",IValue);
// 	
// 	if(DisplayLine[0]=='0')
// 		Display_WriteData(Display_LEDAddr[1],Display_LED_Off);
// 	else
// 		Display_WriteData(Display_LEDAddr[1],TM1650_LEDNumCode[DisplayLine[0]-'0']);
// 	if(DisplayLine[0]=='0' && DisplayLine[1]=='0')
// 		Display_WriteData(Display_LEDAddr[2],Display_LED_Off);
// 	else
// 		Display_WriteData(Display_LEDAddr[2],TM1650_LEDNumCode[DisplayLine[1]-'0']);
// 	Display_WriteData(Display_LEDAddr[3],TM1650_LEDNumCode[DisplayLine[2]-'0']);
// }
