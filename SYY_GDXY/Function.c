#include "HardwareProfile.h"
void ReadAD1120(void)
{	
	unsigned char i;
	signed long sum;
	ADS1120_CS_W=0;
	__delay_ms(1);
	for(i=0;i<ADAverage;i++)
	{
		ADS1120_SPI_Proc(0x08);//Æô¶¯×ª»»
		__delay_ms(1);
		while(ADS1120_DRDY_R);
		ADResult[i].s8s.u8_h=ADS1120_SPI_Proc(0x00);
		ADResult[i].s8s.s8_l=ADS1120_SPI_Proc(0x00);
		__delay_ms(1);
	}
	sum=0;
	for(i=0;i<ADAverage;i++)
	{
		sum=sum+ADResult[i].s16;
	}
	ADValue.s16=sum>>2;
	ADS1120_CS_W=1;
}

void SetBright(unsigned int x)
{
	x=x&0x00ff;
	x=x<<4;
	TLV56XX_WriteData(x);
//	__delay_20ms(3);
//	TLV56XX_WriteData(x);
}

void SetCutOffV(unsigned int x)
{
	x=x&0x0fff;	
	TLV56XX_2_WriteData(x);
//	__delay_20ms(3);
//	TLV56XX_2_WriteData(x);
}

void SwitchLED(unsigned char index,unsigned char x)
{
	LED1_W=0;
	LED2_W=0;
	LED3_W=0;
	LED4_W=0;
	LED5_W=0;
	LED6_W=0;

	switch(index)
	{
	case 0x01:
		LED1_W=x;
		break;
	case 0x02:
		LED2_W=x;
		break;
	case 0x03:
		LED3_W=x;
		break;
	case 0x04:
		LED4_W=x;
		break;
	case 0x05:
		LED5_W=x;
		break;
	case 0x06:
		LED6_W=x;
		break;
	}
}
