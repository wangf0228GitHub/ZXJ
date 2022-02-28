#include "HardwareProfile.h"
#include <string.h>
#include <ctype.h>

#include "Function.h"
void InitMCU(void)             //系统初始化程序
{
	/************************************************************************/
	/* AD,外部参考电压0~3.3V                                                */
	/************************************************************************/
	ADCON1=0b00001111;//AN0:电位器调节，AN1：电流信号 
	CMCON=0x07;	

	
	TRISA = TRISA | 0x0f;
	TRISB = TRISB | 0x3f;

	INTEDG0 = 0;//B 下降沿 中断
	INTEDG1 = 0;//B 下降沿 中断
	INTEDG2 = 0;//B 下降沿 中断

	//INT0IP = 1; //高级中断
	INT1IP = 1;
	INT2IP = 1;

	INT0IF = 0;
	INT1IF = 0;
	INT2IF = 0;

	INT0IE = 1;
	INT1IE = 1;
	INT2IE = 1;

	Beep_W = 0;
	Beep_DIR = 0;
	
	
	SimI2C_CLK_IO=0;
	SimI2C_2_CLK_IO=0;
	SimI2C_3_CLK_IO=0;
	SimI2C_4_CLK_IO=0;
	/************************************************************************/
	/* TMR0   计时						         	*/
	/************************************************************************/
	T0CON=0b10000010;//关闭，定时器，1:8,2us
	SetTMR0();
	TMR0IP=0;//低优先级
	TMR0IE=1;//使能中断
	TMR0IF=0;//清中断标志

	/************************************************************************/
	/* TMR2   蜂鸣器						         	*/
	/************************************************************************/
// 	T2CON = 0b01111011;//关闭，定时器，1:256,16us
// 	PR2 = 250;
// 	TMR2IP = 0;//低优先级
// 	TMR2IF = 0;//清中断标志
// 	TMR2IE = 1;//使能中断	
	/************************************************************************/
	/* 全局中断																*/
	/************************************************************************/
	IPEN=1;//使能中断的优先级
	PEIE=1;
	
}
void InitVariable(void)
{
	unsigned char i;
	knobFlags.AllFlag = 0;
	If = 850;
	Ic = 450;
	U = 0;
	Ifset = 10;
	Icset = 10;
	Uset = 10;
	SystemTick = 0;
	IaTick = SystemTick;
// 	if(GetRomData()==0)
// 	{
// 		RomParams.AD0=0;
// 		SaveRomData();	
// 	}		
}
void InitSystem( void )
{
	unsigned int i;
	InitMCU();
	InitVariable();
	
	Display_Init();
	Display_ShowSet(0x07);
	DAC8830_Init();
	DAC8830_2_Init();
	DAC8830_3_Init();
	MCP3201_Init();

	DAC8830_Setting(0);
	DAC8830_2_Setting(0);
	DAC8830_3_Setting(0);
	MCP3201_ReadAD();
}
