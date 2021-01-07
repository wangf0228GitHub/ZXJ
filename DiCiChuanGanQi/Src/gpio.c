/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "..\vsDCCGQ\ADS131M06.h"
#include "..\Inc\usart.h"

uint32_t osrADC[3];
uint8_t UARTTxList[9];
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == DRDY_Pin)
	{
		ADS131_ReadADC();
		osrADC[1] += MAKE_INT(spiRxList[9], MAKE_SHORT(spiRxList[10], spiRxList[11]));
		osrADC[0] += MAKE_INT(spiRxList[12], MAKE_SHORT(spiRxList[13], spiRxList[14]));
		osrADC[2] += MAKE_INT(spiRxList[15], MAKE_SHORT(spiRxList[16], spiRxList[17]));
		myOSR++;
		if (myOSR == myOSRMax)//达到采样次数，准备发送
		{
			myOSR = 0;
			osrADC[0] = osrADC[0] / myOSRMax;
			osrADC[1] = osrADC[1] / myOSRMax;
			osrADC[2] = osrADC[2] / myOSRMax;
			UARTTxList[0] = (uint8_t)(osrADC[0] >> 16);
			UARTTxList[1] = (uint8_t)(osrADC[0] >> 8);
			UARTTxList[2] = (uint8_t)(osrADC[0]);
			UARTTxList[3] = (uint8_t)(osrADC[1] >> 16);
			UARTTxList[4] = (uint8_t)(osrADC[1] >> 8);
			UARTTxList[5] = (uint8_t)(osrADC[1]);
			UARTTxList[6] = (uint8_t)(osrADC[2] >> 16);
			UARTTxList[7] = (uint8_t)(osrADC[2] >> 8);
			UARTTxList[8] = (uint8_t)(osrADC[2]);
			osrADC[0] = 0;
			osrADC[1] = 0;
			osrADC[2] = 0;
			HAL_UART_Transmit_DMA(&huart2, UARTTxList, 9);
		}
	}
}
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI_CS_Pin|REST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = DRDY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DRDY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SPI_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(SPI_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = REST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(REST_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
  //HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
