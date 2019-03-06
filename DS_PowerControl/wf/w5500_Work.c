#include "w5500_Work.h"
//#include "wizchip_conf.h"
#include "socket.h"
#include "..\..\..\WF_Device\CP1616_Client.h"
#include "..\..\..\WF_Device\wfDefine.h"
#include "Variables.h"
#include "..\..\..\WF_Device\GPS_GPRMC.h"
#include "..\..\..\WF_Device\MS8607.h"
#include "..\..\..\WF_Device\Verify.h"
#include "tim.h"



wiz_NetInfo gWIZNETINFO = { 
	.mac = {0x00, 0x08, 0xdc,0x00, 0xab, 0x00},
	.ip = {192, 168, 1, 104},
	.sn = {255,255,255,0},
	.gw = {192, 168, 1, 1},
	.dns = {0,0,0,0},
	.dhcp = NETINFO_STATIC 
};
volatile uint32_t bW5500Net;
#define UseSocket 0
uint8_t pc_ip[4]={192,168,1,100};/*����Ŀ���������IP��ַ*/
uint16_t DESPORT=6000;
uint16_t myPort = 50000;

uint8_t NetBuf[1024];
unsigned char NetTxList[150];
unsigned char NetTxCount;
extern uint32_t bRIONewData;
void TCPSend(void);
void loopback_tcpc(void)
{
	int32_t ret;
	uint16_t size,i,j,sentsize;
	uint32_t x,y,sum;
	// Socket Status Transitions
	// Check the W5500 Socket n status register (Sn_SR, The 'Sn_SR' controlled by Sn_CR command or Packet send/recv status)
	switch(getSn_SR(UseSocket))
	{
	case SOCK_ESTABLISHED :
		if(getSn_IR(UseSocket) & Sn_IR_CON)	// Socket n interrupt register mask; TCP CON interrupt = connection with peer is successful
		{
			setSn_IR(UseSocket, Sn_IR_CON);  // this interrupt should be write the bit cleared to '1'
		}
		//////////////////////////////////////////////////////////////////////////////////////////////
		// Data Transaction Parts; Handle the [data receive and send] process
		//////////////////////////////////////////////////////////////////////////////////////////////
		if((size = getSn_RX_RSR(UseSocket)) > 0) // Sn_RX_RSR: Socket n Received Size Register, Receiving data length
		{
			if(size > DATA_BUF_SIZE) 
				size = DATA_BUF_SIZE; 			
			// DATA_BUF_SIZE means user defined buffer size (array)
 			ret = recv(UseSocket, NetBuf, size); // Data Receive process (H/W Rx socket buffer -> User's buffer)
			MissServer=0;
			htim17.Instance->EGR = TIM_EGR_UG;
			w5500Retry=0;
 			if(ret <= 0) // If the received data length <= 0, receive failed and process end
 			{
 				bW5500Net=0;
 				return;
 			}		
 			CP1616_Client_EndProcCommand();
 			for(j=0;j<size;j++)
 			{
				CP1616_Client_ProcRx(NetBuf[j]);
 				if(CP1616_Client_Flags.Bits.bRx)
 				{
 					switch(CP1616_Client_RxList[pCP1616_CommandIndex])
 					{
 						//16 16 01 00 00 2d 0d
 					case 0x01:
 								
 						break;
					case 0x02://��ȡ�������
						NetTxList[0] = 0x16;
						NetTxList[1] = 0x16;
						NetTxList[2] = CP1616_Client_RxList[pCP1616_CommandIndex];
						NetTxCount=36;
						NetTxList[3] = HIGH_BYTE(NetTxCount);
						NetTxList[4] = LOW_BYTE(NetTxCount);
						for(x=0;x<36;x++)
						{
							NetTxList[pCP1616_ClientData+x]=SystemParam.allByte[4+x];
						}						
						NetTxList[pCP1616_ClientData+NetTxCount] = GetVerify_Sum(NetTxList, pCP1616_ClientData+NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount + 1] = 0x0d;

						TCPSend();
						break;
					case 0x03://�趨�������
						for(x=0;x<28;x++)
						{
							SystemParam.allByte[x+12]=CP1616_Client_RxList[pCP1616_ClientData+x];
						}
						sum=0;
						for(x=1;x<SystemParamLen;x++)
						{
							sum+=SystemParam.all[x];
						}
						SystemParam.sum=sum;
						STMFLASH_Write(wfEEPROM_BASE_ADDR,SystemParam.all,SystemParamLen);
						NetTxList[0] = 0x16;
						NetTxList[1] = 0x16;
						NetTxList[2] = CP1616_Client_RxList[pCP1616_CommandIndex];
						NetTxCount=0;
						NetTxList[3] = HIGH_BYTE(NetTxCount);
						NetTxList[4] = LOW_BYTE(NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount] = GetVerify_Sum(NetTxList, pCP1616_ClientData+NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount + 1] = 0x0d;

						TCPSend();
						break;	
					case 0x05://io����
						if(CP1616_Client_RxList[pCP1616_ClientData]==0x00)
						{
							Power_OFF();
						}
						else
						{
							Power_ON();
						}
						NetTxList[0] = 0x16;
						NetTxList[1] = 0x16;
						NetTxList[2] = CP1616_Client_RxList[pCP1616_CommandIndex];
						NetTxCount=0;
						NetTxList[3] = HIGH_BYTE(NetTxCount);
						NetTxList[4] = LOW_BYTE(NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount] = GetVerify_Sum(NetTxList, pCP1616_ClientData+NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount + 1] = 0x0d;
						TCPSend();
						break;
					case 0x06://������
						NetTxList[0] = 0x16;
						NetTxList[1] = 0x16;
						NetTxList[2] = CP1616_Client_RxList[pCP1616_CommandIndex];
						NetTxCount=0;
						NetTxList[3] = HIGH_BYTE(NetTxCount);
						NetTxList[4] = LOW_BYTE(NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount] = GetVerify_Sum(NetTxList, pCP1616_ClientData+NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount + 1] = 0x0d;

						TCPSend();
						disconnect(UseSocket);
						close(UseSocket);
						NVIC_SystemReset();
						break;
					case 0xf0://ģ�����ͣ�������Ϊ��
						NetTxList[0] = 0x16;
						NetTxList[1] = 0x16;
						NetTxList[2] = CP1616_Client_RxList[pCP1616_CommandIndex];
						NetTxCount=1;
						NetTxList[3] = HIGH_BYTE(NetTxCount);
						NetTxList[4] = LOW_BYTE(NetTxCount);
						NetTxList[5]=WhoIam;
						NetTxList[pCP1616_ClientData+NetTxCount] = GetVerify_Sum(NetTxList, pCP1616_ClientData+NetTxCount);
						NetTxList[pCP1616_ClientData+NetTxCount + 1] = 0x0d;

						TCPSend();
						break;
 					}
 					CP1616_Client_EndProcCommand();
 				}
 
 			}
		}
		if(bNeedTx!=0)
		{
			bNeedTx=0;
			NetTxList[0] = 0x16;
			NetTxList[1] = 0x16;
			NetTxList[2] = 0x50;//���ֵ�Դ������״̬�ϱ�
			NetTxCount=16;
			NetTxList[3] = HIGH_BYTE(NetTxCount);
			NetTxList[4] = LOW_BYTE(NetTxCount);
			x=0;
			//12
			for (i = 0; i < 4; i++)//MS8607�¶�4��
			{
				NetTxList[pCP1616_ClientData+i] = MS8607_Temperature.u8s[i];
			}
			for (i = 0; i < 4; i++)//MS8607ѹ��4��
			{
				NetTxList[pCP1616_ClientData+4+i] = MS8607_Pressure.u8s[i];
			}
			for (i = 0; i < 4; i++)//MS8607ʪ��4��
			{
				NetTxList[pCP1616_ClientData+8+i] = MS8607_RH.u8s[i];
			}			
			//����ͳ��1��
			//13
			NetTxList[pCP1616_ClientData+12]=(uint8_t)MS8607Err;

			//io״̬2��
			//14
			NetTxList[pCP1616_ClientData+13]=HAL_GPIO_ReadPin(LouShui1_GPIO_Port,LouShui1_Pin);
			NetTxList[pCP1616_ClientData+14]=HAL_GPIO_ReadPin(LouShui2_GPIO_Port,LouShui2_Pin);
			
			//��Դ1��
			//16
			NetTxList[pCP1616_ClientData+15]=HAL_GPIO_ReadPin(PowerControl_GPIO_Port,PowerControl_Pin);

			NetTxList[pCP1616_ClientData+NetTxCount] = GetVerify_Sum(NetTxList, pCP1616_ClientData+NetTxCount);
			NetTxList[pCP1616_ClientData+NetTxCount + 1] = 0x0d;

			TCPSend();
		}
		//////////////////////////////////////////////////////////////////////////////////////////////
		break;
	case SOCK_CLOSE_WAIT :
 		if((ret=disconnect(UseSocket)) != SOCK_OK) 
 		{
 			bW5500Net=0;
 			//return ret;
 		}
		break;
	case SOCK_INIT :
 		if( (ret = connect(UseSocket, pc_ip, DESPORT)) != SOCK_OK) 
 		{
 			bW5500Net=0;
 		}//return ret;	//	Try to TCP connect to the TCP server (destination)
		break;

	case SOCK_CLOSED:
 		close(UseSocket);
 		if((ret=socket(UseSocket, Sn_MR_TCP, myPort, 0x00)) != UseSocket) 
 		{
 			bW5500Net=0;
 		}//return ret; // TCP socket open with 'any_port' port number
		break;
	default:
		break;
	}
	//return 1;
}

void TCPSend(void)
{
	uint16_t sentsize=0;
	int32_t ret;
	while(sentsize!=(pCP1616_ClientData+NetTxCount + 2))
	{
		ret=send(UseSocket, NetTxList, pCP1616_ClientData+NetTxCount + 2);
		if(ret<0)
		{
			close(UseSocket); // socket close
			bW5500Net=0;
			//return ret;
		}
		sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
	}
}
void Reset_W5500(void)
{
	HAL_GPIO_WritePin(W5500Reset_GPIO_Port,W5500Reset_Pin,GPIO_PIN_RESET);
	wfDelay_ms(10);  
	HAL_GPIO_WritePin(W5500Reset_GPIO_Port,W5500Reset_Pin,GPIO_PIN_SET);
	wfDelay_ms(1000);
}
void w5500LibInit( void )
{
	uint8_t tmp;
	uint8_t memsize[2][8] = {{16,0,0,0,0,0,0,0},{16,0,0,0,0,0,0,0}};
	reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);	//ע���ٽ�������
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);//ע��SPIƬѡ�źź���
	reg_wizchip_spi_cbfunc(SPI_ReadByte, SPI_WriteByte);	//ע���д����
	bW5500Net=0;
	if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1)
	{
		bW5500Net=0;
		return;
	}
	if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1)
	{
		bW5500Net=0;
		return;
	}
	ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);
	bW5500Net=1;
}
/**
  * @brief  �����ٽ���
  * @retval None
  */
void SPI_CrisEnter(void)
{
	__set_PRIMASK(1);
}
/**
  * @brief  �˳��ٽ���
  * @retval None
  */
void SPI_CrisExit(void)
{
	__set_PRIMASK(0);
}

/**
  * @brief  Ƭѡ�ź�����͵�ƽ
  * @retval None
  */
void SPI_CS_Select(void)
{
	w5500_CSoff();
}
/**
  * @brief  Ƭѡ�ź�����ߵ�ƽ
  * @retval None
  */
void SPI_CS_Deselect(void)
{
	w5500_CSon();
}

/**
  * @brief  д1�ֽ����ݵ�SPI����
  * @param  TxData д�����ߵ�����
  * @retval None
  */
void SPI_WriteByte(uint8_t TxData)
{				 
	SimSPI_Proc(TxData);		
}
/**
  * @brief  ��SPI���߶�ȡ1�ֽ�����
  * @retval ����������
  */
uint8_t SPI_ReadByte(void)
{	
	return SimSPI_Proc(0xff);
// 	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//�ȴ���������			  
// 	SPI1->DR=0xFF;	 	  										//����һ�������ݲ����������ݵ�ʱ�� 
// 	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //�ȴ�������һ��byte  
// 	return SPI1->DR;  						    
}

