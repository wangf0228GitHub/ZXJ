#include "HardwareProfile.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 _CONFIG3(WPDIS_WPDIS);
 _CONFIG2(POSCMOD_HS & DISUVREG_OFF & IOL1WAY_ON & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL_96MHZ_ON & PLLDIV_NODIV & IESO_ON);
 _CONFIG1(WDTPS_PS32768 & FWPSA_PR128 & WINDIS_OFF & FWDTEN_ON & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF);

unsigned int SystemTick;
unsigned int LEDTick;
unsigned int ReadSensorTick;
GFlags gFlags;
ErrFlags errFlags;
uint8_t wfTemp8[20];

volatile uint8_t gTemp;
uint8_t gDATABUF[DATA_BUF_SIZE];
uint Temperature;
unsigned char TCMData[12];
int main()
{
	int32_t ret = 0;
	unsigned char i;	
	__delay_ms(10);
	InitSystem();
	__delay_20ms(10);
	sensorPower_W=sensorPower_ON;
	SystemTick=0;		
	while(1)
	{	
		if(GetDeltaTick(LEDTick)>100)
		{
			LEDTick=SystemTick;
			LED_W=!LED_W;
		}
 		if(GetDeltaTick(ReadSensorTick)>100)
 		{
 			ReadSensorTick=SystemTick;
 			ModbusRTU_Master_SendCommand03(0x0006,2);
 			ModbusRTU_Master_preRxProcInit();		
 			TCM_SendData();
			if(MS8607_Flags.bInit==0)
			{
				MS8607_Init();
			}
			else
			{
				MS8607_ReadPT(ms8607_pressure_resolution_osr_8192);
				MS8607_ReadRH();
			}
 		}
 		if(ModbusRTU_Master_Flags.bRx)
 		{
 			Temperature.u8H=ModbusRTU_Master_RxList[3];
 			Temperature.u8L=ModbusRTU_Master_RxList[4];
 		}
 		if(TCM_Flags.bRx)
 		{
 			for(i=0;i<4;i++)
 			{
 				TCMData[i]=TCM_RxList[5+i];
 				TCMData[4+i]=TCM_RxList[10+i];
 				TCMData[8+i]=TCM_RxList[15+i];
 			}
 		}
		if(NMEA0183_Flags.bRx)
		{
			NMEA0183_Verify();
			GPS_GPRMC_DataProc(NMEA0183_RxBuf);
			NMEA0183_RxCount=0;
			NMEA0183_Flags.bRx=0;
		}
		if(gFlags.bNet)
		{
			loopback_tcpc();
		}
		else
		{
			w5500LibInit();
		}
//  		if( (ret = loopback_tcpc(0, gDATABUF,pc_ip,DESPORT)) < 0) 
//  		{
//  
//  			//printf("SOCKET ERROR : %ld\r\n", ret);
//  		}
	}
	return 1;
}
void __attribute__((__interrupt__,auto_psv)) _T1Interrupt(void)
{
	_T1IF=0;
	ClrWdt();
	SystemTick++;
}
void __attribute__((__interrupt__,auto_psv)) _U2RXInterrupt(void)
{	
	unsigned char rx;
	_U2RXIF=0;
	while(U2STAbits.URXDA)
	{
		rx=(unsigned char)U2RXREG;
		ProcRx_ModbusRTU_Master(rx);
	}
}
void __attribute__((__interrupt__,auto_psv)) _U4RXInterrupt(void)
{	
	unsigned char rx;
	_U4RXIF=0;
	while(U4STAbits.URXDA)
	{
		rx=(unsigned char)U4RXREG;
		NMEA0183_RxProc(rx);
	}
}
void __attribute__((__interrupt__,auto_psv)) _DefaultInterrupt(void)
{
	IFS0=0;
	IFS1=0;
	IFS2=0;
	IFS3=0;
	IFS4=0;
	IFS5=0;
}
