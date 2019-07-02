#include "HardwareProfile.h"

#define Key_Null	0x06
#define Key_Plus	0x04
#define Key_Minus	0x02

void KeyProc(void)
{	
	unsigned char key,x;
	key=PORTB&Key_Null;
	if(key==Key_Null)
	{
		gFlags.Bits.bKey=0;
		return;
	}
	__delay_ms(20);
	x=PORTB&Key_Null;
	if(x==Key_Null)
	{
		gFlags.Bits.bKey=0;
		return;
	}
	else if(gFlags.Bits.bKey || (x!=key))//已经在按键了，或抖动
	{
		return;
	}
	gFlags.Bits.bKey=1;
	if(gFlags.Bits.bWork)//已经开始工作了，判断加减
	{
		if(key==Key_Plus)
		{
			if(WorkIndex<7)
				WorkIndex++;
		}
		else if(key==Key_Minus)
		{
			if(WorkIndex>0)
				WorkIndex--;
		}
	}
	else
	{
		if(key==Key_Plus)
		{
			gFlags.Bits.bWork=1;
			RBIF=0;	
			RBIE=1;			 	
		}
	}
}