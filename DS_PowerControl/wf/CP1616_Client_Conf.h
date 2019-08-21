#ifndef __CP1616_Client_Conf_h__
#define __CP1616_Client_Conf_h__

#include "stdint.h"

#define CP1616_AddrLen 0
#define CP1616_DataBufLen 2

#define SetRx_CP1616_Client()
#define SetTx_CP1616_Client()

#define CP1616_Client_TxByteWithVerify(x)// Uart1_VerifySumAddTxByte(x)
#define CP1616_Client_TxByte(x)// Uart1_PutChar(x)

#define Verify_Sum
#include "Verify.h"
#define CheckVerify_CP1616_Client()	sum=GetVerify_Sum(CP1616_Client_RxList,CP1616_Client_NeedRxCount-2); \
												if(sum==CP1616_Client_RxList[CP1616_Client_NeedRxCount-2])	\
													{sum=1;}\
												else\
													{sum=0;}


#define MAX_CP1616_Client_RX 100

#define CP1717_Client

#define CP1717_Client_AddrLen 1
#define CP1717_DataBufLen 1

#define SetRx_CP1717_Client()
#define SetTx_CP1717_Client()

#define CP1717_Client_TxByteWithVerify(x)// Uart1_VerifySumAddTxByte(x)
#define CP1717_Client_TxByte(x)// Uart1_PutChar(x)

#define Verify_Sum
#include "Verify.h"
#define CheckVerify_CP1717_Client()	sum=GetVerify_Sum(CP1717_Client_RxList,CP1717_Client_NeedRxCount-2); \
	if(sum==CP1717_Client_RxList[CP1717_Client_NeedRxCount-2])	\
													{sum=1;}\
												else\
													{sum=0;}


#define CP1717_Client_NeedCheckVerify
#define CP1717_Client_VerifyProc(pBuff,Count) GetVerify_Sum(pBuff,Count)

#define MAX_CP1717_Client_RX 100
#endif


