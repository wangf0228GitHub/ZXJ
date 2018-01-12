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
  * COPYRIGHT(c) 2017 STMicroelectronics
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
#include "stm32f1xx_hal.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "SimSPI.h"
#include "socket.h"
#include "wfSys.h"
#include "w5500_Conf.h"
#include "socket.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t wfTemp8[20];
uint8_t pc_ip[4]={192,168,0,152};/*配置目标服务器的IP地址*/
uint16_t DESPORT=6000;
uint8_t buffer[1024];
volatile uint8_t gTemp;
uint8_t gDATABUF[DATA_BUF_SIZE];
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void Reset_W5500(void)
{
	HAL_GPIO_WritePin(WREST_GPIO_Port,WREST_Pin,GPIO_PIN_RESET);
	wfDelay_us(2);  
	HAL_GPIO_WritePin(WREST_GPIO_Port,WREST_Pin,GPIO_PIN_SET);
	wfDelay_ms(800);
}
/* USER CODE END 0 */
int32_t loopback_tcpc(uint8_t sn, uint8_t* buf, uint8_t* destip, uint16_t destport)
{
	int32_t ret; // return value for SOCK_ERRORs
	uint16_t size = 0, sentsize=0;

	// Destination (TCP Server) IP info (will be connected)
	// >> loopback_tcpc() function parameter
	// >> Ex)
	//	uint8_t destip[4] = 	{192, 168, 0, 214};
	//	uint16_t destport = 	5000;

	// Port number for TCP client (will be increased)
	uint16_t any_port = 	50000;

	// Socket Status Transitions
	// Check the W5500 Socket n status register (Sn_SR, The 'Sn_SR' controlled by Sn_CR command or Packet send/recv status)
	switch(getSn_SR(sn))
	{
	case SOCK_ESTABLISHED :
		if(getSn_IR(sn) & Sn_IR_CON)	// Socket n interrupt register mask; TCP CON interrupt = connection with peer is successful
		{
#ifdef _LOOPBACK_DEBUG_
			printf("%d:Connected to - %d.%d.%d.%d : %d\r\n",sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
			setSn_IR(sn, Sn_IR_CON);  // this interrupt should be write the bit cleared to '1'
		}

		//////////////////////////////////////////////////////////////////////////////////////////////
		// Data Transaction Parts; Handle the [data receive and send] process
		//////////////////////////////////////////////////////////////////////////////////////////////
		if((size = getSn_RX_RSR(sn)) > 0) // Sn_RX_RSR: Socket n Received Size Register, Receiving data length
		{
			if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE; // DATA_BUF_SIZE means user defined buffer size (array)
			ret = recv(sn, buf, size); // Data Receive process (H/W Rx socket buffer -> User's buffer)

			if(ret <= 0) return ret; // If the received data length <= 0, receive failed and process end
			sentsize = 0;

			// Data sentsize control
			while(size != sentsize)
			{
				ret = send(sn, buf+sentsize, size-sentsize); // Data send process (User's buffer -> Destination through H/W Tx socket buffer)
				if(ret < 0) // Send Error occurred (sent data length < 0)
				{
					close(sn); // socket close
					return ret;
				}
				sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////
		break;

	case SOCK_CLOSE_WAIT :
#ifdef _LOOPBACK_DEBUG_
		//printf("%d:CloseWait\r\n",sn);
#endif
		if((ret=disconnect(sn)) != SOCK_OK) return ret;
#ifdef _LOOPBACK_DEBUG_
		printf("%d:Socket Closed\r\n", sn);
#endif
		break;

	case SOCK_INIT :
#ifdef _LOOPBACK_DEBUG_
		printf("%d:Try to connect to the %d.%d.%d.%d : %d\r\n", sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
		if( (ret = connect(sn, destip, destport)) != SOCK_OK) return ret;	//	Try to TCP connect to the TCP server (destination)
		break;

	case SOCK_CLOSED:
		close(sn);
		if((ret=socket(sn, Sn_MR_TCP, any_port++, 0x00)) != sn) return ret; // TCP socket open with 'any_port' port number
#ifdef _LOOPBACK_DEBUG_
		//printf("%d:TCP client loopback start\r\n",sn);
		//printf("%d:Socket opened\r\n",sn);
#endif
		break;
	default:
		break;
	}
	return 1;
}
int main(void)
{

  /* USER CODE BEGIN 1 */
	int32_t ret = 0;
	uint8_t x;
	uint16_t len=0;
	uint16_t anyport=7000;/*定义一个任意端口并初始化*/
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
  wfDelay_init(8);
  SimSPI_Init();
  Reset_W5500();
  w5500LibInit(); 
//   w5500_Init();
//   w5500_Set_Mac_self();
//   w5500_Set_SubnetMask_self();
//   w5500_Set_GateWay_self();
//   w5500_Set_IP_self();
//   w5500_Socket_BufSizeInit(0xff,w5500_RegVal_BufSize2K,w5500_RegVal_BufSize2K);///*初始化8个socket*/
//   w5500_Set_RetransmissionTime(2000);//设置溢出时间值=200ms
//   w5500_Set_NumOfRetransmission(5);//设置最大重新发送次数
//   w5500_Get_Mac(wfTemp8);
//   w5500_Get_SubnetMask(wfTemp8);
//   w5500_Get_GateWay(wfTemp8);
//   w5500_Get_IP(wfTemp8);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  if( (ret = loopback_tcpc(0, gDATABUF,pc_ip,DESPORT)) < 0) 
	  {

		  //printf("SOCKET ERROR : %ld\r\n", ret);
	  }
// 	  switch(w5500_Get_SocketN_SocketStatus(0))/*获取socket0的状态*/
// 	  {
// 	  case w5500_RegVal_SOCK_INIT:/*socket初始化完成*/
// 		  w5500_SocketConnect(0, pc_ip ,DESPORT);/*在TCP模式下向服务器发送连接请求*/ 
// 		  break;
// 	  case w5500_RegVal_SOCK_ESTABLISHED:/*socket连接建立*/
// 		  if(w5500_Get_SocketN_InterruptStatus(0) & w5500_RegVal_Sn_IR_CON)
// 		  {
// 			  w5500_Set_SocketN_InterruptReg(0, w5500_RegVal_Sn_IR_CON);/*Sn_IR的第0位置1*/
// 		  }
// 
// 		  len=w5500_Get_SocketN_RxBufSize(0);/*len为已接收数据的大小*/
// 
// 		  if(len>0)
// 		  {
// 			  w5500_SocketRecv(0,buffer,len);/*W5500接收来自Sever的数据*/
// 			  w5500_SocketSend(0,buffer,len);
// // 			  Com1_TxCounter = len;  //接收长度
// // 			  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  //开启串口发送中断 发送以太网接收来的数据
// 		  }	
// 
// // 		  if(Com1_Counter>0)  //表示串口接收缓冲内有内容，需要经网口发送
// // 		  {
// // 			  send(0,Com1_Rxbuff,Com1_Counter);
// // 			  Com1_Counter = 0;  				    
// // 		  }
// 
// 		  break;
// 	  case w5500_RegVal_SOCK_CLOSE_WAIT:/*socket等待关闭状态*/
// 		  w5500_SocketClose(0);
// 		  break;
// 	  case w5500_RegVal_SOCK_CLOSED:/*socket关闭*/
// 		  w5500_MakeSocket(0,w5500_RegVal_Sn_MR_TCP,anyport++,w5500_RegVal_Sn_MR_ND);/*打开socket0的一个端口*/
// 		  break;
// 	  default:
// 		  gTemp=w5500_Get_SocketN_SocketStatus(0);
// 		  len=0;
// 		  break;
// 	  }

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
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
