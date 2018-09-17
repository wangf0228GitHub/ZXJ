﻿#include "lcd.h"
#include "stdlib.h" 
#include "wfSys.h"
#include "wfDefine.h"
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RZET6,正点原子MiniSTM32开发板,主频72MHZ
//中景园液晶驱动 for STM32 IO模拟
//淘宝网站：https://shop73023976.taobao.com/?spm=2013.1.1000126.d21.dSpP3S
//我司提供技术支持，任何技术问题欢迎随时交流学习
//技术交流QQ群:2534656669
//创建日期:2015/5/5
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 中景园电子
//All rights reserved
//All rights reserved
/****************************************************************************************************
//=======================================液晶屏数据线接线==========================================//
STM32 PB组接液晶屏DB0~DB15,举例依次为DB0接PB0,..DB15接PB15.   
//=======================================液晶屏控制线接线==========================================//
//LCD_CS	接PC9	//片选信号
//LCD_RS	接PC8	//寄存器/数据选择信号
//LCD_WR	接PC7	//写信号
//LCD_RD	接PC6	//读信号
//LCD_RST	接PC5	//复位信号
//LCD_LED	接PC10	//背光控制信号(高电平点亮)

**************************************************************************************************/	
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
uint16_t  POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
uint16_t  DeviceCode;	


//******************************************************************
//函数名：  LCD_WR_REG
//作者：   中景园电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位指令
//输入参数：Reg:待写入的指令值
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_REG(uint8_t data)
{ 
#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
	LCD_RS_CLR;
	LCD_CS_CLR;
	DATAOUT(data<<8);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
	
#else//使用16位并行数据总线模式
	LCD_RS_CLR;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
			
#endif	
}

//******************************************************************
//函数名：  LCD_WR_DATA
//作者：   中景园电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位数据
//输入参数：Data:待写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_DATA(uint16_t  data)
{
#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data<<8);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
	
#else//使用16位并行数据总线模式
	LCD_RS_SET;
	LCD_CS_CLR;
	LCD_RD_SET;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;			
#endif
}
//******************************************************************
//函数名：  LCD_DrawPoint_16Bit
//作者：   中景园电子
//日期：    2013-02-22
//功能：    8位总线下如何写入一个16位数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint_16Bit(uint16_t  color)
{
#if LCD_USE8BIT_MODEL==1
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;//写地址  	 
	DATAOUT(color);	
	LCD_WR_CLR;
	LCD_WR_SET;	
	DATAOUT(color<<8);	
	LCD_WR_CLR;
	LCD_WR_SET;	 
	LCD_CS_SET;
#else
	LCD_WR_DATA(color); 
#endif

}

//******************************************************************
//函数名：  LCD_WriteReg
//作者：   中景园电子
//日期：    2013-02-22
//功能：    写寄存器数据
//输入参数：LCD_Reg:寄存器地址
//			LCD_RegValue:要写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t  LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}	   
	 
//******************************************************************
//函数名：  LCD_WriteRAM_Prepare
//作者：   中景园电子
//日期：    2013-02-22
//功能：    开始写GRAM
//			在给液晶屏传送RGB数据前，应该发送写GRAM指令
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

//******************************************************************
//函数名：  LCD_DrawPoint
//作者：   中景园电子
//日期：    2013-02-22
//功能：    在指定位置写入一个像素点数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint(uint16_t  x,uint16_t  y)
{
	LCD_SetCursor(x,y);//设置光标位置 
#if LCD_USE8BIT_MODEL==1
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;//写地址  	 
	DATAOUT(POINT_COLOR);	
	LCD_WR_CLR;
	LCD_WR_SET;	
	DATAOUT(POINT_COLOR<<8);	
	LCD_WR_CLR;
	LCD_WR_SET;	 
	LCD_CS_SET;
#else
	LCD_WR_DATA(POINT_COLOR); 
#endif


}

//******************************************************************
//函数名：  LCD_Clear
//作者：   中景园电子
//日期：    2013-02-22
//功能：    LCD全屏填充清屏函数
//输入参数：Color:要清屏的填充色
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Clear(uint16_t  Color)
{
	uint32_t index=0;      
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
#if LCD_USE8BIT_MODEL==1
	LCD_RS_SET;//写数据 
	LCD_CS_CLR;	   
	for(index=0;index<lcddev.width*lcddev.height;index++)
	{
		DATAOUT(Color);	
		LCD_WR_CLR;
		LCD_WR_SET;	
		
		DATAOUT(Color<<8);	
		LCD_WR_CLR;
		LCD_WR_SET;	   
	}
	LCD_CS_SET;	
#else //16位模式
	for(index=0;index<lcddev.width*lcddev.height;index++)
	{
		LCD_WR_DATA(Color);		  
	}
#endif
	
} 

//******************************************************************
//函数名：  LCD_Reset
//作者：   中景园电子
//日期：    2013-02-22
//功能：    LCD复位函数，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_RESET(void)
{
	//HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	LCD_RST_CLR;
	wfDelay_ms(100);	
	LCD_RST_SET;
	//HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
	wfDelay_ms(50);
}
 	 
//******************************************************************
//函数名：  LCD_Init
//作者：   中景园电子
//日期：    2013-02-22
//功能：    LCD初始化
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Init(void)
{
 	LCD_RESET();
	//************* Start Initial Sequence **********//		
	LCD_WR_REG(0XF1);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x8F);

	LCD_WR_REG(0XF2);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0xA3);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0xB2);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0XF8);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x04);

	LCD_WR_REG(0XF9);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x08);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x44);
	LCD_WR_DATA(0x77);
	LCD_WR_DATA(0x38);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0XE1);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x3B);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x53);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x3D);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x23);
	LCD_WR_DATA(0x1F);
	LCD_WR_DATA(0x0F);

	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x08);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55); // 8bit,16bit=0x55 18bit=0x66

	LCD_WR_REG(0XB1);    // Frame rate 70Hz b0 11
	LCD_WR_DATA(0xB0);
	LCD_WR_DATA(0x11); 

	LCD_WR_REG(0XB4);
	LCD_WR_DATA(0x02);

	LCD_WR_REG(0XB6);
	LCD_WR_DATA(0x00);  //MCU:0x02  RGB:0x22
	LCD_WR_DATA(0x42);  // rotate 180 degree 0x42
	LCD_WR_DATA(0x3B);

	LCD_WR_REG(0XB7);
	LCD_WR_DATA(0xC6);

	LCD_WR_REG(0XC0);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x05);

	LCD_WR_REG(0XC1);
	LCD_WR_DATA(0x41);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0XC2);
	LCD_WR_DATA(0x22);

	LCD_WR_REG(0XC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x31);  // Adjust Flicker
	LCD_WR_DATA(0x80); 

	LCD_WR_REG(0x11);
	wfDelay_ms(120);
	LCD_WR_REG(0x29);

	LCD_SetParam(); 
	HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_SET);//点亮背光	 
	LCD_Clear(COLOR_BLACK);
}
  		  
/*************************************************
函数名：LCD_SetWindows
功能：设置lcd显示窗口，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void LCD_SetWindows(uint16_t  xStar, uint16_t  yStar,uint16_t  xEnd,uint16_t  yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd); 

	LCD_WriteRAM_Prepare();	//开始写入GRAM				
}   

/*************************************************
函数名：LCD_SetCursor
功能：设置光标位置
入口参数：xy坐标
返回值：无
*************************************************/
void LCD_SetCursor(uint16_t  Xpos, uint16_t  Ypos)
{	  	    			
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(Xpos>>8);
	LCD_WR_DATA(0x00FF&Xpos);		
	LCD_WR_DATA(0x0001);
	LCD_WR_DATA(0x003F);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(Ypos>>8);
	LCD_WR_DATA(0x00FF&Ypos);		
	LCD_WR_DATA(0x0001);
	LCD_WR_DATA(0x00Df);	

	LCD_WriteRAM_Prepare();	//开始写入GRAM	
} 

//设置LCD参数
//方便进行横竖屏模式切换
void LCD_SetParam(void)
{ 	
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//Ê¹ÓÃºáÆÁ	  
	lcddev.dir=1;//ºáÆÁ
	lcddev.width=480;
	lcddev.height=320;			
	LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
#else//ÊúÆÁ
	lcddev.dir=0;//ÊúÆÁ				 	 		
	lcddev.width=320;
	lcddev.height=480;	
	LCD_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
#endif
}	


