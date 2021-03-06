#include "HardwareProfile.h"
void InitMCU(void)             //系统初始化程序
{
	//AD初始化	
	ANSEL=0;//RA2为模拟输入
	ANSELH=0;
	
	

	OPTION=0b00001111;//看门狗预分频128	
	/************************************************************************/
	/* IO初始化                                                             */
	/************************************************************************/
	TRISB=0x07;
	PWM=1;
	TRISC1=0;
	/************************************************************************/
	/* TMR1 系统节拍，100ms                                                 */
	/************************************************************************/
	T1CON=0b00000000;//1:8,8us	
	TMR1ON=0;
	TMR1IE=1;//使能中断
	TMR1IF=0;//清中断标志
	/************************************************************************/
	/* 电平变化中断                                                         */
	/************************************************************************/
	IOCB=0x01;
// 	RBIE=1;
// 	RBIF=0;	
	PEIE=1;
	GIE=1;
}
void InitVariable(void)
{
	gFlags.AllFlag=0;
	WorkIndex=0;
}
void InitSystem( void )
{
	InitMCU();	
}
