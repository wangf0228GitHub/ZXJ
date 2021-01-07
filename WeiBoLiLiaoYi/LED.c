#include "HardwareProfile.h"
const unsigned char LEDNum[16]=
{
	0b00111111,	//0
	0b00000110, //1
	0b01011011,	//2
	0b01001111,	//3
	0b01100110,	//4
	0b01101101,	//5
	0b01111101,	//6
	0b00000111,	//7
	0b01111111,	//8
	0b01101111,	//9
	0b11011100, //a
	0b01111100, //b
	0b00111001, //c
	0b01100011, //d
	0b01111001, //e
	0b01110001, //f
	//0b01000000  // -
};
void LED_NULL(void)
{
	TM1638_WriteData(0, 0x40);
	TM1638_WriteData(2, 0x40);
	TM1638_WriteData(4, 0x40);
	TM1638_WriteData(6, 0x40);
	TM1638_WriteData(8, 0x40);
	TM1638_WriteData(10, 0x40);
}
void LED_MCTime(void)
{
 	unsigned char x,y;
 	x=MCTime_M%10;
 	y=MCTime_M/10;
 	TM1638_WriteData(2,LEDNum[x]);
 	TM1638_WriteData(0,LEDNum[y]);

	x = MCTime_S % 10;
	y = MCTime_S / 10;
	TM1638_WriteData(6, LEDNum[x]);
	TM1638_WriteData(4, LEDNum[y]);
// 	TM1638_WriteData(4,LEDNum[HIGH_NIBBLE(MCTime)]);
// 	TM1638_WriteData(2,LEDNum[LOW_NIBBLE(MCTime)]);
}
void LED_MCLevel(void)
{
	unsigned char x, y;
	x = MCLevel % 10;
	y = MCLevel / 10;
	TM1638_WriteData(10, LEDNum[x]);
	TM1638_WriteData(8, LEDNum[y]);
}
void PLed_ON(void)
{
	TM1638_WriteData(14, 0x01);
}
void CLed_ON(void)
{
	TM1638_WriteData(14, 0x02);
}
void SLed_Toggle()
{
	if (gFlags.Bits.bShow)
	{
		gFlags.Bits.bShow = 0;
		TM1638_WriteData(12, 0x00);
	}
	else
	{
		gFlags.Bits.bShow = 1;
		TM1638_WriteData(12, 0x03);
	}
}
void SLed_ON(void)
{
	gFlags.Bits.bShow = 1;
	TM1638_WriteData(12, 0x03);	
}
void LED_Switch(unsigned char s)
{
	unsigned char l;
	l=0b00000010;
	if(s==0)
		TM1638_WriteCommand(0x80|l);
	else
		TM1638_WriteCommand(0x88|l);
	//TM1638_WriteData(6,LEDNum[0]);
}
