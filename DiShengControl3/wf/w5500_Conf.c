#include "w5500_Conf.h"
#include "wizchip_conf.h"
#include "socket.h"
#include "..\..\..\WF_Device\CP1616_Client.h"
#include "..\..\..\WF_Device\wfDefine.h"
#include "Variables.h"
#include "..\..\..\WF_Device\GPS_GPRMC.h"
#include "..\..\..\WF_Device\MS8607.h"
#include "..\..\..\WF_Device\Verify.h"


wiz_NetInfo gWIZNETINFO = { 
	.mac = {0x00, 0x08, 0xdc,0x00, 0xab, 0xcd},
	.ip = {192, 168, 1, 201},
	.sn = {255,255,255,0},
	.gw = {192, 168, 1, 1},
	.dns = {0,0,0,0},
	.dhcp = NETINFO_STATIC 
};
volatile uint32_t bW5500Net;
#define UseSocket 0
uint8_t pc_ip[4]={192,168,1,200};/*配置目标服务器的IP地址*/
uint16_t DESPORT=6000;
uint16_t myPort = 50000;

uint8_t NetBuf[1024];
unsigned char NetTxList[100];
unsigned char NetTxCount;
void loopback_tcpc(void)
{
	int32_t ret;
	uint16_t size,i,j,sentsize;
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
 						NetTxList[0] = 0x16;
 						NetTxList[1] = 0x16;
 						NetTxList[2] = CP1616_Client_RxList[pCP1616_CommandIndex];
 						NetTxCount=2+12+10+6+4+4+4+1;
 						NetTxList[3] = HIGH_BYTE(NetTxCount);
 						NetTxList[4] = LOW_BYTE(NetTxCount);
 						NetTxList[pCP1616_ClientData]=Temperature.u8H;
 						NetTxList[pCP1616_ClientData+1]=Temperature.u8L;
 						for (i = 0; i < 12; i++)
 						{
 							NetTxList[pCP1616_ClientData+2+i] = TCMData[i];
 						}
 						for (i = 0; i < 10; i++)
 						{
 							NetTxList[pCP1616_ClientData+2+12+i] = GPS_GPRMC.UTCTime[i];
 						}
 						for (i = 0; i < 6; i++)
 						{
 							NetTxList[pCP1616_ClientData+2+12+10+i] = GPS_GPRMC.UTCDate[i];
 						}
 						for (i = 0; i < 4; i++)
 						{
 							NetTxList[pCP1616_ClientData+2+12+10+6+i] = MS8607_Temperature.u8s[i];
 						}
 						for (i = 0; i < 4; i++)
 						{
 							NetTxList[pCP1616_ClientData+2+12+10+6+4+i] = MS8607_Pressure.u8s[i];
 						}
 						for (i = 0; i < 4; i++)
 						{
 							NetTxList[pCP1616_ClientData+2+12+10+6+4+4+i] = MS8607_RH.u8s[i];
 						}
						NetTxList[pCP1616_ClientData+2+12+10+6+4+4+4]=(uint8_t)TCMErr;
 						NetTxList[pCP1616_ClientData+NetTxCount] = GetVerify_Sum(NetTxList, pCP1616_ClientData+NetTxCount);
 						NetTxList[pCP1616_ClientData+NetTxCount + 1] = 0x0d;
 
 						sentsize=0;
 						// Data sentsize control
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
 						break;
 					}
 					CP1616_Client_EndProcCommand();
 				}
 
 			}
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
 		if((ret=socket(UseSocket, Sn_MR_TCP, myPort++, 0x00)) != UseSocket) 
 		{
 			bW5500Net=0;
 		}//return ret; // TCP socket open with 'any_port' port number
		break;
	default:
		break;
	}
	//return 1;
}
void w5500LibInit( void )
{
	uint8_t tmp;
	uint8_t memsize[2][8] = {{16,0,0,0,0,0,0,0},{16,0,0,0,0,0,0,0}};
	reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);	//注册临界区函数
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);//注册SPI片选信号函数
	reg_wizchip_spi_cbfunc(SPI_ReadByte, SPI_WriteByte);	//注册读写函数
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
  * @brief  进入临界区
  * @retval None
  */
void SPI_CrisEnter(void)
{
	__set_PRIMASK(1);
}
/**
  * @brief  退出临界区
  * @retval None
  */
void SPI_CrisExit(void)
{
	__set_PRIMASK(0);
}

/**
  * @brief  片选信号输出低电平
  * @retval None
  */
void SPI_CS_Select(void)
{
	w5500_CSoff();
}
/**
  * @brief  片选信号输出高电平
  * @retval None
  */
void SPI_CS_Deselect(void)
{
	w5500_CSon();
}

/**
  * @brief  写1字节数据到SPI总线
  * @param  TxData 写到总线的数据
  * @retval None
  */
void SPI_WriteByte(uint8_t TxData)
{				 
	SimSPI_Proc(TxData);		
}
/**
  * @brief  从SPI总线读取1字节数据
  * @retval 读到的数据
  */
uint8_t SPI_ReadByte(void)
{	
	return SimSPI_Proc(0xff);
// 	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//等待发送区空			  
// 	SPI1->DR=0xFF;	 	  										//发送一个空数据产生输入数据的时钟 
// 	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //等待接收完一个byte  
// 	return SPI1->DR;  						    
}

