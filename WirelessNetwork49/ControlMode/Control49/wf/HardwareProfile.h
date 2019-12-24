#ifndef __HardwareProfile_H__
#define __HardwareProfile_H__

#include "gpio.h"
#define A7128SPI hspi3
#define A7128_SCS_Low() HAL_GPIO_WritePin(A7128_SCS_GPIO_Port,A7128_SCS_Pin,GPIO_PIN_RESET)//;nop();nop();nop();nop();nop();nop();nop();nop();nop();nop()
#define A7128_SCS_High() HAL_GPIO_WritePin(A7128_SCS_GPIO_Port,A7128_SCS_Pin,GPIO_PIN_SET)//;nop();nop();nop();nop();nop();nop();nop();nop();nop();nop()
#define A7128_GIO1_Read() HAL_GPIO_ReadPin(A7128_GIO1_GPIO_Port,A7128_GIO1_Pin)
#define A7128_GIO2_Read() HAL_GPIO_ReadPin(A7128_GIO2_GPIO_Port,A7128_GIO2_Pin)
#define A7128_SCS_Read() HAL_GPIO_ReadPin(A7128_SCS_GPIO_Port,A7128_SCS_Pin)

#define YLED_ON() HAL_GPIO_WritePin(Run_YLED_GPIO_Port,Run_YLED_Pin,GPIO_PIN_RESET)
#define YLED_OFF() HAL_GPIO_WritePin(Run_YLED_GPIO_Port,Run_YLED_Pin,GPIO_PIN_SET)
#define YLED_Toggle() HAL_GPIO_TogglePin(Run_YLED_GPIO_Port,Run_YLED_Pin)


#define RLED_ON() HAL_GPIO_WritePin(Run_RLED_GPIO_Port,Run_RLED_Pin,GPIO_PIN_RESET)
#define RLED_OFF() HAL_GPIO_WritePin(Run_RLED_GPIO_Port,Run_RLED_Pin,GPIO_PIN_SET)
#define RLED_Toggle() HAL_GPIO_TogglePin(Run_RLED_GPIO_Port,Run_RLED_Pin)

#define DMA4Copy hdma_memtomem_dma2_stream3
#define DMA4Clear hdma_memtomem_dma1_stream2

#define CP1616_Client_AddrLen 0
#define CP1616_Client_DataBufLen 2
#define CP1616_Client_TxProc(x,y)// Uart1_VerifySumAddTxByte(x)
#define CP1616_Client_VerifyProc(x,y) 1
#endif
