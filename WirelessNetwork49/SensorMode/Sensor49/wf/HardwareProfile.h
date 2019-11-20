#ifndef __HardwareProfile_H__
#define __HardwareProfile_H__

#include "gpio.h"
#define A7128SPI hspi1
#define A7128_SCS_Low() HAL_GPIO_WritePin(A7128_SCS_GPIO_Port,A7128_SCS_Pin,GPIO_PIN_RESET)//;nop();nop();nop();nop();nop();nop();nop();nop();nop();nop()
#define A7128_SCS_High() HAL_GPIO_WritePin(A7128_SCS_GPIO_Port,A7128_SCS_Pin,GPIO_PIN_SET)//;nop();nop();nop();nop();nop();nop();nop();nop();nop();nop()
#define A7128_SCS_Toggle() HAL_GPIO_TogglePin(A7128_SCS_GPIO_Port,A7128_SCS_Pin)


#define A7128_GIO1_Read() HAL_GPIO_ReadPin(A7128_GIO1_GPIO_Port,A7128_GIO1_Pin)
#define A7128_GIO2_Read() HAL_GPIO_ReadPin(A7128_GIO2_GPIO_Port,A7128_GIO2_Pin)
#define A7128_SCS_Read() HAL_GPIO_ReadPin(A7128_SCS_GPIO_Port,A7128_SCS_Pin)

#define YLED_ON() HAL_GPIO_WritePin(Run_YLED_GPIO_Port,Run_YLED_Pin,GPIO_PIN_RESET)
#define YLED_OFF() HAL_GPIO_WritePin(Run_YLED_GPIO_Port,Run_YLED_Pin,GPIO_PIN_SET)
#define YLED_Toggle() HAL_GPIO_TogglePin(Run_YLED_GPIO_Port,Run_YLED_Pin)


#define RLED_ON() HAL_GPIO_WritePin(Run_RLED_GPIO_Port,Run_RLED_Pin,GPIO_PIN_RESET)
#define RLED_OFF() HAL_GPIO_WritePin(Run_RLED_GPIO_Port,Run_RLED_Pin,GPIO_PIN_SET)
#define RLED_Toggle() HAL_GPIO_TogglePin(Run_RLED_GPIO_Port,Run_RLED_Pin)


#define ENBAT_Enable() HAL_GPIO_WritePin(EN_BAT_GPIO_Port,EN_BAT_Pin,GPIO_PIN_SET)
#define ENBAT_Disable() HAL_GPIO_WritePin(EN_BAT_GPIO_Port,EN_BAT_Pin,GPIO_PIN_RESET)

#define EN_ADD_3P3_Enable() HAL_GPIO_WritePin(EN_ADD_3P3_GPIO_Port,EN_ADD_3P3_Pin,GPIO_PIN_SET)
#define EN_ADD_3P3_Disable() HAL_GPIO_WritePin(EN_ADD_3P3_GPIO_Port,EN_ADD_3P3_Pin,GPIO_PIN_RESET)

#define EN_ADD_1P25_Enable() HAL_GPIO_WritePin(EN_ADD_1P25_GPIO_Port,EN_ADD_1P25_Pin,GPIO_PIN_SET)
#define EN_ADD_1P25_Disable() HAL_GPIO_WritePin(EN_ADD_1P25_GPIO_Port,EN_ADD_1P25_Pin,GPIO_PIN_RESET)
#endif
