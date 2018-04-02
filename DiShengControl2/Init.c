#include "HardwareProfile.h"
//#define Uart3_BAUDRATE 9600 //
#define Uart1_BAUDRATE 38400 //电子罗盘
#define Uart2_BAUDRATE 9600 //温度
#define Uart3_BAUDRATE 9600 //光源
#define Uart4_BAUDRATE 4800 //授时
void InitMCU()
{
	AD1PCFGL=0xffff;
 	PMAEN=0x0000;
	
	w5500_CS_W=1;
	w5500_CS_DIR=0;

	sensorPower_W=sensorPower_OFF;
	sensorPower_DIR=0;//倾角与电子罗盘
	

	LouShui1_DIR=1;//漏水检测1

	LouShui2_DIR=1;//漏水检测2
	
	ModbusRTU_RS485DE_DIR=0;

	LED_W=LED_ON;
	LED_DIR=0;
//	_TRISD1=1;
//	_TRISD2=0;
	/************************************************************************/
	/* 系统节拍，10ms                                                       */
	/************************************************************************/
	T1CON=0;
	T1CONbits.TCKPS=0b11;//1:256
	PR1=625;
	_T1IP=1;
	_T1IF=0;
	_T1IE=1;
	T1CONbits.TON=1;
	/************************************************************************/
	/* 串口3，CPU卡                                                         */
	/************************************************************************/
 	//iPPSInput(IN_FN_PPS_U3RX,IN_PIN_PPS_RP24);  //使用PPS配置端口
 	//iPPSOutput(OUT_PIN_PPS_RP19,OUT_FN_PPS_U3TX);
 	//U3MODE=0;
 	//U3MODEbits.USIDL=1;//当器件进入空闲模式时，模块停止工作							
 	//U3MODEbits.BRGH=1;//高速
 	//U3MODEbits.PDSEL=0b00;//8位数据位，无校验
 	//U3STA=0;
 	//U3STAbits.UTXINV=0;//UxTX 的空闲状态为1
 	//U3BRG=((FCY/Uart3_BAUDRATE)/4)-1;
 	//U3MODEbits.UARTEN=1;
 	//U3STAbits.UTXEN=1;//使能UARTx 发送器，由UARTx 控制UxTX 引脚（如果UARTEN = 1）
 	//_U3RXIP=4;
 	//_U3RXIE=1;
	/************************************************************************/
	/* 串口1，电子罗盘                                                      */
	/************************************************************************/
 	iPPSInput(IN_FN_PPS_U1RX,IN_PIN_PPS_RP25);  //使用PPS配置端口
 	iPPSOutput(OUT_PIN_PPS_RP22,OUT_FN_PPS_U1TX);
 	U1MODE=0;
 	U1MODEbits.USIDL=1;//当器件进入空闲模式时，模块停止工作							
 	U1MODEbits.BRGH=1;//高速
 	U1MODEbits.PDSEL=0b00;//8位数据位，无校验
 	U1STA=0;
 	U1STAbits.UTXINV=0;//UxTX 的空闲状态为1
 	U1BRG=((FCY/Uart1_BAUDRATE)/4)-1;
 	U1MODEbits.UARTEN=1;
 	U1STAbits.UTXEN=1;//使能UARTx 发送器，由UARTx 控制UxTX 引脚（如果UARTEN = 1）
 	_U1RXIP=1;
 	_U1RXIF=1;
 	_U1RXIE=1;
 	_U1TXIE=0;
	/************************************************************************/
	/* 串口2，温度，Modbus                                                  */
	/************************************************************************/
 	iPPSInput(IN_FN_PPS_U2RX,IN_PIN_PPS_RP23);  //使用PPS配置端口
 	iPPSOutput(OUT_PIN_PPS_RP24,OUT_FN_PPS_U2TX);
 	U2MODE=0;
 	U2MODEbits.USIDL=1;//当器件进入空闲模式时，模块停止工作							
 	U2MODEbits.BRGH=1;//高速
 	U2MODEbits.PDSEL=0b00;//8位数据位，无校验
	U2MODEbits.STSEL=1;//两个停止位
 	U2STA=0;
 	U2STAbits.UTXINV=0;//UxTX 的空闲状态为1
 	U2BRG=((FCY/Uart2_BAUDRATE)/4)-1;
 	U2MODEbits.UARTEN=1;
 	U2STAbits.UTXEN=1;//使能UARTx 发送器，由UARTx 控制UxTX 引脚（如果UARTEN = 1）
 	_U2RXIP=3;
 	_U2RXIE=1;
	/************************************************************************/
	/* 串口3，光源                                                          */
	/************************************************************************/
	iPPSInput(IN_FN_PPS_U3RX,IN_PIN_PPS_RP21);  //使用PPS配置端口
	iPPSOutput(OUT_PIN_PPS_RP19,OUT_FN_PPS_U3TX);
	U3MODE=0;
	U3MODEbits.USIDL=1;//当器件进入空闲模式时，模块停止工作							
	U3MODEbits.BRGH=1;//高速
	U3MODEbits.PDSEL=0b00;//8位数据位，无校验
	//U3MODEbits.STSEL=1;//两个停止位
	U3STA=0;
	U3STAbits.UTXINV=0;//UxTX 的空闲状态为1
	U3BRG=((FCY/Uart3_BAUDRATE)/4)-1;
	U3MODEbits.UARTEN=1;
	U3STAbits.UTXEN=1;//使能UARTx 发送器，由UARTx 控制UxTX 引脚（如果UARTEN = 1）
	_U3RXIP=3;
	_U3RXIE=0;
	/************************************************************************/
	/* 串口4，授时                                                          */
	/************************************************************************/
	iPPSInput(IN_FN_PPS_U4RX,IN_PIN_PPS_RP27);  //使用PPS配置端口
	iPPSOutput(OUT_PIN_PPS_RP26,OUT_FN_PPS_U4TX);
	U4MODE=0;
	U4MODEbits.USIDL=1;//当器件进入空闲模式时，模块停止工作							
	U4MODEbits.BRGH=1;//高速
	U4MODEbits.PDSEL=0b00;//8位数据位，无校验
	//U4MODEbits.STSEL=1;//两个停止位
	U4STA=0;
	U4STAbits.UTXINV=0;//UxTX 的空闲状态为1
	U4BRG=((FCY/Uart4_BAUDRATE)/4)-1;
	U4MODEbits.UARTEN=1;
	U4STAbits.UTXEN=1;//使能UARTx 发送器，由UARTx 控制UxTX 引脚（如果UARTEN = 1）
	_U4RXIP=3;
	_U4RXIE=1;
	__builtin_write_OSCCONL(OSCCON | 0x40);
}
// void GetSystemTime(_SystemTIME* dt)
// {
// 	DS1302_Time.Second &= 0x7f;
// 	dt->Year=DS1302_Time.Year;
// 	dt->Month=DS1302_Time.Month;
// 	dt->Day=DS1302_Time.Day;
// 	dt->Hour=DS1302_Time.Hour;
// 	dt->Minute=DS1302_Time.Minute;
// 	dt->Second=DS1302_Time.Second;
// }
void InitVariable(void)
{
	ModbusRTU_Master_TargetAddr=1;
	gFlags.bNet=0;
}
void InitSystem( void )
{
	InitMCU();
	InitVariable();	
	Init_ModbusRTU_Master();
	CP1616_NoAddr_Init();
	ModbusRTU_Master_WaitClientTime=30;
	ModbusRTU_Master_TargetAddr=1;
	SimSPI_Init();
	w5500LibInit();
	SimI2C_Init();
	MS8607_Init();
}
