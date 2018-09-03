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
  * COPYRIGHT(c) 2018 STMicroelectronics
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "stm32f1xx_hal.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define SwitchRange_Pin GPIO_PIN_13
#define SwitchRange_GPIO_Port GPIOC
#define AD_RVS_Pin GPIO_PIN_3
#define AD_RVS_GPIO_Port GPIOA
#define AD_CS_Pin GPIO_PIN_4
#define AD_CS_GPIO_Port GPIOA
#define AD_SCLK_Pin GPIO_PIN_5
#define AD_SCLK_GPIO_Port GPIOA
#define AD_MISO_Pin GPIO_PIN_6
#define AD_MISO_GPIO_Port GPIOA
#define AD_MOSI_Pin GPIO_PIN_7
#define AD_MOSI_GPIO_Port GPIOA
#define KEY_Clear_Pin GPIO_PIN_4
#define KEY_Clear_GPIO_Port GPIOC
#define LCD_RST_Pin GPIO_PIN_5
#define LCD_RST_GPIO_Port GPIOC
#define DB0_Pin GPIO_PIN_0
#define DB0_GPIO_Port GPIOB
#define DB1_Pin GPIO_PIN_1
#define DB1_GPIO_Port GPIOB
#define DB2_Pin GPIO_PIN_2
#define DB2_GPIO_Port GPIOB
#define DB10_Pin GPIO_PIN_10
#define DB10_GPIO_Port GPIOB
#define DB11_Pin GPIO_PIN_11
#define DB11_GPIO_Port GPIOB
#define DB12_Pin GPIO_PIN_12
#define DB12_GPIO_Port GPIOB
#define DB13_Pin GPIO_PIN_13
#define DB13_GPIO_Port GPIOB
#define DB14_Pin GPIO_PIN_14
#define DB14_GPIO_Port GPIOB
#define DB15_Pin GPIO_PIN_15
#define DB15_GPIO_Port GPIOB
#define LCD_RD_Pin GPIO_PIN_6
#define LCD_RD_GPIO_Port GPIOC
#define LCD_WR_Pin GPIO_PIN_7
#define LCD_WR_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_8
#define LCD_RS_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_9
#define LCD_CS_GPIO_Port GPIOC
#define LCD_LED_Pin GPIO_PIN_10
#define LCD_LED_GPIO_Port GPIOC
#define DB3_Pin GPIO_PIN_3
#define DB3_GPIO_Port GPIOB
#define DB4_Pin GPIO_PIN_4
#define DB4_GPIO_Port GPIOB
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOB
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOB
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOB
#define DB8_Pin GPIO_PIN_8
#define DB8_GPIO_Port GPIOB
#define DB9_Pin GPIO_PIN_9
#define DB9_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define STM32_Flash4EEPROM
#define wfEEPROM_INFO
#define wfEEPROM_BASE_ADDR 0x0807f000 //page31
/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
