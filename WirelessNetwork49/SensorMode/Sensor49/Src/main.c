/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "..\..\..\A7128\A7128.h"
#include "..\..\..\..\..\WF_Device\stm32\wfSys.h"
#include "..\wf\Variables.h"
#include "..\wf\Function.h"
#include "..\Drivers\STM32L0xx_HAL_Driver\Inc\stm32l0xx_hal_adc_ex.h"
#include "..\..\..\..\..\WF_Device\wfDefine.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t PN9_Tab[]=
{   0xFF,0x83,0xDF,0x17,0x32,0x09,0x4E,0xD1,
0xE7,0xCD,0x8A,0x91,0xC6,0xD5,0xC4,0xC4,
0x40,0x21,0x18,0x4E,0x55,0x86,0xF4,0xDC,
0x8A,0x15,0xA7,0xEC,0x92,0xDF,0x93,0x53,
0x30,0x18,0xCA,0x34,0xBF,0xA2,0xC7,0x59,
0x67,0x8F,0xBA,0x0D,0x6D,0xD8,0x2D,0x7D,
0x54,0x0A,0x57,0x97,0x70,0x39,0xD2,0x7A,
0xEA,0x24,0x33,0x85,0xED,0x9A,0x1D,0xE0
};
uint8_t oldA7128_RxFIFO[64];
uint32_t bFirst;
uint32_t bRLEDOn;
uint32_t bRXing;
uint32_t RLEOnTick;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t i;
	uint32_t x;
	uint8_t ux;
	float fx;
	uint16_t u16x;
	ADC_ChannelConfTypeDef sConfig = {0};
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  MX_GPIO_Init();
  //EEData.u16[0]=0x6677;
  //EEData.u8[2]=5;
  //wfEEPROM_WriteWord(0,EEData.u32);
  //EEData.u32=0;
//   SensorIDData.u16[0]=0x6677;
//   SensorIDData.u8[2]=10;
//   wfEEPROM_WriteWord(0,SensorIDData.u32);
//   SensorIDData.u32=0;
  SensorIDData.u32=wfEEPROM_ReadWord(0);
  if(SensorIDData.u16[0]==0x6677)//地址验证正确
  {
	  SensorAddr=SensorIDData.u8[2];
	  Linear_k.u32=wfEEPROM_ReadWord(4);
	  Linear_b.u32=wfEEPROM_ReadWord(8);
	  SensorGain.u32=wfEEPROM_ReadWord(12);
  }
  else
  {
	  SensorAddr=101;
	  Linear_k.f=1;
	  Linear_b.f=0;
	  SensorGain.f=1;
	  SensorIDData.u16[0]=0x6677;
	  SensorIDData.u8[2]=101;
	  wfEEPROM_WriteWord(0,SensorIDData.u32);
	  wfEEPROM_WriteWord(4,Linear_k.u32);
	  wfEEPROM_WriteWord(8,Linear_b.u32);
	  wfEEPROM_WriteWord(12,SensorGain.u32);
	  
  }
  InitTimeIndex();
  
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_DMA_Init();
  MX_ADC_Init();
  MX_SPI1_Init();
  MX_TIM7_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  wfDelay_init(32);
  HAL_NVIC_DisableIRQ(EXTI0_1_IRQn);
   A7128_Init();
   A7128_StrobeCmd(CMD_STBY);
   A7128_SetCH(60); //freq 915.001MHz
  NetWorkType=Net_RxData;
  bFirst=1;
  ADCSaveIndex=0;
  YLED_OFF();
  RLED_OFF();  
  ENBAT_Disable();
//   EN_ADD_3P3_Disable();
//   EN_ADD_1P25_Disable();
  htim2.Instance->PSC = tim2Prescaler[SensorType];//0;
  htim2.Instance->ARR = tim2Period[SensorType];//6249;
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  YLED_ON();   
//   bNewFrame=0;
//   TimeIndex=999;
//   HAL_TIM_Base_Stop_IT(&htim7);
//   __HAL_TIM_SET_COUNTER(&htim7,0);
//   __HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
//   HAL_TIM_Base_Start_IT(&htim7);
//   A7128_SetRx();
// 
//     HAL_ADC_Stop(&hadc);
//     HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);//校准ADC，24us
//     sConfig.Channel = ADC_CHANNEL_1;
//     sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
//     if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//     {
//   	  Error_Handler();
//     }
//     sConfig.Channel = ADC_CHANNEL_8;
//     sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
//     if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//     {
//   	  Error_Handler();
//     }
//     ENBAT_Enable();
//     EN_ADD_3P3_Enable();
//     EN_ADD_1P25_Enable();
//     ADCSaveIndex=0;
//     ADCData4TXBuf=ADCData4TX2;
//     ADCData4SaveBuf=ADCData4TX1;
//     HAL_TIM_Base_Start(&htim2);
//     HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADCData4DMA.u8, 4);
//     while(1)
//     {
// 		if(bNewFrame)
// 		{
// 			bNewFrame=0;
// 			PCM_TxBuf[0]=0x16;
// 			PCM_TxBuf[1]=0x16;
// 			PCM_TxBuf[2]=ADCDataSendCommand;
// 			PCM_TxBuf[3]=0x1e;
// 			PCM_TxBuf[4]=0x01;
// 			PCM_TxBuf[5]=0x00;
// 			PCM_TxBuf[6]=0x0d;
// 			HAL_UART_Transmit(&huart2,PCM_TxBuf,5,1000);
// 			HAL_UART_Transmit(&huart2,ADCData4TXBuf,7680,1000);
// 			ux=ADCBATData;
// 			HAL_UART_Transmit(&huart2,&ux,1,1000);
// 			HAL_UART_Transmit(&huart2,&PCM_TxBuf[5],2,1000);
// 		}
//     }
  //   while (1)
  //   {
  // 	  A7128_StrobeCmd(CMD_RX);
  // 	  while(A7128_GIO1_Read()==1);
  // 	  A7128_RxPacket();
  //   }
  //   for(i=0;i<6;i++)
  //   {
  // 	  __HAL_TIM_SET_COUNTER(&htim6,0);
  // 	  wfDelay_ms(500);
  //   }
//  ENBAT_Enable();
//  EN_ADD_3P3_Enable();
//  EN_ADD_1P25_Enable();
//   HAL_TIM_Base_Start_IT(&htim2);
//   HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADCData4DMA.u8, 4);
////   RLED_Toggle();
////   ADCBAT();
////  while(1)
////  {
////// 	  RLED_Toggle();
////// 	  ADCBAT(); 
////  }
//
// 
   //HAL_ADC_Stop(&hadc);
   //HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);//校准ADC，24us
   //sConfig.Channel = ADC_CHANNEL_1;
   //sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
   //if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
   //{
 	 // Error_Handler();
   //}
   //sConfig.Channel = ADC_CHANNEL_8;
   //sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
   //if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
   //{
 	 // Error_Handler();
   //}
   //ENBAT_Enable();
   //EN_ADD_3P3_Enable();
   //EN_ADD_1P25_Enable();
   //ADCSaveIndex=0;
   //ADCData4TXBuf=ADCData4TX2;
   //ADCData4SaveBuf=ADCData4TX1;
   //HAL_TIM_Base_Start(&htim2);
   //HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADCData4DMA.u8, 4);
   //while(1)
   //{
 
   //}
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
     __HAL_TIM_SET_COUNTER(&htim6,0);
     __HAL_TIM_CLEAR_IT(&htim6,TIM_IT_UPDATE);
     HAL_TIM_Base_Start_IT(&htim6); 

  A7128_SetRx();
  NetWorkType=Net_RxData;
//  A7128_StrobeCmd(CMD_RX); //entry rx
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 
  while (1)
  {

  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_8;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
