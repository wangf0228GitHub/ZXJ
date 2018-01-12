#include "HardwareProfile.h"
#include <string.h>
#include <ctype.h>
void InitMCU(void)             //系统初始化程序
{
	//AD初始化
	ADCON1=0b00001111;  //数字口
	CMCON=0x07;


	LED1_W=0;
	LED2_W=0;
	LED3_W=0;
	LED4_W=0;
	LED5_W=0;
	LED6_W=0;
	LED1_DIR=0;
	LED2_DIR=0;
	LED3_DIR=0;
	LED4_DIR=0;
	LED5_DIR=0;
	LED6_DIR=0;

	UcControl_W=1;
	UcControl_DIR=0;

	ADGainControl_W=0;//1小增益，0大增益
	ADGainControl_DIR=0;

	KEY1_DIR=1;
	KEY2_DIR=1;
	KEY3_DIR=1;
	KEY4_DIR=1;

	LCDBusy_DIR=1;
	/************************************************************************/
	/* 串口2                                                                */
	/* 发送：数据装入TXREG后开始发送                                        */
	/* 接收：接收到后从RCREG中读数据                                        */
	/************************************************************************/
	TRISG2=1;
	TRISG1=0;
	TXSTA2=0b00100110;//异步方式、使能发送、9位字长、低波特率
	RCSTA2=0b10010000; //使能串口、使能接收、异步方式、9位字长
#ifdef Proteus
	SPBRG2=103;
#else
	BRG162=1;
	SPBRG2=33;	//Baud Rate = Fosc/(4(SPBRG+1)) = 115200
#endif
	
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

// 	TRISG0=0;
// 	M24XX_WP_W=1;
}
void InitVariable(void)
{
	unsigned char i;
	Curve2Max=300;
	Curve1Max=300;
	MeasureIndex=0;
	if(GetRomData()==0)
	{
		for(i=0;i<6;i++)
		{
			RomParams.hWorkCurrent[i]=50;
			RomParams.hCorrection[i]=0.99;
			RomParams.FACorrection[i]=0.99;
			RomParams.FAWorkCurrent[i]=50;
		}
		RomParams.exWorkTepy.AllFlag=0;
		strcpy(RomParams.ServerIP,"192.168.1.105");
		strcpy(RomParams.ServerPort,"8000");
		strcpy(RomParams.WifiSSID,"Pic238Hou");
		strcpy(RomParams.WifiPASS,"1Q2W3E4R");	
		strcpy(RomParams.SitNum,"??");
		SaveRomData();
	}
	StudentClass[0]='\0';
	StudentNum[0]='\0';
	workScreen=0;
	GotoScreen=0;
	for(i=0;i<6;i++)
	{
		ManVAIndex[i]=0xff;
		ManGQIndex[i]=0xff;
		Curve1Flags[i]=0;
	}
	for(i=0;i<4;i++)
	{
		Curve2Flags[i]=0;
	}
	bCalcH=0;
}
void InitSystem( void )
{
	unsigned int i;
	InitMCU();
	InitVariable();
	EndProcCommandFromTFT();	
	ATCommand_Init();	
/************************************************************************/
/* 初始化ADS1120                                                        */
/************************************************************************/
	SimSPI_Init();
	ADS1120_SPI_Proc(0b01000011);//写寄存器指令
	ADS1120_SPI_Proc(0b00110000);
	ADS1120_SPI_Proc(0b00000000);
	ADS1120_SPI_Proc(0b11000000);
	ADS1120_SPI_Proc(0b00000000);
/************************************************************************/
/* DA初始化                                                             */
/************************************************************************/
	TLV56XX_Init();//5623
	TLV56XX_WriteData(0x0000);
	TLV56XX_2_Init();
	TLV56XX_2_WriteData(0x9000);
	TLV56XX_2_WriteData(0x0000);

	InitWithTFT();
	InitWifi();
	if(Wifi_ErrState==WifiNoErr)
	{
		__delay_20ms(100);
		SetScreen(sID_Screen1);
	}
	else
	{
		EnterDlgReNum=sID_Screen1;
		ShowEnterDlg(strNo8266);
	}
}
