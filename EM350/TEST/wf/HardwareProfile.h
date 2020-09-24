#ifndef __HardwareProfile_H__
#define __HardwareProfile_H__

#include "usart.h"
#include "wfSys.h"

#define ATCommand_Tx_Ex
#define ATCommand_TxByte(x) txChar=x;HAL_UART_Transmit(&huart1,(uint8_t *)&txChar,1,1000)
#define ATCommand_PutString(x) HAL_UART_Transmit(&huart1,(uint8_t *)x,strlen(x),1000)
extern uint32_t atIndex;
extern uint32_t atCount;
extern uint8_t* ATList[100];
#endif
