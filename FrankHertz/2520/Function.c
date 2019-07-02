#include "Function.h"
#include "..\..\..\WF_Device\wfDefine.h"
unsigned char DisplayLine[5];
#include <stdio.h>
#include "SimSPI.h"
#include "..\..\..\WF_Device\TypeDefine.h"

void FastModeOut(void)
{
	uint16_t i;
	DAC0832_WriteData(FastModeData[0]);
	__delay_us(10);
	TB_W=1;
	for(i=1;i<10;i++)
	{
		DAC0832_WriteData(FastModeData[i]);
		__delay_us(2);
	}
	TB_W=0;
	for(i=0;i<256;i++)
	{
		DAC0832_WriteData(FastModeData[i]);
		__delay_us(2);
	}

	DAC0832_WriteData(FastModeData[0]);
	__delay_us(10);
	TB_W=1;
	for(i=1;i<10;i++)
	{
		DAC0832_WriteData(FastModeData[i]);
		__delay_us(2);
	}
	TB_W=0;

	__delay_ms(1);
}
void DAC0832_WriteData(uint8_t da)
{
	u8_wf x;
	x.u8=da;
	LATC=x.u8;
	LATB1=x.bits.b6;
	LATB2=x.bits.b7;
	DAC0832_CS_W=0;
	__delay_us(1);
	DAC0832_WR_W=0;__delay_us(1);
	DAC0832_WR_W=1;__delay_us(1);
	DAC0832_CS_W=0;
}

