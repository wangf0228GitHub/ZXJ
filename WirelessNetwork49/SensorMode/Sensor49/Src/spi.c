/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
#include "spi.h"

/* USER CODE BEGIN 0 */
#include "..\wf\HardwareProfile.h"
#include "..\..\..\A7128\A7128.h"
#include "..\wf\Variables.h"
#include "..\Inc\tim.h"
#include "..\wf\Function.h"
#include "..\Inc\adc.h"
#include "..\Drivers\STM32L0xx_HAL_Driver\Inc\stm32l0xx_hal_adc_ex.h"
#include "..\..\..\..\..\WF_Device\wfDefine.h"
#include "..\..\..\..\..\WF_Device\stm32\wfSys.h"
/************************************************************************/
/* DMA传输数据完成后，启动发送                                          */
/************************************************************************/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance==A7128SPI.Instance)
	{
		A7128_SCS_High();
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
		HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
		A7128_StrobeCmd(CMD_TX);
	}
}
/************************************************************************/
/* DMA读取完成，用于接收到网络数据的后续处理                            */
/************************************************************************/
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{	
	uint32_t i;
	ADC_ChannelConfTypeDef sConfig = {0};
	if(hspi->Instance==A7128SPI.Instance)
	{
		A7128_SCS_High();		
		if(A7128_RxFIFO[pSourceIDIndex]!=MasterAddr)//节点只接收控制器数据
		{
			A7128_SetRx();
			return;
		}
		__HAL_TIM_SET_COUNTER(&htim6,0);//A7128动作重置休眠计时器
		if(A7128_RxFIFO[pCommandIndex]==SetIDCommand)//设定地址指令
		{
			if(A7128_RxFIFO[pTargetIDIndex]==BroadcastAddr || A7128_RxFIFO[pTargetIDIndex]==SensorAddr)//广播地址设定
			{
				NetWorkType=Net_TxComData;
				A7128_TxFIFO[pTargetIDIndex]=MasterAddr;
				A7128_TxFIFO[pSourceIDIndex]=SensorAddr;		
				A7128_TxFIFO[pCommandIndex]=SetIDCommand;
				A7128_TxFIFO[pLenIndex]=3;	//数据区长度
				A7128_TxFIFO[pDataIndex]=SensorAddr;
				A7128_TxFIFO[pDataIndex+1]=0x02;
				A7128_TxFIFO[pDataIndex+2]=A7128_RxFIFO[pDataIndex];
				SensorIDData.u16[0]=0x6677;
				SensorIDData.u8[2]=A7128_RxFIFO[pDataIndex];
				wfEEPROM_WriteWord(0,SensorIDData.u32);
				SensorAddr=A7128_RxFIFO[pDataIndex];
				A7128_WriteFIFO_DMA();
				return;
			}
			else
			{
				A7128_SetRx();
				return;
			}
		}
		if(SensorAddr==0 || SensorAddr==101)//未设定地址的
		{
			A7128_SetRx();
			return;
		}
		if(A7128_RxFIFO[pCommandIndex]>=0x10)//非广播地址
		{			
		 	if(A7128_RxFIFO[pTargetIDIndex]!=SensorAddr)//判断地址是否相符
			{				
				A7128_SetRx();
				return;
			}
		}
		switch(A7128_RxFIFO[pCommandIndex])
		{
		case WakeUpCommand://唤醒指令
			A7128_SetRx();
			break;
		case StartNetCommand://启动采集网络			
			if(WF_CHECK_FLAG(htim2.Instance->CR1,TIM_CR1_CEN)==0)//开始采集数据,双通道
			{
				HAL_ADC_Stop(&hadc);
				HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);//校准ADC，24us
				sConfig.Channel = ADC_CHANNEL_1;
				sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
				if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
				{
					Error_Handler();
				}
				sConfig.Channel = ADC_CHANNEL_8;
				sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
				if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
				{
					Error_Handler();
				}
				ENBAT_Enable();
// 				EN_ADD_3P3_Enable();
// 				EN_ADD_1P25_Enable();
				ADCSaveIndex=0;
				HAL_TIM_Base_Start(&htim2);
				HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADCData4DMA.u8, 4);
			}
			A7128_SetRx();
			break;
		case StopNetCommand://停止采集网络
//			wfDelay_ms(500);//500ms后复位
			NVIC_SystemReset();
// 			ENBAT_Disable();
// 			EN_ADD_3P3_Disable();
// 			EN_ADD_1P25_Disable();
// 			HAL_TIM_Base_Stop_IT(&htim2);
// 			HAL_TIM_Base_Stop_IT(&htim7);
// 			A7128_SetRx();
// 			NetWorkType=Net_RxData;
			break;
		case FrameSyncCommand://同步时间轴
			//RLED_Toggle();
			TimeIndex=999;
			HAL_TIM_Base_Stop_IT(&htim7);
			__HAL_TIM_SET_COUNTER(&htim7,0);
			__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
			HAL_TIM_Base_Start_IT(&htim7);
			HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
			A7128_StrobeCmd(CMD_STBY);
			//A7128_SetRx();
			bCalibrationNet=A7128_RxFIFO[pDataIndex];
			if(WF_CHECK_FLAG(htim2.Instance->CR1,TIM_CR1_CEN)==0)//开始采集数据,双通道
			{
				HAL_ADC_Stop(&hadc);
				HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);//校准ADC，24us
				sConfig.Channel = ADC_CHANNEL_1;
				sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
				if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
				{
					Error_Handler();
				}
				sConfig.Channel = ADC_CHANNEL_8;
				sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
				if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
				{
					Error_Handler();
				}
				ENBAT_Enable();
// 				EN_ADD_3P3_Enable();
// 				EN_ADD_1P25_Enable();
				ADCSaveIndex=0;
				HAL_TIM_Base_Start(&htim2);
				HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADCData4DMA.u8, 4);
			}
			break;
		case AbnormalAddrListCommand://异常节点名单
			if(bAbnormal)
			{
				A7128_SetRx();
				break;
			}
			for(i=0;i<A7128_RxFIFO[pLenIndex];i++)
			{
				if(A7128_RxFIFO[pDataIndex+i]==SensorAddr)//异常名单中
				{
					bAbnormal=1;
					A7128_SetRx();
					break;
				}
			}
			if(bAbnormal==0)
			{
				HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
				A7128_StrobeCmd(CMD_SLEEP);
			}
			break;
		case SignInCommand: //点名，签到，数据区为电池电量
			ADCBAT();
			NetWorkType=Net_TxComData;
			A7128_TxFIFO[pTargetIDIndex]=MasterAddr;
			A7128_TxFIFO[pSourceIDIndex]=SensorAddr;		
			A7128_TxFIFO[pCommandIndex]=SignInCommand;
			A7128_TxFIFO[pLenIndex]=1;	//数据区长度
			A7128_TxFIFO[pDataIndex]=ADCBATData;
			A7128_WriteFIFO_DMA();
			break;
		case DataResendCommand://利用采集数据帧重新发送指定帧的采集数据
			NetWorkType=Net_TxComData;
			A7128_TxFIFO[pTargetIDIndex]=MasterAddr;
			A7128_TxFIFO[pSourceIDIndex]=SensorAddr;		
			A7128_TxFIFO[pCommandIndex]=ADCDataSendCommand;
			A7128_TxFIFO[pFrameNumIndex]=A7128_RxFIFO[pDataIndex];	//数据帧号
			TxADCDataProc(A7128_RxFIFO[pDataIndex]);
			//A7128_WriteFIFO_DMA_ADC((uint8_t*)(&ADCData4[A7128_RxFIFO[pDataIndex]*60]));
			break;
		case SetCalibrationCommand:
			NetWorkType=Net_TxComData;
			A7128_TxFIFO[pTargetIDIndex]=MasterAddr;
			A7128_TxFIFO[pSourceIDIndex]=SensorAddr;		
			A7128_TxFIFO[pCommandIndex]=SetCalibrationCommand;
			A7128_TxFIFO[pLenIndex]=24;	//数据区长度
			for(i=0;i<4;i++)
			{
				A7128_TxFIFO[pDataIndex+i]=Linear_k.u8[i];
				A7128_TxFIFO[pDataIndex+i+4]=Linear_b.u8[i];
				A7128_TxFIFO[pDataIndex+i+8]=SensorGain.u8[i];
			}
			for(i=0;i<4;i++)
			{
				Linear_k.u8[i]=A7128_RxFIFO[pDataIndex+i];
				Linear_b.u8[i]=A7128_RxFIFO[pDataIndex+i+4];
				SensorGain.u8[i]=A7128_RxFIFO[pDataIndex+i+8];
			}
			for(i=0;i<4;i++)
			{
				A7128_TxFIFO[pDataIndex+i+12]=Linear_k.u8[i];
				A7128_TxFIFO[pDataIndex+i+16]=Linear_b.u8[i];
				A7128_TxFIFO[pDataIndex+i+20]=SensorGain.u8[i];
			}
			wfEEPROM_WriteWord(4,Linear_k.u32);
			wfEEPROM_WriteWord(8,Linear_b.u32);
			wfEEPROM_WriteWord(12,SensorGain.u32);
			A7128_WriteFIFO_DMA();
			break;
		case GetCalibrationCommand:
			NetWorkType=Net_TxComData;
			A7128_TxFIFO[pTargetIDIndex]=MasterAddr;
			A7128_TxFIFO[pSourceIDIndex]=SensorAddr;		
			A7128_TxFIFO[pCommandIndex]=GetCalibrationCommand;
			A7128_TxFIFO[pLenIndex]=12;	//数据区长度
			for(i=0;i<4;i++)
			{
				A7128_TxFIFO[pDataIndex+i]=Linear_k.u8[i];
				A7128_TxFIFO[pDataIndex+i+4]=Linear_b.u8[i];
				A7128_TxFIFO[pDataIndex+i+8]=SensorGain.u8[i];
			}
			A7128_WriteFIFO_DMA();
			break;
		default:
			A7128_SetRx();
			break;
		}
	}
}
/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = A7128_SCK_Pin|A7128_GIO2_Pin|A7128_SDIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* SPI1 DMA Init */
    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA1_Channel3;
    hdma_spi1_tx.Init.Request = DMA_REQUEST_1;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(spiHandle,hdmatx,hdma_spi1_tx);

    /* SPI1_RX Init */
    hdma_spi1_rx.Instance = DMA1_Channel2;
    hdma_spi1_rx.Init.Request = DMA_REQUEST_1;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(spiHandle,hdmarx,hdma_spi1_rx);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOA, A7128_SCK_Pin|A7128_GIO2_Pin|A7128_SDIO_Pin);

    /* SPI1 DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmatx);
    HAL_DMA_DeInit(spiHandle->hdmarx);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
