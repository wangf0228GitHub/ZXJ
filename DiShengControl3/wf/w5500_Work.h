#ifndef __w5500_Conf_h__
#define __w5500_Conf_h__

#include "gpio.h"
#include "SimSPI.h"
#include "wizchip_conf.h"


extern volatile uint32_t bW5500Net;
extern wiz_NetInfo gWIZNETINFO;
extern uint8_t pc_ip[4];/*配置目标服务器的IP地址*/
extern uint16_t DESPORT;
extern uint16_t myPort;

#define w5500_CSoff() HAL_GPIO_WritePin(SPI_WSCS_GPIO_Port,SPI_WSCS_Pin,GPIO_PIN_RESET)
#define w5500_CSon() HAL_GPIO_WritePin(SPI_WSCS_GPIO_Port,SPI_WSCS_Pin,GPIO_PIN_SET)

#define w5500_SPIProc(x) SimSPI_Proc(x)

void SPI_Configuration(void);
void SPI_WriteByte(uint8_t TxData);
uint8_t SPI_ReadByte(void);
void SPI_CrisEnter(void);
void SPI_CrisExit(void);
void SPI_CS_Select(void);
void SPI_CS_Deselect(void);
void w5500LibInit(void);
void loopback_tcpc(void);
void Reset_W5500(void);

/************************************************************************/
/* loopback                                                             */
/************************************************************************/
#define DATA_BUF_SIZE			2048

#endif


