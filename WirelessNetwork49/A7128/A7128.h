#ifndef   __A7128_h__
#define   __A7128_h__

#include "HardwareProfile.h"
#include "A7128reg.h"

/************************************************************************/
/* 数据帧格式定义                                                       */
/************************************************************************/
#define pTargetIDIndex 1
#define pSourceIDIndex 2
#define pCommandIndex	 3
#define pLenIndex		 4
#define pFrameNumIndex 4
#define pBATIndex		 4
#define pDataIndex	 5
/************************************************************************/
/* 设备地址定义                                                         */
/************************************************************************/
#define MasterAddr	0xf3
#define BroadcastAddr	0xfe

/************************************************************************/
/* 帧命令定义                                                           */
/************************************************************************/
//广播指令
#define WakeUpCommand		0x01 //唤醒
#define StartNetCommand	0x02 //采集网络启动
#define StopNetCommand	0x03 //采集网络停止
#define FrameSyncCommand	0x04 //帧同步
#define AbnormalAddrListCommand	0x05 //异常地址名单
//问答指令
#define SignInCommand 0x10 //点名，签到，数据区为电池电量
#define DataResendCommand 0x11 //请求重传采集数据，数据区长度为1，内容为请求重传的帧号
#define ADCDataSendCommand 0x20 //无线节点数据上传，数据区长度字节意义转为数据帧号，数据区长度固定为60个字节
#define ADCDataSendCommand_BAT 0x21 //无线节点最后一帧数据上传，帧号可由地址规律计算出，帧号区（数据区长度字节）为电池电量，数据区长度固定为60个字节
#define ADCDataSendCommand_Calibration 0x22//用于标定的ADC数据
//特殊指令
#define SetIDCommand 0xf0 //设定节点ID
#define SetCalibrationCommand 0xf1 //设定标定参数
#define GetCalibrationCommand 0xf2 //获得标定参数

// #define A7128_SCK_Low() HAL_GPIO_WritePin(A7128_SCK_GPIO_Port,A7128_SCK_Pin,GPIO_PIN_RESET)
// #define A7128_SCK_High() HAL_GPIO_WritePin(A7128_SCK_GPIO_Port,A7128_SCK_Pin,GPIO_PIN_SET)
// 
// #define A7128_SDIO_Low() HAL_GPIO_WritePin(A7128_SDIO_GPIO_Port,A7128_SDIO_Pin,GPIO_PIN_RESET)
// #define A7128_SDIO_High() HAL_GPIO_WritePin(A7128_SDIO_GPIO_Port,A7128_SDIO_Pin,GPIO_PIN_SET)
// 
// #define A7128_SDIO_Read() HAL_GPIO_ReadPin(A7128_SDIO_GPIO_Port,A7128_SDIO_Pin)
//
// #define A7128_GIO2_Read() HAL_GPIO_ReadPin(A7128_GIO2_GPIO_Port,A7128_GIO2_Pin)
// 
// #define A7128_SDIO_OUT() GPIO_InitTypeDef GPIO_InitStruct_Out;  \
// 	GPIO_InitStruct_Out.Pin = A7128_SDIO_Pin;  \
// 	GPIO_InitStruct_Out.Mode = GPIO_MODE_OUTPUT_PP;  \
// 	GPIO_InitStruct_Out.Pull = GPIO_PULLUP;  \
// 	GPIO_InitStruct_Out.Speed = GPIO_SPEED_FREQ_LOW;  \
// 	HAL_GPIO_Init(A7128_SDIO_GPIO_Port, &GPIO_InitStruct_Out);	
// 
// #define A7128_SDIO_IN() GPIO_InitTypeDef GPIO_InitStruct_In;  \
// 	GPIO_InitStruct_In.Pin = A7128_SDIO_Pin;  \
// 	GPIO_InitStruct_In.Mode = GPIO_MODE_INPUT;  \
// 	GPIO_InitStruct_In.Pull = GPIO_PULLUP;  \
// 	HAL_GPIO_Init(A7128_SDIO_GPIO_Port, &GPIO_InitStruct_In);


extern volatile uint8_t A7128_TxFIFO[65];
extern volatile uint8_t A7128_RxFIFO[65];

void A7128_Init(void);
void A7128_StrobeCmd(uint8_t cmd);
void A7128_SetCH(uint8_t ch);
void A7128_WriteFIFO(void);
void A7128_WriteFIFO_DMA(void);
void A7128_WriteFIFO_DMA_ADC(uint8_t* pBuf);
void A7128_WriteID(void);
void A7128_ReadID(void);
void A7128_RxPacket(void);
void A7128_RxPacket_DMA(void);
void A7128_WriteReg(uint8_t  addr, uint8_t dataByte);
uint8_t A7128_ReadReg(uint8_t addr);
void A7128_WOREnable(void);
#endif
