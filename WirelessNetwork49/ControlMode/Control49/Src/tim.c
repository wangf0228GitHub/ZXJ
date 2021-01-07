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
#include "..\..\..\..\..\WF_Device\wfDefine.h"
#include "..\Inc\dma.h"
#include "..\wf\Function.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint32_t addr,fIndex,i;
	uint32_t x;
	if(htim->Instance==TIM13)//����ͬ��ָ����ڵ���ͬ��ʱ϶ʱ��ƫ��
	{
		HAL_TIM_Base_Stop_IT(&htim13);	
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		A7128_StrobeCmd(CMD_STBY);//Ϊ��ù̶���ʱ��Լ428us
		A7128Work=A7128Work_FrameSync;
		A7128_TxFIFO[pTargetIDIndex]=BroadcastAddr;
		A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
		A7128_TxFIFO[pCommandIndex]=FrameSyncCommand;
		A7128_TxFIFO[pLenIndex]=1;				
		A7128_TxFIFO[pDataIndex]=bCalibrationNet;	
		A7128_WriteFIFO_DMA();
	}
	if(htim->Instance==TIM14)
	{
		RLED_Toggle();
		if(TimeIndex>=999)
		{
			TimeIndex=0;			
			gTempIndex++;
		}
		else
			TimeIndex++;
		/************************************************************************/
		/*  ����ʱ϶��������״̬                                                */
		/************************************************************************/
		if(TimeIndex==999)//��ʼ�������ڵĳ�ʼ����
		{
			if(ADCData4SaveBuf==0)//�״���������
			{
				ADCData4TXBuf=&ADCData4TX1;
				ADCData4SaveBuf=&ADCData4TX2;
				bNewFrame=0;
				bNewADCData=0;
			}
			else
			{
				if(ADCData4SaveBuf==&ADCData4TX1)
				{
					ADCData4TXBuf=&ADCData4TX1;
					ADCData4SaveBuf=&ADCData4TX2;
				}
				else
				{
					ADCData4TXBuf=&ADCData4TX2;
					ADCData4SaveBuf=&ADCData4TX1;
				}
				bNewADCData=0;
				if(NetWorkMode!=Net_Stop)
					bNewFrame=1;
			}			
			//������ݵ����־,20us����
			gMEMDMA2=0;
			HAL_DMA_PollForTransfer(&DMA4Clear,HAL_DMA_FULL_TRANSFER,1);
			HAL_DMA_Start(&DMA4Clear,(uint32_t)(&gMEMDMA2),(uint32_t)(&ADCDataTag.all),159);
			//�����ǰ�洢������������
 			HAL_DMA_PollForTransfer(&DMA4Clear,HAL_DMA_FULL_TRANSFER,1);
 			HAL_DMA_Start(&DMA4Clear,(uint32_t)(&gMEMDMA2),(uint32_t)(&ADCData4SaveBuf->all),9750);			
		}
		else if(TimeIndex==998)//ͬ��ʱ϶��������ʱ��13�����ڵ���ͬ��ʱ϶ʱ��ƫ��
		{
			if (bA7128Reseted == 0)
				return;
			__HAL_TIM_SET_COUNTER(&htim13,0);
			__HAL_TIM_CLEAR_IT(&htim13,TIM_IT_UPDATE);
			HAL_TIM_Base_Start_IT(&htim13);	
			/************************************************************************/
			/* ����Ƿ�ģ�������ʧ									                */
			/************************************************************************/
			if (A7128_ReadReg(PLL1_REG) != 60)
			{
				bA7128Reseted = 0;
				HAL_TIM_Base_Stop_IT(&htim13);
			}
		}
		else//�쳣����
		{
			if (bA7128Reseted == 0)
				return;
			if(NetWorkMode==Net_Stop)//Ҫ��ֹͣ���磬����ֹͣ����ָ��
			{
				if(bNewADCData==0)//����ֹͣ�ɹ�
				{					
					HAL_TIM_Base_Stop_IT(&htim14);						
				}
				else
				{
					HAL_NVIC_DisableIRQ(EXTI0_IRQn);
					A7128_StrobeCmd(CMD_PLL);//Ϊ��ù̶���ʱ��Լ428us
					A7128Work=A7128Work_OnlyTx;
					A7128_TxFIFO[pTargetIDIndex]=BroadcastAddr;
					A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
					A7128_TxFIFO[pCommandIndex]=StopNetCommand;
					A7128_TxFIFO[pLenIndex]=0;	
					A7128_WriteFIFO_DMA();
				}
			}
			else//�������쳣�������ٽ����������
			{
				if(TimeIndex>=768)//768~997Ϊ�쳣����ʱ϶
				{			
					if(GetBit(TimeIndex,0)==0)//ż��ʱ϶�����ʴ�����
					{
						/************************************************************************/
						/*  ��ʼ�쳣����ʱ϶,2��ʱ϶һ�飬�ʴ�ʽ                              */
						/************************************************************************/
						if(AbnormalFrameErr>5)
						{
							AbnormalFrameIndex++;
							AbnormalFrameErr=0;
						}
						if(AbnormalFrameIndex>=AbnormalFrameCount)
						{
							AbnormalFrameIndex=0;
						}
						for(i=AbnormalFrameIndex;i<AbnormalFrameCount;i++)
						{
							if(AbnormalFrameList[i].addr!=0)
							{
								AbnormalFrameErr++;
								NetAbnormalTxProc(AbnormalFrameList[i].addr,AbnormalFrameList[i].fIndex);
								return;
							}
						}
						for(i=0;i<AbnormalFrameIndex;i++)
						{
							if(AbnormalFrameList[i].addr!=0)
							{
								AbnormalFrameErr++;
								NetAbnormalTxProc(AbnormalFrameList[i].addr,AbnormalFrameList[i].fIndex);
								return;
							}
						}						
					}		
				}
				else if(TimeIndex>760)
				{
					A7128Work=A7128Work_OnlyTx;
					A7128_TxFIFO[pTargetIDIndex]=BroadcastAddr;
					A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
					A7128_TxFIFO[pCommandIndex]=AbnormalAddrListCommand;
					A7128_TxFIFO[pLenIndex]=AbnormalAddrCount;	
					if(AbnormalAddrCount!=0)
						A7128_WriteFIFO_DMA_ADC(AbnormalAddr);
					else
						A7128_WriteFIFO_DMA();
				}
				else if(TimeIndex==760)//�����쳣��������
				{
					HAL_NVIC_DisableIRQ(EXTI0_IRQn);
					A7128_StrobeCmd(CMD_PLL);//Ϊ��ù̶���ʱ��Լ428us
					MakeAbnormalFrameList();		
				}
			}
		}		
	}	
}
//��ʱ��13�����ڵ���ͬ��ʱ϶ʱ��ƫ��
//��ʱ��14��1ms��ʱ��
//��ʱ��7��200usΪʱ��������������ʱ
//��ʱ��6,1usʱ�������ڵ����ʴ�ĳ�ʱ�ж�
/* USER CODE END 0 */

TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;

/* TIM7 init function */
void MX_TIM7_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 48000-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 50000-1;
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
/* TIM13 init function */
void MX_TIM13_Init(void)
{

  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 3;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 17790;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM14 init function */
void MX_TIM14_Init(void)
{

  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 3;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 60060;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM7)
  {
  /* USER CODE BEGIN TIM7_MspInit 0 */

  /* USER CODE END TIM7_MspInit 0 */
    /* TIM7 clock enable */
    __HAL_RCC_TIM7_CLK_ENABLE();
  /* USER CODE BEGIN TIM7_MspInit 1 */

  /* USER CODE END TIM7_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM13)
  {
  /* USER CODE BEGIN TIM13_MspInit 0 */

  /* USER CODE END TIM13_MspInit 0 */
    /* TIM13 clock enable */
    __HAL_RCC_TIM13_CLK_ENABLE();

    /* TIM13 interrupt Init */
    HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
  /* USER CODE BEGIN TIM13_MspInit 1 */

  /* USER CODE END TIM13_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM14)
  {
  /* USER CODE BEGIN TIM14_MspInit 0 */

  /* USER CODE END TIM14_MspInit 0 */
    /* TIM14 clock enable */
    __HAL_RCC_TIM14_CLK_ENABLE();

    /* TIM14 interrupt Init */
    HAL_NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
  /* USER CODE BEGIN TIM14_MspInit 1 */

  /* USER CODE END TIM14_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM7)
  {
  /* USER CODE BEGIN TIM7_MspDeInit 0 */

  /* USER CODE END TIM7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM7_CLK_DISABLE();
  /* USER CODE BEGIN TIM7_MspDeInit 1 */

  /* USER CODE END TIM7_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM13)
  {
  /* USER CODE BEGIN TIM13_MspDeInit 0 */

  /* USER CODE END TIM13_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM13_CLK_DISABLE();

    /* TIM13 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM8_UP_TIM13_IRQn);
  /* USER CODE BEGIN TIM13_MspDeInit 1 */

  /* USER CODE END TIM13_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM14)
  {
  /* USER CODE BEGIN TIM14_MspDeInit 0 */

  /* USER CODE END TIM14_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM14_CLK_DISABLE();

    /* TIM14 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM8_TRG_COM_TIM14_IRQn);
  /* USER CODE BEGIN TIM14_MspDeInit 1 */

  /* USER CODE END TIM14_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
/*
for(addr=0;addr<90;addr++)
{
if(SensorSignIn.L[addr]!=0 && ADCDataTag.L[addr]==0)
{
NetAbnormalTxProc(addr+11,0);
return;
}
}
for(addr=0;addr<6;addr++)
{
for(fIndex=0;fIndex<8;fIndex++)
{
if(SensorSignIn.M[addr]!=0 && ADCDataTag.M[addr][fIndex]==0)
{
NetAbnormalTxProc(addr+5,fIndex);
return;
}					
}
}
for(addr=0;addr<4;addr++)
{
for(fIndex=0;fIndex<128;fIndex++)
{
if(SensorSignIn.H[addr]!=0 && ADCDataTag.H[addr][fIndex]==0)
{
NetAbnormalTxProc(addr+1,fIndex);
return;
}
}
}
*/