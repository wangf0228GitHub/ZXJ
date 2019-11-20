/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

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
#define A7128_GIO2_Pin GPIO_PIN_13
#define A7128_GIO2_GPIO_Port GPIOC
#define A7128_GIO1_Pin GPIO_PIN_0
#define A7128_GIO1_GPIO_Port GPIOA
#define A7128_GIO1_EXTI_IRQn EXTI0_1_IRQn
#define INA118_OUT_Pin GPIO_PIN_1
#define INA118_OUT_GPIO_Port GPIOA
#define A7128_SCS_Pin GPIO_PIN_4
#define A7128_SCS_GPIO_Port GPIOA
#define A7128_SCK_Pin GPIO_PIN_5
#define A7128_SCK_GPIO_Port GPIOA
#define A7128_GIO2A6_Pin GPIO_PIN_6
#define A7128_GIO2A6_GPIO_Port GPIOA
#define A7128_SDIO_Pin GPIO_PIN_7
#define A7128_SDIO_GPIO_Port GPIOA
#define BAT_AD_OUT_Pin GPIO_PIN_0
#define BAT_AD_OUT_GPIO_Port GPIOB
#define EN_BAT_Pin GPIO_PIN_1
#define EN_BAT_GPIO_Port GPIOB
#define Run_YLED_Pin GPIO_PIN_10
#define Run_YLED_GPIO_Port GPIOA
#define Run_RLED_Pin GPIO_PIN_11
#define Run_RLED_GPIO_Port GPIOA
#define A7128_CKO_Pin GPIO_PIN_15
#define A7128_CKO_GPIO_Port GPIOA
#define CONFIG1_Pin GPIO_PIN_3
#define CONFIG1_GPIO_Port GPIOB
#define CONFIG2_Pin GPIO_PIN_4
#define CONFIG2_GPIO_Port GPIOB
#define CONFIG3_Pin GPIO_PIN_5
#define CONFIG3_GPIO_Port GPIOB
#define CONFIG4_Pin GPIO_PIN_6
#define CONFIG4_GPIO_Port GPIOB
#define CONFIG5_Pin GPIO_PIN_7
#define CONFIG5_GPIO_Port GPIOB
#define EN_ADD_3P3_Pin GPIO_PIN_8
#define EN_ADD_3P3_GPIO_Port GPIOB
#define EN_ADD_1P25_Pin GPIO_PIN_9
#define EN_ADD_1P25_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define TXMode
#define YLED_ON() HAL_GPIO_WritePin(Run_YLED_GPIO_Port,Run_YLED_Pin,GPIO_PIN_RESET)
#define YLED_OFF() HAL_GPIO_WritePin(Run_YLED_GPIO_Port,Run_YLED_Pin,GPIO_PIN_SET)

#define RLED_ON() HAL_GPIO_WritePin(Run_RLED_GPIO_Port,Run_RLED_Pin,GPIO_PIN_RESET)
#define RLED_OFF() HAL_GPIO_WritePin(Run_RLED_GPIO_Port,Run_RLED_Pin,GPIO_PIN_SET)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
