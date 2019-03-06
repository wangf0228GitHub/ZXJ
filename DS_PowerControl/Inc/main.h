/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include "stm32f0xx_hal.h"

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
#define LouShui1_Pin GPIO_PIN_2
#define LouShui1_GPIO_Port GPIOA
#define LouShui2_Pin GPIO_PIN_3
#define LouShui2_GPIO_Port GPIOA
#define W5500Reset_Pin GPIO_PIN_7
#define W5500Reset_GPIO_Port GPIOA
#define IOBak6_Pin GPIO_PIN_5
#define IOBak6_GPIO_Port GPIOC
#define IOBak5_Pin GPIO_PIN_0
#define IOBak5_GPIO_Port GPIOB
#define IOBak4_Pin GPIO_PIN_1
#define IOBak4_GPIO_Port GPIOB
#define IOBak3_Pin GPIO_PIN_2
#define IOBak3_GPIO_Port GPIOB
#define IOBak2_Pin GPIO_PIN_10
#define IOBak2_GPIO_Port GPIOB
#define PowerControl_Pin GPIO_PIN_11
#define PowerControl_GPIO_Port GPIOB
#define SPI_WSCS_Pin GPIO_PIN_12
#define SPI_WSCS_GPIO_Port GPIOB
#define SPI_CLK_Pin GPIO_PIN_13
#define SPI_CLK_GPIO_Port GPIOB
#define SPI_MISO_Pin GPIO_PIN_14
#define SPI_MISO_GPIO_Port GPIOB
#define SPI_MOSI_Pin GPIO_PIN_15
#define SPI_MOSI_GPIO_Port GPIOB
#define SenserPower_Pin GPIO_PIN_15
#define SenserPower_GPIO_Port GPIOA
#define JTPower_Pin GPIO_PIN_6
#define JTPower_GPIO_Port GPIOB
#define RUNLED_Pin GPIO_PIN_7
#define RUNLED_GPIO_Port GPIOB
#define SimI2C_CLK_Pin GPIO_PIN_8
#define SimI2C_CLK_GPIO_Port GPIOB
#define SimI2C_DATA_Pin GPIO_PIN_9
#define SimI2C_DATA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define WhoIam 0x01 //传感器采集板
#define Verify_Sum
#define Verify_CRC16
#define MS8607_SimI2C
#define MCU_STM32
#define STM32_Flash4EEPROM
#define wfGetTick() HAL_GetTick()
#define wfEEPROM_INFO
#define wfEEPROM_BASE_ADDR 0x0803f800


#define Power_ON() HAL_GPIO_WritePin(PowerControl_GPIO_Port,PowerControl_Pin,GPIO_PIN_SET)
#define Power_OFF() HAL_GPIO_WritePin(PowerControl_GPIO_Port,PowerControl_Pin,GPIO_PIN_RESET)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
