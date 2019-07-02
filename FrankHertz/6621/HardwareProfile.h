#ifndef __STDAFX_H__
#define __STDAFX_H__

//#define Proteus

#include <htc.h>
#include "stdint.h"
#define _XTAL_FREQ 16000000
#include "TypeDefine.h"
#include "FlagDefine.h"
#define WFRomOperation
#define eeprom_offset 5
#include "afx.h"
#include "Variables.h"
#define Verify_Sum
#include "Verify.h"

#define wfDelay_ms(x) __delay_ms(x)

#define Uart_Uart1//PC,1616从
#define Uart_TRMT TRMT1
#define Uart_TXREG TXREG1

#define Uart_Uart2//18f2520,1616主
#define Uart2_TRMT TRMT2
#define Uart2_TXREG TXREG2
#include "wfUart.h"

#define CP1616_Client_AddrLen 0
#define CP1616_Client_DataBufLen 1

#define CP1616_Client_NeedCheckVerify
#define CP1616_Client_Tx_OneByOne
#define CP1616_Client_TxByteWithVerify(x) Uart1_VerifySumAddTxByte(x)
#define CP1616_Client_TxByte(x) Uart1_PutChar(x)
#define CP1616_Client_VerifyProc(pBuf,len) GetVerify_Sum(pBuf,len)
#define CP1616_Client_RxList_LenMax 100


#define CP1616_Master_AddrLen 0
#define CP1616_Master_DataBufLen 2

#define CP1616_Master_TxByte_Ex
#define CP1616_Master_Tx_OneByOne
#define CP1616_Master_TxByteWithVerify(x) Uart2_VerifySumAddTxByte(x)
#define CP1616_Master_TxByte(x) Uart2_PutChar(x)
#define CP1616_Master_VerifyProc(pBuf,len) GetVerify_Sum(pBuf,len)
#define CP1616_Master_RxList_LenMax 100





//TMR0的定时周期为100ms,1:8
#define SetTMR0() TMR0H=0x3c;TMR0L=0xb0

//#define CONTROLTIME	0xfb80
#define TLC5615_CS_W LATD5
#define TLC5615_CLK_W LATD6
#define TLC5615_DIN_W LATD7
#define TLC5615_DOUT_R   RD4

#define TLC5615_CS_IO TRISD5
#define TLC5615_CLK_IO TRISD6
#define TLC5615_DIN_IO TRISD7
#define TLC5615_DOUT_IO TRISD4 



#define SimSPI_SPI0
#define SimSPI_Delay_Ex
#define SimSPI_Delay() wfDelay_ms(1);
#define SIMSPI_SCL_Low() TLC5615_CLK_W=0
#define SIMSPI_SCL_High() TLC5615_CLK_W=1

#define SIMSPI_SDO_Low() TLC5615_DIN_W=0
#define SIMSPI_SDO_High() TLC5615_DIN_W=1

#define SIMSPI_SDI_Read() TLC5615_DOUT_R
/************************************************************************/
/* 显示相关                                                             */
/************************************************************************/
//#ifdef Proteus
#define Max7221_DIN_W LATA5   
#define Max7221_CLK_W LATA4
#define Max7221_CS_W  LATF6	

#define Max7221_DIN_DIR TRISA5 
#define Max7221_CLK_DIR TRISA4 
#define Max7221_CS_DIR 	TRISF6

#define Max7221_2
#define Max7221_DIN_W_2 LATC1    
#define Max7221_CLK_W_2 LATC0
#define Max7221_CS_W_2  LATF7	

#define Max7221_DIN_DIR_2 TRISC1	 
#define Max7221_CLK_DIR_2 TRISC0 
#define Max7221_CS_DIR_2  TRISF7
//#include "Max7221.h"
//#else
#define SimI2C
#define SimI2C_Delay_Ex
#define SimI2C_Delay() __delay_us(50);
#define SimI2C_CLK_IO TRISA4
#define SimI2C_DATA_IO TRISA5
#define SimI2C_CLK_W LATA4
#define SimI2C_DATA_W LATA5
#define SimI2C_DATA_R RA5

#define SIMI2C_SCL_High() SimI2C_CLK_W=1
#define SIMI2C_SCL_Low()	SimI2C_CLK_W=0

#define SIMI2C_SDA_IN()	SimI2C_DATA_IO=1
#define SIMI2C_SDA_OUT()  SimI2C_DATA_IO=0
#define SIMI2C_SDA_High() SimI2C_DATA_W=1
#define SIMI2C_SDA_Low()	SimI2C_DATA_W=0
#define SIMI2C_SDA_Read() SimI2C_DATA_R

#define SimI2C_2
#define SimI2C_2_Delay_Ex
#define SimI2C_2_Delay() __delay_us(50);
#define SimI2C_2_CLK_IO TRISC0
#define SimI2C_2_DATA_IO TRISC1
#define SimI2C_2_CLK_W LATC0
#define SimI2C_2_DATA_W LATC1
#define SimI2C_2_DATA_R RC1

#define SimI2C_2_SCL_High() SimI2C_2_CLK_W=1
#define SimI2C_2_SCL_Low()	SimI2C_2_CLK_W=0

#define SimI2C_2_SDA_IN()	SimI2C_2_DATA_IO=1
#define SimI2C_2_SDA_OUT()  SimI2C_2_DATA_IO=0
#define SimI2C_2_SDA_High() SimI2C_2_DATA_W=1
#define SimI2C_2_SDA_Low()	SimI2C_2_DATA_W=0
#define SimI2C_2_SDA_Read() SimI2C_2_DATA_R

#include "SimI2C.h"
#define TM1650_2
//#endif
//#include "TM1650.h"
/************************************************************************/
/* 按键                                                                 */
/************************************************************************/
#define KEY_C0_R RB0
#define KEY_Mode_R RB2
#define KEY_FS_R RB3

#define KEY_C0_DIR TRISB0
#define KEY_Mode_DIR TRISB2
#define KEY_FS_DIR TRISB3


void InitMCU(void);
void InitSystem(void);

#endif
