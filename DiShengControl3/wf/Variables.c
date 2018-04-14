#include "Variables.h"
#include "..\..\..\WF_Device\stm32\wfEEPROM.h"
#include "w5500_Conf.h"

u16_wf Temperature;
uint8_t TCMData[12];
uint32_t TCMErr;
uint32_t ModbusErr;
uint32_t MS8607Err;
uint32_t RIOErr;
uint32_t GPRSErr;
uint8_t ModbusRTU_MasterRx;
uint8_t GPRSRx;
uint32_t MissServer;
uint32_t w5500Retry;
_SystemParam SystemParam;


void InitSystemParam(void)
{
	uint32_t i,sum;
	wfEEPROM_ReadWords(0,SystemParam.all,SystemParamLen);
	sum=0;
	for(i=1;i<SystemParamLen;i++)
	{
		sum+=SystemParam.all[i];
	}
	if(sum!=SystemParam.sum)
	{
		for(i=0;i<6;i++)
		{
			SystemParam.mac[i]=gWIZNETINFO.mac[i];
		}
		for(i=0;i<4;i++)
		{
			SystemParam.ip[i]=gWIZNETINFO.ip[i];
			SystemParam.sn[i]=gWIZNETINFO.sn[i];
			SystemParam.gw[i]=gWIZNETINFO.gw[i];
			SystemParam.dns[i]=gWIZNETINFO.dns[i];
			SystemParam.pc_ip[i]=pc_ip[i];
		}
		SystemParam.DESPORT=DESPORT;
		SystemParam.myPort=myPort;
		sum=0;
		for(i=1;i<SystemParamLen;i++)
		{
			sum+=SystemParam.all[i];
		}
		SystemParam.sum=sum;
		STMFLASH_Write(wfEEPROM_BASE_ADDR,SystemParam.all,SystemParamLen);
	}
	else
	{
// 		for(i=0;i<6;i++)
// 		{
// 			gWIZNETINFO.mac[i]=SystemParam.mac[i];
// 		}
		for(i=0;i<4;i++)
		{
			gWIZNETINFO.ip[i]=SystemParam.ip[i];
			gWIZNETINFO.sn[i]=SystemParam.sn[i];
			gWIZNETINFO.gw[i]=SystemParam.gw[i];
			//gWIZNETINFO.dns[i]=SystemParam.dns[i];
			pc_ip[i]=SystemParam.pc_ip[i];
		}
		DESPORT=SystemParam.DESPORT;
		myPort=SystemParam.myPort;
	}
}




#define FLASH_WAITETIME  50000          //FLASH等待超时时间
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)	
{ 
	uint32_t i;
	FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus=HAL_OK;
	uint32_t SectorError=0;
	HAL_FLASH_Unlock();             //解锁	
	FlashEraseInit.TypeErase=FLASH_TYPEERASE_PAGES;       //擦除类型，页擦除 
	FlashEraseInit.PageAddress=WriteAddr;   //要擦除的页，即写入地址
	FlashEraseInit.NbPages=1;               //只擦除一页
	if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
	{
		HAL_FLASH_Lock();           //上锁
		return;//发生错误了	
	}	
	FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            //等待上次操作完成
	if(FlashStatus==HAL_OK)
	{
		for(i=0;i<NumToWrite;i++)
		{
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,WriteAddr,*pBuffer)!=HAL_OK)//写入数据
			{ 
				break;	//写入异常
			}
			WriteAddr+=4;
			pBuffer++;
		}
	}
	HAL_FLASH_Lock();           //上锁
} 
