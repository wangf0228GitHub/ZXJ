#include "Function.h"
#include "Variables.h"
#include "..\..\..\A7128\A7128.h"
#include "..\..\..\A7128\A7128reg.h"
#include "..\Drivers\STM32L0xx_HAL_Driver\Inc\stm32l0xx_hal_pwr.h"
#include "..\Drivers\STM32L0xx_HAL_Driver\Inc\stm32l0xx_hal_tim.h"
#include "..\Drivers\STM32L0xx_HAL_Driver\Inc\stm32l0xx_hal_gpio.h"
#include "..\Inc\tim.h"
#include "..\Inc\adc.h"

// uint32_t CheckRxPacket(void)
// {
// 	uint8_t x;
// 	x=A7128_ReadReg(MODE_REG);
// 	if((x&0x20)==0)//判断是否CRC校验出错
// 	{
// 		A7128_RxPacket();
// 		if(A7128_RxFIFO[pSourceIDIndex]!=MasterAddr)//节点只接收控制器数据
// 			return 0;
// 		if(A7128_RxFIFO[pCommandIndex]>=0x10)//非广播地址
// 		{
// 			if(A7128_RxFIFO[pTargetIDIndex]!=SensorAddr)//判断地址是否相符
// 				return 0;
// 		}
// 		return 1;
// 	}
// 	return 0;
// }
void A7128_SetTx(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
	A7128_StrobeCmd(CMD_TX);
}
void A7128_SetRx(void)
{
	A7128_StrobeCmd(CMD_RFR);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
	A7128_StrobeCmd(CMD_RX);
}
void MCUSleep(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ENBAT_Disable();
// 	EN_ADD_3P3_Disable();
// 	EN_ADD_1P25_Disable();

	HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
 	HAL_TIM_Base_Stop_IT(&htim7);
 	A7128_StrobeCmd(CMD_STBY);
 	A7128_WOREnable();

	NetWorkType = Net_Sleep;
	GPIO_InitStruct.Pin = A7128_GIO1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(A7128_GIO1_GPIO_Port, &GPIO_InitStruct);
	
	 HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);


	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1); 
	
	HAL_PWR_EnterSTANDBYMode();
}
void InitTimeIndex(void)
{
	if(SensorAddr==0 || SensorAddr==101)
	{
		TxStartTimeIndex=-1;
		TxEndTimeIndex=-1;
		SensorType=-1;
	}
	else if(SensorAddr<=4)//高频4（1~4）,128+2
	{
		TxStartTimeIndex=(SensorAddr-1)*130;
		TxEndTimeIndex=SensorAddr*130-3;
		SensorType=0;
	}
	else if(SensorAddr<=10)//中频6（5~10）,8+2
	{
		TxStartTimeIndex=520+(SensorAddr-1-4)*10;
		TxEndTimeIndex=520+(SensorAddr-4)*10-3;
		SensorType=1;
	}
	else if(SensorAddr<=100)//低频90（11~100）,1+1
	{
		TxStartTimeIndex=580+(SensorAddr-1-10)*2;
		TxEndTimeIndex=TxStartTimeIndex;
		SensorType=2;
	}
	else//异常
	{
		TxStartTimeIndex=-1;
		TxEndTimeIndex=-1;
		SensorType=-1;
	}
}
void TxADCDataProc(uint32_t FrameIndex)
{
	uint32_t x1,x2,i,j;
	x1=ADCData4TxStart+FrameIndex*60;//判断起始位置是否超过数组尾
	if(x1>=ADCDataMax[SensorType])
	{
		x1=x1-ADCDataMax[SensorType];
		A7128_WriteFIFO_DMA_ADC((uint8_t*)(&ADCData4[x1]));
	}
	else
	{
		x2=x1+60;//再判断数据尾的位置
		if(x2<ADCDataMax[SensorType])//无需两头取
		{
			A7128_WriteFIFO_DMA_ADC((uint8_t*)(&ADCData4[x1]));
		}
		else
		{
			j=0;
			for(i=x1;i<ADCDataMax[SensorType];i++)//先取尾部
			{
				A7128_TxFIFO[pDataIndex+j]=ADCData4[i];
				j++;
			}
			for(i=0;j<60;j++,i++)//再取头部
			{
				A7128_TxFIFO[pDataIndex+j]=ADCData4[i];
			}
			A7128_WriteFIFO_DMA();
		}
	}
}
void ADCBAT(void)//117us
{
	ADC_ChannelConfTypeDef sConfig = {0};
	HAL_ADC_Stop(&hadc);
	HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);

	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_RANK_NONE;
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
	hadc.Instance->CFGR1 &= (uint32_t)(~(3 << 10));//单独电池通道，软件触发
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc,100);
	ADCBATData=HAL_ADC_GetValue(&hadc);
	ADCBATData=ADCBATData>>2;
	hadc.Instance->CFGR1 |= hadc.Init.ExternalTrigConv |	hadc.Init.ExternalTrigConvEdge;
}