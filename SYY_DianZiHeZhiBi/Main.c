//Build F:\work_tfs\MCU\WYP\Saving2\Saving2 for device 18F6621
//Using driver C:\Program Files\HI-TECH Software\PICC-18\PRO\9.63\bin\picc18.exe
#include "HardwareProfile.h"
#include <stdio.h>
#include <stdlib.h>
#include "Function.h"
__CONFIG(1,OSCSDIS&HSHW);
__CONFIG(2,PWRTEN&BOREN&BORV42&WDTPS32K&WDTEN);//看门狗2s复位
__CONFIG(3,MCLREN&CCP2RC1);
__CONFIG(4,STVREN&LVPDIS);
void AutoMode_Init(void);
void AutoModeProc(void);
void ManualMode_Init(void);
void ManualModeProc(void);
void main()
{	
	unsigned char i;
	unsigned int AD;
	__delay_ms(5);	
	InitSystem();
	__delay_ms(5);
	GIE = 1;
	while(1)
	{
		FlashTick();
		if (knobFlags.AllFlag != 0)
		{
			Beep_W = 1;
			if (knobFlags.bCW3)
			{
				if(Ic<450)
				{
					Ic += Icset;
					if (Ic > 450)
						Ic = 450;
					gFlags.bSetIc = 1;
					gFlags.bSetIc_Show = 1;
					SetTick_Ic = SystemTick;
					DASet(0x02);
					Display_ShowSet(0x02);
				}
			}
			if (knobFlags.bCCW3)
			{
				if (Ic != 0)
				{
					if (Ic <= Icset)
						Ic = 0;
					else
						Ic -= Icset;
					gFlags.bSetIc = 1;
					gFlags.bSetIc_Show = 1;
					SetTick_Ic = SystemTick;
					DASet(0x02);
					Display_ShowSet(0x02);
				}
			}
			if (knobFlags.bCW1)
			{
				if(If<850)
				{
					If += Ifset;
					if (If > 850)
						If = 850;
					gFlags.bSetIf = 1;
					gFlags.bSetIf_Show = 1;
					SetTick_If = SystemTick;
					DASet(0x01);
					Display_ShowSet(0x01);
				}
			}
			if (knobFlags.bCCW1)
			{
				if (If != 0)
				{
					if (If <= Ifset)
						If = 0;
					else
						If -= Ifset;
					gFlags.bSetIf = 1;
					gFlags.bSetIf_Show = 1;
					SetTick_If = SystemTick;
					DASet(0x01);
					Display_ShowSet(0x01);
				}
			}
			if (knobFlags.bCW2)
			{
				if(U<1500)
				{
					U += Uset;
					if (U > 1500)
						U = 1500;
					gFlags.bSetU = 1;
					gFlags.bSetU_Show = 1;
					SetTick_U = SystemTick;
					DASet(0x04);
					Display_ShowSet(0x04);
				}
			}
			if (knobFlags.bCCW2)
			{
				if (U != 0)
				{
					if (U <= Uset)
						U = 0;
					else
						U -= Uset;
					gFlags.bSetU = 1;
					gFlags.bSetU_Show = 1;
					SetTick_U = SystemTick;
					DASet(0x04);
					Display_ShowSet(0x04);
				}
			}
			knobFlags.AllFlag = 0;
			__delay_ms(10);
			Beep_W = 0;
		}
		if (K3_R == 0)
		{
			__delay_ms(5);
			if (K3_R == 0)
			{
				Beep_W = 1;	
				gFlags.bSetIc_Show = 0;
				if (gFlags.bSetIc)
				{			
					Display_ShowSet(0x02);
					if (Icset == 10)
						Icset = 100;
// 					else if (Icset == 100)
// 						Icset = 1;
					else
						Icset = 10;
				}
				else
				{
					gFlags.bSetIc = 1;
					Icset = 10;
				}
				SetTick_Ic = SystemTick;
				Display_ShowFlash(0x02);
				__delay_20ms(3);
				Beep_W = 0;
				while (K3_R == 0)
				{
					FlashTick();
				}
			}
		}
		if (K1_R == 0)
		{
			__delay_ms(5);
			if (K1_R == 0)
			{
				Beep_W = 1;
				gFlags.bSetIf_Show = 0;
				if(gFlags.bSetIf)				
				{
					Display_ShowSet(0x01);
					if (Ifset == 10)
						Ifset = 100;
					else
						Ifset = 10;
				}
				else
				{
					gFlags.bSetIf = 1;
					Ifset = 10;
				}
				SetTick_If = SystemTick;
				Display_ShowFlash(0x01);
				__delay_20ms(3);
				Beep_W = 0;
				while (K1_R == 0)
				{
					FlashTick();
				}
			}
		}
		if (K2_R == 0)
		{
			__delay_ms(5);
			if (K2_R == 0)
			{
				Beep_W = 1;
				gFlags.bSetU_Show = 0;
				if(gFlags.bSetU)
				{
					Display_ShowSet(0x04);
					if (Uset == 10)
						Uset = 100;
					else
						Uset = 10;
				}
				else
				{
					gFlags.bSetU = 1;
					Uset = 10;
				}
				SetTick_U = SystemTick;
				Display_ShowFlash(0x04);
				__delay_20ms(3);
				Beep_W = 0;
				while (K2_R == 0)
				{
					FlashTick();
				}
			}
		}
		if (K4_R == 0)
		{
			__delay_ms(5);
			if (K4_R == 0)
			{
				Beep_W = 1;
// 				Ia0 = MCP3201_ReadAD() / 4;
// 				Display_ShowIa();
				AD = 0;
				for (i = 0; i < 8; i++)
				{
					AD += MCP3201_ReadAD();
				}
				AD = AD / 8;
				Ia0 = AD / 4;
				__delay_20ms(3);
				Beep_W = 0;
				while (K4_R == 0)
				{
					FlashTick();
				}
			}
		}
		if (GetDeltaTick(IaTick) > 3)
		{
			Display_ShowIa();
			IaTick = SystemTick;
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
}

void interrupt HighISR(void)
{
	unsigned char rx;
	if (knobFlags.AllFlag != 0)
	{
		INT0IF = 0;
		INT1IF = 0;
		INT2IF = 0;
		return;
	}
	knobFlags.AllFlag = 0;
	//下降沿中断
	if (INT0IE&&INT0IF)
	{
		INT0IF = 0;
		__delay_us(50);
		if (RB0 != 0)
			return;
		if (K1_A_R == 0)
			knobFlags.bCW1 = 1;
		else
			knobFlags.bCCW1 = 1;
	}
	if (INT1IE&&INT1IF)
	{
		INT1IF = 0;
		__delay_us(50);
		if (RB1 != 0)
			return;
		if (K3_A_R == 0)
			knobFlags.bCW3 = 1;
		else
			knobFlags.bCCW3 = 1;
	}
	if (INT2IE&&INT2IF)
	{
		INT2IF = 0;
		__delay_us(50);
		if (RB2 != 0)
			return;
		if (K2_A_R == 0)
			knobFlags.bCW2 = 1;
		else
			knobFlags.bCCW2 = 1;
	}	
}

