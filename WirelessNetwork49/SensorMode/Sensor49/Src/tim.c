/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "..\wf\HardwareProfile.h"
#include "..\wf\Variables.h"
#include "..\..\..\A7128\A7128.h"
#include "..\wf\Function.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint32_t FrameIndex;
	if(htim->Instance==TIM7)
	{
		RLED_Toggle();
		if(TimeIndex>=999)
		{
			TimeIndex=0;			
			YLED_Toggle();
			ADCData4TxEnd=ADCSaveIndex;
			if(ADCData4TxEnd<ADCDataLen[SensorType])
			{
				ADCData4TxStart=ADCDataLen[SensorType]-ADCData4TxEnd;
				ADCData4TxStart=ADCDataMax[SensorType]-ADCData4TxStart;
			}
			else
			{
				ADCData4TxStart=ADCData4TxEnd-ADCDataLen[SensorType];
			}
			HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
			A7128_StrobeCmd(CMD_STBY);
		}
		else
			TimeIndex++;		
		
		if(SensorAddr!=1)
		{
			if(TimeIndex==2)
			{
				HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
				A7128_StrobeCmd(CMD_SLEEP);
			}
			else if(TimeIndex==TxStartTimeIndex-2)
			{
				HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
				A7128_StrobeCmd(CMD_STBY);//为省电
			}
		}
		/************************************************************************/
		/*  根据时隙处理主机状态                                                */
		/************************************************************************/
		if(TimeIndex>=TxStartTimeIndex && TimeIndex<=TxEndTimeIndex)
		{
			FrameIndex=TimeIndex-TxStartTimeIndex;
			if(TimeIndex==TxStartTimeIndex)//第一次启动PLL，减少发送延时
			{
				HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
				A7128_StrobeCmd(CMD_PLL);//为获得固定延时，约428us
			}
 			if(TimeIndex==TxEndTimeIndex)//最后一帧，带有电池电量
 			{
 				NetWorkType=Net_TxADCData;
 				A7128_TxFIFO[pTargetIDIndex]=MasterAddr;
 				A7128_TxFIFO[pSourceIDIndex]=SensorAddr;		
 				A7128_TxFIFO[pCommandIndex]=ADCDataSendCommand_BAT;
 				A7128_TxFIFO[pFrameNumIndex]=ADCBATData;	//数据帧号
				TxADCDataProc(FrameIndex);
 				//A7128_WriteFIFO_DMA_ADC((uint8_t*)(&ADCData4TXBuf[ADCDataMax[SensorType]-60]));	
 			}
 			else 
 			{
 				NetWorkType=Net_TxADCData;
 				A7128_TxFIFO[pTargetIDIndex]=MasterAddr;
 				A7128_TxFIFO[pSourceIDIndex]=SensorAddr;		
 				A7128_TxFIFO[pCommandIndex]=ADCDataSendCommand;
 				//x=TimeIndex-TxStartTimeIndex;
 				A7128_TxFIFO[pFrameNumIndex]=FrameIndex;	//数据帧号
 				TxADCDataProc(FrameIndex);
				//A7128_WriteFIFO_DMA_ADC((uint8_t*)(&ADCData4TXBuf[x*60]));
 			}		
		}
		else if(TimeIndex==(TxEndTimeIndex+1))//发送采集数据时隙过后，进入命令交互处理
		{
			HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
			A7128_StrobeCmd(CMD_STBY);//为省电
			if(SensorAddr>=98)
			{
				A7128_SetRx();
				NetWorkType=Net_RxData;	
			}
			else
			{
				A7128_StrobeCmd(CMD_SLEEP);
			}
		}
		else if(TimeIndex==757 && SensorAddr<=97)//异常处理前3ms，进入接收状态
		{
			HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
			A7128_StrobeCmd(CMD_STBY);//为省电			
		}
		else if(TimeIndex==759 && SensorAddr!=100)
		{
			A7128_SetRx();
			NetWorkType=Net_RxData;	
		}
	}
	if(htim->Instance==TIM6)//10以上A7128未有动作，休眠
	{
		MCUSleep();
	}
	if(htim->Instance==TIM2)//ADC触发
	{
		//A7128_SCS_Toggle();
	}
}
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 3;//0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 31249;//6249;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM6 init function */
void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 31999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 10000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM7 init function */
void MX_TIM7_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 31999;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* TIM6 clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM7)
  {
  /* USER CODE BEGIN TIM7_MspInit 0 */

  /* USER CODE END TIM7_MspInit 0 */
    /* TIM7 clock enable */
    __HAL_RCC_TIM7_CLK_ENABLE();

    /* TIM7 interrupt Init */
    HAL_NVIC_SetPriority(TIM7_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
  /* USER CODE BEGIN TIM7_MspInit 1 */

  /* USER CODE END TIM7_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspDeInit 0 */

  /* USER CODE END TIM6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();

    /* TIM6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspDeInit 1 */

  /* USER CODE END TIM6_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM7)
  {
  /* USER CODE BEGIN TIM7_MspDeInit 0 */

  /* USER CODE END TIM7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM7_CLK_DISABLE();

    /* TIM7 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM7_IRQn);
  /* USER CODE BEGIN TIM7_MspDeInit 1 */

  /* USER CODE END TIM7_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
