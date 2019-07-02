#ifndef __STDAFX_H__
#define __STDAFX_H__

//#define Proteus

#include <htc.h>
#include "stdint.h"
#define _XTAL_FREQ 16000000
#include "TypeDefine.h"
#include "FlagDefine.h"
#include "afx.h"
#include "Variables.h"
#define Verify_Sum
#include "Verify.h"


#define Uart_Uart1//6621,1616从
#define Uart_TRMT TRMT
#define Uart_TXREG TXREG
#include "wfUart.h"

#define CP1616_Client_AddrLen 0
#define CP1616_Client_DataBufLen 2


#define CP1616_Client_Tx_OneByOne
#define CP1616_Client_TxByteWithVerify(x) Uart1_VerifySumAddTxByte(x)
#define CP1616_Client_TxByte(x) Uart1_PutChar(x)
//#define CP1616_Client_VerifyProc(pBuf,len) GetVerify_Sum(pBuf,len)
#define CP1616_Client_RxList_LenMax 300

//TMR0的定时周期为100ms,1:8
#define SetTMR0() TMR0H=0x3c;TMR0L=0xb0


#define DAC0832_CS_W LATA3
#define DAC0832_WR_W LATA2

#define DAC0832_CS_IO TRISA3
#define DAC0832_WR_IO TRISA2 


#define TB_W LATA1

#define TB_IO TRISA1
#endif
