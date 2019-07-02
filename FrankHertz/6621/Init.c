#include "HardwareProfile.h"
#include <string.h>
#include <ctype.h>
#include "..\..\..\WF_Device\SimSPI.h"
#include "..\..\..\WF_Device\CP1616_Client.h"
#include "..\..\..\WF_Device\CP1616_Master.h"
#include "Function.h"
void InitMCU(void)             //系统初始化程序
{
	/************************************************************************/
	/* AD,外部参考电压0~3.3V                                                */
	/************************************************************************/
	ADCON1=0b00111101;//AN0:电位器调节，AN1：电流信号 
	CMCON=0x07;	
	TRISA1=1;
	TRISA0=1;	
	ADCON2=0b10111110;
	ADCON0=0x01;//通道0

	KEY_C0_DIR=1;
	KEY_Mode_DIR=1;
	KEY_FS_DIR=1;

	SimI2C_CLK_IO=0;
	SimI2C_2_CLK_IO=0;

	/************************************************************************/
	/* 串口2                                                                */
	/* 发送：数据装入TXREG后开始发送                                        */
	/* 接收：接收到后从RCREG中读数据                                        */
	/************************************************************************/
	TRISG2=1;
	TRISG1=0;
	TXSTA2=0b00100010;//异步方式、使能发送、9位字长、低波特率
	RCSTA2=0b10010000; //使能串口、使能接收、异步方式、9位字长
	SPBRG2=103;
	
	RC2IP=0;//低优先级
	RC2IE=1;//使能中断
	RC2IF=0;//清中断标志
	/************************************************************************/
	/* TMR0   计时						         	*/
	/************************************************************************/
	T0CON=0b10000010;//关闭，定时器，1:8,2us
	SetTMR0();
	TMR0IP=0;//低优先级
	TMR0IE=1;//使能中断
	TMR0IF=0;//清中断标志
	/************************************************************************/
	/* 串口1																*/
	/************************************************************************/
	TRISC7=1;
	TRISC6=1;
	TXSTA=0b00100110;//异步方式、使能发送(bit6=1是9位数据)八位字长、高波特率(bit2低速0)
	RCSTA=0b10010000; //使能串口、使能接收、异步方式、(bit6=1是9位数据)八位字长
	//BAUDCON1=0x40;//不用自动波特率自动检测
	SPBRG=0x67;	//Baud Rate = Fosc/(16(SPBRG+1)) = 9600
	RCIP=0;//低优先级
	RCIE=1;//使能中断
	RCIF=0;//清中断标志	

	/************************************************************************/
	/* 全局中断																*/
	/************************************************************************/
	//IPEN=1;//使能中断的优先级
	PEIE=1;
	GIE=1;
}
void InitVariable(void)
{
	unsigned char i;
	if(GetRomData()==0)
	{
		RomParams.AD0=0;
		SaveRomData();	
	}
		
}
void InitSystem( void )
{
	unsigned int i;
	InitMCU();
	InitVariable();
	CP1616_Client_Init();
	CP1616_Master_Init();
	CP1616_Master_WaitClientTime=1;
//	SimI2C_2_DATA_IO=0;
//	SimI2C_DATA_IO=0;
//	SimI2C_2_SDA_Low();
//	SimI2C_2_SDA_High();
//	SimI2C_2_SCL_Low();
//	SimI2C_2_SCL_High();
//	SIMI2C_SDA_Low();
//	SIMI2C_SDA_High();
//	SIMI2C_SCL_Low();
//	SIMI2C_SCL_High();
	Display_Init();
	/************************************************************************/
	/* 初始化TLC5615                                                        */
	/************************************************************************/
	TLC5615_CLK_W=0;
	TLC5615_CS_W=1;
	TLC5615_CS_IO=0; 
	TLC5615_CLK_IO=0;
	TLC5615_DIN_IO=0;
	TLC5615_DOUT_IO=1;
	SimSPI_Init();
	VOutput(0);
}
