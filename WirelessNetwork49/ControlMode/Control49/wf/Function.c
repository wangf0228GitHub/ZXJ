#include "Function.h"
#include "Variables.h"
#include "..\..\..\A7128\A7128reg.h"
#include "..\..\..\A7128\A7128.h"
#include "..\Inc\tim.h"
#include "..\Inc\usart.h"
#include "..\..\..\..\..\WF_Device\CP1616_Client.h"

void A7128_SetTx(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_TX);
}
void A7128_SetRx(void)
{
	A7128_StrobeCmd(CMD_RFR);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_RX);
}
void NetAbnormalTxProc(uint32_t addr,uint32_t fIndex)
{
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_STBY);//为获得固定延时，约428us
	A7128Work=A7128Work_AbnormalTx;
	A7128_TxFIFO[pTargetIDIndex]=addr;
	A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
	A7128_TxFIFO[pCommandIndex]=DataResendCommand;
	A7128_TxFIFO[pLenIndex]=1;	
	/************************************************************************/
	/* 获取需要重新请求的数据帧号                                           */
	/************************************************************************/
	A7128_TxFIFO[pDataIndex]=fIndex;	
	A7128_WriteFIFO_DMA();
}
uint32_t Networking_SetID(void)
{
	uint32_t retry,x;
	Networking_WakeUp(2);
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_STBY);//为获得固定延时，约428us
	htim7.Instance->ARR = 125-1;//25ms;
	for(retry=0;retry<5;retry++)//重试4次，每次25ms超时
	{
		A7128_StrobeCmd(CMD_STBY);
		A7128_TxFIFO[pTargetIDIndex]=CP1616_Client_RxList[pCP1616_Client_DataIndex];
		A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
		A7128_TxFIFO[pCommandIndex]=SetIDCommand;
		A7128_TxFIFO[pLenIndex]=1;	
		A7128_TxFIFO[pDataIndex]=CP1616_Client_RxList[pCP1616_Client_DataIndex+1];	
		A7128_WriteFIFO();
		A7128_StrobeCmd(CMD_TX); 
		while(A7128_GIO1_Read()==1);//发送完成
		A7128_StrobeCmd(CMD_RFR);
		A7128_StrobeCmd(CMD_RX);
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);		
		while(1)
		{	
			if(A7128_GIO1_Read()==0)//收到数据，判断数据的正确性
			{
				x=A7128_ReadReg(MODE_REG);
				if((x&0x20)==0)//判断是否CRC校验出错
				{
					A7128_RxPacket();
					if(A7128_RxFIFO[pCommandIndex]==SetIDCommand)					
					{
						if(A7128_RxFIFO[pDataIndex+2]==CP1616_Client_RxList[pCP1616_Client_DataIndex+1])
						{
							return 1;
						}
					}					 	
				}
				break;
			}				
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//超时重试
			{
				break;
			}
		}
	}
	return 0;
}
uint32_t Networking_SetCalibration(void)
{
	uint32_t retry,x,i;
	Networking_WakeUp(2);
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_STBY);//为获得固定延时，约428us
	htim7.Instance->ARR = 125-1;//25ms;
	for(retry=0;retry<5;retry++)//重试4次，每次25ms超时
	{
		A7128_StrobeCmd(CMD_STBY);
		A7128_TxFIFO[pTargetIDIndex]=CP1616_Client_RxList[pCP1616_Client_DataIndex];
		A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
		A7128_TxFIFO[pCommandIndex]=SetCalibrationCommand;
		A7128_TxFIFO[pLenIndex]=12;	
		for(i=0;i<12;i++)
			A7128_TxFIFO[pDataIndex+i]=CP1616_Client_RxList[pCP1616_Client_DataIndex+1+i];	
		A7128_WriteFIFO();
		A7128_StrobeCmd(CMD_TX); 
		while(A7128_GIO1_Read()==1);//发送完成
		A7128_StrobeCmd(CMD_RFR);
		A7128_StrobeCmd(CMD_RX);
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);		
		while(1)
		{	
			if(A7128_GIO1_Read()==0)//收到数据，判断数据的正确性
			{
				x=A7128_ReadReg(MODE_REG);
				if((x&0x20)==0)//判断是否CRC校验出错
				{
					A7128_RxPacket();
					if(A7128_RxFIFO[pCommandIndex]==SetCalibrationCommand)					
					{
						if(A7128_RxFIFO[pSourceIDIndex]==CP1616_Client_RxList[pCP1616_Client_DataIndex])
						{
							return 1;
						}
					}					 	
				}
				break;
			}				
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//超时重试
			{
				break;
			}
		}
	}
	return 0;
}
uint32_t Networking_GetCalibration(void)
{
	uint32_t retry,x,i;
	Networking_WakeUp(2);
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_STBY);//为获得固定延时，约428us
	htim7.Instance->ARR = 125-1;//25ms;
	for(retry=0;retry<5;retry++)//重试4次，每次25ms超时
	{
		A7128_StrobeCmd(CMD_STBY);
		A7128_TxFIFO[pTargetIDIndex]=CP1616_Client_RxList[pCP1616_Client_DataIndex];
		A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
		A7128_TxFIFO[pCommandIndex]=GetCalibrationCommand;
		A7128_TxFIFO[pLenIndex]=0;				
		A7128_WriteFIFO();
		A7128_StrobeCmd(CMD_TX); 
		while(A7128_GIO1_Read()==1);//发送完成
		A7128_StrobeCmd(CMD_RFR);
		A7128_StrobeCmd(CMD_RX);
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);		
		while(1)
		{	
			if(A7128_GIO1_Read()==0)//收到数据，判断数据的正确性
			{
				x=A7128_ReadReg(MODE_REG);
				if((x&0x20)==0)//判断是否CRC校验出错
				{
					A7128_RxPacket();
					if(A7128_RxFIFO[pCommandIndex]==GetCalibrationCommand)					
					{
						if(A7128_RxFIFO[pSourceIDIndex]==CP1616_Client_RxList[pCP1616_Client_DataIndex])
						{
							return 1;
						}
					}					 	
				}
				break;
			}				
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//超时重试
			{
				break;
			}
		}
	}
	return 0;
}
void UartRxProc(void)
{	
	uint32_t i;
	if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]!=3)
	{
		CP1616_Client_TxList[pCP1616_Client_CommandIndex]=CP1616_Client_RxList[pCP1616_Client_CommandIndex];
		CP1616_Client_TxList[3]=0;
		CP1616_Client_TxList[4]=1;
		CP1616_Client_TxList[7]=0x0d;
	}
	if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==1)//启动网络
	{
		bCalibrationNet=0;
		if(NetWorkMode==Net_Stop)
		{			
			NetWorkMode=Net_Start;
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=1;			
		}
		else if(NetWorkMode==Net_Start)
		{
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=2;//网络已经启动，自动接入即可
		}
		else if(NetWorkMode ==Net_Start_Calibration)
		{
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=3;//标定网络已经启动，将自动转为测量网络，自动接入即可
		}
		HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);	
	}
	else if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==3)//收到数据确认
	{
// 		if(CP1616_Client_RxList[pCP1616_Client_DataIndex]==waitConfirmCommand)
// 			bRxConfirm=1;
	}
	else if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==4)//设定ID
	{
		if(NetWorkMode==Net_Stop)
		{
			if(Networking_SetID()==1)
			{
				CP1616_Client_TxList[4]=3;				
				CP1616_Client_TxList[pCP1616_Client_DataIndex]=1;//成功设定
				CP1616_Client_TxList[pCP1616_Client_DataIndex+1]=A7128_RxFIFO[pDataIndex];
				CP1616_Client_TxList[pCP1616_Client_DataIndex+2]=A7128_RxFIFO[pDataIndex+2];
				CP1616_Client_TxList[9]=0x0d;
				HAL_UART_Transmit(&huart1,CP1616_Client_TxList,10,1000);
			}
			else
			{
				CP1616_Client_TxList[pCP1616_Client_DataIndex]=2;//设定失败，没有节点响应
				HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);
			}
		}
		else
		{
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=3;//网络已启动,需停止网络后再设定ID
			HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);
		}		
	}	
	if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==5)//启动标定网络
	{
		bCalibrationNet=1;
		if(NetWorkMode==Net_Stop)
		{			
			NetWorkMode=Net_Start_Calibration;
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=1;			
		}
		else if(NetWorkMode==Net_Start_Calibration)
		{
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=2;//网络已经启动，直接接入即可
		}
		else if(NetWorkMode==Net_Start)
		{
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=3;//测量网络已经启动，将转为标定网络，自动接入
		}
		HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);
	}
	else if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==6)//设定标定系数
	{
		if(NetWorkMode==Net_Stop)
		{
			if(Networking_SetCalibration()==1)
			{	
				CP1616_Client_TxList[4]=1+1+12+12;				
				CP1616_Client_TxList[pCP1616_Client_DataIndex]=1;//成功设定
				CP1616_Client_TxList[pCP1616_Client_DataIndex+1]=A7128_RxFIFO[pSourceIDIndex];//节点ID
				for(i=0;i<24;i++)
					CP1616_Client_TxList[pCP1616_Client_DataIndex+2+i]=A7128_RxFIFO[pDataIndex+i];
				CP1616_Client_TxList[32]=0x0d;
				HAL_UART_Transmit(&huart1,CP1616_Client_TxList,7+CP1616_Client_TxList[4],1000);	
			}
			else
			{
				CP1616_Client_TxList[pCP1616_Client_DataIndex]=2;//设定失败，没有节点响应
				HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);	
			}
		}
		else
		{
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=3;//网络已启动,需停止网络后再设定ID
			HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);	
		}		
	}	
	else if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==7)//读取标定系数
	{
		if(NetWorkMode==Net_Stop)
		{
			if(Networking_GetCalibration()==1)
			{
				CP1616_Client_TxList[4]=1+1+12;				
				CP1616_Client_TxList[pCP1616_Client_DataIndex]=1;//成功设定
				CP1616_Client_TxList[pCP1616_Client_DataIndex+1]=A7128_RxFIFO[pSourceIDIndex];
				for(i=0;i<12;i++)
					CP1616_Client_TxList[pCP1616_Client_DataIndex+2+i]=A7128_RxFIFO[pDataIndex+i];
				CP1616_Client_TxList[20]=0x0d;
				HAL_UART_Transmit(&huart1,CP1616_Client_TxList,7+CP1616_Client_TxList[4],1000);
			}
			else
			{
				CP1616_Client_TxList[pCP1616_Client_DataIndex]=2;//设定失败，没有节点响应
				HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);	
			}
		}
		else
		{
			CP1616_Client_TxList[pCP1616_Client_DataIndex]=3;//网络已启动,需停止网络后再设定ID
			HAL_UART_Transmit(&huart1,CP1616_Client_TxList,8,1000);
		}		
	}	
	if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]!=3)
		CP1616_Client_EndProcCommand();
}

/************************************************************************/
/* 20s持续发送，唤醒无线节点                                            */
/************************************************************************/
void Networking_WakeUp(uint32_t x5)
{
	uint32_t i;;
	htim7.Instance->ARR = 20000-1;//4s//50000-1;//10s;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_PLL);//为获得固定延时，约428us
	A7128_TxFIFO[pTargetIDIndex]=BroadcastAddr;
	A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
	A7128_TxFIFO[pCommandIndex]=WakeUpCommand;
	A7128_TxFIFO[pLenIndex]=0;	
	A7128_WriteFIFO();
	for(i=0;i<x5;i++)
	{
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);		
		while(1)
		{
			A7128_StrobeCmd(CMD_TX); //entry tx
			while(1)
			{
				if(A7128_GIO1_Read()==0)
					break;			
			}
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))
				break;
		}		
	}
	HAL_TIM_Base_Stop(&htim7);
}
/************************************************************************/
/* 10s 无线节点点名		                                              */
/************************************************************************/
void Networking_SignIn(void)
{	
	uint32_t retry,addr,x,bOk;
	htim7.Instance->ARR = 125-1;//25ms;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_STBY);//为获得固定延时，约428us
	for(addr=0;addr<=26;addr++)
	{
		SensorSignIn.all[addr]=0;
		SensorBAT.all[addr]=0;
	}
	ADCDataLen=0;
	ADCDataLen_Calibration=0;
	for(addr=1;addr<=100;addr++)
	{
		for(retry=0;retry<4;retry++)//重试4次，每次25ms超时
		{
			bOk=0;
			A7128_StrobeCmd(CMD_STBY);
			A7128_TxFIFO[pTargetIDIndex]=addr;
			A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
			A7128_TxFIFO[pCommandIndex]=SignInCommand;
			A7128_TxFIFO[pLenIndex]=0;	
			A7128_WriteFIFO();
			A7128_StrobeCmd(CMD_TX); 
			while(A7128_GIO1_Read()==1);//发送完成
			A7128_StrobeCmd(CMD_RFR);
			A7128_StrobeCmd(CMD_RX);
			HAL_TIM_Base_Stop(&htim7);
			__HAL_TIM_SET_COUNTER(&htim7,0);
			__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
			HAL_TIM_Base_Start(&htim7);		
			while(1)
			{	
				if(A7128_GIO1_Read()==0)//收到数据，判断数据的正确性
				{
					x=A7128_ReadReg(MODE_REG);
					if((x&0x20)==0)//判断是否CRC校验出错
					{
					 	A7128_RxPacket();
					 	if(A7128_RxFIFO[pSourceIDIndex]==addr)
						{
							if(A7128_RxFIFO[pCommandIndex]==SignInCommand)
							{
								bOk=1;
								if(addr<5)
								{
									SensorSignIn.H[addr-1]=1;
									SensorBAT.H[addr-1]=A7128_RxFIFO[pDataIndex];
									ADCDataLen=ADCDataLen+7680+1;
								}
								else if(addr<11)
								{
									SensorSignIn.M[addr-5]=1;
									SensorBAT.M[addr-1]=A7128_RxFIFO[pDataIndex];
									ADCDataLen=ADCDataLen+480+1;
								}
								else
								{
									SensorSignIn.L[addr-11]=1;
									SensorBAT.L[addr-1]=A7128_RxFIFO[pDataIndex];
									ADCDataLen=ADCDataLen+60+1;
								}
								ADCDataLen_Calibration=ADCDataLen_Calibration+4;//数据3字节，电量1字节
							}
						}					 	
					}
					break;
				}				
				if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//超时重试
				{
					break;
				}
			}	
			if(bOk)
				break;
		}
	}
}
uint32_t Uart_SignInProc(void)
{
	uint32_t retry;
	HAL_TIM_Base_Stop(&htim7);
	htim7.Instance->ARR = 2000-1;//400ms;
	for(retry=0;retry<10;retry++)
	{
		//waitConfirmCommand=SignInCommand;
		CP1616_Client_TxList[pCP1616_Client_CommandIndex]=SignInCommand;
		CP1616_Client_TxList[3]=0;
		CP1616_Client_TxList[4]=208;//104个签到，104个电池
		CP1616_Client_TxList[5]=0x00;
		CP1616_Client_TxList[6]=0x0d;
		HAL_UART_Transmit(&huart1,CP1616_Client_TxList,5,100);
		HAL_UART_Transmit(&huart1,(uint8_t*)SensorSignIn.all,104,1000);
		HAL_UART_Transmit(&huart1,(uint8_t*)SensorBAT.all,104,1000);
		HAL_UART_Transmit(&huart1,&CP1616_Client_TxList[5],2,100);
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);
		while(1)
		{	
			if(CP1616_Client_Flags.Bits.bRx)
			{
				UartRxProc();
				if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==3)
				{
					if(CP1616_Client_RxList[pCP1616_Client_DataIndex]==SignInCommand)
					{
						return 1;				
					}
				}	
			}
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//超时重试
			{
				break;
			}
		}
	}		
	return 0;
}
void Uart_ClosedProc(void)
{
	uint32_t retry;
	CP1616_Client_TxList[pCP1616_Client_CommandIndex]=0x02;//网络已关闭
	CP1616_Client_TxList[3]=0;
	CP1616_Client_TxList[4]=0;//104个签到，104个电池
	CP1616_Client_TxList[5]=0x00;
	CP1616_Client_TxList[6]=0x0d;
	for(retry=0;retry<10;retry++)
	{		
		HAL_UART_Transmit(&huart1,CP1616_Client_TxList,7,100);
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);
		while(1)
		{	
			if(CP1616_Client_Flags.Bits.bRx)
			{				
				if(CP1616_Client_RxList[pCP1616_Client_CommandIndex]==3)
				{
					CP1616_Client_EndProcCommand();
					if(CP1616_Client_RxList[pCP1616_Client_DataIndex]==0x02)
					{
						return;				
					}
					
				}
				else
				{
					UartRxProc();
				}
			}
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//超时重试
			{
				break;
			}
		}
		//wfDelay_ms(100);
	}		
	return;
}
/************************************************************************/
/* 2s持续发送，启动网络                                                 */
/************************************************************************/
void Networking_StartNet(void)
{
	uint32_t i;
	htim7.Instance->ARR = 10000-1;//2s;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_PLL);//为获得固定延时，约428us
	A7128_TxFIFO[pTargetIDIndex]=BroadcastAddr;
	A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
	A7128_TxFIFO[pCommandIndex]=StartNetCommand;
	A7128_TxFIFO[pLenIndex]=1;				
	A7128_TxFIFO[pDataIndex]=bCalibrationNet;
	A7128_WriteFIFO();
	HAL_TIM_Base_Stop(&htim7);
	__HAL_TIM_SET_COUNTER(&htim7,0);
	__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start(&htim7);		
	while(1)
	{
		A7128_StrobeCmd(CMD_TX); //entry tx
		while(1)
		{
			if(A7128_GIO1_Read()==0)
				break;			
		}
		if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))
			break;	
	}	
	HAL_TIM_Base_Stop(&htim7);
}