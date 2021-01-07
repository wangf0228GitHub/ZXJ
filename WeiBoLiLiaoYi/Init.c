#include "HardwareProfile.h"
void InitMCU(void)             //系统初始化程序
{
	//AD初始化	
	//AD初始化	
	ANSEL = 0;  //全部为数据口
	ANSELH = 0;
	TRISA = 0;
	TRISB = 0;
	TRISC = 0;
	TRISD=0;
	TRISE=0;
	OPTION = 0b11011111;
	/************************************************************************/
	/* IO初始化                                                             */
	/************************************************************************/
	TRISD3 = 1;
	U5_8_DIR = 0;
	RUNLed_DIR = 0;
	BZ_DIR = 0;
	U1_1_DIR = 1;

	U5_8_OFF();
	RUNLed_OFF();
	BZ_OFF();	
	/************************************************************************/
	/* TMR1 系统节拍，100ms                                                 */
	/************************************************************************/
	T1CON=0b10110000;//1:8,8us
	WRITETIMER1(T1_100ms);//100ms
	TMR1ON=1;
	TMR1IE=1;//使能中断
	TMR1IF=0;//清中断标志


	T2CON = 0b01001011;//1:160,160us
	PR2 = 125;//20ms
	TMR2 = 0;
	TMR2IE = 1;//使能中断
	TMR2IF = 0;//清中断标志
	/************************************************************************/
	/* 电平变化中断                                                         */
	/************************************************************************/
// 	IOCB=0x70;
// 	RBIE=1;
// 	RBIF=0;	
//	T0IE=1;
	PEIE=1;
	GIE=1;
}
void InitVariable(void)
{
	gFlags.AllFlag=0;
	gFlags.Bits.bReKey=1;
	gFlags.Bits.bPause = 1;
	gFlags.Bits.bShow = 1;
	SystemTick=0;
	KeyTick=0;
	MCLevel=1;
	MCTime_M = 15;
	MCTime_S = 00;
	T2Times = 0;
}
void InitSystem( void )
{
	InitMCU();	
	InitVariable(); 	
	TLV56XX_Init();
	DAStop();
	TM1638_Init();	
	LED_Switch(1);
	LED_NULL();
	while (1)
	{
		if (U1_1_R == 1)
		{
			__delay_us(20);
			if (U1_1_R == 1)
				break;
		}
	}
	LED_MCLevel();
	LED_MCTime();
	PLed_ON();
	SLed_ON();	
	Beep();
	//WTH040_OneLine_Play(1);
}
