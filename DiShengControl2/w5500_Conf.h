#ifndef __w5500_Conf_h__
#define __w5500_Conf_h__

#include "SimSPI.h"
#include <stdint.h>

#define w5500_CSoff() w5500_CS_W=0
#define w5500_CSon() w5500_CS_W=1

#define w5500_SPIProc(x) SimSPI_Proc(x)

void SPI_Configuration(void);
void SPI_WriteByte(unsigned char TxData);
unsigned char SPI_ReadByte(void);
void SPI_CrisEnter(void);
void SPI_CrisExit(void);
void SPI_CS_Select(void);
void SPI_CS_Deselect(void);
void w5500LibInit(void);

void loopback_tcpc(void);

/************************************************************************/
/* loopback                                                             */
/************************************************************************/
#define DATA_BUF_SIZE			2048

#endif


