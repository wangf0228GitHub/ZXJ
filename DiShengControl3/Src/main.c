/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "wfSys.h"
#include "SimSPI.h"
#include "w5500_Work.h"
#include "..\wf\TCM.h"
#include "..\wf\Variables.h"
#include "ModbusRTU_Master.h"
#include "SimI2C.h"
#include "MS8607.h"
#include "RIO.h"
#include "..\..\..\WF_Device\NMEA0183.h"
#include "..\..\..\WF_Device\GPS_GPRMC.h"
#include "wfDefine.h"
#include "..\..\..\WF_Device\stm32\wfEEPROM.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint32_t RunTick;
uint32_t RIOSeconds;
uint32_t bRIONewData;
uint32_t ReadSensorTick;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	uint32_t i,sum;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_USART6_UART_Init();
  MX_USART3_UART_Init();
  MX_USART5_UART_Init();
  MX_USART7_UART_Init();
  MX_USART4_UART_Init();
  MX_USART8_UART_Init();
  MX_IWDG_Init();
  MX_TIM17_Init();

  /* USER CODE BEGIN 2 */
  TIM17->CR1 |= TIM_CR1_URS;  
  wfDelay_init(48);
  Reset_W5500();

  //ResetSystemParam();

  InitSystemParam();
  SimSPI_Init();
  w5500LibInit(); 
  SenserPower_ON();
  JTPower_ON();
  SimI2C_Init();
  MS8607_Init();
  ModbusRTU_Master_TargetAddr=1;
  HAL_UART_Receive_IT(&TCMUart,&TCM_Rx,1);
  HAL_UART_Receive_IT(&ModbusRTU_MasterUart,&ModbusRTU_MasterRx,1);
  HAL_UART_Receive_IT(&RIOUart,&RIO_Rx,1);
  HAL_UART_Receive_IT(&GPRSUart,&GPRSRx,1); 
  __HAL_TIM_CLEAR_IT(&htim17, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim17);
  RIOSeconds=3600;
  bRIONewData=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //i=1/0;
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  HAL_IWDG_Refresh(&hiwdg);
	  if(w5500Retry>10)
	  {
		  w5500Retry=0;
		  MissServer=0;
		  //NVIC_SystemReset();
	  }
	  if(MissServer>10)
	  {
		  Reset_W5500();
		  w5500LibInit(); 
		  MissServer=0;
		  w5500Retry++;
	  }
	  if(GetDeltaTick(RunTick)>1000)
	  {
		  RunTick=HAL_GetTick();
		  HAL_GPIO_TogglePin(RUNLED_GPIO_Port,RUNLED_Pin);
	  }	  
	  if(GetDeltaTick(ReadSensorTick)>1000)
	  {
		  ReadSensorTick=HAL_GetTick();
		  TCMErr++;
		  ModbusErr++;
		  MS8607Err++;
		  //RIOErr++;
		  RIOSeconds++;
		  //GPRSErr++;
		  TCM_SendData();
		  ModbusRTU_Master_SendCommand03(0x0006,2);
		  ModbusRTU_Master_preRxProcInit();	
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
		  if(bRIORead==0)//配置光功率时，暂停读光源状态,读取一次光源内部存储的光功率值
		  {
			  if(RIO_ReadCommand(0x26)==1)
			  {
				  RIOCur=MAKE_SHORT(RIO_RxList[pRIOData],RIO_RxList[pRIOData+1]);
				  bRIORead=1;
				  RIOErr=0;
			  }			
			  else
				  RIOErr++;
		  }
		  else//正常按照时序读取光源状态
		  {
			  if(RIOSeconds>=3600)
			  {
				  RIOSeconds=0;
				  if(RIO_ReadCommand(0x0e)==1)
				  {
					  bRIONewData=1;
					  for(i=0;i<6;i++)
					  {
						  RIO_0E[i]=RIO_RxList[pRIOData+i];
					  }
					  RIOErr=0;
				  }
				  else
					  RIOErr++;
			  }
		  }
	  }
	  if(ModbusRTU_Master_Flags.bRx)
	  {
		  Temperature.u8H=ModbusRTU_Master_RxList[3];
		  Temperature.u8L=ModbusRTU_Master_RxList[4];
		  ModbusErr=0;
	  }
	  if(TCMErr>10)
	  {
		  MX_USART3_UART_Init();
		  HAL_UART_Receive_IT(&TCMUart,&TCM_Rx,1);
		  SenserPower_OFF();
		  wfDelay_ms(50);
		  SenserPower_ON();
		  for(i=0;i<12;i++)
		  {
			  TCMData[i]=0;
		  }
		  TCMErr=0;
	  }	 
	  if(ModbusErr>10)
	  {
		  MX_USART6_UART_Init();
		  HAL_UART_Receive_IT(&ModbusRTU_MasterUart,&ModbusRTU_MasterRx,1);
		  SenserPower_OFF();
		  wfDelay_ms(50);
		  SenserPower_ON();
		  Temperature.u16=0;
		  ModbusErr=0;
	  }
	  if(NMEA0183_Flags.bRx)
	  {
		  NMEA0183_Verify();
		  if(GPS_GPRMC_DataProc(NMEA0183_RxBuf)!=0)
			  GPRSErr=0;
		  NMEA0183_RxCount=0;
		  NMEA0183_Flags.bRx=0;
	  }
	  if(TCM_Flags.bRx)
	  {
		  for(i=0;i<4;i++)
		  {
			  TCMData[i]=TCM_RxList[5+i];
			  TCMData[4+i]=TCM_RxList[10+i];
			  TCMData[8+i]=TCM_RxList[15+i];
		  }
		  TCMErr=0;
	  }
 	  if(bW5500Net==0)
 		  w5500LibInit();
 	  else
 		  loopback_tcpc();
//  	  wfDelay_ms(50);
//  	  HAL_GPIO_TogglePin(RUNLED_GPIO_Port,RUNLED_Pin);
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
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
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 1, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
	  wfDelay_ms(100);
	  HAL_GPIO_TogglePin(RUNLED_GPIO_Port,RUNLED_Pin);
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
