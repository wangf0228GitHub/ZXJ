#ifndef   __Variables_h__
#define   __Variables_h__

#include <stdint.h>
#include "TypeDefine.h"
#include "main.h"

#define SystemParamLen 10
typedef union
{	
	struct
	{
		uint32_t sum;
		//w5500网络参数:6
		uint8_t mac[8];  ///< Source Mac Address
		uint8_t ip[4];   ///< Source IP Address
		uint8_t sn[4];   ///< Subnet Mask 
		uint8_t gw[4];   ///< Gateway IP Address
		uint8_t dns[4];  ///< DNS server IP Address
		//服务器网络参数：3
		uint8_t pc_ip[4];/*配置目标服务器的IP地址*/
		uint32_t DESPORT;
		uint32_t myPort;
	};
	uint32_t all[SystemParamLen];
	uint8_t allByte[SystemParamLen<<2];
}_SystemParam;


extern _SystemParam SystemParam;
extern u16_wf Temperature;
extern uint8_t TCMData[12];
extern uint32_t TCMErr;
extern uint32_t ModbusErr;
extern uint32_t MS8607Err;
extern uint32_t RIOErr;
extern uint32_t GPRSErr;
extern uint8_t ModbusRTU_MasterRx;
extern uint8_t GPRSRx;
extern uint32_t MissServer;
extern uint32_t w5500Retry;

void InitSystemParam(void);
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);
#endif
