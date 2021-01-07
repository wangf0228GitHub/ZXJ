#include "HardwareProfile.h"
// #define Key_MCTime 	0x0004
// #define Key_MCLevel 0x0040
// #define Key_Set	 	0x0400
// #define Key_SE 		0x0200
// #define Key_Up 		0x0020
// #define Key_Down	0x0002
// #define Key_Enter	0x0001

unsigned int OldKey;
unsigned char KeyTimes;
void KeyProc(void)
{
	unsigned int key;
	TM1638_ReadKey();
	key=TM1638_KeyValue.u16s.u16L.u16;
	if(key==0)
	{
		gFlags.Bits.bReKey=1;
		OldKey=0;
		KeyTimes = 0;
		return;
	}
 	if(key==OldKey)//之前已经按过按键了，属于重复触发
 	{
 		if(!gFlags.Bits.bReKey)
 			return;		
		if (GetDeltaTick(KeyTick) > 4)
		{
			KeyTick = SystemTick;
			KeyTimes++;
		}
 		else 
 			return;
 	}
 	else
 	{
 		KeyTick=SystemTick;
 		OldKey=key;
 		gFlags.Bits.bReKey=1;
		KeyTimes=1;
 	} 	
 	switch(key)
 	{ 	
	case KEY_S1: //时间-
		gFlags.Bits.bReKey=1;
		if (KeyTimes < 2)
			MCTime_M--;
		else if (KeyTimes < 8)
			MCTime_M -= 2;
		else
			MCTime_M -= 3;
		if (MCTime_M > 30)
		{
			MCTime_M = 0;
			gFlags.Bits.bReKey = 0;
		}
		LED_MCTime();
//		if (KeyTimes == 1)
//		{
//			Beep();
//		}
		break;
	case KEY_S4: //时间+
		gFlags.Bits.bReKey = 1;
		if (KeyTimes < 2)
			MCTime_M++;
		else if (KeyTimes < 8)
			MCTime_M += 2;
		else
			MCTime_M += 3;
		if (MCTime_M >30)
			MCTime_M=30;
		LED_MCTime();
//		if (KeyTimes == 1)
//		{
//			Beep();
//		}
		break;
	case KEY_S6: //功率-
		gFlags.Bits.bReKey = 1;
		if (KeyTimes < 2)
			MCLevel--;
		else if (KeyTimes < 8)
			MCLevel -= 2;
		else
			MCLevel -= 3;
		if (MCLevel > 30 || MCLevel==0)
		{
			MCLevel = 1;
			gFlags.Bits.bReKey = 0;
		}
		LED_MCLevel();
		if (gFlags.Bits.bWork)
		{
			DAOut();
		}
//		if (KeyTimes == 1)
//		{
//			Beep();
//		}
		break;
	case KEY_S7: //功率+
		gFlags.Bits.bReKey = 1;
		if (KeyTimes < 2)
			MCLevel++;
		else if (KeyTimes < 8)
			MCLevel += 2;
		else
			MCLevel += 3;
		if (MCLevel > 30)
		{
			MCLevel = 30;
			gFlags.Bits.bReKey = 0;
		}
		LED_MCLevel();
		if (gFlags.Bits.bWork)
		{
			DAOut();
		}
//		if (KeyTimes == 1)
//		{
//			Beep();
//		}
		break;
 	case KEY_S2://暂停/复位:短按暂停，长按复位
		gFlags.Bits.bReKey=1; 
		if (KeyTimes == 1)//初次按键，暂停工作
		{
			gFlags.Bits.bWork = 0;
			U5_8_OFF();
			TMR2ON = 0;
			SLed_ON();
			DAStop();
			MCLevel = 1;
			LED_MCLevel();
			//Beep();
		}
		else if(KeyTimes>8)//长按复位
		{
			gFlags.Bits.bReKey = 0;
			MCLevel = 1;
			MCTime_M = 15;
			MCTime_S = 00;
			T2Times = 0;
			TMR2 = 0;
			LED_MCTime();
			LED_MCLevel();
			gFlags.Bits.bPause = 1;
			PLed_ON();
			Beep();
		}
		
 		break;
	case KEY_S3://脉冲/持续
		gFlags.Bits.bReKey = 0;		
		gFlags.Bits.bPause = !gFlags.Bits.bPause;
		if (gFlags.Bits.bPause)
			PLed_ON();
		else
			CLed_ON();
		if (gFlags.Bits.bWork)
		{
			U5_8_ON();
		}
		//Beep();
		break;
	case KEY_S5://启动
		gFlags.Bits.bReKey = 0;
		gFlags.Bits.bWork = 1;
		U5_8_ON();
		TMR2ON = 1;
		DAOut();
		//Beep();
		break;
 	default:
 		break;	
 	}
 	//if(key!=Key_Power)
		
}