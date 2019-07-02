#include "Function.h"
#include "..\..\..\WF_Device\wfDefine.h"
unsigned char DisplayLine[5];
#include <stdio.h>
#include "SimSPI.h"


void TLC5615_WriteData(uint16_t d)
{
	uint8_t i;
	TLC5615_CS_W=0;
	__delay_us(1);
	gTemp1=100;
	gTemp1=SimSPI_Proc(HIGH_BYTE(d));
	gTemp2=SimSPI_Proc(LOW_BYTE(d));
	TLC5615_CS_W=1;	
}

#ifdef Proteus
#include "Max7221.h"
#define Display_WriteData(addr,data) Max7221_WriteData(addr,data)
#define Display_WriteData_2(addr,data) Max7221_WriteData_2(addr,data)
#define Display_LEDNumCode Max7221_LEDNumCode
#define Display_LEDNumCode_P 0x67
#define Display_LEDNumCode_Off 0x00
#define Display_LEDNumCode_L 0x0e
#define Display_LEDNumCode_H 0x37
#define Display_LED_Off 0x00
#define Display_SetDP(x) x=x|0x80
const unsigned char Display_LEDAddr[4]={0x01,0x02,0x03,0x04};//从左至右
#else
#include "TM1650.h"
#define Display_WriteData(addr,data) TM1650_WriteData(addr,data)
#define Display_WriteData_2(addr,data) TM1650_2_WriteData(addr,data)
#define Display_LEDNumCode TM1650_LEDNumCode
#define Display_LEDNumCode_P 0x73
#define Display_LEDNumCode_Off 0x17
#define Display_LEDNumCode_L 0x38
#define Display_LEDNumCode_H 0x76
#define Display_LED_Off 0x00
#define Display_SetDP(x) x=x|0x80
const unsigned char Display_LEDAddr[4]={0x6e,0x6c,0x6a,0x68};//从左至右
#endif



void Display_Init(void)
{
#ifdef Proteus
	Max7221_Init();
	Display_WriteData(0x09,0x00);   
	Display_WriteData(0x0a,0x07); 
	Display_WriteData(0x0b,0x03); 
	Display_WriteData(0x0c,0x01);
	Display_WriteData(Display_LEDAddr[0],Display_LEDNumCode_Off); 
	Display_WriteData(Display_LEDAddr[1],Display_LEDNumCode_Off);
	Display_WriteData(Display_LEDAddr[2],Display_LEDNumCode[0]|0x80);
	Display_WriteData(Display_LEDAddr[3],Display_LEDNumCode[0]);

	Max7221_Init_2();
	Display_WriteData_2(0x09,0x00);   
	Display_WriteData_2(0x0a,0x07); 
	Display_WriteData_2(0x0b,0x03); 
	Display_WriteData_2(0x0c,0x01);
	Display_WriteData_2(Display_LEDAddr[0],Display_LEDNumCode_Off); 
	Display_WriteData_2(Display_LEDAddr[1],Display_LEDNumCode_Off);
	Display_WriteData_2(Display_LEDAddr[2],Display_LEDNumCode_Off);
	Display_WriteData_2(Display_LEDAddr[3],Display_LEDNumCode[0]);
#else
	TM1650_Init();
	while(Display_WriteData(0x48,0x41)==0);
	Display_WriteData(Display_LEDAddr[0],Display_LEDNumCode[1]); 
	Display_WriteData(Display_LEDAddr[1],Display_LEDNumCode[2]);
	Display_WriteData(Display_LEDAddr[2],Display_LEDNumCode[3]);
	Display_WriteData(Display_LEDAddr[3],Display_LEDNumCode[4]);

	TM1650_2_Init();
	while(Display_WriteData_2(0x48,0x41)==0);
	Display_WriteData_2(0x48,0x41);  
	Display_WriteData_2(Display_LEDAddr[0],Display_LEDNumCode[1]); 
	Display_WriteData_2(Display_LEDAddr[1],Display_LEDNumCode[2]);
	Display_WriteData_2(Display_LEDAddr[2],Display_LEDNumCode[3]);
	Display_WriteData_2(Display_LEDAddr[3],Display_LEDNumCode[4]);
#endif
}
// void Display_ShowParam(void);
/************************************************************************/
/*                                                                      */
/************************************************************************/
void VOutput(uint16_t da)
{
	uint8_t x;
	float v=da*0.082;//ad/1024*2.048*2*20.5
// 	uint16_t v;
// 	v=da<<3;//乘8，ad/1024*2.048*2*100*20,1mV
	sprintf(DisplayLine,"%04.1f",v);
	x=Display_LEDNumCode[DisplayLine[1]-'0'];
	Display_SetDP(x);
	Display_WriteData_2(Display_LEDAddr[0],Display_LED_Off); 
	if(DisplayLine[0]=='0')
		Display_WriteData_2(Display_LEDAddr[1],Display_LED_Off);
	else
		Display_WriteData_2(Display_LEDAddr[1],Display_LEDNumCode[DisplayLine[0]-'0']);
	Display_WriteData_2(Display_LEDAddr[2],x);
	Display_WriteData_2(Display_LEDAddr[3],Display_LEDNumCode[DisplayLine[3]-'0']);
	da=da<<2;
	da=da&0x0ffc;
	TLC5615_WriteData(da);
}
void ReadAD_RP(void)
{
	uint8_t i;
	uint16_t ad;
	ADCON0=0x01;//通道0
	__delay_ms(1);
	ad=0;
	for(i=0;i<4;i++)
	{
		GODONE=1;
		while(GODONE);
		ad+=MAKE_SHORT(ADRESH,ADRESL);
	}
	RPValue=ad>>2;
}

void ShowAD_I(void)
{
	uint8_t i;
	uint16_t ad;
	ADCON0=0x05;//通道1
	__delay_ms(1);
	ad=0;
	for(i=0;i<8;i++)
	{
		GODONE=1;
		while(GODONE);
		ad+=MAKE_SHORT(ADRESH,ADRESL);
	}
	IValue=ad>>3;
	if(IValue<RomParams.AD0)
	{
		IValue=RomParams.AD0-IValue;
		IValue=IValue>>1;
		if(IValue==0)
		{
			Display_WriteData(Display_LEDAddr[0],Display_LED_Off); 
		}
		else
		{
			Display_WriteData(Display_LEDAddr[0],Display_LEDNumCode[0x10]); 
		}		
	}
	else
	{
		IValue=IValue-RomParams.AD0;
		Display_WriteData(Display_LEDAddr[0],Display_LED_Off); 
		IValue=IValue>>1;		
	}
	
	
	sprintf(DisplayLine,"%03d",IValue);
	
	if(DisplayLine[0]=='0')
		Display_WriteData(Display_LEDAddr[1],Display_LED_Off);
	else
		Display_WriteData(Display_LEDAddr[1],Display_LEDNumCode[DisplayLine[0]-'0']);
	if(DisplayLine[0]=='0' && DisplayLine[1]=='0')
		Display_WriteData(Display_LEDAddr[2],Display_LED_Off);
	else
		Display_WriteData(Display_LEDAddr[2],Display_LEDNumCode[DisplayLine[1]-'0']);
	Display_WriteData(Display_LEDAddr[3],Display_LEDNumCode[DisplayLine[2]-'0']);
}
