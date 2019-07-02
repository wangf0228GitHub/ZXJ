//HI-TECH C PRO for the PIC18 MCU Family  V9.63PL3
#include "HardwareProfile.h"

__CONFIG(HS&WDTEN&PWRTEN&MCLREN&CP&BOREN&LVPDIS);
GFlags gFlags;
unsigned char WorkIndex;
extern void InitSystem( void );
void main()
{
	InitSystem();
	while(1)
	{		
		CLRWDT();
		KeyProc();	
	}
}
void interrupt lowISR(void)
{	
	unsigned char x;
	if(TMR1IE&&TMR1IF)//���ճ�ʱ
	{	
		TMR1IF=0;
		TMR1ON=0;
		PWM=0;
		__delay_us(500);
		PWM=1;
	}	
	if(RBIE&&RBIF)//������
	{
		x=PORTB;
		RBIF=0;
		if(WorkIndex>6)//һֱ�ߵ�ƽ
		{
			PWM=0;
		}
		else
		{
			WRITETIMER1(WORKTIME[WorkIndex]);//100ms
			TMR1ON=1;
		}		
	}
}

