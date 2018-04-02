#include "HardwareProfile.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>
void ProcCommandFromTFT_Setting( void );
void CheckWifiSet(unsigned char sID)
{
	unsigned char i;
	pWifiStr=strstr((const char*)ATCommand_RxList,"WIFI GOT IP");
	if(pWifiStr!=0)
	{
	 	gFlags.bWifiSet=0;				
	 	pWifiStr=strstr((const char*)ATCommand_RxList,"SSID:");
	 	if(pWifiStr==0)//字符解析错误
	 	{
			StopSetWifi();
			EnterDlgReNum=sID_WIFIconfiguration;
	 		ShowEnterDlg(strErr);	 		
	 		gFlags.bError=1;
			return;
	 	}
	 	i=0;
	 	while(pWifiStr[i+5]!=13)//'\n'
	 	{
	 		RomParams.WifiSSID[i]=pWifiStr[i+5];
	 		i++;
	 	}
	 	RomParams.WifiSSID[i]='\0';
	 	pWifiStr=strstr((const char*)ATCommand_RxList,"PASSWORD:");
	 	if(pWifiStr==0)//字符解析错误
	 	{
			StopSetWifi();
			EnterDlgReNum=sID_WIFIconfiguration;
	 		ShowEnterDlg(strErr);
	 		gFlags.bError=1;
			return;
	 	}
	 	i=0;
	 	while(pWifiStr[i+9]!=13)
	 	{
	 		RomParams.WifiPASS[i]=pWifiStr[i+9];
	 		i++;
	 	}
	 	RomParams.WifiPASS[i]='\0';
		EnterDlgReNum=sID_Setting;
	 	ShowEnterDlg(strWifiSetSeccess);
	 	StopSetWifi();
	}
	if(GetDeltaTick(WaitWifiSetTick)>9)
	{		
	 	WaitWifiSetTick=SystemTick;
	 	if(WaitSCount==0)//配置失败
	 	{
			StopSetWifi();
			EnterDlgReNum=sID_WIFIconfiguration;
	 		ShowEnterDlg(strErr);	 		
	 		gFlags.bWifiSet=0;
	 	}
	 	else
	 	{
	 		WaitSCount--;
	 		if(gFlags.bWXSetWifi)
	 			SetProgress(sID,1,WaitSCount);
	 		else
	 			SetProgress(sID,1,WaitSCount);
	 	}
	}
}
void Setting_AutoWifi(unsigned char sID)
{
	unsigned char key,x,i;
	unsigned int ix;	
	if(sID==sID_APKWifi)
	{
		StartSetWifi(1);
	}
	else
	{
		StartSetWifi(2);
	}
	ATCommand_InitWaitData();
	WaitWifiSetTick=SystemTick;
	WaitSCount=60;
	SetProgress(sID,1,WaitSCount);
	gFlags.bWifiSet=1;
	while(GotoScreen==sID)
	{		
		if(TFTFlags.bWithTFTRx)
		{
			ProcCommandFromTFT_Setting();
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
		if(gFlags.bWifiSet)
		{
			CheckWifiSet(sID);
		}
	}
	if(GotoScreen==sID_WIFIconfiguration)
	{
		StopSetWifi();
		SetScreen(sID_WIFIconfiguration);		
	}
}
void Setting_Wifimima(void)
{
	GetTxtFlags.bNeedGetWifiSet;
	while(1)
	{
		while(GotoScreen==sID_wifimima)
		{	
			if(TFTFlags.bWithTFTRx)
			{
				ProcCommandFromTFT_Setting();
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
		if(GetTxtFlags.bNeedGetWifiSet)
		{			
			if(WithTFT_GetTxt(sID_wifimima,2,RomParams.WifiSSID)==0)
			{
				EnterDlgReNum=sID_wifimima;
				ShowEnterDlg(strErr);
				continue;
			}
			if(WithTFT_GetTxt(sID_wifimima,1,RomParams.WifiPASS)==0)
			{
				EnterDlgReNum=sID_wifimima;
				ShowEnterDlg(strErr);
				continue;
			}
			SaveRomData();
			EnterDlgReNum=sID_Setting;
			ShowEnterDlg(strWifiSetSeccess);			
			return;
		}
		else
		{
			SetScreen(sID_WIFIconfiguration);		
			return;
		}
	}
}
void Setting_ParamSet(void)
{
	GetTxtFlags.bNeedGetParamSet=0;
	while(1)
	{
		while(GotoScreen==sID_ParamSet)
		{	
			if(TFTFlags.bWithTFTRx)
			{
				ProcCommandFromTFT_Setting();
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
		if(GetTxtFlags.bNeedGetParamSet)
		{			
			if(WithTFT_GetTxt(sID_ParamSet,2,RomParams.SitNum)==0)
			{
				EnterDlgReNum=sID_ParamSet;
				ShowEnterDlg(strErr);
				continue;
			}
			if(WithTFT_GetTxt(sID_ParamSet,1,RomParams.ServerIP)==0)
			{
				EnterDlgReNum=sID_ParamSet;
				ShowEnterDlg(strErr);
				continue;
			}
			if(WithTFT_GetTxt(sID_ParamSet,13,RomParams.ServerPort)==0)
			{
				EnterDlgReNum=sID_ParamSet;
				ShowEnterDlg(strErr);
				continue;
			}
			SaveRomData();
			EnterDlgReNum=sID_Setting;
			ShowEnterDlg(strParamSetSeccess);			
			return;
		}
		else
		{
			SetScreen(sID_Setting);		
			return;
		}
	}
}
void Setting_hWorkParam(void)
{
	unsigned char i;
	GetTxtFlags.bNeedGethCur=0;
	while(1)
	{
		while(GotoScreen==sID_hWorkCurrent)
		{	
			if(TFTFlags.bWithTFTRx)
			{
				ProcCommandFromTFT_Setting();
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
		if(GetTxtFlags.bNeedGethCur)
		{			
			gFlags.bError=0;
			GetTxtFlags.bNeedGethCur=0;
			for(i=0;i<6;i++)
			{
				if(WithTFT_GetTxt(sID_hWorkCurrent,1+i,pGetTxtBuf)==0)
				{
					EnterDlgReNum=sID_hWorkCurrent;
					ShowEnterDlg(strErr);
					gFlags.bError=1;
					break;
				}
				RomParams.hWorkCurrent[i]=atoi(pGetTxtBuf);
				if(WithTFT_GetTxt(sID_hWorkCurrent,30+i,pGetTxtBuf)==0)
				{
					EnterDlgReNum=sID_hWorkCurrent;
					ShowEnterDlg(strErr);
					gFlags.bError=1;
					break;
				}
				RomParams.hCorrection[i]=atof(pGetTxtBuf);
			}
			if(!gFlags.bError)
			{
				SaveRomData();
				EnterDlgReNum=sID_Setting;
				ShowEnterDlg(strParamSetSeccess);				
				return;
			}
		}
		else
		{
			SetScreen(sID_Setting);		
			return;
		}
	}
}
void Setting_FAWorkParam(void)
{
	unsigned char i;
	GetTxtFlags.bNeedGetFACur=0;
	while(1)
	{
		while(GotoScreen==sID_FuAnWorkCurrent)
		{	
			if(TFTFlags.bWithTFTRx)
			{
				ProcCommandFromTFT_Setting();
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
		if(GetTxtFlags.bNeedGetFACur)
		{			
			gFlags.bError=0;
			GetTxtFlags.bNeedGetFACur=0;
			for(i=0;i<6;i++)
			{
				if(WithTFT_GetTxt(sID_FuAnWorkCurrent,1+i,pGetTxtBuf)==0)
				{
					EnterDlgReNum=sID_FuAnWorkCurrent;
					ShowEnterDlg(strErr);
					gFlags.bError=1;
					break;
				}
				RomParams.FAWorkCurrent[i]=atoi(pGetTxtBuf);
				if(WithTFT_GetTxt(sID_FuAnWorkCurrent,30+i,pGetTxtBuf)==0)
				{
					EnterDlgReNum=sID_FuAnWorkCurrent;
					ShowEnterDlg(strErr);
					gFlags.bError=1;
					break;
				}
				RomParams.FACorrection[i]=atof(pGetTxtBuf);
			}
			if(!gFlags.bError)
			{
				SaveRomData();
				EnterDlgReNum=sID_Setting;
				ShowEnterDlg(strParamSetSeccess);				
				return;
			}
		}
		else
		{
			SetScreen(sID_Setting);		
			return;
		}
	}
}
void Setting_ExperimentConfig(void)
{
	unsigned char i;
	GetTxtFlags.bNeedGetWorkType=0;
	while(1)
	{
		while(GotoScreen==sID_ExperimentConfig)
		{	
			if(TFTFlags.bWithTFTRx)
			{
				ProcCommandFromTFT_Setting();
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
		if(GetTxtFlags.bNeedGetWorkType)
		{
			GetTxtFlags.bNeedGetFACur=0;
			if(WithTFT_GetTxt(sID_ExperimentConfig,31,&pGetButton)==0)
			{
				EnterDlgReNum=sID_ExperimentConfig;
				ShowEnterDlg(strErr);
				continue;
			}
			if(pGetButton==0x01)
			{
				RomParams.exWorkTepy.bFAAuto=1;
			}
			else
			{
				RomParams.exWorkTepy.bFAAuto=0;
			}
			if(WithTFT_GetTxt(sID_ExperimentConfig,34,&pGetButton)==0)
			{
				EnterDlgReNum=sID_ExperimentConfig;
				ShowEnterDlg(strErr);
				continue;
			}
			if(pGetButton==0x01)
			{
				RomParams.exWorkTepy.bFAPrint=1;
			}
			else
			{
				RomParams.exWorkTepy.bFAPrint=0;
			}
			if(WithTFT_GetTxt(sID_ExperimentConfig,22,&pGetButton)==0)
			{
				EnterDlgReNum=sID_ExperimentConfig;
				ShowEnterDlg(strErr);
				continue;
			}
			if(pGetButton==0x01)
			{
				RomParams.exWorkTepy.bGQAuto=1;
			}
			else
			{
				RomParams.exWorkTepy.bGQAuto=0;
			}
			if(WithTFT_GetTxt(sID_ExperimentConfig,39,&pGetButton)==0)
			{
				EnterDlgReNum=sID_ExperimentConfig;
				ShowEnterDlg(strErr);
				continue;
			}
			if(pGetButton==0x01)
			{
				RomParams.exWorkTepy.bGQPrint=1;
			}
			else
			{
				RomParams.exWorkTepy.bGQPrint=0;
			}
			if(WithTFT_GetTxt(sID_ExperimentConfig,57,&pGetButton)==0)
			{
				EnterDlgReNum=sID_ExperimentConfig;
				ShowEnterDlg(strErr);
				continue;
			}
			if(pGetButton==0x01)
			{
				RomParams.exWorkTepy.bPLKPrint=1;
			}
			else
			{
				RomParams.exWorkTepy.bPLKPrint=0;
			}
			SaveRomData();
			EnterDlgReNum=sID_Screen0;
			ShowEnterDlg(strSaveReset);
			
			RESET();
			return;
		}
		else
		{
			SetScreen(sID_Setting);		
			return;
		}
	}
}
void ProcCommandFromTFT_Setting( void )
{	
	unsigned char i;
	unsigned int x;
	WithTFTRxLen.u16=WithTFTRxCount-12;
	switch(TFTMsg.cmd_type)//命令字
	{
	case 0xb1://主命令		
		if(TFTMsg.ctrl_msg==0x11)
		{
			if(TFTMsg.control_type==0x10)//按钮
			{
				if(TFTMsg.screen_id.u8H==sID_APKWifi)//"Setting"页面
				{
					if(TFTMsg.control_id.u8H==3)//"返回"
					{
						GotoScreen=sID_WIFIconfiguration;
						gFlags.bWifiSet=0;
					}					
				}
				else if(TFTMsg.screen_id.u8H==sID_wxWifi)//"wifimima"页面
				{
					if(TFTMsg.control_id.u8H==3)//确定
					{
						GotoScreen=sID_WIFIconfiguration;	
						gFlags.bWifiSet=0;
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_wifimima)//"wifimima"页面
				{
					if(TFTMsg.control_id.u8H==6)//确定
					{
						GotoScreen=sID_WIFIconfiguration;	
						GetTxtFlags.bNeedGetWifiSet=1;
					}
					else if(TFTMsg.control_id.u8H==10)//取消
					{
						GotoScreen=sID_WIFIconfiguration;	
						GetTxtFlags.bNeedGetWifiSet=0;
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_ParamSet)//"wifimima"页面
				{
					if(TFTMsg.control_id.u8H==7)//确定
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGetParamSet=1;
					}
					else if(TFTMsg.control_id.u8H==12)//取消
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGetParamSet=0;
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_hWorkCurrent)//"wifimima"页面
				{
					if(TFTMsg.control_id.u8H==11)//确定
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGethCur=1;
					}
					else if(TFTMsg.control_id.u8H==8)//取消
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGethCur=0;
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_FuAnWorkCurrent)//"wifimima"页面
				{
					if(TFTMsg.control_id.u8H==11)//确定
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGetFACur=1;
					}
					else if(TFTMsg.control_id.u8H==8)//取消
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGetFACur=0;
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_ExperimentConfig)//"wifimima"页面
				{
					if(TFTMsg.control_id.u8H==1)//确定
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGetWorkType=1;
					}
					else if(TFTMsg.control_id.u8H==12)//取消
					{
						GotoScreen=sID_Setting;	
						GetTxtFlags.bNeedGetWorkType=0;
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
void Setting_APKWifi(void)
{
	unsigned char key,x,i;
	unsigned int ix;	
	while(workScreen!=0)
	{		
		// 		if(TFTFlags.bWithTFTRx)
		// 		{
		// 			ProcCommandFromTFT_Setting();
		// 			EndProcCommandFromTFT();
		// 		}
		// 		if(GetTxtFlags.bNeedGetWifiSet)
		// 		{
		// 			GetTxt_sID=11;
		// 			GetTxt_cID=2;
		// 			gFlags.bGetTxt=0;
		// 			pGetTxtBuf=RomParams.WifiSSID;
		// 			if(WithTFT_GetTxt()==0)
		// 			{
		// 				gFlags.bEnterDlgJump=0;				
		// 				ShowEnterDlg("have error,pls retry");
		// 				GetTxtFlags.bNeedGetWifiSet=0;
		// 				continue;
		// 			}
		// 			GetTxt_sID=11;
		// 			GetTxt_cID=1;
		// 			gFlags.bGetTxt=0;
		// 			pGetTxtBuf=RomParams.WifiPASS;
		// 			if(WithTFT_GetTxt()==0)
		// 			{
		// 				gFlags.bEnterDlgJump=0;
		// 				ShowEnterDlg("have error,pls retry");
		// 				GetTxtFlags.bNeedGetWifiSet=0;
		// 				continue;
		// 			}			
		// 			SaveRomData();
		// 			SetScreen(12);
		// 			GetTxtFlags.bNeedGetWifiSet=0;
		// 		}
		// 		if(GetTxtFlags.bNeedGetParamSet)
		// 		{
		// 			GetTxt_sID=16;
		// 			GetTxt_cID=2;
		// 			gFlags.bGetTxt=0;
		// 			pGetTxtBuf=RomParams.SitNum;
		// 			if(WithTFT_GetTxt()==0)
		// 			{
		// 				gFlags.bEnterDlgJump=0;
		// 				ShowEnterDlg("have error,pls retry");
		// 				GetTxtFlags.bNeedGetParamSet=0;
		// 				continue;
		// 			}
		// 			GetTxt_sID=16;
		// 			GetTxt_cID=1;
		// 			gFlags.bGetTxt=0;
		// 			pGetTxtBuf=RomParams.ServerIP;
		// 			if(WithTFT_GetTxt()==0)
		// 			{
		// 				gFlags.bEnterDlgJump=0;
		// 				ShowEnterDlg("have error,pls retry");
		// 				GetTxtFlags.bNeedGetParamSet=0;
		// 				continue;
		// 			}		
		// 			GetTxt_sID=16;
		// 			GetTxt_cID=13;
		// 			gFlags.bGetTxt=0;
		// 			pGetTxtBuf=RomParams.ServerPort;
		// 			if(WithTFT_GetTxt()==0)
		// 			{
		// 				gFlags.bEnterDlgJump=0;
		// 				ShowEnterDlg("have error,pls retry");
		// 				GetTxtFlags.bNeedGetParamSet=0;
		// 				continue;
		// 			}	
		// 			SaveRomData();
		// 			SetScreen(12);
		// 			GetTxtFlags.bNeedGetParamSet=0;
		// 		}	
		// 		if(GetTxtFlags.bNeedGethCur)
		// 		{
		// 			GetTxt_sID=18;
		// 			gFlags.bError=0;
		// 			for(i=0;i<6;i++)
		// 			{
		// 				GetTxt_cID=i+1;
		// 				gFlags.bGetTxt=0;
		// 				pGetTxtBuf=cGetCur;
		// 				if(WithTFT_GetTxt()==0)
		// 				{
		// 					gFlags.bEnterDlgJump=0;
		// 					ShowEnterDlg("have error,pls retry");
		// 					GetTxtFlags.bNeedGethCur=0;
		// 					gFlags.bError=1;
		// 					break;
		// 				}
		// 				RomParams.hWorkCurrent[i]=atoi(cGetCur);
		// 			}
		// 			if(gFlags.bError==0)
		// 			{
		// 				SaveRomData();
		// 				SetScreen(12);
		// 				GetTxtFlags.bNeedGethCur=0;
		// 			}
		// 		}
		// 		if(GetTxtFlags.bNeedGetFACur)
		// 		{
		// 			GetTxt_sID=19;
		// 			gFlags.bError=0;
		// 			for(i=0;i<6;i++)
		// 			{
		// 				GetTxt_cID=i+1;
		// 				gFlags.bGetTxt=0;
		// 				pGetTxtBuf=cGetCur;
		// 				if(WithTFT_GetTxt()==0)
		// 				{
		// 					gFlags.bEnterDlgJump=0;
		// 					ShowEnterDlg("have error,pls retry");
		// 					GetTxtFlags.bNeedGetFACur=0;
		// 					gFlags.bError=1;
		// 					break;
		// 				}
		// 				RomParams.FAWorkCurrent[i]=atoi(cGetCur);
		// 			}
		// 			if(gFlags.bError==0)
		// 			{
		// 				SaveRomData();
		// 				SetScreen(12);
		// 				GetTxtFlags.bNeedGetFACur=0;
		// 			}
		// 		}
		// 		if(gFlags.bWifiSet)
		// 		{
		// 			pWifiStr=strstr((const char*)ATCommand_RxList,"WIFI GOT IP");
		// 			if(pWifiStr!=0)
		// 			{
		// 				gFlags.bWifiSet=0;				
		// 				pWifiStr=strstr((const char*)ATCommand_RxList,"SSID:");
		// 				if(pWifiStr==0)//字符解析错误
		// 				{
		// 					ShowEnterDlg("wifi setting Error,pls retry!!!");
		// 					StopSetWifi();
		// 					continue;
		// 				}
		// 				i=0;
		// 				while(pWifiStr[i+5]!=13)//'\n'
		// 				{
		// 					RomParams.WifiSSID[i]=pWifiStr[i+5];
		// 					i++;
		// 				}
		// 				RomParams.WifiSSID[i]='\0';
		// 				pWifiStr=strstr((const char*)ATCommand_RxList,"PASSWORD:");
		// 				if(pWifiStr==0)//字符解析错误
		// 				{
		// 					ShowEnterDlg("wifi setting Error,pls retry!!!");
		// 					StopSetWifi();
		// 					continue;
		// 				}
		// 				i=0;
		// 				while(pWifiStr[i+9]!=13)
		// 				{
		// 					RomParams.WifiPASS[i]=pWifiStr[i+9];
		// 					i++;
		// 				}
		// 				RomParams.WifiPASS[i]='\0';
		// 				gFlags.bEnterDlgJump=1;
		// 				EnterDlgReNum=12;
		// 				ShowEnterDlg("wifi setting seccess!!!");
		// 				StopSetWifi();
		// 			}
		// 			if(GetDeltaTick(WaitWifiSetTick)>9)
		// 			{		
		// 				WaitWifiSetTick=SystemTick;
		// 				if(WaitSCount==0)//配置失败
		// 				{
		// 					ShowEnterDlg("wifi setting Error,pls retry!!!");
		// 					StopSetWifi();
		// 					gFlags.bWifiSet=0;
		// 				}
		// 				else
		// 				{
		// 					WaitSCount--;
		// 					if(gFlags.bWXSetWifi)
		// 						SetProgress(15,1,WaitSCount);
		// 					else
		// 						SetProgress(13,1,WaitSCount);
		// 				}
		// 			}
		// 		}
	}
}
