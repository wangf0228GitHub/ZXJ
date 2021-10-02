#include "HardwareProfile.h"
#include "dac.h"
#include "adc.h"
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
		break;
	case 0x02://设定DAC,0~4096
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 
			MAKE_SHORT(CP1616_Client_RxList[pCP1616_Client_DataIndex], CP1616_Client_RxList[pCP1616_Client_DataIndex+1]));
		CP1616_Client_SendOK(cmd);
		break;
	case 0x03://读取ADC1
		ReadADC1();
		UartTxCMDData[0] = HIGH_BYTE(ADC1Value);
		UartTxCMDData[1] = LOW_BYTE(ADC1Value);
		CP1616_Client_SendData(cmd,UartTxCMDData,2);
		break;
	case 0x04://自动采集
		break;
	case 0x05://调制输出
		HAL_UART_Transmit(&huart1, &CP1616_Client_RxList[pCP1616_Client_DataIndex], CP1616_Client_RxList[4], 1000);
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