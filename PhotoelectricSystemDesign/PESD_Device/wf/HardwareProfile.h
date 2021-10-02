#ifndef __HardwareProfile_H__
#define __HardwareProfile_H__

#include "gpio.h"
#include "wfSys.h"
#include "wfDefine.h"

#define Verify_Sum
#include "Verify.h"

#define CP1616_Client_AddrLen 0
#define CP1616_Client_DataBufLen 2

#define SetRx_CP1616_Client()
#define SetTx_CP1616_Client()

#define CP1616_Client_NeedCheckVerify
#include "usart.h"
#define CP1616_Client_TxProc(List,Index) HAL_UART_Transmit(&huart1,List,Index,1000)
#define CP1616_Client_VerifyProc(pBuf,len) GetVerify_Sum(pBuf,len)
#define CP1616_Client_RxList_LenMax 100
#define CP1616_Client_TxList_LenMax 100
#include "CP1616_Client.h"


#endif
