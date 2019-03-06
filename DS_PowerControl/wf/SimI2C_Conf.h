#ifndef __SIMI2C_Conf_h__
#define __SIMI2C_Conf_h__

#include "gpio.h"
#include "wfSys.h"

#define SimI2C_Delay_Ex
#define SimI2C_Delay() wfDelay_ms(1);


#define SIMI2C_SCL_Low() HAL_GPIO_WritePin(SimI2C_CLK_GPIO_Port,SimI2C_CLK_Pin,GPIO_PIN_RESET)
#define SIMI2C_SCL_High() HAL_GPIO_WritePin(SimI2C_CLK_GPIO_Port,SimI2C_CLK_Pin,GPIO_PIN_SET)

#define SIMI2C_SDA_Low() HAL_GPIO_WritePin(SimI2C_DATA_GPIO_Port,SimI2C_DATA_Pin,GPIO_PIN_RESET)
#define SIMI2C_SDA_High() HAL_GPIO_WritePin(SimI2C_DATA_GPIO_Port,SimI2C_DATA_Pin,GPIO_PIN_SET)

#define SIMI2C_SDA_Read() HAL_GPIO_ReadPin(SimI2C_DATA_GPIO_Port,SimI2C_DATA_Pin)

#define SIMI2C_SDA_OUT() GPIO_InitTypeDef GPIO_InitStruct_Out;  \
	GPIO_InitStruct_Out.Pin = SimI2C_DATA_Pin;  \
	GPIO_InitStruct_Out.Mode = GPIO_MODE_OUTPUT_PP;  \
	GPIO_InitStruct_Out.Pull = GPIO_PULLUP;  \
	GPIO_InitStruct_Out.Speed = GPIO_SPEED_FREQ_LOW;  \
	HAL_GPIO_Init(SimI2C_DATA_GPIO_Port, &GPIO_InitStruct_Out);	

#define SIMI2C_SDA_IN() GPIO_InitTypeDef GPIO_InitStruct_In;  \
	GPIO_InitStruct_In.Pin = SimI2C_DATA_Pin;  \
	GPIO_InitStruct_In.Mode = GPIO_MODE_INPUT;  \
	GPIO_InitStruct_In.Pull = GPIO_PULLUP;  \
	HAL_GPIO_Init(SimI2C_DATA_GPIO_Port, &GPIO_InitStruct_In);


#define SimI2C_CLK_Holding() GPIO_InitTypeDef GPIO_InitStruct;  \
 	GPIO_InitStruct.Pin = SimI2C_CLK_Pin;  \
 	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  \
 	GPIO_InitStruct.Pull = GPIO_PULLUP;  \
 	HAL_GPIO_Init(SimI2C_CLK_GPIO_Port, &GPIO_InitStruct);  \
 	wfDelay_ms(1);  \
	while(HAL_GPIO_ReadPin(SimI2C_CLK_GPIO_Port,SimI2C_CLK_Pin)==0);  \
	GPIO_InitStruct.Pin = SimI2C_CLK_Pin;  \
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  \
	GPIO_InitStruct.Pull = GPIO_PULLUP;  \
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  \
	HAL_GPIO_Init(SimI2C_CLK_GPIO_Port, &GPIO_InitStruct);


#endif


