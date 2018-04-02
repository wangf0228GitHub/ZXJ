#include "HardwareProfile.h"
#include <stdio.h>
#include "stdlib.h"
// void ProcAnimationFinish(void)
// {
// 	switch(TFTMsg.screen_id.u8H)
// 	{
// 	case 0://启动屏
// 		//切换到登录屏
// 		ScreenID=0x01;
// 		//SetTxt(0x01,0x01,"20");
// 		break;
// 	}
// }
void ProcRxFromTFT(unsigned char rx)
{
	unsigned char x;
	if(TFTFlags.bWithTFTRx==1)
		return;
	TFTMsg.All[WithTFTRxCount++]=rx;
	if(WithTFTRxCount>5)
	{
		if(TFTFlags.bLen)
		{

		}
		else 	
		{	
			x=TFTMsg.All[WithTFTRxCount-1];
			if(x==0xff)
			{
				x=TFTMsg.All[WithTFTRxCount-2];
				if(x==0xff)
				{
					x=TFTMsg.All[WithTFTRxCount-3];
					if(x==0xfc)
					{
						x=TFTMsg.All[WithTFTRxCount-4];
						if(x==0xff)
						{
							TFTFlags.bWithTFTRx=1;	
						}
					}
				}
			}
		}
		if(WithTFTRxCount>MAXWithTFTRX)
		{
			WithTFTRxCount=0;
			WithTFTNeedRxCount=0xffff;				
		}
	}
// 	else if(WithTFTRxCount==7)
// 	{
// 		WithTFTNeedRxCount=MAKE_INT(WithTFTRxList[5],WithTFTRxList[6])+9;
// 	}
// 	else if(WithTFTRxCount==4)//判断地址
// 	{
// 		//地址不符，退出当前接收状态				
// 		if(WithTFTRxList[2]!=ROMParams.UnitAddr.u8H || WithTFTRxList[3]!=ROMParams.UnitAddr.u8L)
// 		{
// 			if(WithTFTRxList[2]!=0xff || WithTFTRxList[3]!=0xff)//0xffff 广播地址
// 			{
// 				WithTFTRxCount=0;				
// 				WithTFTNeedRxCount=0xffff;
// 			}
// 		}
// 	}
// 	else if(WithTFTRxCount==2)
// 	{
// 		if(rx!=0x16)
// 		{
// 			WithTFTRxCount=0;
// 		}
//	}
	else if(WithTFTRxCount==1)
	{
		if(rx!=0xee)
		{
			WithTFTRxCount=0;
		}
	}	
}
void ShowEnterDlg(const char *content)
{	
	SetTxt(sID_EnterDlg,3,content);
	SetScreen(sID_EnterDlg);
	while(GotoScreen==sID_EnterDlg)
	{
		if(TFTFlags.bWithTFTRx)
		{
			WithTFTRxLen.u16=WithTFTRxCount-12;
			switch(TFTMsg.cmd_type)//命令字
			{
			case 0xb1://主命令		
				if(TFTMsg.ctrl_msg==0x11)
				{
					if(TFTMsg.control_type==0x10)//按钮
					{
						if(TFTMsg.screen_id.u8H==sID_EnterDlg)//"确定对话框"页面
						{
							if(TFTMsg.control_id.u8H==0x05)
							{
								//if(gFlags.bEnterDlgJump)
								SetScreen(EnterDlgReNum);	
								EndProcCommandFromTFT();
								return;
							}
						}				
					}					
				}			
				// 		else if(TFTMsg.ctrl_msg==0x27)//动画播放完成
				// 		{
				// 			ProcAnimationFinish();
				// 		}
				break;
			case 0x07://显示器复位
				//初始化显示变量
				RESET();
				//gFlags.bLCDInit=1;
				break;
			}
			EndProcCommandFromTFT();
		}
		if(OERR1)
		{
			CREN1=0;
			NOP();
			CREN1=1;
		}
		if(OERR2)
		{
			CREN2=0;
			NOP();
			CREN2=1;
		}
	}
}
void ShowQueryDlg(const char *content)
{	
	SetTxt(sID_QueryDlg,2,content);
	SetScreen(sID_QueryDlg);
	while(GotoScreen==sID_QueryDlg)
	{
		if(TFTFlags.bWithTFTRx)
		{
			WithTFTRxLen.u16=WithTFTRxCount-12;
			switch(TFTMsg.cmd_type)//命令字
			{
			case 0xb1://主命令		
				if(TFTMsg.ctrl_msg==0x11)
				{
					if(TFTMsg.control_type==0x10)//按钮
					{
						if(TFTMsg.screen_id.u8H==sID_QueryDlg)//"确定对话框"页面
						{
							if(TFTMsg.control_id.u8H==6)
							{
								//if(gFlags.bEnterDlgJump)
								SetScreen(EnterDlgReNum);	
								EndProcCommandFromTFT();
								return;
							}
							else if(TFTMsg.control_id.u8H==4)
							{
								//if(gFlags.bEnterDlgJump)
								SetScreen(QueryDlgCancelNum);	
								EndProcCommandFromTFT();
								return;
							}
						}				
					}					
				}			
				// 		else if(TFTMsg.ctrl_msg==0x27)//动画播放完成
				// 		{
				// 			ProcAnimationFinish();
				// 		}
				break;
			case 0x07://显示器复位
				//初始化显示变量
				RESET();
				//gFlags.bLCDInit=1;
				break;
			}
			EndProcCommandFromTFT();
		}
		if(OERR1)
		{
			CREN1=0;
			NOP();
			CREN1=1;
		}
		if(OERR2)
		{
			CREN2=0;
			NOP();
			CREN2=1;
		}
	}
}
void ProcCommandFromTFT_Main( void )
{	
	unsigned char i;
	WithTFTRxLen.u16=WithTFTRxCount-12;
	switch(TFTMsg.cmd_type)//命令字
	{
	case 0xb1://主命令		
		if(TFTMsg.ctrl_msg==0x11)
		{
			if(TFTMsg.control_type==0x10)//按钮
			{
				if(TFTMsg.screen_id.u8H==sID_Screen1)//首页
				{
					if(TFTMsg.control_id.u8H==4)
					{
						GotoScreen=sID_Menu;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);						
						//GetTxtFlags.bNeedGetStudent=1;
					}					
				}
				else if(TFTMsg.screen_id.u8H==sID_Menu)//"shiyan"页面
				{
					if(TFTMsg.control_id.u8H==1)//返回
					{
						GotoScreen=sID_Screen1;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
					}
 					else if(TFTMsg.control_id.u8H==4)
 					{
 						GotoScreen=sID_Print;
 					}
				}
				else if(TFTMsg.screen_id.u8H==sID_ExperimentalProject)//"shiyan"页面
				{
					if(TFTMsg.control_id.u8H==4)//普朗克常数测量
					{
						GotoScreen=sID_AutoPuLangke;						
					}
					else if(TFTMsg.control_id.u8H==6)//普朗克常数测量
					{
						GotoScreen=sID_AutoGQ;						
					}
					else if(TFTMsg.control_id.u8H==8)//普朗克常数测量
					{
						GotoScreen=sID_AutoVA;						
					}
// 					else if(TFTMsg.control_id.u8H==2)//普朗克常数测量
// 					{
// 						GotoScreen=sID_Menu;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
// 					}
				}
 				else if(TFTMsg.screen_id.u8H==sID_WIFIconfiguration)//首页
 				{
 					if(TFTMsg.control_id.u8H==4)//APK wifi
 					{
 						GotoScreen=sID_APKWifi;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
 					}	
					else if(TFTMsg.control_id.u8H==6)//APK wifi
					{
						GotoScreen=sID_wxWifi;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
					}
					else if(TFTMsg.control_id.u8H==8)//APK wifi
					{
						GotoScreen=sID_wifimima;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
					}
 				}
				else if(TFTMsg.screen_id.u8H==sID_Setting)//首页
				{
					if(TFTMsg.control_id.u8H==3)//设备参数配置
					{
						GotoScreen=sID_ParamSet;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
					}	
					else if(TFTMsg.control_id.u8H==10)//实验配置
					{
						GotoScreen=sID_ExperimentConfig;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_FactorySettings)//首页
				{
					if(TFTMsg.control_id.u8H==2)
					{
						GotoScreen=sID_hWorkCurrent;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
					}	
					else if(TFTMsg.control_id.u8H==5)
					{
						GotoScreen=sID_FuAnWorkCurrent;
// 						EndProcCommandFromTFT();						
// 						SetScreen(GotoScreen);	
					}
				}
			}					
		}			
// 		else if(TFTMsg.ctrl_msg==0x27)//动画播放完成
// 		{
// 			ProcAnimationFinish();
// 		}
		break;
	case 0x07://显示器复位
		//初始化显示变量
		RESET();
		//gFlags.bLCDInit=1;
		break;
	}
}

void EndProcCommandFromTFT( void )
{
	WithTFTRxCount=0;
	WithTFTNeedRxCount=0xffff;
	TFTFlags.AllFlag=0;
}
void SetTxt(unsigned char sID,unsigned char cID,const char* data)
{
	unsigned char i;
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x10);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);
	i=0;
	while (data[i] != '\0')                         //逐个放入缓冲区
	{
		TFTUartTx(data[i]);
		i++;
	}
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void ShowPic(unsigned char picID,unsigned int x,unsigned int y,unsigned int weight,unsigned int high)
{
	unsigned char i;
	TFTUartTx(0xee);
	TFTUartTx(0x33);
	TFTUartTx(HIGH_BYTE(x));
	TFTUartTx(LOW_BYTE(x));
	TFTUartTx(HIGH_BYTE(y));
	TFTUartTx(LOW_BYTE(y));
	TFTUartTx(0x00);
	TFTUartTx(picID);
	TFTUartTx(HIGH_BYTE(x));
	TFTUartTx(LOW_BYTE(x));
	TFTUartTx(HIGH_BYTE(y));
	TFTUartTx(LOW_BYTE(y));
	TFTUartTx(HIGH_BYTE(weight));
	TFTUartTx(LOW_BYTE(weight));
	TFTUartTx(HIGH_BYTE(high));
	TFTUartTx(LOW_BYTE(high));
	TFTUartTx(0x00);
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void GetTxt(unsigned char sID,unsigned char cID)
{
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x11);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);	
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void GetScreenID()
{
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x01);	
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void SetChar(unsigned char sID,unsigned char cID,char data)
{
	unsigned char i;
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x10);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);
	TFTUartTx(data);
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}

void SetScreen(unsigned char sID)
{
	unsigned char i;
	SetScreenRetry=SetScreenRetryMax;
	//while(SetScreenRetry!=0)
	while(1)
	{		
		TFTUartTx(0xee);
		TFTUartTx(0xb1);
		TFTUartTx(0x00);
		TFTUartTx(0x00);
		TFTUartTx(sID);
		TFTUartTx(0xff);
		TFTUartTx(0xfc);
		TFTUartTx(0xff);
		TFTUartTx(0xff);
 		__delay_20ms(2);
		EndProcCommandFromTFT();
 		TFTUartTx(0xee);
 		TFTUartTx(0xb1);
 		TFTUartTx(0x01);	
 		TFTUartTx(0xff);
 		TFTUartTx(0xfc);
 		TFTUartTx(0xff);
 		TFTUartTx(0xff);
		TempWithTFTTick=SystemTick;
		while(1)
		{
			if(TFTFlags.bWithTFTRx)
			{
				WithTFTRxLen.u16=WithTFTRxCount-12;
				if(TFTMsg.cmd_type==0xb1)//命令字
				{		
					if(TFTMsg.ctrl_msg==0x01)
					{
						if(TFTMsg.screen_id.u8H==sID)
						{							
							//if(TFTMsg.control_id.u8H==100)
							{
								EndProcCommandFromTFT();
								workScreen=sID;
								GotoScreen=workScreen;
								return;
							}
						}						
					}
				}
				EndProcCommandFromTFT();
			}
			if(GetDeltaTick(TempWithTFTTick)>5)
			{
				GetTxtRetry--;
				break;
			}
		}
	}
	//ShowEnterDlg(strSetScreenErr);
	//return 0;
}
void SetButton(unsigned char sID,unsigned char cID,unsigned char status)
{
	unsigned char i;
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x10);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);
	TFTUartTx(status);
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void SetProgress(unsigned char sID,unsigned char cID,unsigned char status)
{
	unsigned char i;
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x10);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);
	TFTUartTx(0x00);
	TFTUartTx(0x00);
	TFTUartTx(0x00);
	TFTUartTx(status);
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void DeleteCurve(unsigned char sID,unsigned char cID,unsigned char n)
{
	unsigned char i;
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x33);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);	
	TFTUartTx(n);
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void SetTextFlash(unsigned char sID,unsigned char cID,unsigned int time)
{
	unsigned char i;
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x15);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);
	TFTUartTx(HIGH_BYTE(time));
	TFTUartTx(LOW_BYTE(time));
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void AddCurveData(unsigned char sID,unsigned char cID,unsigned char channel,unsigned int data)
{
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x32);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);
	TFTUartTx(channel);
	TFTUartTx(0x00);
	TFTUartTx(0x02);
	TFTUartTx(HIGH_BYTE(data));
	TFTUartTx(LOW_BYTE(data));	
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}
void SetCurveVerticalScaling(unsigned char sID,unsigned char cID,unsigned int XScaling,unsigned int YScaling)
{
	TFTUartTx(0xee);
	TFTUartTx(0xb1);
	TFTUartTx(0x34);
	TFTUartTx(0x00);
	TFTUartTx(sID);
	TFTUartTx(0x00);
	TFTUartTx(cID);
	TFTUartTx(0x00);
	TFTUartTx(0x00);
	TFTUartTx(HIGH_BYTE(XScaling));
	TFTUartTx(LOW_BYTE(XScaling));	
	TFTUartTx(0x00);
	TFTUartTx(0x00);
	TFTUartTx(HIGH_BYTE(YScaling));
	TFTUartTx(LOW_BYTE(YScaling));	
	TFTUartTx(0xff);
	TFTUartTx(0xfc);
	TFTUartTx(0xff);
	TFTUartTx(0xff);
}

void InitWithTFT(void)
{
	unsigned char i;
	float fx;
	InitLCDTick=SystemTick;
	while(1)
	{		
		if(GetDeltaTick(InitLCDTick)>20)
		{
			InitLCDTick=SystemTick;
			TFTUartTx(0xee);
			TFTUartTx(0x07);
			TFTUartTx(0x35);
			TFTUartTx(0x5a);
			TFTUartTx(0x53);
			TFTUartTx(0xa5);
			TFTUartTx(0xff);
			TFTUartTx(0xfc);
			TFTUartTx(0xff);
			TFTUartTx(0xff);
		}
		if(TFTFlags.bWithTFTRx)
		{
			if(TFTMsg.cmd_type==0x07)//复位
			{			
				EndProcCommandFromTFT();
				break;
			}	
			EndProcCommandFromTFT();
		}
	}
	__delay_20ms(100);	
	SetTxt(sID_AutoPuLangke,16,"000.0");
	SetChar(sID_AutoPuLangke,30,'0');
	SetChar(sID_AutoPuLangke,31,'0');
	SetChar(sID_AutoPuLangke,32,'0');
	SetChar(sID_AutoPuLangke,33,'0');
	SetTextFlash(sID_AutoPuLangke,33,50);

	SetTxt(sID_Screen1,0x01,RomParams.SitNum);


	SetTxt(sID_wifimima,2,RomParams.WifiSSID);
	SetTxt(sID_wifimima,1,RomParams.WifiPASS);
	SetTxt(sID_ParamSet,2,RomParams.SitNum);
	SetTxt(sID_ParamSet,1,RomParams.ServerIP);
	SetTxt(sID_ParamSet,13,RomParams.ServerPort);
	for(i=0;i<6;i++)
	{
		sprintf(DisplayLine,"%d",RomParams.hWorkCurrent[i]);
		SetTxt(sID_hWorkCurrent,1+i,DisplayLine);
		sprintf(DisplayLine,"%.2f",RomParams.hCorrection[i]);
		SetTxt(sID_hWorkCurrent,30+i,DisplayLine);
	}
	for(i=0;i<6;i++)
	{
		sprintf(DisplayLine,"%d",RomParams.FAWorkCurrent[i]);
		SetTxt(sID_FuAnWorkCurrent,1+i,DisplayLine);
		sprintf(DisplayLine,"%.2f",RomParams.FACorrection[i]);
		SetTxt(sID_FuAnWorkCurrent,30+i,DisplayLine);
	}
	if(RomParams.exWorkTepy.bFAAuto)
	{
		SetButton(sID_ExperimentConfig,31,1);
		SetButton(sID_ExperimentConfig,13,0);
	}
	else
	{
		SetButton(sID_ExperimentConfig,31,0);
		SetButton(sID_ExperimentConfig,13,1);
	}
	if(RomParams.exWorkTepy.bFAPrint)
		SetButton(sID_ExperimentConfig,34,1);
	else
		SetButton(sID_ExperimentConfig,34,0);
	if(RomParams.exWorkTepy.bGQAuto)
	{
		SetButton(sID_ExperimentConfig,22,1);
		SetButton(sID_ExperimentConfig,26,0);
	}
	else
	{
		SetButton(sID_ExperimentConfig,22,0);
		SetButton(sID_ExperimentConfig,26,1);
	}
	if(RomParams.exWorkTepy.bGQPrint)
	{
		SetButton(sID_ExperimentConfig,39,1);
	}
	else
	{
		SetButton(sID_ExperimentConfig,39,0);
	}
	if(RomParams.exWorkTepy.bPLKPrint)
	{
		SetButton(sID_ExperimentConfig,57,1);
	}
	else
	{
		SetButton(sID_ExperimentConfig,57,0);
	}

	
	fx=300*0.000763;
	fx=fx/5;
	sprintf(DisplayLine,"%.1f",fx);
	SetTxt(sID_AutoVA,16,DisplayLine);
	SetTxt(sID_AutoVA_Work,16,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*2);
	SetTxt(sID_AutoVA,15,DisplayLine);
	SetTxt(sID_AutoVA_Work,15,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*3);
	SetTxt(sID_AutoVA,14,DisplayLine);
	SetTxt(sID_AutoVA_Work,14,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*4);
	SetTxt(sID_AutoVA,13,DisplayLine);
	SetTxt(sID_AutoVA_Work,13,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*5);
	SetTxt(sID_AutoVA,12,DisplayLine);
	SetTxt(sID_AutoVA_Work,12,DisplayLine);

	sprintf(DisplayLine,"%.1f",fx);
	SetTxt(sID_ManVA,16,DisplayLine);
	SetTxt(sID_ManVA_Work,13,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*2);
	SetTxt(sID_ManVA,15,DisplayLine);
	SetTxt(sID_ManVA_Work,11,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*3);
	SetTxt(sID_ManVA,14,DisplayLine);
	SetTxt(sID_ManVA_Work,10,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*4);
	SetTxt(sID_ManVA,13,DisplayLine);
	SetTxt(sID_ManVA_Work,7,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*5);
	SetTxt(sID_ManVA,10,DisplayLine);
	SetTxt(sID_ManVA_Work,5,DisplayLine);

	sprintf(DisplayLine,"%.1f",fx);
	SetTxt(sID_AutoGQ,14,DisplayLine);
	SetTxt(sID_AutoGQ_Work,6,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*2);
	SetTxt(sID_AutoGQ,13,DisplayLine);
	SetTxt(sID_AutoGQ_Work,5,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*3);
	SetTxt(sID_AutoGQ,12,DisplayLine);
	SetTxt(sID_AutoGQ_Work,4,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*4);
	SetTxt(sID_AutoGQ,9,DisplayLine);
	SetTxt(sID_AutoGQ_Work,3,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*5);
	SetTxt(sID_AutoGQ,6,DisplayLine);
	SetTxt(sID_AutoGQ_Work,2,DisplayLine);

	sprintf(DisplayLine,"%.1f",fx);
	SetTxt(sID_ManGQ,17,DisplayLine);
	SetTxt(sID_ManGQ_Work,10,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*2);
	SetTxt(sID_ManGQ,12,DisplayLine);
	SetTxt(sID_ManGQ_Work,9,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*3);
	SetTxt(sID_ManGQ,10,DisplayLine);
	SetTxt(sID_ManGQ_Work,7,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*4);
	SetTxt(sID_ManGQ,9,DisplayLine);
	SetTxt(sID_ManGQ_Work,5,DisplayLine);
	sprintf(DisplayLine,"%.1f",fx*5);
	SetTxt(sID_ManGQ,1,DisplayLine);
	SetTxt(sID_ManGQ_Work,1,DisplayLine);
	//SetCurveVerticalScaling(6,1,600,100);
	EndProcCommandFromTFT();
}
unsigned char WithTFT_GetTxt(unsigned char sID,unsigned char cID,char* pBuf)
{
	unsigned char i;
	GetTxtRetry=GetTxtRetryMax;
	while(GetTxtRetry!=0)
	{		
		TFTUartTx(0xee);
		TFTUartTx(0xb1);
		TFTUartTx(0x11);
		TFTUartTx(0x00);
		TFTUartTx(sID);
		TFTUartTx(0x00);
		TFTUartTx(cID);	
		TFTUartTx(0xff);
		TFTUartTx(0xfc);
		TFTUartTx(0xff);
		TFTUartTx(0xff);
		TempWithTFTTick=SystemTick;
		while(1)
		{
			if(TFTFlags.bWithTFTRx)
			{
				WithTFTRxLen.u16=WithTFTRxCount-12;
				if(TFTMsg.cmd_type==0xb1)//命令字
				{		
					if(TFTMsg.ctrl_msg==0x11)
					{
						if(pBuf==&pGetButton)
						{
							if(TFTMsg.control_type==0x10)//按钮
							{
								if(TFTMsg.screen_id.u8H==sID)//指定的页面
								{
									if(TFTMsg.control_id.u8H==cID)//指定的控件
									{										
										*pBuf=TFTMsg.data[1];
										EndProcCommandFromTFT();
										return 1;
									}					
								}
							}
						}
						else
						{
							if(TFTMsg.control_type==0x11)//文本
							{
								if(TFTMsg.screen_id.u8H==sID)//指定的页面
								{
									if(TFTMsg.control_id.u8H==cID)//指定的控件
									{
										i=0;
										while(TFTMsg.data[i]!='\0')
										{
											pBuf[i]=TFTMsg.data[i];
											i++;
										}
										pBuf[i]='\0';
										EndProcCommandFromTFT();
										return 1;
									}					
								}
							}	
						}		
					}
				}
				EndProcCommandFromTFT();
			}			
			if(GetDeltaTick(TempWithTFTTick)>3)
			{
				GetTxtRetry--;
				break;
			}
		}		
	}
	return 0;
}
