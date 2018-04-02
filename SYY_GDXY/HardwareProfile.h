#ifndef __STDAFX_H__
#define __STDAFX_H__

//#define Proteus

#include <htc.h>
#define _XTAL_FREQ 16000000
#include "TypeDefine.h"
#include "FlagDefine.h"
#define WFRomOperation
#define eeprom_offset 5
#include "afx.h"
#include "Verify.h"

#define Uart_Uart1//TFT
#define Uart_TRMT TRMT1
#define Uart_TXREG TXREG1

#define Uart_Uart2//wifi
#define Uart2_TRMT TRMT2
#define Uart2_TXREG TXREG2
#include "Uart.h"

#define LED1_W LATD5
#define LED2_W LATD4
#define LED3_W LATD3
#define LED4_W LATD2
#define LED5_W LATD1
#define LED6_W LATD0

#define LED1_DIR TRISD0
#define LED2_DIR TRISD1
#define LED3_DIR TRISD2
#define LED4_DIR TRISD3
#define LED5_DIR TRISD4
#define LED6_DIR TRISD5

#define UcControl_W LATD7
#define UcControl_DIR TRISD7

#define LCDBusy_R RF0
#define LCDBusy_DIR TRISF0

#define ADGainControl_W LATF1
#define ADGainControl_DIR TRISF1
/************************************************************************/
/* 画面id                                                               */
/************************************************************************/
#define sID_Screen0 0
#define sID_Screen1 1
#define sID_Menu 2
#define sID_Setting 3
#define sID_WIFIconfiguration 4
#define sID_wifimima 5
#define sID_wxWifi 6
#define sID_APKWifi 7
#define sID_ParamSet 8
#define sID_ExperimentConfig 10
#define sID_FactorySettings 11
#define sID_hWorkCurrent 12
#define sID_FuAnWorkCurrent 13
#define sID_ExperimentalProject 15
#define sID_AutoVA 16
#define sID_AutoGQ 17
#define sID_AutoPuLangke 18
#define sID_ManVA 19
#define sID_ManGQ 20
#define sID_PLdatePrecessing 22
#define sID_Print 23
#define sID_EnterDlg 25
#define sID_AutoVA_Work 26
#define sID_AutoGQ_Work 27
#define sID_ManVA_Work 28
#define sID_ManGQ_Work 29
#define sID_QueryDlg 30


#define pID_VACut 51
#define pID_GQCut 53
/************************************************************************/
/* 字符串                                                               */
/************************************************************************/
const char strErr[]={0xB7,0xA2,0xC9,0xFA,0xB4,0xED,0xCE,0xF3,0x2C,0xC7,0xEB,0xD6,0xD8,0xCA,0xD4,0xA3,0xA1,0x00};
const char strNo8266[]={0xCE,0xB4,0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0x77,0x69,0x66,0x69,0xC4,0xA3,0xBF,0xE9,0xA3,0xAC,0xCE,0xDE,0xB7,0xA8,0xB4,0xF2,0xD3,0xA1,0xA3,0xA1,0x00};
const char strNoWifi[]={0xCE,0xDE,0xB7,0xA8,0xC1,0xAC,0xBD,0xD3,0xB5,0xBD,0xC9,0xE8,0xB6,0xA8,0xB5,0xC4,0x77,0x69,0x66,0x69,0xCD,0xF8,0xC2,0xE7,0xD6,0xD0,0xA3,0xA1,0x00};
const char strNoServer[]={0xCE,0xDE,0xB7,0xA8,0xC1,0xAC,0xBD,0xD3,0xB5,0xBD,0xB4,0xF2,0xD3,0xA1,0xB7,0xFE,0xCE,0xF1,0xC6,0xF7,0x21,0x00};
const char strWifiSetSeccess[]={0x77,0x69,0x66,0x69,0xC5,0xE4,0xD6,0xC3,0xB3,0xC9,0xB9,0xA6,0x21,0x00};
const char strParamSetSeccess[]={0xB2,0xCE,0xCA,0xFD,0xC9,0xE8,0xD6,0xC3,0xB3,0xC9,0xB9,0xA6,0x21,0x00};
const char strPicF[]={0xC7,0xEB,0xD1,0xA1,0xD4,0xF1,0xCB,0xF9,0xD0,0xE8,0xB9,0xE2,0xC6,0xB5,0xC2,0xCA,0xA3,0xA8,0xD1,0xD5,0xC9,0xAB,0xA3,0xA9,0x21,0x00};
const char strPicI[]={0xC7,0xEB,0xD1,0xA1,0xD4,0xF1,0xD0,0xE8,0xD2,0xAA,0xB5,0xC4,0xB9,0xA4,0xD7,0xF7,0xB5,0xE7,0xC1,0xF7,0xA3,0xA1,0x00};
const char strCurveFinish[]={0xC7,0xFA,0xCF,0xDF,0xB2,0xE2,0xC1,0xBF,0xCD,0xEA,0xB3,0xC9,0x21,0x21,0x00};
const char strPrintSeccess[]={0xB4,0xF2,0xD3,0xA1,0xB3,0xC9,0xB9,0xA6,0x21,0x00};
const char strQueryPrint1[]={0xCA,0xB5,0xD1,0xE9,0xC9,0xD0,0xCE,0xB4,0xC8,0xAB,0xB2,0xBF,0xCD,0xEA,0xB3,0xC9,0xA3,0xAC,0xCA,0xC7,0xB7,0xF1,0xBC,0xCC,0xD0,0xF8,0xB4,0xF2,0xD3,0xA1,0xA3,0xBF,0x00};
const char strQueryPrint2[]={0xD2,0xD1,0xBE,0xAD,0xB4,0xF2,0xD3,0xA1,0xB9,0xFD,0xC1,0xCB,0xA3,0xAC,0xCA,0xC7,0xB7,0xF1,0xBC,0xCC,0xD0,0xF8,0xB4,0xF2,0xD3,0xA1,0xA3,0xBF,0x00};
const char strNoPrint[]={0xC3,0xBB,0xD3,0xD0,0xD0,0xE8,0xD2,0xAA,0xB4,0xF2,0xD3,0xA1,0xB5,0xC4,0xCA,0xB5,0xD1,0xE9,0xC4,0xDA,0xC8,0xDD,0xA3,0xA1,0x00};
const char strSaveReset[]={0xB2,0xCE,0xCA,0xFD,0xC9,0xE8,0xB6,0xA8,0xB3,0xC9,0xB9,0xA6,0xA3,0xAC,0xC9,0xE8,0xB1,0xB8,0xBD,0xAB,0xD6,0xD8,0xC6,0xF4,0xA3,0xA1,0x00};
const char strQueryReset[]={0xB7,0xB5,0xBB,0xD8,0xCA,0xD7,0xD2,0xB3,0xBD,0xAB,0xC7,0xE5,0xBF,0xD5,0xCA,0xB5,0xD1,0xE9,0xCA,0xFD,0xBE,0xDD,0xA3,0xAC,0xCA,0xC7,0xB7,0xF1,0xBC,0xCC,0xD0,0xF8,0x3F,0x00};
/************************************************************************/
/* 显示相关                                                             */
/************************************************************************/
#define Screen_Login 1
unsigned char ScreenID;

#define TFTUartTx(x) while(LCDBusy_R);Uart1_PutChar(x)
#include "WithTFT.h"
/************************************************************************/
/* 显示变量                                                             */
/************************************************************************/
char StudentClass[11];
char StudentNum[13];
char DisplayLine[30];
unsigned char workScreen;
unsigned char GotoScreen;
unsigned int CurveData_FATX[6][101];
unsigned int CurveData_GDLGQ[4][101];
unsigned char CurveNum;
unsigned char MeasureIndex;
unsigned char ManVAIndex[6];
unsigned char ManGQIndex[4];

/************************************************************************/
/* 存储芯片FM25H20                                                      */
/************************************************************************/
// #define SimSPI_SCL_DIR	TRISB0
// #define SimSPI_SDI_DIR	TRISA0
// #define SimSPI_SDO_DIR	TRISB0
// 
// #define SimSPI_SCL_W	LATB0
// #define SimSPI_SDI_R	RA0	
// #define SimSPI_SDO_W	LATB10
// #define SimSPI_SPI3
// // #define SimSPI_Delay_Ex
// // #define SimSPI_Delay() __delay_us(1)
// #include "SimSPI.h"
// #define SPIROM_CS_DIR TRISB0
// #define SPIROM_W_DIR  TRISB1
// #define SPIROM_CS_W LATB0
// #define SPIROM_W_W  LATB1
// #define SPIROM_SPIInit() SimSPI_Init()
// #define SPIROM_SendData(c) SimSPI_Proc(c)
// #define SPIROM_Addr24
// //#define SPIROM_NeedWIP
// #include "SPIROM.h"

//TMR0的定时周期为100ms,1:8
#define SetTMR0() TMR0H=0x3c;TMR0L=0xb0

//#define CONTROLTIME	0xfb80
GFlags gFlags;
unsigned char Curve1Flags[6];
unsigned char Curve2Flags[4];
unsigned char bCalcH;
unsigned int SystemTick;
unsigned int InitLCDTick;
unsigned int NoWithPCRxTick;
unsigned int WaitWithMBusTick;
unsigned int MeasureTick;
unsigned int Curve2Max;
unsigned int Curve1Max;
unsigned int AccelerateV;
#define ADAverage 4
sint ADResult[ADAverage];
sint ADValue;
#define SimSPI_SPI1
#define SimSPI_SCL_DIR	TRISG3
#define SimSPI_SDI_DIR	TRISE0
#define SimSPI_SDO_DIR	TRISE1
 
#define SimSPI_SCL_W	LATG3
#define SimSPI_SDI_R	RE0	
#define SimSPI_SDO_W	LATE1
#include "SimSPI.h"
#define ADS1120_DRDY_DIR TRISG0
#define ADS1120_DRDY_R RG0
#define ADS1120_CS_DIR TRISG4
#define ADS1120_CS_W LATG4
#define ADS1120_SPI_Proc(x) SimSPI_Proc(x)

void ReadAD1120(void);

#define TLV56XX_FS_W	LATE6 
#define TLV56XX_CLK_W	LATE4   
#define TLV56XX_DIO_W	LATE3  
#define TLV56XX_CS_W	LATE5
 
#define TLV56XX_FS_DIR	TRISE6
#define TLV56XX_CLK_DIR TRISE4
#define TLV56XX_DIO_DIR TRISE3  
#define TLV56XX_CS_DIR  TRISE5

#define TLV56XX_2

#define TLV56XX_2_FS_W	LATA3 
#define TLV56XX_2_CLK_W	LATA5   
#define TLV56XX_2_DIO_W	LATA4  
#define TLV56XX_2_CS_W	LATA2

#define TLV56XX_2_FS_DIR	TRISA3
#define TLV56XX_2_CLK_DIR	TRISA5
#define TLV56XX_2_DIO_DIR	TRISA4  
#define TLV56XX_2_CS_DIR	TRISA2
#include "TLV56XX.h"
/************************************************************************/
/* 按键                                                                 */
/************************************************************************/
#define KEY1_R RF2
#define KEY2_R RF3
#define KEY3_R RF4
#define KEY4_R RF5

#define KEY1_DIR TRISF2
#define KEY2_DIR TRISF3
#define KEY3_DIR TRISF4
#define KEY4_DIR TRISF5

#define KeyCheck_ReadKey(x) x=KEY1_R;x|=(KEY2_R<<1);x|=(KEY3_R<<2);x|=(KEY4_R<<3)
#define KeyUp 0x0d
#define KeyDown 0x07
#define KeyLeft 0x0e
#define KeyRight 0x0b
#define KeyCheck_NoKey 0x0f
#include "KeyCheck.h"
/************************************************************************/
/* wifi 相关                                                            */
/************************************************************************/
#define ATCommand_Tx_Ex
#define ATCommand_TxByte(x) Uart2_PutChar(x)
#define ATCommand_PutString(x) Uart2_PutString(x)
#define ATCommand_MaxRX 100
#define ATCommand_WaitClientInterval_Ex
#define ATCommand_WaitClientInterval() __delay_20ms(100);

#define ATCommand_EndChar_Ex
#define ATCommand_EndChar "\r\n\0"
#include "ATCommand.h"
unsigned char Wifi_ErrState;
enum {WifiNoErr=0,MissAT,MissCWQAP,MissCWSMARTSTART,MissCWSMARTSTOP,MissCWMODE,
	MissCIPSEND,MissWifi,MissServer,ServerACKTimeOut,SendTimeOut};
void ConnectWifi(void);
void DisconnectWifi(void);
void SendMearData(void);
void InitWifi(void);
void ShowWifiErr(void);


void InitMCU(void);
void InitSystem(void);
void SwitchLED(unsigned char index,unsigned char x);
void SetBright(unsigned int x);
void SetCutOffV(unsigned int x);
void EX_ProcPLKCS(void);
void EX_ProcFATXQX_Auto(void);
void EX_ProcFATXQX_Man(void);
void EX_ProcGDLGQ_Auto(void);
void Setting_AutoWifi(unsigned char sID);
void Setting_Wifimima(void);
void Setting_APKWifi(void);
void Setting_ParamSet(void);
void EX_ProcPrint(void);
void Setting_hWorkParam(void);
void Setting_FAWorkParam(void);
void Setting_ExperimentConfig(void);
void EX_ProcGDLGQ_Man(void);
//wifi
char *pWifiStr=0;
unsigned int WaitWifiSetTick;
unsigned char WaitSCount;
unsigned int TempWithTFTTick;
#define GetTxtRetryMax 5
#define SetScreenRetryMax 5
unsigned char SetScreenRetry;
unsigned char GetTxtRetry;
float I_nA;
unsigned char EnterDlgReNum;
unsigned char QueryDlgCancelNum;
_GetTxtFlags GetTxtFlags;
void StartSetWifi(unsigned char type);
void StopSetWifi(void);
float fUs[6];
float fH;
float fH_K;
float fH_B;
char pGetTxtBuf[10];
char pGetButton;
#endif
