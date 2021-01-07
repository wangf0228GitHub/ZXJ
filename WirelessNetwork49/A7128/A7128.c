#include "A7128.h"
#include "A7128reg.h"
#include "A7128Config.h"
#include "wfSys.h"
#include "spi.h"

const uint8_t ID_Tab[9]={IDCODE_REG,0xaa,0xbb,0xcc,0xee,0xC7,0x33,0x45,0xE8}; //ID code

//uint8_t ROCT;
volatile uint8_t A7128_TxFIFO[65];
volatile uint8_t A7128_RxFIFO[65];
uint8_t A7128_RxID[8];
void A7128_WriteReg(uint8_t  addr, uint8_t dataByte);
uint8_t A7128_ReadReg(uint8_t addr);
//void A7128_ByteSend(uint8_t src);
//uint8_t A7128_ByteRead(void);
//void A7128_Send4Bit(uint8_t src);
/*********************************************************************
** SetCH
*********************************************************************/
void A7128_SetCH(uint8_t ch)
{
	//RF freq = RFbase + (CH_Step * ch)
	A7128_WriteReg(PLL1_REG, ch);
}
/************************************************************************
**  Reset_RF
************************************************************************/
void A7128_Reset(void)
{
	A7128_WriteReg(MODE_REG, 0x00); //reset RF chip
}

/************************************************************************
**  WriteID
************************************************************************/
void A7128_WriteID(void)
{
	A7128_SCS_Low();
	HAL_SPI_Transmit(&A7128SPI,(uint8_t*)ID_Tab,8+1,100);
	A7128_SCS_High();
	//A7128_ReadID();
}
void A7128_ReadID(void)
{
	uint8_t rID[9];
	//for check
	rID[0]=IDCODE_REG | 0x40;
	A7128_SCS_Low();
	HAL_SPI_TransmitReceive(&A7128SPI,rID,rID,8+1,100);
	A7128_SCS_High();
}
/*********************************************************************
** CHGroupCal
*********************************************************************/
int A7128_CHGroupCal(uint8_t ch)
{
	uint8_t tmp;
	uint8_t vb,vbcf;
	uint8_t deva,adev;
	uint32_t errTimes = 0;
	A7128_WriteReg(PLL1_REG, ch);
	A7128_WriteReg(CALIBRATION_REG, 0x0C);
	do
	{
		tmp = A7128_ReadReg(CALIBRATION_REG);
		tmp &= 0x0C;
		if (tmp != 0)
		{
			wfDelay_ms(1);
			errTimes++;
			if (errTimes > 20)
			{
				return 0;
			}
		}
	}
	while (tmp);
	return 1;
	/*
		//for check
		tmp = A7128_ReadReg(VCOCAL1_REG);
		vb = tmp & 0x07;
		vbcf = (tmp >>3) & 0x01;

		tmp = A7128_ReadReg(VCODEVCAL1_REG);
		deva = tmp;

		tmp = A7128_ReadReg(VCODEVCAL2_REG);
		adev = tmp;

		if (vbcf)
			while(1);//error
	*/
}
/*********************************************************************
** calibration
*********************************************************************/
int A7128_Cal(void)
{
	uint8_t tmp;
	uint8_t fb,fbcf,fcd;
	uint8_t vcb,vccf;
	uint32_t errTimes=0;
	//calibration RSSI,IF, VCC procedure
	A7128_StrobeCmd(CMD_PLL); //PLL state
	A7128_WriteReg(CALIBRATION_REG, 0x13);
	do
	{
		tmp = A7128_ReadReg(CALIBRATION_REG);
		tmp &= 0x13;
		if(tmp!=0)
		{
			wfDelay_ms(1);
			errTimes++;
			if (errTimes > 20)
			{
				return 0;
			}
		}
	}
	while (tmp);

	//calibration VBC,VDC procedure
	//校准905M,915M,925M三个频点
	if (A7128_CHGroupCal(20) == 0) //calibrate channel group Bank I
		return 0;
	if (A7128_CHGroupCal(60) == 0) //calibrate channel group Bank II
		return 0;
	if (A7128_CHGroupCal(100) == 0) //calibrate channel group Bank III
		return 0;
	A7128_StrobeCmd(CMD_STBY); //return to STBY state
	return 1;
	/*
	//for check
	tmp = A7128_ReadReg(IFCAL1_REG);
	fb = tmp & 0x0F;
	fbcf = (tmp >>4) & 0x01;//检查IF Filter校准是否成功

	tmp = A7128_ReadReg(IFCAL2_REG);
	fcd = tmp & 0x1F;//

	tmp = A7128_ReadReg(VCOCCAL_REG);//检查VCO Current校准是否成功
	vcb = tmp & 0x0F;
	vccf = (tmp >>4) & 0x01;

	if (fbcf || vccf)
		while(1);//error
	*/
}

/*********************************************************************
** A7128_RCCal
*********************************************************************/
void A7128_RCCal(void)
{
	uint8_t tmp;
	uint8_t rcoc;
	uint8_t tmp_roct;
	uint8_t var_data;
	uint8_t f_err;
	uint8_t i;

	tmp_roct = 0;

	for (i=0; i<50 ;i++)//retry 5 times
	{
		var_data = tmp_roct | 0x0C;
		A7128_WriteReg(RCOSC3_REG, var_data);
		do
		{
			tmp = A7128_ReadReg(RCOSC1_REG);
			tmp &= 0x40;
		}
		while (tmp);

		rcoc = A7128_ReadReg(RCOSC1_REG) & 0x3F;

		//ROCT OK
		if (rcoc > 10 && rcoc < 63)
		{
			f_err = 0;
			break;
		}

		//ROCT too low
		if (rcoc <= 10)
		{
			if (tmp_roct == 0x30)
			{
				f_err = 1;
				break;
			}

			tmp_roct = tmp_roct + 0x10;
		}

		//ROCT too high
		if (rcoc > 62)
		{
			if (tmp_roct == 0x00)
			{
				f_err = 1;
				break;
			}

			tmp_roct = tmp_roct - 0x10;
		}
	}

	if(f_err==1)
	{
		NVIC_SystemReset();
		while(1);//Err_State();
	}
// 	else
// 	{
// 		ROCT = tmp_roct;//saving ROCT value
// 		A7128_WriteReg(RCOSC3_REG, 0x00);
// 	}
}

/*********************************************************************
** A7128_Config
*********************************************************************/
void A7128_Config(void)
{
	uint8_t i;
	uint8_t set[100];
	//0x00 Mode register, for reset
	//0x05 FIFO data register
	//0x06 ID code register
	//0x3D Reserved register
	//0x3E FCF register
	//0x3F USID register

	A7128_WriteReg( GIO1_REG, 0x01);		//	GIO1 WTR
	A7128_WriteReg( GIO2_REG, 0x19	);		//	GIO2 Disable

	for (i=0x01; i<=0x04; i++)
		A7128_WriteReg(i, A7128Config[i]);

// 	for (i=0x01; i<=0x04; i++)
// 		set[i]=A7128_ReadReg(i);

	for (i=0x07; i<=0x3C; i++)
		A7128_WriteReg(i, A7128Config[i]);

// 	for (i=0x07; i<=0x3c; i++)
// 		set[i]=A7128_ReadReg(i);
// 
// 	set[i]=A7128_ReadReg(i);
}
/*********************************************************************
** WOR_enable
*********************************************************************/
void A7128_WOREnable(void)
{
	A7128_RCCal();
	A7128_ReadReg(RCOSC3_REG);
	//A7128_StrobeCmd(CMD_RFR);
	//休眠5s，醒1ms，WOR_SL=640,WOR_AC=3
	A7128_WriteReg(RCOSC1_REG, 0x70);//setup the sleep time
	A7128_WriteReg(RCOSC2_REG, 0x86);//setup the Rx time
	A7128_WriteReg(RCOSC3_REG, 0x04);//select WOR mode
 	A7128_WriteReg(GIO1_REG, 0x05);//WTR signal
// 	A7128_WriteReg(GIO2_REG, 0x05);//RX sync signal
	A7128_WriteReg(MODECTRL_REG, 0x6A);//WOR enable
	A7128_StrobeCmd(CMD_SLEEP);
	
	//while(1)
	//{
	//	if(A7128_GIO1_Read()==1)
	//	{
	//		A7128_ReadReg(RCOSC3_REG);
	//		A7128_StrobeCmd(CMD_STBY);
	//		break;
	//	}
	//}
	//while(GIO2==0);//stay in WOR mode until receiving data
}

/*********************************************************************
** RSSI_measurement_enable
*********************************************************************/
// void A7128_RSSI_measurement_enable(void)
// {
// 	uint8_t tmp;
// 
// 	A7128_WriteReg(MODECTRL_REG, 0x62);// enable ARSSI
// 	A7128_WriteReg(GIO1_REG, 0x01);//WTR signal
// 	A7128_WriteReg(GIO2_REG, 0x05);//RX sync signal
// 	A7128_StrobeCmd(CMD_RX); //entry rx
// 	tmp = A7128_ReadReg(RSSI_REG);//read RSSI value(environment RSSI)
// 	while(1)
// 	{
// 		if(A7128_GIO2_Read()==1)
// 			break;
// 	}
// 	//while(GIO2==0);//receiving ID code
// 	tmp = A7128_ReadReg(RSSI_REG);//read RSSI value(wanted signal RSSI)
// }
/*********************************************************************
** A7128_WriteFIFO
*********************************************************************/
void A7128_WriteFIFO(void)
{
	A7128_StrobeCmd(CMD_TFR);
	A7128_TxFIFO[0]=FIFO_REG;
	A7128_SCS_Low();
	HAL_SPI_Transmit(&A7128SPI,(uint8_t*)A7128_TxFIFO,65,1000);
	A7128_SCS_High();
}
void A7128_WriteFIFO_DMA(void)
{
	A7128_StrobeCmd(CMD_TFR);
	A7128_TxFIFO[0]=FIFO_REG;
	A7128_SCS_Low();
	HAL_SPI_Transmit_DMA(&A7128SPI,(uint8_t*)A7128_TxFIFO,65);

	//while(A7128_SCS_Read()==GPIO_PIN_RESET);
// 	HAL_SPI_Transmit(&A7128SPI,A7128_TxFIFO,65,1000);
// 	A7128_SCS_High();
}
void A7128_WriteFIFO_DMA_ADC(uint8_t* pBuf)
{
	A7128_StrobeCmd(CMD_TFR);
	A7128_TxFIFO[0]=FIFO_REG;
	A7128_SCS_Low();
	HAL_SPI_Transmit(&A7128SPI,(uint8_t*)A7128_TxFIFO,5,1000);
	HAL_SPI_Transmit_DMA(&A7128SPI,pBuf,60);
}
void A7128_TxData_byFIFO(void)
{
	A7128_StrobeCmd(CMD_TFR);
	A7128_TxFIFO[0]=FIFO_REG;
	A7128_SCS_Low();
	HAL_SPI_Transmit_DMA(&A7128SPI,(uint8_t*)A7128_TxFIFO,65);
	while(A7128_SCS_Read()==GPIO_PIN_RESET);
	// 	
	// 	A7128_SCS_High();
}
/*********************************************************************
** RxPacket
*********************************************************************/
void A7128_RxPacket(void)
{
	A7128_RxFIFO[0]=FIFO_REG|0x40;
	A7128_SCS_Low();
	HAL_SPI_TransmitReceive(&A7128SPI,(uint8_t*)A7128_RxFIFO,(uint8_t*)A7128_RxFIFO,65,2);
	A7128_SCS_High();
}
void A7128_RxPacket_DMA(void)
{
	A7128_RxFIFO[0]=FIFO_REG|0x40;
	A7128_SCS_Low();
	HAL_SPI_TransmitReceive_DMA(&A7128SPI,(uint8_t*)A7128_RxFIFO,(uint8_t*)A7128_RxFIFO,65);
}
/*********************************************************************
** Strobe Command
*********************************************************************/
void A7128_StrobeCmd(uint8_t cmd)
{
	A7128_SCS_Low();
	HAL_SPI_Transmit(&A7128SPI,&cmd,1,100);
	A7128_SCS_High();
}
/*********************************************************************
** initRF
*********************************************************************/
void A7128_Init(void)
{
	//init io pin
	A7128_SCS_High();
// 	A7128_SCK_Low();
// 	A7128_SDIO_OUT();
	while(1)
	{
		A7128_Reset(); //reset A7128 RF chip
		wfDelay_ms(1);
		A7128_Config(); //config A7128 chip
		A7128_WriteID(); //write ID code 	
		if (A7128_Cal() == 1)
			break;//calibration
	}
 	//A7128_RCCal(); //Ring osc calibration
}
/************************************************************************
**  A7128_WriteReg
************************************************************************/
void A7128_WriteReg(uint8_t  addr, uint8_t dataByte)
{
	uint8_t tx[2];
	addr |= 0x00; //bit cmd=0,r/w=0
	tx[0]=addr;
	tx[1]=dataByte;
	A7128_SCS_Low();
	HAL_SPI_Transmit(&A7128SPI,tx,2,100);
	A7128_SCS_High();
}

/************************************************************************
**  A7128_ReadReg
************************************************************************/
uint8_t A7128_ReadReg(uint8_t addr)
{
	uint8_t tx[2];
 
	A7128_SCS_Low();
	tx[0]= addr|0x40; //bit cmd=0,r/w=1
	HAL_SPI_TransmitReceive(&A7128SPI,tx,tx,2,100);
 	A7128_SCS_High();
	return tx[1];
}
/************************************************************************
**  ByteSend
************************************************************************/
// void A7128_ByteSend(uint8_t src)
// {
// 	uint8_t i;
// 
// 	for(i = 0; i < 8; i++)
// 	{
// 		if((src & 0x80)!=0x00)
// 			A7128_SDIO_High();
// 		else
// 			A7128_SDIO_Low();
// 
// 		A7128_SCK_High(); 
// 		nop();
// 		nop();
// 		A7128_SCK_Low();
// 		src = src << 1;
// 	}
// }

/************************************************************************
**  ByteRead
************************************************************************/
// uint8_t A7128_ByteRead(void)
// {
// 	uint8_t i,tmp;
// 
// 	A7128_SDIO_IN();
// 	for(i = 0; i < 8; i++)
// 	{
// 		if(A7128_SDIO_Read()==1)
// 			tmp = (tmp << 1) | 0x01;
// 		else
// 			tmp = tmp << 1;
// 
// 		A7128_SCK_High(); 
// 		nop();
// 		nop();
// 		A7128_SCK_Low(); 
// 	}
// 	A7128_SDIO_OUT();
// 	return tmp;
// }


