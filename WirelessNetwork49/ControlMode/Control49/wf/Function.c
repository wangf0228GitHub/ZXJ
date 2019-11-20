#include "Function.h"
#include "Variables.h"
#include "..\..\..\A7128\A7128reg.h"
#include "..\..\..\A7128\A7128.h"
#include "..\Inc\tim.h"
#include "..\Inc\usart.h"
#include "..\..\..\..\..\WF_Device\CP1616_Master.h"

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
	A7128_StrobeCmd(CMD_STBY);//Ϊ��ù̶���ʱ��Լ428us
	A7128Work=A7128Work_AbnormalTx;
	A7128_TxFIFO[pTargetIDIndex]=addr;
	A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
	A7128_TxFIFO[pCommandIndex]=DataResendCommand;
	A7128_TxFIFO[pLenIndex]=1;	
	/************************************************************************/
	/* ��ȡ��Ҫ�������������֡��                                           */
	/************************************************************************/
	A7128_TxFIFO[pDataIndex]=fIndex;	
	A7128_WriteFIFO_DMA();
}
uint32_t Networking_SetID(void)
{
	uint32_t retry,x;
	Networking_WakeUp(2);
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_STBY);//Ϊ��ù̶���ʱ��Լ428us
	htim7.Instance->ARR = 125-1;//25ms;
	for(retry=0;retry<5;retry++)//����4�Σ�ÿ��25ms��ʱ
	{
		A7128_StrobeCmd(CMD_STBY);
		A7128_TxFIFO[pTargetIDIndex]=BroadcastAddr;
		A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
		A7128_TxFIFO[pCommandIndex]=SetIDCommand;
		A7128_TxFIFO[pLenIndex]=1;	
		A7128_TxFIFO[pDataIndex]=PCM_RxBuf[pCP1616_Master_DataIndex];	
		A7128_WriteFIFO();
		A7128_StrobeCmd(CMD_TX); 
		while(A7128_GIO1_Read()==1);//�������
		A7128_StrobeCmd(CMD_RFR);
		A7128_StrobeCmd(CMD_RX);
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);		
		while(1)
		{	
			if(A7128_GIO1_Read()==0)//�յ����ݣ��ж����ݵ���ȷ��
			{
				x=A7128_ReadReg(MODE_REG);
				if((x&0x20)==0)//�ж��Ƿ�CRCУ�����
				{
					A7128_RxPacket();
					if(A7128_RxFIFO[pCommandIndex]==SetIDCommand)					
					{
						if(A7128_RxFIFO[pDataIndex+2]==PCM_RxBuf[pCP1616_Master_DataIndex])
						{
							return 1;
						}
					}					 	
				}
				break;
			}				
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//��ʱ����
			{
				break;
			}
		}
	}
	return 0;
}
void UartRxProc(void)
{	
	PCM_TxBuf[pCP1616_Master_CommandIndex]=PCM_RxBuf[pCP1616_Master_CommandIndex];
	PCM_TxBuf[3]=0;
	PCM_TxBuf[4]=1;
	PCM_TxBuf[7]=0x0d;
	if(PCM_RxBuf[pCP1616_Master_CommandIndex]==1)//��������
	{
		if(NetWorkMode==Net_Stop)
		{			
			NetWorkMode=Net_Start;
			PCM_TxBuf[pCP1616_Master_DataIndex]=1;			
		}
		else
		{
			PCM_TxBuf[pCP1616_Master_DataIndex]=2;//�����Ѿ�������ֱ�ӽ��뼴��
		}
		HAL_UART_Transmit(&huart1,PCM_TxBuf,8,1000);
		HAL_UART_Receive_DMA(&huart1,PCM_RxBuf,PCM_RxFrameLen);	
	}
	else if(PCM_RxBuf[pCP1616_Master_CommandIndex]==3)//�յ�����ȷ��
	{
// 		if(PCM_RxBuf[pCP1616_Master_DataIndex]==waitConfirmCommand)
// 			bRxConfirm=1;
	}
	else if(PCM_RxBuf[pCP1616_Master_CommandIndex]==4)//�趨ID
	{
		if(NetWorkMode==Net_Stop)
		{
			if(Networking_SetID()==1)
			{
				PCM_TxBuf[4]=3;				
				PCM_TxBuf[pCP1616_Master_DataIndex]=1;//�ɹ��趨
				PCM_TxBuf[pCP1616_Master_DataIndex+1]=A7128_RxFIFO[pDataIndex];
				PCM_TxBuf[pCP1616_Master_DataIndex+2]=A7128_RxFIFO[pDataIndex+2];
				PCM_TxBuf[9]=0x0d;
				HAL_UART_Transmit(&huart1,PCM_TxBuf,10,1000);
				HAL_UART_Receive_DMA(&huart1,PCM_RxBuf,PCM_RxFrameLen);	
			}
			else
			{
				PCM_TxBuf[pCP1616_Master_DataIndex]=2;//�趨ʧ�ܣ�û�нڵ���Ӧ
				HAL_UART_Transmit(&huart1,PCM_TxBuf,8,1000);
				HAL_UART_Receive_DMA(&huart1,PCM_RxBuf,PCM_RxFrameLen);	
			}
		}
		else
		{
			PCM_TxBuf[pCP1616_Master_DataIndex]=3;//����������,��ֹͣ��������趨ID
			HAL_UART_Transmit(&huart1,PCM_TxBuf,8,1000);
			HAL_UART_Receive_DMA(&huart1,PCM_RxBuf,PCM_RxFrameLen);	
		}		
	}		
	bRxFrame=0;
}

/************************************************************************/
/* 20s�������ͣ��������߽ڵ�                                            */
/************************************************************************/
void Networking_WakeUp(uint32_t x5)
{
	uint32_t i;;
	htim7.Instance->ARR = 25000-1;//4s//50000-1;//10s;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_PLL);//Ϊ��ù̶���ʱ��Լ428us
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
/* 10s ���߽ڵ����		                                              */
/************************************************************************/
void Networking_SignIn(void)
{	
	uint32_t retry,addr,x,bOk;
	htim7.Instance->ARR = 125-1;//25ms;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_STBY);//Ϊ��ù̶���ʱ��Լ428us
	for(addr=0;addr<=26;addr++)
	{
		SensorSignIn.all[addr]=0;
		SensorBAT.all[addr]=0;
	}
	ADCDataLen=0;
	for(addr=1;addr<=100;addr++)
	{
		for(retry=0;retry<4;retry++)//����4�Σ�ÿ��25ms��ʱ
		{
			bOk=0;
			A7128_StrobeCmd(CMD_STBY);
			A7128_TxFIFO[pTargetIDIndex]=addr;
			A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
			A7128_TxFIFO[pCommandIndex]=SignInCommand;
			A7128_TxFIFO[pLenIndex]=0;	
			A7128_WriteFIFO();
			A7128_StrobeCmd(CMD_TX); 
			while(A7128_GIO1_Read()==1);//�������
			A7128_StrobeCmd(CMD_RFR);
			A7128_StrobeCmd(CMD_RX);
			HAL_TIM_Base_Stop(&htim7);
			__HAL_TIM_SET_COUNTER(&htim7,0);
			__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
			HAL_TIM_Base_Start(&htim7);		
			while(1)
			{	
				if(A7128_GIO1_Read()==0)//�յ����ݣ��ж����ݵ���ȷ��
				{
					x=A7128_ReadReg(MODE_REG);
					if((x&0x20)==0)//�ж��Ƿ�CRCУ�����
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
							}
						}					 	
					}
					break;
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
}
uint32_t Uart_SignInProc(void)
{
	uint32_t retry;
	HAL_TIM_Base_Stop(&htim7);
	htim7.Instance->ARR = 2000-1;//400ms;
	for(retry=0;retry<10;retry++)
	{
		waitConfirmCommand=SignInCommand;
		PCM_TxBuf[pCP1616_Master_CommandIndex]=SignInCommand;
		PCM_TxBuf[3]=0;
		PCM_TxBuf[4]=208;//104��ǩ����104�����
		PCM_TxBuf[5]=0x00;
		PCM_TxBuf[6]=0x0d;
		HAL_UART_Transmit(&huart1,PCM_TxBuf,5,100);
		HAL_UART_Transmit(&huart1,(uint8_t*)SensorSignIn.all,104,1000);
		HAL_UART_Transmit(&huart1,(uint8_t*)SensorBAT.all,104,1000);
		HAL_UART_Transmit(&huart1,&PCM_TxBuf[5],2,100);
		HAL_UART_Receive_DMA(&huart1,PCM_RxBuf,PCM_RxFrameLen);
		HAL_TIM_Base_Stop(&htim7);
		__HAL_TIM_SET_COUNTER(&htim7,0);
		__HAL_TIM_CLEAR_FLAG(&htim7,TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start(&htim7);
		while(1)
		{	
			if(bRxFrame)
			{
				UartRxProc();
				if(PCM_RxBuf[pCP1616_Master_CommandIndex]==3)
				{
					if(PCM_RxBuf[pCP1616_Master_DataIndex]==SignInCommand)
					{
						return 1;				
					}
				}	
			}
			if(__HAL_TIM_GET_FLAG(&htim7,TIM_FLAG_UPDATE))//��ʱ����
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
	PCM_TxBuf[pCP1616_Master_CommandIndex]=0x02;//�����ѹر�
	PCM_TxBuf[3]=0;
	PCM_TxBuf[4]=0;//104��ǩ����104�����
	PCM_TxBuf[5]=0x00;
	PCM_TxBuf[6]=0x0d;
	for(retry=0;retry<10;retry++)
	{		
		HAL_UART_Transmit(&huart1,PCM_TxBuf,7,100);
		wfDelay_ms(100);
	}		
	return;
}
/************************************************************************/
/* 2s�������ͣ���������                                                 */
/************************************************************************/
void Networking_StartNet(void)
{
	uint32_t i;
	htim7.Instance->ARR = 10000-1;//2s;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	A7128_StrobeCmd(CMD_PLL);//Ϊ��ù̶���ʱ��Լ428us
	A7128_TxFIFO[pTargetIDIndex]=BroadcastAddr;
	A7128_TxFIFO[pSourceIDIndex]=MasterAddr;		
	A7128_TxFIFO[pCommandIndex]=StartNetCommand;
	A7128_TxFIFO[pLenIndex]=0;	
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