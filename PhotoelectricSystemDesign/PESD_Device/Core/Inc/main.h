/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_WorkLink_AD2JT_Pin GPIO_PIN_0
#define LED_WorkLink_AD2JT_GPIO_Port GPIOA
#define LED_WorkLink_Tx2_Pin GPIO_PIN_1
#define LED_WorkLink_Tx2_GPIO_Port GPIOA
#define LED_WorkLink_HL2TZ_Pin GPIO_PIN_5
#define LED_WorkLink_HL2TZ_GPIO_Port GPIOA
#define LED_WorkLink_HL2Led_Pin GPIO_PIN_6
#define LED_WorkLink_HL2Led_GPIO_Port GPIOA
#define LED_WorkLink_DAC_Pin GPIO_PIN_7
#define LED_WorkLink_DAC_GPIO_Port GPIOA
#define LED_Mode3_Pin GPIO_PIN_12
#define LED_Mode3_GPIO_Port GPIOB
#define LED_Mode2_Pin GPIO_PIN_13
#define LED_Mode2_GPIO_Port GPIOB
#define LED_Mode1_Pin GPIO_PIN_14
#define LED_Mode1_GPIO_Port GPIOB
#define LED_WorkLink_PC_Pin GPIO_PIN_15
#define LED_WorkLink_PC_GPIO_Port GPIOB
#define Button2_Pin GPIO_PIN_15
#define Button2_GPIO_Port GPIOA
#define Button1_Pin GPIO_PIN_3
#define Button1_GPIO_Port GPIOB
#define LED_WorkLink_ADC2_Pin GPIO_PIN_4
#define LED_WorkLink_ADC2_GPIO_Port GPIOB
#define LED_WorkLink_XH2AD_Pin GPIO_PIN_5
#define LED_WorkLink_XH2AD_GPIO_Port GPIOB
#define LED_WorkLink_ADC1_Pin GPIO_PIN_6
#define LED_WorkLink_ADC1_GPIO_Port GPIOB
#define LED_WorkLink_IV2AD_Pin GPIO_PIN_7
#define LED_WorkLink_IV2AD_GPIO_Port GPIOB
#define LED_WorkLink_Si2IV_Pin GPIO_PIN_8
#define LED_WorkLink_Si2IV_GPIO_Port GPIOB
#define LED_WorkLink_Rx2_Pin GPIO_PIN_9
#define LED_WorkLink_Rx2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

extern uint8_t huart1Rx;
extern uint8_t huart2Rx;
extern uint8_t Mode;
extern uint8_t AD2List[200];
extern uint8_t AD2NeedCount;
extern uint8_t AD2ListIndex;
extern uint8_t Uart2List[200];
extern uint8_t Uart2ListIndex;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
