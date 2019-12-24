/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
#include "..\wf\HardwareProfile.h"
#include "..\wf\Variables.h"
#include "..\..\..\..\..\WF_Device\wfDefine.h"
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc1)
{
	uint16_t x1,x2;
	float fx1,fx2;
	//RLED_Toggle();
	/************************************************************************/
	/* ADCData4DMA.u16[0]=0x0123;
	   ADCData4DMA.u16[2]=0x0456;    
	   //x.u8[4] : 23 41 56 xx
	   _ADCData4DMA y;
	   y.u8[0]=ADCData4DMA.u8[0];
	   y.u8[1]=MAKE_BYTE(ADCData4DMA.u8[5],ADCData4DMA.u8[1]);
	   y.u8[2]=ADCData4DMA.u8[4];
	*/
	/************************************************************************/
	if(bCalibrationNet)//标定时直接传输ad数据
	{
		ADCData4[ADCSaveIndex++]=ADCData4DMA.u8[0];
		
		fx1=Linear_k.f*ADCData4DMA.u16[0]+Linear_b.f;
		fx1=fx1*SensorGain.f;
		x1=(uint16_t)fx1;
		ADCData4[ADCSaveIndex++]=MAKE_BYTE(HIGH_BYTE(x1),ADCData4DMA.u8[1]);
		ADCData4[ADCSaveIndex++]=LOW_BYTE(x1);
	}
	else//利用系数计算当前物理量
	{
		/************************************************************************/
		/* 运算时长30us                                                         */
		/************************************************************************/
		fx1=Linear_k.f*ADCData4DMA.u16[0]+Linear_b.f;
		fx1=fx1*SensorGain.f;
		x1=(uint16_t)fx1;

		fx2=Linear_k.f*ADCData4DMA.u16[2]+Linear_b.f;
		fx2=fx2*SensorGain.f;
		x2=(uint16_t)fx2;

		ADCData4[ADCSaveIndex++]=LOW_BYTE(x1);
		ADCData4[ADCSaveIndex++]=MAKE_BYTE(HIGH_BYTE(x2),HIGH_BYTE(x1));
		ADCData4[ADCSaveIndex++]=LOW_BYTE(x2);
	}
	ADCBATData=ADCData4DMA.u16[3]>>4;
 	if(ADCSaveIndex==ADCDataMax[SensorType])
	{
		ADCSaveIndex=0;
	}
// 	ADCData4SaveBuf[ADCSaveIndex++]=LOW_BYTE(sinx[sinx_index]);
// 	ADCData4SaveBuf[ADCSaveIndex++]=MAKE_BYTE(HIGH_BYTE(sinx[sinx_index]),HIGH_BYTE(sinx[sinx_index+1]));
// 	ADCData4SaveBuf[ADCSaveIndex++]=LOW_BYTE(sinx[sinx_index+1]);
// 	sinx_index+=2;
// 	if(sinx_index>255)
// 		sinx_index=0;
	
	
}
/* USER CODE END 0 */

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

/* ADC init function */
void MX_ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = ENABLE;
  hadc.Init.Oversample.Ratio = ADC_OVERSAMPLING_RATIO_8;
  hadc.Init.Oversample.RightBitShift = ADC_RIGHTBITSHIFT_3;
  hadc.Init.Oversample.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_TRGO;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_8;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC GPIO Configuration    
    PA1     ------> ADC_IN1
    PB0     ------> ADC_IN8 
    */
    GPIO_InitStruct.Pin = INA118_OUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(INA118_OUT_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BAT_AD_OUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BAT_AD_OUT_GPIO_Port, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC Init */
    hdma_adc.Instance = DMA1_Channel1;
    hdma_adc.Init.Request = DMA_REQUEST_0;
    hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc.Init.Mode = DMA_CIRCULAR;
    hdma_adc.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_adc) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC GPIO Configuration    
    PA1     ------> ADC_IN1
    PB0     ------> ADC_IN8 
    */
    HAL_GPIO_DeInit(INA118_OUT_GPIO_Port, INA118_OUT_Pin);

    HAL_GPIO_DeInit(BAT_AD_OUT_GPIO_Port, BAT_AD_OUT_Pin);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
