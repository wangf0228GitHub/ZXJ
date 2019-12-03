#ifndef   __Function_h__
#define   __Function_h__

#include <stdint.h>
#include "main.h"

void A7128_SetTx(void);
void A7128_SetRx(void);
void NetAbnormalTxProc(uint32_t addr,uint32_t fIndex);
void Networking_WakeUp(uint32_t x5);
void Networking_SignIn(void);
void Networking_StartNet(void);
void UartRxProc(void);
uint32_t Uart_SignInProc(void);
void Uart_ClosedProc(void);
uint32_t Networking_GetCalibration(void);
uint32_t Networking_SetCalibration(void);
#endif
