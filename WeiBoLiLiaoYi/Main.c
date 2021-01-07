//Using driver C:\Program Files\HI-TECH Software\PICC\9.71a\bin\picc.exe
#include "HardwareProfile.h"

//__CONFIG(HS&WDTEN&PWRTEN&MCLREN&BOREN);
__CONFIG(HS&
			WDTEN&
			PWRTEN&
			MCLREN&
			BOREN&
			CP&
			CPD&
			IESODIS&
			FCMDIS&
			LVPDIS);

// __CONFIG(HS&
// 	MCLREN&
// 	IESODIS&
// 	FCMDIS&
// 	LVPDIS);


__CONFIG(BORV40&
	WP2);


//GFlags gFlags;
//unsigned int SystemTick;
//unsigned int BeepTick;
//unsigned int KeyTick;
//unsigned char MCTime_M;//介入时间
//unsigned char MCTime_S;//介入时间
//unsigned char MCLevel;//介入周期
void main()
{
	InitSystem();
	while(1)
	{		
		CLRWDT();	
		KeyProc();
		if(GetDeltaTick(BeepTick)>1)
		{
			BZ_W=0;
		}
		if(gFlags.Bits.bWork)
		{
			if (gFlags.Bits.bHalfSecond)
			{
				gFlags.Bits.bHalfSecond = 0;
				SLed_Toggle();
			}
			if (gFlags.Bits.bSecond)
			{
				gFlags.Bits.bSecond = 0;				
				if (MCTime_S == 0)
				{
					if (MCTime_M == 0)//工作完成
					{
						gFlags.Bits.bWork = 0;
						TMR2ON = 0;
						SLed_ON();//秒灯点亮
						U5_8_OFF();
						TLV56XX_WriteData(0);
						DAStop();
						BZ_ON();
						__delay_20ms(10);
						BZ_OFF();
						__delay_20ms(20);
						BZ_ON();
						__delay_20ms(10);
						BZ_OFF();
						__delay_20ms(20);
						BZ_ON();
						__delay_20ms(10);
						BZ_OFF();
						__delay_20ms(20);
						MCLevel = 1;
						MCTime_M = 15;
						MCTime_S = 00;
						T2Times = 0;
						TMR2 = 0;
						LED_MCTime();
						LED_MCLevel();
					}
					else
					{
						MCTime_M--;
						MCTime_S = 59;
						LED_MCTime();
						if (gFlags.Bits.bPause)
						{
							U5_8_W = !U5_8_W;
						}
					}
				}
				else
				{
					MCTime_S--;
					LED_MCTime();
					if (gFlags.Bits.bPause)
					{
						if ((MCTime_S & 0x01) == 0)
							U5_8_W = !U5_8_W;
					}
				}
			}
		}
	}
}
void interrupt lowISR(void)
{	
	if(TMR1IE&&TMR1IF)
	{				
		CLRWDT();
		TMR1IF=0;
		WRITETIMER1(T1_100ms);//100ms
		SystemTick++;			
	}	
	if (TMR2IE&&TMR2IF)
	{
		TMR2IF=0;
		T2Times++;
		if (T2Times == 50)
		{
			T2Times = 0;
			gFlags.Bits.bSecond = 1;
			gFlags.Bits.bHalfSecond = 1;
		}
		else if (T2Times == 25)
		{
			gFlags.Bits.bHalfSecond = 1;
		}
	}
}
