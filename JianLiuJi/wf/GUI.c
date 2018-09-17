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
		Gui_Drawbmp16(198,184,16,24,gImage_NumNull);
	}
	else
	{
		Gui_Drawbmp16(198,184,16,24,gImage_NumSign);
		I=-I;
	}
	x[0]=I;
	x[3]=x[0]/1000;
	x[0]=x[0]%1000;
	x[2]=x[0]/100;
	x[0]=x[0]%100;
	x[1]=x[0]/10;
	x[0]=x[0]%10;
	Gui_Drawbmp16(198+16,184,16,24,NumPList[x[3]]);
	Gui_Drawbmp16(198+32,184,16,24,NumList[x[2]]);
	Gui_Drawbmp16(198+48,184,16,24,NumList[x[1]]);
	Gui_Drawbmp16(198+64,184,16,24,NumList[x[0]]);
}
//******************************************************************
//��������  GUI_DrawPoint
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    GUI���һ����
//���������x:���λ��x����
//        	y:���λ��y����
//			color:Ҫ������ɫ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void GUI_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_SetCursor(x,y);//���ù��λ�� 
	LCD_DrawPoint_16Bit(color); 
}

//******************************************************************
//��������  LCD_Fill
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ָ�������������ɫ
//���������sx:ָ������ʼ��x����
//        	sy:ָ������ʼ��y����
//			ex:ָ�����������x����
//			ey:ָ�����������y����
//        	color:Ҫ������ɫ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{  	

	uint16_t i,j;			
	uint16_t width=ex-sx+1; 		//�õ����Ŀ���
	uint16_t height=ey-sy+1;		//�߶�
	LCD_SetWindows(sx,sy,ex-1,ey-1);//������ʾ����

#if LCD_USE8BIT_MODEL==1
	LCD_RS_SET;//д���� 
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
#else //16λģʽ
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		LCD_WR_DATA(color);	//д������ 	 
	}
#endif
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ���������Ϊȫ��
}

//******************************************************************
//��������  LCD_DrawLine
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    GUI����
//���������x1,y1:�������
//        	x2,y2:�յ����� 
//����ֵ��  ��
//�޸ļ�¼����
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

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
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

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		//LCD_DrawPoint(uRow,uCol);//���� 
		LCD_SetCursor(uRow,uCol);//���ù��λ��
		if(uCol<160)
		{
			index=uCol*960+uRow*2;			
			color=MAKE_SHORT(gImage_pic[index+1],gImage_pic[index]);
		}
		else
		{
			color=COLOR_BLACK;
		}
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
//��������  LCD_DrawRectangle
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    GUI������(�����)
//���������(x1,y1),(x2,y2):���εĶԽ�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}  

//******************************************************************
//��������  LCD_DrawFillRectangle
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    GUI������(���)
//���������(x1,y1),(x2,y2):���εĶԽ�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************   
void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_Fill(x1,y1,x2,y2,POINT_COLOR);

}
 
//******************************************************************
//��������  _draw_circle_8
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    8�Գ��Ի�Բ�㷨(�ڲ�����)
//���������(xc,yc) :Բ��������
// 			(x,y):��������Բ�ĵ�����
//         	c:������ɫ
//����ֵ��  ��
//�޸ļ�¼����
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
//��������  gui_circle
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ָ��λ�û�һ��ָ����С��Բ(���)
//���������(xc,yc) :Բ��������
//         	c:������ɫ
//		 	r:Բ�뾶
//		 	fill:����жϱ�־��1-��䣬0-�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void gui_circle(int xc, int yc,uint16_t c,int r, int fill)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		// �����䣨��ʵ��Բ��
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
		// �������䣨������Բ��
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
//��������  LCD_ShowChar
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾ����Ӣ���ַ�
//���������(x,y):�ַ���ʾλ����ʼ����
//        	fc:ǰ�û�����ɫ
//			bc:������ɫ
//			num:��ֵ��0-94��
//			size:�����С
//			mode:ģʽ  0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
// void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode)
// {  
//     uint8_t temp;
//     uint8_t pos,t;
// 	uint16_t colortemp=POINT_COLOR;      
// 		   
// 	num=num-' ';//�õ�ƫ�ƺ��ֵ
// 	LCD_SetWindows(x,y,x+size/2-1,y+size-1);//���õ���������ʾ����
// 	if(!mode) //�ǵ��ӷ�ʽ
// 	{
// 		
// 		for(pos=0;pos<size;pos++)
// 		{
// 			if(size==12)temp=asc2_1206[num][pos];//����1206����
// 			else temp=asc2_1608[num][pos];		 //����1608����
// 			for(t=0;t<size/2;t++)
// 		    {                 
// 		        if(temp&0x01)LCD_DrawPoint_16Bit(fc); 
// 				else LCD_DrawPoint_16Bit(bc); 
// 				temp>>=1; 
// 				
// 		    }
// 			
// 		}	
// 	}else//���ӷ�ʽ
// 	{
// 		for(pos=0;pos<size;pos++)
// 		{
// 			if(size==12)temp=asc2_1206[num][pos];//����1206����
// 			else temp=asc2_1608[num][pos];		 //����1608����
// 			for(t=0;t<size/2;t++)
// 		    {   
// 				POINT_COLOR=fc;              
// 		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����    
// 		        temp>>=1; 
// 		    }
// 		}
// 	}
// 	POINT_COLOR=colortemp;	
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��    	   	 	  
// } 
//******************************************************************
//��������  LCD_ShowString
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾӢ���ַ���
//���������x,y :�������	 
//			size:�����С
//			*p:�ַ�����ʼ��ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  	  
// void LCD_ShowString(uint16_t x,uint16_t y,uint8_t size,uint8_t *p,uint8_t mode)
// {         
//     while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
//     {   
// 		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
// 		return;     
//         LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
//         x+=size/2;
//         p++;
//     }  
// } 

//******************************************************************
//��������  mypow
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��m��n�η�(gui�ڲ�����)
//���������m:����
//	        n:��
//����ֵ��  m��n�η�
//�޸ļ�¼����
//******************************************************************  
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}

//******************************************************************
//��������  LCD_ShowNum
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾ�������ֱ���ֵ
//���������x,y :�������	 
//			len :ָ����ʾ���ֵ�λ��
//			size:�����С(12,16)
//			color:��ɫ
//			num:��ֵ(0~4294967295)
//����ֵ��  ��
//�޸ļ�¼����
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
//��������  GUI_DrawFont16
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾ����16X16��������
//���������x,y :�������
//			fc:ǰ�û�����ɫ
//			bc:������ɫ	 
//			s:�ַ�����ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
// void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
// {
// 	uint8_t i,j;
// 	uint16_t k;
// 	uint16_t HZnum;
// 	uint16_t x0=x;
// 	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//�Զ�ͳ�ƺ�����Ŀ
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
// 					if(!mode) //�ǵ��ӷ�ʽ
// 					{
// 						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint_16Bit(fc);
// 						else LCD_DrawPoint_16Bit(bc);
// 					}
// 					else
// 					{
// 						POINT_COLOR=fc;
// 						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//��һ����
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
// 		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
// 	}
// 
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��  
// } 

//******************************************************************
//��������  GUI_DrawFont24
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾ����24X24��������
//���������x,y :�������
//			fc:ǰ�û�����ɫ
//			bc:������ɫ	 
//			s:�ַ�����ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
// void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
// {
// 	uint8_t i,j;
// 	uint16_t k;
// 	uint16_t HZnum;
// 	uint16_t x0=x;
// 	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//�Զ�ͳ�ƺ�����Ŀ
// 		
// 			for (k=0;k<HZnum;k++) 
// 			{
// 			  if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
// 			  { 	LCD_SetWindows(x,y,x+24-1,y+24-1);
// 				    for(i=0;i<24*3;i++)
// 				    {
// 							for(j=0;j<8;j++)
// 							{
// 								if(!mode) //�ǵ��ӷ�ʽ
// 								{
// 									if(tfont24[k].Msk[i]&(0x80>>j))	LCD_DrawPoint_16Bit(fc);
// 									else LCD_DrawPoint_16Bit(bc);
// 								}
// 							else
// 							{
// 								POINT_COLOR=fc;
// 								if(tfont24[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//��һ����
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
// 				continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
// 			}
// 
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��  
// }

//******************************************************************
//��������  GUI_DrawFont32
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾ����32X32��������
//���������x,y :�������
//			fc:ǰ�û�����ɫ
//			bc:������ɫ	 
//			s:�ַ�����ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
// void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
// {
// 	uint8_t i,j;
// 	uint16_t k;
// 	uint16_t HZnum;
// 	uint16_t x0=x;
// 	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//�Զ�ͳ�ƺ�����Ŀ
// 	for (k=0;k<HZnum;k++) 
// 			{
// 			  if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
// 			  { 	LCD_SetWindows(x,y,x+32-1,y+32-1);
// 				    for(i=0;i<32*4;i++)
// 				    {
// 						for(j=0;j<8;j++)
// 				    	{
// 							if(!mode) //�ǵ��ӷ�ʽ
// 							{
// 								if(tfont32[k].Msk[i]&(0x80>>j))	LCD_DrawPoint_16Bit(fc);
// 								else LCD_DrawPoint_16Bit(bc);
// 							}
// 							else
// 							{
// 								POINT_COLOR=fc;
// 								if(tfont32[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//��һ����
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
// 				continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
// 			}
// 	
// 	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��  
// } 

//******************************************************************
//��������  Show_Str
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾһ���ַ���,������Ӣ����ʾ
//���������x,y :�������
// 			fc:ǰ�û�����ɫ
//			bc:������ɫ
//			str :�ַ���	 
//			size:�����С
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************    	   		   
// void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
// {					
// 	uint16_t x0=x;							  	  
//   	uint8_t bHz=0;     //�ַ��������� 
//     while(*str!=0)//����δ����
//     { 
//         if(!bHz)
//         {
// 			if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) 
// 			return; 
// 	        if(*str>0x80)bHz=1;//���� 
// 	        else              //�ַ�
// 	        {          
// 		        if(*str==0x0D)//���з���
// 		        {         
// 		            y+=size;
// 					x=x0;
// 		            str++; 
// 		        }  
// 		        else
// 				{
// 					if(size>16)//�ֿ���û�м���12X24 16X32��Ӣ������,��8X16����
// 					{  
// 					LCD_ShowChar(x,y,fc,bc,*str,16,mode);
// 					x+=8; //�ַ�,Ϊȫ�ֵ�һ�� 
// 					}
// 					else
// 					{
// 					LCD_ShowChar(x,y,fc,bc,*str,size,mode);
// 					x+=size/2; //�ַ�,Ϊȫ�ֵ�һ�� 
// 					}
// 				} 
// 				str++; 
// 		        
// 	        }
//         }else//���� 
//         {   
// 			if(x>(lcddev.width-size)||y>(lcddev.height-size)) 
// 			return;  
//             bHz=0;//�к��ֿ�    
// 			if(size==32)
// 			GUI_DrawFont32(x,y,fc,bc,str,mode);	 	
// 			else if(size==24)
// 			GUI_DrawFont24(x,y,fc,bc,str,mode);	
// 			else
// 			GUI_DrawFont16(x,y,fc,bc,str,mode);
// 				
// 	        str+=2; 
// 	        x+=size;//��һ������ƫ��	    
//         }						 
//     }   
// }

//******************************************************************
//��������  Gui_StrCenter
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ������ʾһ���ַ���,������Ӣ����ʾ
//���������x,y :�������
// 			fc:ǰ�û�����ɫ
//			bc:������ɫ
//			str :�ַ���	 
//			size:�����С
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************   
// void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
// {
// 	uint16_t len=strlen((const char *)str);
// 	uint16_t x1=(lcddev.width-len*8)/2;
// 	Show_Str(x+x1,y,fc,bc,str,size,mode);
// } 
 
//******************************************************************
//��������  Gui_Drawbmp16
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʾһ��16λBMPͼ��
//���������x,y :�������
// 			*p :ͼ��������ʼ��ַ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void Gui_Drawbmp16(uint16_t x,uint16_t y,uint16_t w,uint16_t h,const unsigned char *p) //��ʾ40*40 QQͼƬ
{
  	uint32_t i,j,k; 
	unsigned char picH,picL; 
	uint16_t pic;
	LCD_SetWindows(x,y,x+w-1,y+h-1);//��������
	k=0;
	for(i=0;i<w*h;i++)
	{
		picL=*(p+i*2);	
		picH=*(p+i*2+1);

		LCD_DrawPoint_16Bit(picH<<8|picL);
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ���ʾ����Ϊȫ��
}