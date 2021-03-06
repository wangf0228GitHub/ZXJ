#include "lcd.h"
#include "string.h"
#include "font.h" 
#include "wfSys.h"
#include "gui.h"
#include "wfDefine.h"
#include "Variables.h"


void GUI_ShowGraphicsI(float I)
{
	uint8_t sIndex;
	uint16_t x2,f;
	int y2;
	I=I+2.505;
	I=I*10;	
	sIndex=I;
	x2=ScalePoint[sIndex+1][2]-ScalePoint[sIndex][2];
	y2=ScalePoint[sIndex+1][3]-ScalePoint[sIndex][3];
	I=I*10;
	f=I;
	if(f==oldI)
		return;
	oldI=f;
	f=f%10;
	x2=x2*f;
	x2=x2+5;
	x2=x2/10;

	y2=y2*f;
	y2=y2+5;
	y2=y2/10;
	LCD_DrawLine_GoBack(oldLine[0],oldLine[1],oldLine[2],oldLine[3]);
	POINT_COLOR=COLOR_RED;
	LCD_DrawLine(ScalePoint[sIndex][0],ScalePoint[sIndex][1],ScalePoint[sIndex][2]+x2,ScalePoint[sIndex][3]+y2);
}
void GUI_ShowNumI(float I)
{
	uint16_t x[4];
	if(I>0)
	{
		Gui_Drawbmp16(184,185,23,33,gImage_NumNull);
	}
	else
	{
		Gui_Drawbmp16(184,185,23,33,gImage_NumSign);
		I=-I;
	}
	x[0]=I;
	x[3]=x[0]/1000;
	x[0]=x[0]%1000;
	x[2]=x[0]/100;
	x[0]=x[0]%100;
	x[1]=x[0]/10;
	x[0]=x[0]%10;
	Gui_Drawbmp16(184+23*1,185,23,33,NumPList[x[3]]);
	Gui_Drawbmp16(184+23*2,185,23,33,NumList[x[2]]);
	Gui_Drawbmp16(184+23*3,185,23,33,NumList[x[1]]);
	Gui_Drawbmp16(184+23*4,185,23,33,NumList[x[0]]);
}
//******************************************************************
//函数名：  GUI_DrawPoint
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    GUI描绘一个点
//输入参数：x:光标位置x坐标
//        	y:光标位置y坐标
//			color:要填充的颜色
//返回值：  无
//修改记录：无
//******************************************************************
void GUI_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_SetCursor(x,y);//设置光标位置 
	LCD_DrawPoint_16Bit(color); 
}

//******************************************************************
//函数名：  LCD_Fill
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    在指定区域内填充颜色
//输入参数：sx:指定区域开始点x坐标
//        	sy:指定区域开始点y坐标
//			ex:指定区域结束点x坐标
//			ey:指定区域结束点y坐标
//        	color:要填充的颜色
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{  	

	uint16_t i,j;			
	uint16_t width=ex-sx+1; 		//得到填充的宽度
	uint16_t height=ey-sy+1;		//高度
	LCD_SetWindows(sx,sy,ex-1,ey-1);//设置显示窗口

#if LCD_USE8BIT_MODEL==1
	LCD_RS_SET;//写数据 
	LCD_CS_CLR;	   
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			DATAOUT(color);	
			LCD_WR_CLR;
			LCD_WR_SET;	
			
			DATAOUT(color<<8);	
			LCD_WR_CLR;
			LCD_WR_SET;	
		}   
	}
	LCD_CS_SET;	
#else //16位模式
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		LCD_WR_DATA(color);	//写入数据 	 
	}
#endif
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口设置为全屏
}

//******************************************************************
//函数名：  LCD_DrawLine
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    GUI画线
//输入参数：x1,y1:起点坐标
//        	x2,y2:终点坐标 
//返回值：  无
//修改记录：无
//****************************************************************** 
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	oldLine[0]=x1;
	oldLine[1]=y1;
	oldLine[2]=x2;
	oldLine[3]=y2;

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 
void LCD_DrawLine_GoBack(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t,color;
	uint32_t index;
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		//LCD_DrawPoint(uRow,uCol);//画点 
		LCD_SetCursor(uRow,uCol);//设置光标位置
// 		if(uCol<160)
// 		{
			index=uCol*960+uRow*2;			
			color=MAKE_SHORT(gImage_pic[index+1],gImage_pic[index]);
// 		}
// 		else
// 		{
// 			color=COLOR_BLACK;
// 		}
		LCD_WR_DATA(color); 
		
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}
//******************************************************************
//函数名：  LCD_DrawRectangle
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    GUI画矩形(非填充)
//输入参数：(x1,y1),(x2,y2):矩形的对角坐标
//返回值：  无
//修改记录：无
//******************************************************************  
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}  

//******************************************************************
//函数名：  LCD_DrawFillRectangle
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    GUI画矩形(填充)
//输入参数：(x1,y1),(x2,y2):矩形的对角坐标
//返回值：  无
//修改记录：无
//******************************************************************   
void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_Fill(x1,y1,x2,y2,POINT_COLOR);

}
 
//******************************************************************
//函数名：  _draw_circle_8
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    8对称性画圆算法(内部调用)
//输入参数：(xc,yc) :圆中心坐标
// 			(x,y):光标相对于圆心的坐标
//         	c:填充的颜色
//返回值：  无
//修改记录：无
//******************************************************************  
void _draw_circle_8(int xc, int yc, int x, int y, uint16_t c)
{
	GUI_DrawPoint(xc + x, yc + y, c);

	GUI_DrawPoint(xc - x, yc + y, c);

	GUI_DrawPoint(xc + x, yc - y, c);

	GUI_DrawPoint(xc - x, yc - y, c);

	GUI_DrawPoint(xc + y, yc + x, c);

	GUI_DrawPoint(xc - y, yc + x, c);

	GUI_DrawPoint(xc + y, yc - x, c);

	GUI_DrawPoint(xc - y, yc - x, c);
}

//******************************************************************
//函数名：  gui_circle
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    在指定位置画一个指定大小的圆(填充)
//输入参数：(xc,yc) :圆中心坐标
//         	c:填充的颜色
//		 	r:圆半径
//		 	fill:填充判断标志，1-填充，0-不填充
//返回值：  无
//修改记录：无
//******************************************************************  
void gui_circle(int xc, int yc,uint16_t c,int r, int fill)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		// 如果填充（画实心圆）
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// 如果不填充（画空心圆）
		while (x <= y) {
			_draw_circle_8(xc, yc, x, y, c);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

//******************************************************************
//函数名：  LCD_ShowChar
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示单个英文字符
//输入参数：(x,y):字符显示位置起始坐标
//        	fc:前置画笔颜色
//			bc:背景颜色
//			num:数值（0-94）
//			size:字体大小
//			mode:模式  0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************  
// void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode)
// {  
//     uint8_t temp;
//     uint8_t pos,t;
// 	uint16_t colortemp=POINT_COLOR;      
// 		   
// 	num=num-' ';//得到偏移后的值
// 	LCD_SetWindows(x,y,x+size/2-1,y+size-1);//设置单个文字显示窗口
// 	if(!mode) //非叠加方式
// 	{
// 		
// 		for(pos=0;pos<size;pos++)
// 		{
// 			if(size==12)temp=asc2_1206[num][pos];//调用1206字体
// 			else temp=asc2_1608[num][pos];		 //调用1608字体
// 			for(t=0;t<size/2;t++)
// 		    {                 
// 		        if(temp&0x01)LCD_DrawPoint_16Bit(fc); 
// 				else LCD_DrawPoint_16Bit(bc); 
// 				temp>>=1; 
// 				
// 		    }
// 			
// 		}	
// 	}else//叠加方式
// 	{
// 		for(pos=0;pos<size;pos++)
// 		{
// 			if(size==12)temp=asc2_1206[num][pos];//调用1206字体
// 			else temp=asc2_1608[num][pos];		 //调用1608字体
// 			for(t=0;t<size/2;t++)
// 		    {   
// 				POINT_COLOR=fc;              
// 		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点    
// 		        temp>>=1; 
// 		    }
// 		}
// 	}
// 	POINT_COLOR=colortemp;	
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏    	   	 	  
// } 
//******************************************************************
//函数名：  LCD_ShowString
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示英文字符串
//输入参数：x,y :起点坐标	 
//			size:字体大小
//			*p:字符串起始地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************  	  
// void LCD_ShowString(uint16_t x,uint16_t y,uint8_t size,uint8_t *p,uint8_t mode)
// {         
//     while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
//     {   
// 		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
// 		return;     
//         LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
//         x+=size/2;
//         p++;
//     }  
// } 

//******************************************************************
//函数名：  mypow
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    求m的n次方(gui内部调用)
//输入参数：m:乘数
//	        n:幂
//返回值：  m的n次方
//修改记录：无
//******************************************************************  
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}

//******************************************************************
//函数名：  LCD_ShowNum
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示单个数字变量值
//输入参数：x,y :起点坐标	 
//			len :指定显示数字的位数
//			size:字体大小(12,16)
//			color:颜色
//			num:数值(0~4294967295)
//返回值：  无
//修改记录：无
//******************************************************************  			 
// void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
// {         	
// 	uint8_t t,temp;
// 	uint8_t enshow=0;						   
// 	for(t=0;t<len;t++)
// 	{
// 		temp=(num/mypow(10,len-t-1))%10;
// 		if(enshow==0&&t<(len-1))
// 		{
// 			if(temp==0)
// 			{
// 				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0);
// 				continue;
// 			}else enshow=1; 
// 		 	 
// 		}
// 	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0); 
// 	}
// } 

//******************************************************************
//函数名：  GUI_DrawFont16
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示单个16X16中文字体
//输入参数：x,y :起点坐标
//			fc:前置画笔颜色
//			bc:背景颜色	 
//			s:字符串地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************
// void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
// {
// 	uint8_t i,j;
// 	uint16_t k;
// 	uint16_t HZnum;
// 	uint16_t x0=x;
// 	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//自动统计汉字数目
// 	
// 			
// 	for (k=0;k<HZnum;k++) 
// 	{
// 	  if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
// 	  { 	LCD_SetWindows(x,y,x+16-1,y+16-1);
// 		    for(i=0;i<16*2;i++)
// 		    {
// 				for(j=0;j<8;j++)
// 		    	{	
// 					if(!mode) //非叠加方式
// 					{
// 						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint_16Bit(fc);
// 						else LCD_DrawPoint_16Bit(bc);
// 					}
// 					else
// 					{
// 						POINT_COLOR=fc;
// 						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//画一个点
// 						x++;
// 						if((x-x0)==16)
// 						{
// 							x=x0;
// 							y++;
// 							break;
// 						}
// 					}
// 
// 				}
// 				
// 			}
// 			
// 			
// 		}				  	
// 		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
// 	}
// 
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
// } 

//******************************************************************
//函数名：  GUI_DrawFont24
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示单个24X24中文字体
//输入参数：x,y :起点坐标
//			fc:前置画笔颜色
//			bc:背景颜色	 
//			s:字符串地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************
// void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
// {
// 	uint8_t i,j;
// 	uint16_t k;
// 	uint16_t HZnum;
// 	uint16_t x0=x;
// 	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//自动统计汉字数目
// 		
// 			for (k=0;k<HZnum;k++) 
// 			{
// 			  if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
// 			  { 	LCD_SetWindows(x,y,x+24-1,y+24-1);
// 				    for(i=0;i<24*3;i++)
// 				    {
// 							for(j=0;j<8;j++)
// 							{
// 								if(!mode) //非叠加方式
// 								{
// 									if(tfont24[k].Msk[i]&(0x80>>j))	LCD_DrawPoint_16Bit(fc);
// 									else LCD_DrawPoint_16Bit(bc);
// 								}
// 							else
// 							{
// 								POINT_COLOR=fc;
// 								if(tfont24[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//画一个点
// 								x++;
// 								if((x-x0)==24)
// 								{
// 									x=x0;
// 									y++;
// 									break;
// 								}
// 							}
// 						}
// 					}
// 					
// 					
// 				}				  	
// 				continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
// 			}
// 
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
// }

//******************************************************************
//函数名：  GUI_DrawFont32
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示单个32X32中文字体
//输入参数：x,y :起点坐标
//			fc:前置画笔颜色
//			bc:背景颜色	 
//			s:字符串地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//****************************************************************** 
// void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
// {
// 	uint8_t i,j;
// 	uint16_t k;
// 	uint16_t HZnum;
// 	uint16_t x0=x;
// 	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//自动统计汉字数目
// 	for (k=0;k<HZnum;k++) 
// 			{
// 			  if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
// 			  { 	LCD_SetWindows(x,y,x+32-1,y+32-1);
// 				    for(i=0;i<32*4;i++)
// 				    {
// 						for(j=0;j<8;j++)
// 				    	{
// 							if(!mode) //非叠加方式
// 							{
// 								if(tfont32[k].Msk[i]&(0x80>>j))	LCD_DrawPoint_16Bit(fc);
// 								else LCD_DrawPoint_16Bit(bc);
// 							}
// 							else
// 							{
// 								POINT_COLOR=fc;
// 								if(tfont32[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//画一个点
// 								x++;
// 								if((x-x0)==32)
// 								{
// 									x=x0;
// 									y++;
// 									break;
// 								}
// 							}
// 						}
// 					}
// 					
// 					
// 				}				  	
// 				continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
// 			}
// 	
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
// } 

//******************************************************************
//函数名：  Show_Str
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示一个字符串,包含中英文显示
//输入参数：x,y :起点坐标
// 			fc:前置画笔颜色
//			bc:背景颜色
//			str :字符串	 
//			size:字体大小
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************    	   		   
// void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
// {					
// 	uint16_t x0=x;							  	  
//   	uint8_t bHz=0;     //字符或者中文 
//     while(*str!=0)//数据未结束
//     { 
//         if(!bHz)
//         {
// 			if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) 
// 			return; 
// 	        if(*str>0x80)bHz=1;//中文 
// 	        else              //字符
// 	        {          
// 		        if(*str==0x0D)//换行符号
// 		        {         
// 		            y+=size;
// 					x=x0;
// 		            str++; 
// 		        }  
// 		        else
// 				{
// 					if(size>16)//字库中没有集成12X24 16X32的英文字体,用8X16代替
// 					{  
// 					LCD_ShowChar(x,y,fc,bc,*str,16,mode);
// 					x+=8; //字符,为全字的一半 
// 					}
// 					else
// 					{
// 					LCD_ShowChar(x,y,fc,bc,*str,size,mode);
// 					x+=size/2; //字符,为全字的一半 
// 					}
// 				} 
// 				str++; 
// 		        
// 	        }
//         }else//中文 
//         {   
// 			if(x>(lcddev.width-size)||y>(lcddev.height-size)) 
// 			return;  
//             bHz=0;//有汉字库    
// 			if(size==32)
// 			GUI_DrawFont32(x,y,fc,bc,str,mode);	 	
// 			else if(size==24)
// 			GUI_DrawFont24(x,y,fc,bc,str,mode);	
// 			else
// 			GUI_DrawFont16(x,y,fc,bc,str,mode);
// 				
// 	        str+=2; 
// 	        x+=size;//下一个汉字偏移	    
//         }						 
//     }   
// }

//******************************************************************
//函数名：  Gui_StrCenter
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    居中显示一个字符串,包含中英文显示
//输入参数：x,y :起点坐标
// 			fc:前置画笔颜色
//			bc:背景颜色
//			str :字符串	 
//			size:字体大小
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************   
// void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
// {
// 	uint16_t len=strlen((const char *)str);
// 	uint16_t x1=(lcddev.width-len*8)/2;
// 	Show_Str(x+x1,y,fc,bc,str,size,mode);
// } 
 
//******************************************************************
//函数名：  Gui_Drawbmp16
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示一副16位BMP图像
//输入参数：x,y :起点坐标
// 			*p :图像数组起始地址
//返回值：  无
//修改记录：无
//******************************************************************  
void Gui_Drawbmp16(uint16_t x,uint16_t y,uint16_t w,uint16_t h,const unsigned char *p) //显示40*40 QQ图片
{
  	uint32_t i,j,k; 
	unsigned char picH,picL; 
	uint16_t pic;
	LCD_SetWindows(x,y,x+w-1,y+h-1);//窗口设置
	k=0;
	for(i=0;i<w*h;i++)
	{
		picL=*(p+i*2);	
		picH=*(p+i*2+1);

		LCD_DrawPoint_16Bit(picH<<8|picL);
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复显示窗口为全屏
}