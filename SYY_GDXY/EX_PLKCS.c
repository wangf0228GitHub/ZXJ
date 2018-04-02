#include "HardwareProfile.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void ProcCommandFromTFT_PLKCS( void );
unsigned int CutOffV;
unsigned char SetIndex;
const float fHz[6]={7.5,6.5,5.8,5.2,5,4.8};
const float fFenMu=5.38;
const float fXAve=5.8;
unsigned char LEDIndex;
void EX_ProcPLKCS(void)
{
	unsigned char key,x,i;
	unsigned int ix;
	float f1,fYAve,fx;
	float fCutOffV;
	ADGainControl_W=0;//前置大增益
	UcControl_W=0;//反向电压
	MeasureTick=SystemTick-10000;
	//SetBright(100);
	CutOffV=0;
	SetCutOffV(CutOffV);
	LEDIndex=0;
	SetIndex=0;
	while(1)
	{
		while(GotoScreen==sID_AutoPuLangke)
		{
			key=KeyCheck();
			if(key!=KeyCheck_NoKey)
			{			
				switch(key)
				{
				case KeyUp:
					ix=1;
					for(i=0;i<SetIndex;i++)
						ix=ix*10;
					CutOffV=CutOffV+ix;
					if(CutOffV>2000)
						CutOffV=2000;
					sprintf(DisplayLine,"%04d",CutOffV);
					SetChar(sID_AutoPuLangke,30,DisplayLine[0]);
					SetChar(sID_AutoPuLangke,31,DisplayLine[1]);
					SetChar(sID_AutoPuLangke,32,DisplayLine[2]);
					SetChar(sID_AutoPuLangke,33,DisplayLine[3]);
					fCutOffV=(float)CutOffV;
					f1=fCutOffV/RomParams.hCorrection[LEDIndex];
					f1=f1+0.5;
					SetCutOffV((unsigned int)f1);
					break;
				case KeyDown:
					ix=1;
					for(i=0;i<SetIndex;i++)
						ix=ix*10;
					if(CutOffV>ix)
						CutOffV=CutOffV-ix;
					else
						CutOffV=0;
					sprintf(DisplayLine,"%04d",CutOffV);
					SetChar(sID_AutoPuLangke,30,DisplayLine[0]);
					SetChar(sID_AutoPuLangke,31,DisplayLine[1]);
					SetChar(sID_AutoPuLangke,32,DisplayLine[2]);
					SetChar(sID_AutoPuLangke,33,DisplayLine[3]);
					fCutOffV=(float)CutOffV;
					f1=fCutOffV/RomParams.hCorrection[LEDIndex];
					f1=f1+0.5;
					SetCutOffV((unsigned int)f1);
					break;
				case KeyLeft:
					SetTextFlash(sID_AutoPuLangke,33-SetIndex,0);
					if(SetIndex>=2)
						SetIndex=0;
					else
						SetIndex++;
					SetTextFlash(sID_AutoPuLangke,33-SetIndex,50);
					break;
				case KeyRight:
					SetTextFlash(sID_AutoPuLangke,33-SetIndex,0);
					if(SetIndex==0)
						SetIndex=2;
					else
						SetIndex--;
					SetTextFlash(sID_AutoPuLangke,33-SetIndex,50);
					break;
				}			
				// 			fCutOffV=((float)CutOffV)/1000;
				// 			sprintf(DisplayLine,"%.3f",fCutOffV);
				// 			SetTxt(3,21,DisplayLine);
			}
			if(TFTFlags.bWithTFTRx)
			{
				ProcCommandFromTFT_PLKCS();
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
			if(GetDeltaTick(MeasureTick)>5)
			{
				MeasureTick=SystemTick;
				ReadAD1120();
				// 			sprintf(DisplayLine,"%d",ADValue.s16);
				// 			SetTxt(3,16,DisplayLine);
				I_nA=ADValue.s16;
				I_nA=I_nA*0.0763;
				sprintf(DisplayLine,"%05.1f",I_nA);
				SetTxt(sID_AutoPuLangke,16,DisplayLine);
			}
		}
		if(GotoScreen==sID_ExperimentalProject)
		{
			GotoScreen=workScreen;
			SetScreen(sID_ExperimentalProject);
			
				SwitchLED(0,0);
				SetBright(0);
				SetCutOffV(0);
				SetButton(sID_AutoPuLangke,1,0);
				SetButton(sID_AutoPuLangke,2,0);
				SetButton(sID_AutoPuLangke,3,0);
				SetButton(sID_AutoPuLangke,4,0);
				SetButton(sID_AutoPuLangke,5,0);
				SetButton(sID_AutoPuLangke,6,0);
				SetTxt(sID_AutoPuLangke,16,"000.0");
				SetChar(sID_AutoPuLangke,30,'0');
				SetChar(sID_AutoPuLangke,31,'0');
				SetChar(sID_AutoPuLangke,32,'0');
				SetChar(sID_AutoPuLangke,33,'0');
				SetTextFlash(sID_AutoPuLangke,33,50);
				//SetButton(3,7,0);
				return;
		}
		if(GotoScreen==sID_PLdatePrecessing)
		{
			GotoScreen=workScreen;
			SetScreen(sID_PLdatePrecessing);
//			if(SetScreen(sID_PLdatePrecessing)==0)
//			{
//				EnterDlgReNum=sID_AutoPuLangke;
//				ShowEnterDlg(strErr);
//			}
//			else
			{
				SwitchLED(0,0);
				SetBright(0);
				SetCutOffV(0);
				SetButton(3,1,0);
				SetButton(3,2,0);
				SetButton(3,3,0);
				SetButton(3,4,0);
				SetButton(3,5,0);
				SetButton(3,6,0);
				SetTxt(sID_AutoPuLangke,16,"000.0");
				SetChar(sID_AutoPuLangke,30,'0');
				SetChar(sID_AutoPuLangke,31,'0');
				SetChar(sID_AutoPuLangke,32,'0');
				SetChar(sID_AutoPuLangke,33,'0');
				SetTextFlash(sID_AutoPuLangke,33,50);
				while(1)
				{
					while(GotoScreen==sID_PLdatePrecessing)
					{
						if(TFTFlags.bWithTFTRx)
						{
							ProcCommandFromTFT_PLKCS();
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
						if(GetTxtFlags.bNeedCalcH)
						{
							GetTxtFlags.bNeedCalcH=0;
							gFlags.bError=0;
							for(i=0;i<6;i++)
							{
								if(WithTFT_GetTxt(sID_PLdatePrecessing,30+i,pGetTxtBuf)==0)
								{
									EnterDlgReNum=sID_PLdatePrecessing;
									ShowEnterDlg(strErr);
									gFlags.bError=1;
									break;
								}
								fUs[i]=atof(pGetTxtBuf);
							}
							if(!gFlags.bError)
							{
								/************************************************************************/
								/* 开始计算普朗克常数                                                   */
								/************************************************************************/
								f1=0;
								for(i=0;i<6;i++)
								{
									f1=f1+fUs[i]*fHz[i];
								}
								fYAve=0;
								for(i=0;i<6;i++)
								{
									fYAve=fYAve+fUs[i];
								}
								fH_K=f1-fXAve*fYAve;
								fH_K=fH_K/fFenMu;
								fH_B=fYAve/6-fH_K*fXAve;
								fH=fH_K*16.02;
								sprintf(DisplayLine,"%.3f",fH_K);
								SetTxt(sID_PLdatePrecessing,16,DisplayLine);
								sprintf(DisplayLine,"%+.3f",fH_B);
								SetTxt(sID_PLdatePrecessing,4,DisplayLine);
								sprintf(DisplayLine,"%.3f",fH);
								SetTxt(sID_PLdatePrecessing,19,DisplayLine);
								DeleteCurve(sID_PLdatePrecessing,2,0);
								for(i=4;i<9;i++)
								{
									fx=i*fH_K+fH_B;
									if(fx<0)
										fx=0;
									fx=fx*150;
									AddCurveData(sID_PLdatePrecessing,2,0,(unsigned int)fx);
								}								
								bCalcH=1;
							}
						}
					}					
					if(GotoScreen==sID_AutoPuLangke)
					{
						GotoScreen=workScreen;
						SetScreen(sID_AutoPuLangke);
//						if(SetScreen(sID_AutoPuLangke)==0)
//						{
//							EnterDlgReNum=sID_PLdatePrecessing;
//							ShowEnterDlg(strErr);
//						}
//						else
						{
							CutOffV=0;
							SetCutOffV(CutOffV);							
							SetIndex=0;
							break;
						}
					}
				}
			}
		}
	}
}
void ProcCommandFromTFT_PLKCS( void )
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
				if(TFTMsg.screen_id.u8H==sID_AutoPuLangke)//"普朗克常数"页面
				{
					if(TFTMsg.control_id.u8H>=1 && TFTMsg.control_id.u8H<=6)//紫光
					{
						SwitchLED(TFTMsg.control_id.u8H,TFTMsg.data[1]);
						LEDIndex=TFTMsg.control_id.u8H-1;
						SetBright(RomParams.hWorkCurrent[TFTMsg.control_id.u8H-1]);
						if(TFTMsg.data[1]==0)
						{
							CutOffV=0;
							SetCutOffV(CutOffV);
							SetChar(sID_AutoPuLangke,30,'0');
							SetChar(sID_AutoPuLangke,31,'0');
							SetChar(sID_AutoPuLangke,32,'0');
							SetChar(sID_AutoPuLangke,33,'0');
						}
					}
// 					else if(TFTMsg.control_id.u8H==0x07)//全灭
// 					{
// 						SwitchLED(0,0);
// 					}
					else if(TFTMsg.control_id.u8H==9)//返回
					{
// 						SwitchLED(0,0);
// 						SetBright(0);
// 						SetCutOffV(0);
 						GotoScreen=sID_ExperimentalProject;
// 						SetButton(3,1,0);
// 						SetButton(3,2,0);
// 						SetButton(3,3,0);
// 						SetButton(3,4,0);
// 						SetButton(3,5,0);
// 						SetButton(3,6,0);
						//SetButton(3,7,0);
					}
					else if(TFTMsg.control_id.u8H==19)//数据处理
					{
						GotoScreen=sID_PLdatePrecessing;						
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_PLdatePrecessing)//"普朗克数据处理"页面
				{
					if(TFTMsg.control_id.u8H==20)//返回
					{
						GotoScreen=sID_AutoPuLangke;
					}
					else if(TFTMsg.control_id.u8H==1)//计算
					{
						GetTxtFlags.bNeedCalcH=1;
					}
				}
			}
//  			else if(TFTMsg.control_type==0x11)//文本
//  			{
//  				if(TFTMsg.screen_id.u8H==0x03)//"普朗克常数"页面
//  				{
//  					if(TFTMsg.control_id.u8H==19)//班级
//  					{
//  						x=atoi(TFTMsg.data);
//  						SetBright(x);
//  					}
//  				}
//  			}			
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
