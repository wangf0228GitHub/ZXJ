
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
#include "stm32f1xx_hal.h"
#include "gpio.h"


/* USER CODE BEGIN Includes */
#include "wfSys.h"
#include "..\wf\lcd.h"
#include "..\wf\GUI.h"
#include "..\wf\Variables.h"
#include "ADS8689.h"
#include "..\wf\ADS8689_Conf.h"
#include "wfDefine.h"
#include <math.h>
#include "wfEEPROM.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint32_t bShowNum;
uint32_t adListIndex;
uint32_t adList[1000];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t i;
	uint8_t h,m,l,ll;
	uint32_t x,ad;
	float V,I,absX;
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
  /* USER CODE BEGIN 2 */
  wfDelay_init(72);	
  LCD_Init();
  ADS8689_CS_High();
  ADS8689_Setting(0x10,0x0100);//0.625*4.096
  ADS8689_Setting(0x14,0x0004);//0.625*4.096
  //LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
  Gui_Drawbmp16(0, 0,480,320,gImage_pic);
  bShowNum=0;
  oldI=0xffff;
  adListIndex=0;
  wfEEPROM_ReadWords(0,SystemParam.all,SystemParamLen);
  if(SystemParam.sum!=0)
  {
	  SystemParam.V0=0;
  }
//   Gui_Drawbmp16(192,179,134,34,gImage_TextBox);
//   Gui_Drawbmp16(198,184,16,24,NumPList[0]);
//   Gui_Drawbmp16(198+16,184,16,24,NumList[1]);
//   Gui_Drawbmp16(198+32,184,16,24,NumList[2]);
//   Gui_Drawbmp16(198+48,184,16,24,NumList[3]);
//   Gui_Drawbmp16(198+64,184,16,24,NumList[4]);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  ad=0;
	  for(i=0;i<2048;i++)//250ms
	  {
		  //HAL_Delay(10);
		  while(1)
		  {
			  if(ADS8689_RVS_Read()==1)//rvs拉高后继续
				  break;
		  }
		  ADS8689_CS_Low();
		  while(1)
		  {
			  if(ADS8689_RVS_Read()==0)//rvs拉低后继续
				  break;
		  }
		  //	HAL_GPIO_WritePin(AD_CS_GPIO_Port,GPIO_PIN_2,GPIO_PIN_SET);
		  h=ADS8689_SPIProc(0xff);
		  m=ADS8689_SPIProc(0xff);		  
		  l=ADS8689_SPIProc(0xff);
		  ll=ADS8689_SPIProc(0xff);
		  ADS8689_CS_High();
		  x=MAKE_SHORT(h,m);
		  x=x<<2;
		  l=l>>6;
		  x=x+l;
		  adList[adListIndex++]=x;
		  if(adListIndex>100)
			  adListIndex=0;
		  ad+=x;	

	  }	 
	  ad=ad>>11;
	  V=ad*5.12;
	  V=V/262144;
   	  V=V-2.56;
	  if(HAL_GPIO_ReadPin(KEY_Clear_GPIO_Port,KEY_Clear_Pin)==GPIO_PIN_RESET)
	  {
		  HAL_Delay(20);
		  if(HAL_GPIO_ReadPin(KEY_Clear_GPIO_Port,KEY_Clear_Pin)==GPIO_PIN_RESET)
		  {
			  SystemParam.V0=V;
			  SystemParam.sum=0;
			  wfEEPROM_WriteWords(wfEEPROM_BASE_ADDR,SystemParam.all,SystemParamLen);
		  }
	  }
	  V=V-SystemParam.V0;
	  if(HAL_GPIO_ReadPin(SwitchRange_GPIO_Port,SwitchRange_Pin)==GPIO_PIN_SET)//小量程
	  {
		  I=V/20000;		  
	  }
	  else//大量程
	  {
		   I=V/1000;		
	  }
	  I=I*1000000;
	  if(bShowNum==0)//没显示数码管
	  {
		  if(I<0)
			  absX=-I;
		  else
			  absX=I;
		  if(absX>2.4)//转换为数码管显示
		  {
			  if(I>0)
			  {
				  GUI_ShowGraphicsI(2.5);
			  }
			  else
			  {
				  GUI_ShowGraphicsI(-2.5);
			  }
			  bShowNum=1;
			  Gui_Drawbmp16(178,180,165,43,gImage_TextBox);
			  GUI_ShowNumI(I);
		  }
		  else
		  {
			  GUI_ShowGraphicsI(I);
		  }
	  }
	  else//当前为显示数码管状态
	  {
		  if(I<0)
			  absX=-I;
		  else
			  absX=I;
		  if(absX<2)//转换为仪表显示方式
		  {
			  bShowNum=0;
			  LCD_Fill(178,180,178+165,180+43,COLOR_BLACK);
			  GUI_ShowGraphicsI(I);
		  }
		  else
		  {
			  if(absX<2500)
			  {	
				  GUI_ShowNumI(I);
			  }
			  else
			  {
				  //LCD_Fill(184,185,184+115,185+33,COLOR_BLACK);
				  Gui_Drawbmp16(184,185,115,33,gImage_OverRange);
			  }
		  }
	  }
	  if(HAL_GPIO_ReadPin(SwitchRange_GPIO_Port,SwitchRange_Pin)==GPIO_PIN_SET)//小量程
	  {
		  if(V<0)
			  absX=-V;
		  else
			  absX=V;
		  if(absX>2.5)//切换到大量程
		  {
			  HAL_GPIO_WritePin(SwitchRange_GPIO_Port,SwitchRange_Pin,GPIO_PIN_RESET);
		  }
	  }
	  else//大量程
	  {
		  if(V<0)
			  absX=-V;
		  else
			  absX=V;
		  if(absX<0.12)//切换回小量程
		  {
			  HAL_GPIO_WritePin(SwitchRange_GPIO_Port,SwitchRange_Pin,GPIO_PIN_SET);
		  }
	  }
// 	  for(i=0;i<500;i++)
// 	  {
// 		  LCD_DrawLine_GoBack(oldLine[0],oldLine[1],oldLine[2],oldLine[3]);
// 		  GUI_ShowI(i*0.01-2.5);
// 		  wfDelay_ms(500);
// 	  }
// 	  for(i=0;i<51;i++)
// 	  {
// 		  //Gui_Drawbmp16(0, 0,480,160,gImage_pic);
// 		  //LCD_Fill(0,160,480,320,COLOR_BLACK);
// 		  //POINT_COLOR=COLOR_BLACK;
// 		  //LCD_DrawLine_GoBack(oldLine[0],oldLine[1],oldLine[2],oldLine[3]);
// 		  POINT_COLOR=COLOR_RED;
// 		  LCD_DrawLine(ScalePoint[i][0],ScalePoint[i][1],ScalePoint[i][2],ScalePoint[i][3]);
// 		  wfDelay_ms(500);
// 	  }
// 
// 
// 	  for(i=0;i<25;i++)
// 	  {
// 		  //Gui_Drawbmp16(0, 0,480,160,gImage_pic);
// 		  //LCD_Fill(0,160,480,320,COLOR_BLACK);
// 		  //POINT_COLOR=COLOR_BLACK;
// 		  LCD_DrawLine_GoBack(x1,y1,x2,y2);
// 		  POINT_COLOR=COLOR_RED;
// 		  LCD_DrawLine(NX1[i],NY1[i],NX2[i],NY2[i]);
// 		  x1=NX1[i];
// 		  y1=NY1[i];
// 		  x2=NX2[i];
// 		  y2=NY2[i];
// 		  wfDelay_ms(500);
// 	  }
// 	  LCD_DrawLine_GoBack(x1,y1,x2,y2);
// 	  POINT_COLOR=COLOR_RED;
// 	  LCD_DrawLine(240,311,240,55);
// 	  x1=240,y1=311,x2=240;y2=55;
// 	  wfDelay_ms(500);
// 	  for(i=0;i<25;i++)
// 	  {
// 		  //Gui_Drawbmp16(0, 0,480,160,gImage_pic);
// 		  //LCD_Fill(0,160,480,320,COLOR_BLACK);
// 		  //POINT_COLOR=COLOR_BLACK;
// 		  LCD_DrawLine_GoBack(x1,y1,x2,y2);
// 		  POINT_COLOR=COLOR_RED;
// 		  LCD_DrawLine(PX1[i],PY1[i],PX2[i],PY2[i]);
// 		  x1=PX1[i];
// 		  y1=PY1[i];
// 		  x2=PX2[i];
// 		  y2=PY2[i];
// 		  wfDelay_ms(500);
// 	  }
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
