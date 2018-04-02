#include "w5500_Conf.h"
#include "wizchip_conf.h"

wiz_NetInfo gWIZNETINFO = { 
	.mac = {0x00, 0x08, 0xdc,0x00, 0xab, 0xcd},
	.ip = {192, 168, 0, 101},
	.sn = {255,255,255,0},
	.gw = {192, 168, 0, 1},
	.dns = {0,0,0,0},
	.dhcp = NETINFO_STATIC 
};
/**
  * @brief  Intialize the network information to be used in WIZCHIP
  * @retval None
  */
void network_init(void)
{
   uint8_t tmpstr[6];
	ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);
	ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);

	// Display Network Information
	ctlwizchip(CW_GET_ID,(void*)tmpstr);
// 	printf("\r\n=== %s NET CONF ===\r\n",(char*)tmpstr);
// 	printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
// 		  gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
// 	printf("SIP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
// 	printf("GAR: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
// 	printf("SUB: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
// 	printf("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
// 	printf("======================\r\n");
}

void w5500LibInit( void )
{
	uint8_t tmp;
	uint8_t memsize[2][8] = {{2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};
	/* USER CODE BEGIN 2 */
	reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);	//注册临界区函数
	/* Chip selection call back */
#if   _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_VDM_
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);//注册SPI片选信号函数
#elif _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_FDM_
	reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);  // CS must be tried with LOW.
#else
	#if (_WIZCHIP_IO_MODE_ & _WIZCHIP_IO_MODE_SIP_) != _WIZCHIP_IO_MODE_SIP_
		#error "Unknown _WIZCHIP_IO_MODE_"
	#else
		reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
	#endif
#endif
	/* SPI Read & Write callback function */
	reg_wizchip_spi_cbfunc(SPI_ReadByte, SPI_WriteByte);	//注册读写函数
	if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1)
	{
		//printf("WIZCHIP Initialized fail.\r\n");
		while(1);
	}
	/* PHY link status check */
	do{
		if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1)
		{
			//printf("Unknown PHY Link stauts.\r\n");
		}
	}while(tmp == PHY_LINK_OFF);
	network_init();
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

