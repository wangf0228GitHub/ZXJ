#include "HardwareProfile.h"
#include <string.h>
#include <ctype.h>

#include "Function.h"
void InitMCU(void)             //ϵͳ��ʼ������
{
	/************************************************************************/
	/* AD,�ⲿ�ο���ѹ0~3.3V                                                */
	/************************************************************************/
	ADCON1=0b00001111;//AN0:��λ�����ڣ�AN1�������ź� 
	CMCON=0x07;	

	
	TRISA = TRISA | 0x0f;
	TRISB = TRISB | 0x3f;

	INTEDG0 = 0;//B �½��� �ж�
	INTEDG1 = 0;//B �½��� �ж�
	INTEDG2 = 0;//B �½��� �ж�

	//INT0IP = 1; //�߼��ж�
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
	/* TMR0   ��ʱ						         	*/
	/************************************************************************/
	T0CON=0b10000010;//�رգ���ʱ����1:8,2us
	SetTMR0();
	TMR0IP=0;//�����ȼ�
	TMR0IE=1;//ʹ���ж�
	TMR0IF=0;//���жϱ�־

	/************************************************************************/
	/* TMR2   ������						         	*/
	/************************************************************************/
// 	T2CON = 0b01111011;//�رգ���ʱ����1:256,16us
// 	PR2 = 250;
// 	TMR2IP = 0;//�����ȼ�
// 	TMR2IF = 0;//���жϱ�־
// 	TMR2IE = 1;//ʹ���ж�	
	/************************************************************************/
	/* ȫ���ж�																*/
	/************************************************************************/
	IPEN=1;//ʹ���жϵ����ȼ�
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
