#include "HardwareProfile.h"
#include "dac.h"
#include "adc.h"
#include "tim.h"
uint16_t ADC1Value;
uint8_t UartTxCMDData[50];
void ReadADC1(void);
void UartRxProc(void)
{
	uint32_t i;
	uint8_t cmd= CP1616_Client_RxList[pCP1616_Client_CommandIndex];
	switch (cmd)
	{
	case 0x01://设备连接
		CP1616_Client_SendOK(cmd);
		HAL_TIM_Base_Stop(&htim7);
		break;
	case 0x02://设定DAC,0~4096
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 
			MAKE_SHORT(CP1616_Client_RxList[pCP1616_Client_DataIndex], CP1616_Client_RxList[pCP1616_Client_DataIndex+1]));
		CP1616_Client_SendOK(cmd);
		HAL_TIM_Base_Stop(&htim7);
		break;
	case 0x03://读取ADC1
		ReadADC1();
		UartTxCMDData[0] = HIGH_BYTE(ADC1Value);
		UartTxCMDData[1] = LOW_BYTE(ADC1Value);
		CP1616_Client_SendData(cmd,UartTxCMDData,2);
		HAL_TIM_Base_Stop(&htim7);
		break;
	case 0x04://自动采集
		break;
	case 0x05://调制输出
		HAL_UART_Transmit(&huart2, &CP1616_Client_RxList[pCP1616_Client_DataIndex], CP1616_Client_RxList[4], 1000000);
		CP1616_Client_SendOK(cmd);
		HAL_TIM_Base_Stop(&htim7);
		break;
	case 0x10://切换模式
		Mode = CP1616_Client_RxList[pCP1616_Client_DataIndex];
		if (Mode == 3)
		{
			AD2ListIndex = 0;
			AD2NeedCount= CP1616_Client_RxList[pCP1616_Client_DataIndex + 2];
			if (AD2NeedCount > 100)
				AD2NeedCount = 100;
			htim7.Instance->ARR = CP1616_Client_RxList[pCP1616_Client_DataIndex + 1];
			HAL_TIM_Base_Start_IT(&htim7);
		}
		else if (Mode == 2)
		{
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 4000);
			Uart2ListIndex = 0;
			HAL_TIM_Base_Stop(&htim7);
		}
		else
		{
			Mode = 1;
			HAL_TIM_Base_Stop(&htim7);
			HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
		}
		CP1616_Client_SendOK(cmd);
		break;
	default:
		break;
	}
	CP1616_Client_EndProcCommand();
}
void ReadADC1(void)
{
	uint32_t i,adSum=0;
	ADC_ChannelConfTypeDef sConfig = { 0 };
	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	for (i = 0; i < 4; i++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,100);
		adSum+= HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
	}
	ADC1Value = adSum >> 2;
}
void ReadADC2(void)
{
	uint32_t i, adSum = 0;
	ADC_ChannelConfTypeDef sConfig = { 0 };
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	for (i = 0; i < 4; i++)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 100);
		adSum += HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
	}
	adSum= adSum >> 2;
	AD2List[AD2ListIndex] = HIGH_BYTE(adSum);
	AD2List[AD2ListIndex+1] = LOW_BYTE(adSum);
	AD2ListIndex += 2;
}