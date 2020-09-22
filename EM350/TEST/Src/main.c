/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
const char ATEnd[] = { "\r\0" };
const char AT0[] = { "AT" };
const char AT1[] = { "ATE1" };
const char AT2[] = { "AT^CURC=0" };
const char AT3[] = { "AT^STSF" };
const char AT4[] = { "ATS0" };
const char AT5[] = { "AT+CGREG=2" };
const char AT6[] = { "AT+CMEE=2" };
const char AT7[] = { "AT+CPIN" };
const char AT8[] = { "AT+CSQ" };
const char AT9[] = { "AT+IOMODE=1,0" };
const char AT10[] = { "AT^SICS=0,conType,GPRS0" };
const char AT11[] = { "AT^SICS=0,apn,1234" };
const char AT12[] = { "AT^SISS=0,conId,0" };
const char AT13[] = { "AT^SISS=0,srvType,Socket" };
const char AT14[] = { "AT^SISS=0,address,\"sockudp://172.22.44.33:7003\"" };
const char AT15[] = { "AT^SISO=0" };
const char AT16[] = { "AT^SISW=0,6" };
const char AT17[] = { "<23545755>" };
const char AT18[] = { "AT^SISR=0,1500" };
const char AT19[] = { "AT^IPINIT=\"1234\"" };
const char AT20[] = { "AT^IPINIT" };
const char AT21[] = { "AT^IPOPEN=1,\"UDP\",\"172.22.44.33\",7003,5500" };
const char AT22[] = { "AT^IPSEND=1,\"123456\"" };
const char AT23[] = { "AT" };
const char AT24[] = { "AT" };
const char AT25[] = { "AT" };
const char AT26[] = { "AT" };
const char AT27[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
// const char AT8[] = { "AT" };
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t atIndex;
uint32_t atCount;
uint8_t* ATList[100];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t i;	
	atIndex=0;
	atCount=0;
	ATList[atCount++]=(uint8_t*)AT0;
	ATList[atCount++]=(uint8_t*)AT1;
	ATList[atCount++]=(uint8_t*)AT2;
	ATList[atCount++]=(uint8_t*)AT3;
	ATList[atCount++]=(uint8_t*)AT4;
	ATList[atCount++]=(uint8_t*)AT5;
	ATList[atCount++]=(uint8_t*)AT6;
	ATList[atCount++]=(uint8_t*)AT7;
	ATList[atCount++]=(uint8_t*)AT8;
	ATList[atCount++]=(uint8_t*)AT9;
	ATList[atCount++]=(uint8_t*)AT10;
	ATList[atCount++]=(uint8_t*)AT11;
	ATList[atCount++]=(uint8_t*)AT12;
	ATList[atCount++]=(uint8_t*)AT13;
	ATList[atCount++]=(uint8_t*)AT14;
	ATList[atCount++]=(uint8_t*)AT15;
	ATList[atCount++]=(uint8_t*)AT16;
	ATList[atCount++]=(uint8_t*)AT17;
	ATList[atCount++]=(uint8_t*)AT18;
	ATList[atCount++]=(uint8_t*)AT19;
	ATList[atCount++]=(uint8_t*)AT20;
	ATList[atCount++]=(uint8_t*)AT21;
	ATList[atCount++]=(uint8_t*)AT22;
	ATList[atCount++]=(uint8_t*)AT23;
	ATList[atCount++]=(uint8_t*)AT24;
	ATList[atCount++]=(uint8_t*)AT25;
	ATList[atCount++]=(uint8_t*)AT26;
	ATList[atCount++]=(uint8_t*)AT27;
// 	ATList[atCount++]=(uint8_t*)AT28;
// 	ATList[atCount++]=(uint8_t*)AT29;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
// 	ATList[atCount++]=(uint8_t*)AT0;
  /* USER CODE END 1 */
  

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  txByteLen=0;
  for(i=0;i<15;i++)
	  txByteList[i]=i;
  txByteLen=15;
  while(HAL_UART_Receive_IT(&huart1,&huart1Rx,1)==HAL_OK);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //下一条指令
	  if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
	  {
		  HAL_Delay(20);
		  if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		  {
			  atIndex++;
			  HAL_UART_Transmit(&huart1,ATList[atIndex],strlen(ATList[atIndex]),1000);
			  HAL_UART_Transmit(&huart1,(uint8_t*)ATEnd,strlen(ATEnd),1000);
			  HAL_Delay(500);
		  }
	  }
	  //重复当前指令
	  if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET)
	  {
		  HAL_Delay(20);
		  if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET)
		  {
			  HAL_UART_Transmit(&huart1,ATList[atIndex],strlen(ATList[atIndex]),1000);
			  HAL_UART_Transmit(&huart1,(uint8_t*)ATEnd,strlen(ATEnd),1000);
			  HAL_Delay(500);
		  }
	  }
// 	  HAL_Delay(1000);
//  	  HAL_UART_Transmit(&huart1,ATList[0],strlen(ATList[0]),1000);
// 	  HAL_UART_Transmit(&huart2,txByteList,txByteLen,1000);
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
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
