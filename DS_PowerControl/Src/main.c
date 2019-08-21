/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "..\..\..\WF_Device\stm32\wfSys.h"
#include "..\wf\w5500_Work.h"
#include "..\wf\Variables.h"
#include "..\..\..\WF_Device\SimSPI.h"
#include "..\..\..\WF_Device\SimI2C.h"
#include "..\..\..\WF_Device\MS8607.h"
#include "..\..\..\WF_Device\CP1616_Client.h"
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
uint32_t RunTick;
uint32_t ReadSensorTick;
uint32_t bLouShui;
uint8_t cp1717TxList1[7]={0x16,0x16,0x01,0x01,0x00,0x2e,0x0d};
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
  MX_IWDG_Init();
  MX_TIM17_Init();
  MX_TIM16_Init();
  MX_TIM14_Init();
  MX_TIM7_Init();
  MX_USART5_UART_Init();
  /* USER CODE BEGIN 2 */
  CP1717_Client_Addr=1;
  TIM17->CR1 |= TIM_CR1_URS; 
  wfDelay_init(48);
  Reset_W5500();
  InitSystemParam();
  SimSPI_Init();
  w5500LibInit(); 
  Power_ON();
  SimI2C_Init();
  MS8607_Init();
  HAL_UART_Receive_IT(&huart5,&Uart3Rx,1);

  __HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim7);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  bLouShui=0;
  bResetAdvantech=0;
  bNeedTx=0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_IWDG_Refresh(&hiwdg);
	  if(bLouShui==0)
	  {
		  if((HAL_GPIO_ReadPin(LouShui1_GPIO_Port,LouShui1_Pin)==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(LouShui2_GPIO_Port,LouShui2_Pin)==GPIO_PIN_RESET))
		  {
			  HAL_Delay(20);
			  if((HAL_GPIO_ReadPin(LouShui1_GPIO_Port,LouShui1_Pin)==GPIO_PIN_RESET) && (HAL_GPIO_ReadPin(LouShui2_GPIO_Port,LouShui2_Pin)==GPIO_PIN_RESET))
			  {
				  bLouShui=1;
				  Power_OFF();
			  }
		  }
	  }
	  
	  if(bLouShui==0 && bResetAdvantech==0)//没漏水且没重启
	  {
		  if(MissAdvantech>60)//300s
		  {
			  Power_OFF();
			  __HAL_TIM_SET_COUNTER(&htim14,0);
			  __HAL_TIM_CLEAR_IT(&htim14, TIM_IT_UPDATE);
			  HAL_TIM_Base_Start_IT(&htim14);
			  bResetAdvantech=1;
		  }
	  }
// 	  if(w5500Retry>10)
// 	  {
// 		  NVIC_SystemReset();
// 	  }
// 	  if(MissServer>10)
// 	  {
// 		  Reset_W5500();
// 		  w5500LibInit(); 
// 		  MissServer=0;
// 		  w5500Retry++;
// 	  }
	  if(GetDeltaTick(RunTick)>1000)
	  {
		  RunTick=HAL_GetTick();
		  HAL_GPIO_TogglePin(RUNLED_GPIO_Port,RUNLED_Pin);
	  }	 
	  if(GetDeltaTick(ReadSensorTick)>2000)
	  {
		  ReadSensorTick=HAL_GetTick();
		  if(bNeedTx==0 || MS8607_Flags.bInit==0)
		  {
			  bNeedTx=1;
			  MS8607Err++;		  
			  if(MS8607_Flags.bInit!=0)
			  {
				  if(MS8607_ReadPT(ms8607_pressure_resolution_osr_8192))
					  MS8607Err=0;
				  if(MS8607_ReadRH()!=0)
					  MS8607Err=0;
			  }
			  else
			  {
				  if(MS8607_Init()!=0)
					  MS8607Err=0;			 
			  }	
		  }	  
	  }
	  if(bW5500Net==0)
		  w5500LibInit();
	  else
		  loopback_tcpc();
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
