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
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "wfSys.h"
#include "A7128.h"
#include "HardwareProfile.h"
#include "..\wf\Variables.h"
#include "..\wf\Function.h"
#include "..\Drivers\STM32H7xx_HAL_Driver\Inc\stm32h7xx_hal_uart.h"
#include "..\..\..\..\..\WF_Device\wfDefine.h"
#include "..\..\..\..\..\WF_Device\CP1616_Client.h"
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
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t i;
	uint32_t x,retry,addr,bOk;
	uint8_t x8;
	SPI_HandleTypeDef hspixxx;
	uint8_t* pbuf;
  /* USER CODE END 1 */
  

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_TIM14_Init();
  MX_USART1_UART_Init();
  MX_TIM13_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  wfDelay_init(480); 
  HAL_NVIC_DisableIRQ(EXTI0_IRQn);
  A7128_Init();
  A7128_StrobeCmd(CMD_STBY);
  A7128_SetCH(60); //freq 915.001MHz
  bA7128Reseted = 1;
//   bFirst=1;
//   bRLEDOn=0;
//   bRXing=0;
  YLED_OFF();
  RLED_OFF();
  CP1616_Client_TxList[0]=0x16;
  CP1616_Client_TxList[1]=0x16;
  while(HAL_UART_Receive_IT(&huart1,&huart1Rx,1)==HAL_OK);
  NetWorkMode=Net_Stop;
  ADCData4TXBuf=&ADCData4TX2;
  ADCData4SaveBuf=&ADCData4TX1;
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(NetWorkMode!=Net_Stop)
	  {
		  RLED_Toggle();
		  Networking_WakeUp(4);		
		  Networking_SignIn();		  
		  if(Uart_SignInProc()==0)
		  {
			  NetWorkMode=Net_Stop;			  
			  continue;
		  }
		  if(ADCDataLen==0)//������
		  {
			  NetWorkMode=Net_Stop;
			  continue;
		  }
		  Networking_StartNet();
		  ADCData4SaveBuf=0;
		  TimeIndex=997;
		  __HAL_TIM_CLEAR_IT(&htim14,TIM_IT_UPDATE);
		  HAL_TIM_Base_Start_IT(&htim14);		
		  while(1)
		  {
			  if (bA7128Reseted == 0)//���³�ʼ��a7128
			  {
				  A7128_Init();
				  A7128_StrobeCmd(CMD_STBY);
				  A7128_SetCH(60); //freq 915.001MHz
				  bA7128Reseted = 1;
			  }
			  if(bNewFrame)
			  {
				  bNewFrame=0;
				  htim7.Instance->ARR = 2000-1;//200ms;
				  for(retry=0;retry<2;retry++)
				  {
					  //waitConfirmCommand=ADCDataSendCommand;
					  bOk=0;
					  if(bCalibrationNet)//У׼��ֻ����1�����ݼ���
					  {
						  CP1616_Client_TxList[pCP1616_Client_CommandIndex]=ADCDataSendCommand_Calibration;
						  CP1616_Client_TxList[3]=HIGH_BYTE(ADCDataLen_Calibration);
						  CP1616_Client_TxList[4]=LOW_BYTE(ADCDataLen_Calibration);
						  CP1616_Client_TxList[5]=0x00;
						  CP1616_Client_TxList[6]=0x0d;
						  HAL_UART_Transmit(&huart1,CP1616_Client_TxList,5,100);
						  for(addr=0;addr<4;addr++)
						  {
							  if(SensorSignIn.H[addr]!=0)
							  {
								  HAL_UART_Transmit(&huart1,ADCData4TXBuf->H[addr][0],3,1000);
								  HAL_UART_Transmit(&huart1,&SensorBAT.H[addr],1,1000);
							  }
						  }
						  for(addr=0;addr<6;addr++)
						  {
							  if(SensorSignIn.M[addr]!=0)
							  {
								  HAL_UART_Transmit(&huart1,ADCData4TXBuf->M[addr][0],3,1000);
								  HAL_UART_Transmit(&huart1,&SensorBAT.M[addr],1,1000);
							  }
						  }
						  for(addr=0;addr<90;addr++)
						  {
							  if(SensorSignIn.L[addr]!=0)
							  {
								  HAL_UART_Transmit(&huart1,ADCData4TXBuf->L[addr],3,1000);
								  HAL_UART_Transmit(&huart1,&SensorBAT.L[addr],1,1000);
							  }
						  }
						  HAL_UART_Transmit(&huart1,&CP1616_Client_TxList[5],2,100);
					  }
					  else//ʵ������
					  {
						  CP1616_Client_TxList[pCP1616_Client_CommandIndex]=ADCDataSendCommand;
						  CP1616_Client_TxList[3]=HIGH_BYTE(ADCDataLen);
						  CP1616_Client_TxList[4]=LOW_BYTE(ADCDataLen);
						  CP1616_Client_TxList[5]=0x00;
						  CP1616_Client_TxList[6]=0x0d;
						  HAL_UART_Transmit(&huart1,CP1616_Client_TxList,5,100);
						  for(addr=0;addr<4;addr++)
						  {
							  if(SensorSignIn.H[addr]!=0)
							  {
								  HAL_UART_Transmit(&huart1,ADCData4TXBuf->H[addr][0],7680,1000);
								  HAL_UART_Transmit(&huart1,&SensorBAT.H[addr],1,1000);
							  }
						  }
						  for(addr=0;addr<6;addr++)
						  {
							  if(SensorSignIn.M[addr]!=0)
							  {
								  HAL_UART_Transmit(&huart1,ADCData4TXBuf->M[addr][0],480,1000);
								  HAL_UART_Transmit(&huart1,&SensorBAT.M[addr],1,1000);
							  }
						  }
						  for(addr=0;addr<90;addr++)
						  {
							  if(SensorSignIn.L[addr]!=0)
							  {
								  HAL_UART_Transmit(&huart1,ADCData4TXBuf->L[addr],60,1000);
								  HAL_UART_Transmit(&huart1,&SensorBAT.L[addr],1,1000);
							  }
						  }
						  HAL_UART_Transmit(&huart1,&CP1616_Client_TxList[5],2,100);
					  }
					  HAL_TIM_Base_Stop(&htim7);
					  __HAL_TIM_SET_COUNTER(&htim7,0);
					  __HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
					  HAL_TIM_Base_Start(&htim7);
					  while(1)
					  {	
						  if(huart1.RxState!=HAL_UART_STATE_BUSY_RX)
						  {
							  while(HAL_UART_Receive_IT(&huart1,&huart1Rx,1)==HAL_OK);
						  }
						  if(CP1616_Client_Flags.Bits.bRx)
						  {							  
							  if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==3)
							  {
								  if(CP1616_Client_RxList[pCP1616_Client_DataIndex]==CP1616_Client_TxList[pCP1616_Client_CommandIndex])
								  {
									  if(CP1616_Client_RxList[pCP1616_Client_DataIndex+1]==0)//�յ�����ȷ��
									  {
										  bOk=1;
									  }
									  else if(CP1616_Client_RxList[pCP1616_Client_DataIndex+1]==1)//�յ�����ȷ��,������ڵ�����
									  {
										  bOk=1;
										  CP1616_Client_EndProcCommand();
										  Uart_SignInProc();
									  }
									  else if(CP1616_Client_RxList[pCP1616_Client_DataIndex+1]==2)//�յ�����ȷ��,������ر�����
									  {
										  NetWorkMode=Net_Stop;
										  bOk=1;
									  }		
									  else if(CP1616_Client_RxList[pCP1616_Client_DataIndex+1]==3)//�����궨�����໥ת��
									  {
										  bCalibrationNet=!bCalibrationNet;
										  bOk=1;
									  }
								  }
								  CP1616_Client_EndProcCommand();
								  break;
							  }
							  else
							  {
								  UartRxProc();
							  }
						  }			
						  if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//��ʱ����
						  {
							  break;
						  }							  
					  }
					  if(bOk)
						  break;
				  }					  
			  }
			  if(NetWorkMode==Net_Stop)
			  {
				  while(1)//�ȴ�����ر�
				  {
					  if(WF_CHECK_FLAG(htim14.Instance->CR1,TIM_CR1_CEN)==0)
						  break;
				  }
				  Uart_ClosedProc();
				  NVIC_SystemReset();
				  break;
			  }
		  }
	  }
	  else//����δ�������ȴ�����ָ��
	  {
		  if(huart1.RxState!=HAL_UART_STATE_BUSY_RX)
		  {
			  while(HAL_UART_Receive_IT(&huart1,&huart1Rx,1)==HAL_OK);
		  }
		  if(CP1616_Client_Flags.Bits.bRx)
		  {
			  if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==3)
			  {
				  CP1616_Client_EndProcCommand();
			  }
			  else
				UartRxProc();
		  }
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable 
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_SPI3
                              |RCC_PERIPHCLK_SPI1|RCC_PERIPHCLK_SPI2;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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
