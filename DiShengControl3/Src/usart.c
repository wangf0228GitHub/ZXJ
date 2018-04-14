/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "TCM.h"
#include "ModbusRTU_Master_Conf.h"
#include "Variables.h"
#include "ModbusRTU_Master.h"
#include "RIO.h"
#include "NMEA0183.h"
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	if(UartHandle->Instance==TCMUart.Instance)
	{
		TCMUart.RxState = HAL_UART_STATE_READY;
		while(HAL_UART_Receive_IT(&TCMUart,&TCM_Rx,1)==HAL_OK);
		TCMErr=5;
	}
	else if(UartHandle->Instance==ModbusRTU_MasterUart.Instance)
	{
		ModbusRTU_MasterUart.RxState = HAL_UART_STATE_READY;
		while(HAL_UART_Receive_IT(&ModbusRTU_MasterUart,&ModbusRTU_MasterRx,1)==HAL_OK);
	}
	else if(UartHandle->Instance==RIOUart.Instance)
	{
		RIOUart.RxState = HAL_UART_STATE_READY;
		while(HAL_UART_Receive_IT(&RIOUart,&RIO_Rx,1)==HAL_OK);
	}
	else if(UartHandle->Instance==GPRSUart.Instance)
	{
		GPRSUart.RxState = HAL_UART_STATE_READY;
		while(HAL_UART_Receive_IT(&GPRSUart,&GPRSRx,1)==HAL_OK);
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* UartHandle)
{
	if(UartHandle->Instance==TCMUart.Instance)
	{
		TCM_ProcRx(TCM_Rx);
		while(HAL_UART_Receive_IT(&TCMUart,&TCM_Rx,1)==HAL_OK);
	}
	else if(UartHandle->Instance==ModbusRTU_MasterUart.Instance)
	{
		ProcRx_ModbusRTU_Master(ModbusRTU_MasterRx);
		while(HAL_UART_Receive_IT(&ModbusRTU_MasterUart,&ModbusRTU_MasterRx,1)==HAL_OK);
	}
	else if(UartHandle->Instance==RIOUart.Instance)
	{
		RIO_ProcRx(RIO_Rx);
		while(HAL_UART_Receive_IT(&RIOUart,&RIO_Rx,1)==HAL_OK);
	}
	else if(UartHandle->Instance==GPRSUart.Instance)
	{
		NMEA0183_RxProc(GPRSRx);
		while(HAL_UART_Receive_IT(&GPRSUart,&GPRSRx,1)==HAL_OK);
	}
}
/* USER CODE END 0 */

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;
UART_HandleTypeDef huart7;
UART_HandleTypeDef huart8;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 38400;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART4 init function */

void MX_USART4_UART_Init(void)
{

  huart4.Instance = USART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART5 init function */

void MX_USART5_UART_Init(void)
{

  huart5.Instance = USART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_2;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART7 init function */

void MX_USART7_UART_Init(void)
{

  huart7.Instance = USART7;
  huart7.Init.BaudRate = 9600;
  huart7.Init.WordLength = UART_WORDLENGTH_8B;
  huart7.Init.StopBits = UART_STOPBITS_1;
  huart7.Init.Parity = UART_PARITY_NONE;
  huart7.Init.Mode = UART_MODE_TX_RX;
  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
  huart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART8 init function */

void MX_USART8_UART_Init(void)
{

  huart8.Instance = USART8;
  huart8.Init.BaudRate = 9600;
  huart8.Init.WordLength = UART_WORDLENGTH_8B;
  huart8.Init.StopBits = UART_STOPBITS_1;
  huart8.Init.Parity = UART_PARITY_NONE;
  huart8.Init.Mode = UART_MODE_TX_RX;
  huart8.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart8.Init.OverSampling = UART_OVERSAMPLING_16;
  huart8.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart8.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart8) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    /**USART3 GPIO Configuration    
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_8_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
  else if(uartHandle->Instance==USART4)
  {
  /* USER CODE BEGIN USART4_MspInit 0 */

  /* USER CODE END USART4_MspInit 0 */
    /* USART4 clock enable */
    __HAL_RCC_USART4_CLK_ENABLE();
  
    /**USART4 GPIO Configuration    
    PA0     ------> USART4_TX
    PA1     ------> USART4_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART4 interrupt Init */
    HAL_NVIC_SetPriority(USART3_8_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART4_MspInit 1 */

  /* USER CODE END USART4_MspInit 1 */
  }
  else if(uartHandle->Instance==USART5)
  {
  /* USER CODE BEGIN USART5_MspInit 0 */

  /* USER CODE END USART5_MspInit 0 */
    /* USART5 clock enable */
    __HAL_RCC_USART5_CLK_ENABLE();
  
    /**USART5 GPIO Configuration    
    PC12     ------> USART5_TX
    PD2     ------> USART5_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_USART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_USART5;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART5 interrupt Init */
    HAL_NVIC_SetPriority(USART3_8_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART5_MspInit 1 */

  /* USER CODE END USART5_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();
  
    /**USART6 GPIO Configuration    
    PA4     ------> USART6_TX
    PA5     ------> USART6_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_USART6;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART3_8_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
  else if(uartHandle->Instance==USART7)
  {
  /* USER CODE BEGIN USART7_MspInit 0 */

  /* USER CODE END USART7_MspInit 0 */
    /* USART7 clock enable */
    __HAL_RCC_USART7_CLK_ENABLE();
  
    /**USART7 GPIO Configuration    
    PC6     ------> USART7_TX
    PC7     ------> USART7_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART7;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART7 interrupt Init */
    HAL_NVIC_SetPriority(USART3_8_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART7_MspInit 1 */

  /* USER CODE END USART7_MspInit 1 */
  }
  else if(uartHandle->Instance==USART8)
  {
  /* USER CODE BEGIN USART8_MspInit 0 */

  /* USER CODE END USART8_MspInit 0 */
    /* USART8 clock enable */
    __HAL_RCC_USART8_CLK_ENABLE();
  
    /**USART8 GPIO Configuration    
    PC2     ------> USART8_TX
    PC3     ------> USART8_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_USART8;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART8 interrupt Init */
    HAL_NVIC_SetPriority(USART3_8_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART8_MspInit 1 */

  /* USER CODE END USART8_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PC10     ------> USART3_TX
    PC11     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
  /* USER CODE BEGIN USART3:USART3_8_IRQn disable */
    /**
    * Uncomment the line below to disable the "USART3_8_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USART3_8_IRQn); */
  /* USER CODE END USART3:USART3_8_IRQn disable */

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART4)
  {
  /* USER CODE BEGIN USART4_MspDeInit 0 */

  /* USER CODE END USART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART4_CLK_DISABLE();
  
    /**USART4 GPIO Configuration    
    PA0     ------> USART4_TX
    PA1     ------> USART4_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1);

    /* USART4 interrupt Deinit */
  /* USER CODE BEGIN USART4:USART3_8_IRQn disable */
    /**
    * Uncomment the line below to disable the "USART3_8_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USART3_8_IRQn); */
  /* USER CODE END USART4:USART3_8_IRQn disable */

  /* USER CODE BEGIN USART4_MspDeInit 1 */

  /* USER CODE END USART4_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART5)
  {
  /* USER CODE BEGIN USART5_MspDeInit 0 */

  /* USER CODE END USART5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART5_CLK_DISABLE();
  
    /**USART5 GPIO Configuration    
    PC12     ------> USART5_TX
    PD2     ------> USART5_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

    /* USART5 interrupt Deinit */
  /* USER CODE BEGIN USART5:USART3_8_IRQn disable */
    /**
    * Uncomment the line below to disable the "USART3_8_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USART3_8_IRQn); */
  /* USER CODE END USART5:USART3_8_IRQn disable */

  /* USER CODE BEGIN USART5_MspDeInit 1 */

  /* USER CODE END USART5_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();
  
    /**USART6 GPIO Configuration    
    PA4     ------> USART6_TX
    PA5     ------> USART6_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5);

    /* USART6 interrupt Deinit */
  /* USER CODE BEGIN USART6:USART3_8_IRQn disable */
    /**
    * Uncomment the line below to disable the "USART3_8_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USART3_8_IRQn); */
  /* USER CODE END USART6:USART3_8_IRQn disable */

  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART7)
  {
  /* USER CODE BEGIN USART7_MspDeInit 0 */

  /* USER CODE END USART7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART7_CLK_DISABLE();
  
    /**USART7 GPIO Configuration    
    PC6     ------> USART7_TX
    PC7     ------> USART7_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

    /* USART7 interrupt Deinit */
  /* USER CODE BEGIN USART7:USART3_8_IRQn disable */
    /**
    * Uncomment the line below to disable the "USART3_8_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USART3_8_IRQn); */
  /* USER CODE END USART7:USART3_8_IRQn disable */

  /* USER CODE BEGIN USART7_MspDeInit 1 */

  /* USER CODE END USART7_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART8)
  {
  /* USER CODE BEGIN USART8_MspDeInit 0 */

  /* USER CODE END USART8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART8_CLK_DISABLE();
  
    /**USART8 GPIO Configuration    
    PC2     ------> USART8_TX
    PC3     ------> USART8_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_2|GPIO_PIN_3);

    /* USART8 interrupt Deinit */
  /* USER CODE BEGIN USART8:USART3_8_IRQn disable */
    /**
    * Uncomment the line below to disable the "USART3_8_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USART3_8_IRQn); */
  /* USER CODE END USART8:USART3_8_IRQn disable */

  /* USER CODE BEGIN USART8_MspDeInit 1 */

  /* USER CODE END USART8_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
