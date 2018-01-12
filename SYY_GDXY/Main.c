//Build F:\work_tfs\MCU\WYP\Saving2\Saving2 for device 18F6621
//Using driver C:\Program Files\HI-TECH Software\PICC-18\PRO\9.63\bin\picc18.exe
#include "HardwareProfile.h"
#include <stdio.h>
#include <stdlib.h>
__CONFIG(1,OSCSDIS&HSHW);
__CONFIG(2,PWRTEN&BOREN&BORV42&WDTPS32K&WDTDIS);//看门狗2s复位
__CONFIG(3,MCLREN&CCP2RC1);
__CONFIG(4,STVREN&LVPDIS);
void main()
{	
	unsigned char i;
	unsigned int ix,iy;
	__delay_ms(5);	
	InitSystem();
	__delay_ms(5);
// 	CheckWifiStatus();
// 	SendMearData();
// 	TLV56XX_WriteData((200<<4));
// 	TLV56XX_2_WriteData(300);	
// 	LED1_W=1;
// 	__delay_20ms(100);
// 	ReadAD1120();
// 	while(1)
// 	{
// 		LED1_W=1;
// 	}
	while(1)
	{					
		if(TFTFlags.bWithTFTRx)
		{
			ProcCommandFromTFT_Main();
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
		if(GotoScreen!=workScreen)
		{
			if(GotoScreen==sID_Screen1)
			{
				EnterDlgReNum=sID_Screen0;
				QueryDlgCancelNum=sID_Menu;
				ShowQueryDlg(strQueryReset);
				if(GotoScreen==sID_Screen0)
					RESET();
			}
			if(GotoScreen==sID_Menu)
			{			
				if(WithTFT_GetTxt(sID_Screen1,5,StudentClass)==0)
				{
					EnterDlgReNum=sID_Screen1;
					ShowEnterDlg(strErr);
					continue;
				}
				if(WithTFT_GetTxt(sID_Screen1,2,StudentNum)==0)
				{
					EnterDlgReNum=sID_Screen1;
					ShowEnterDlg(strErr);
					continue;
				}				
				SetScreen(sID_Menu);
			}
			if(GotoScreen==sID_Print)
			{
				if(RomParams.exWorkTepy.bFAPrint || RomParams.exWorkTepy.bGQPrint || RomParams.exWorkTepy.bPLKPrint)
				{
					if(gFlags.bPrinted)
					{
						EnterDlgReNum=sID_Print;
						QueryDlgCancelNum=sID_Menu;
						ShowQueryDlg(strQueryPrint2);
						if(GotoScreen==sID_Menu)
							continue;
					}
					gFlags.bError=0;
					if(RomParams.exWorkTepy.bFAPrint)
					{
						if(RomParams.exWorkTepy.bFAAuto)
						{
							for(i=0;i<6;i++)
							{
								if(Curve1Flags[i]==0)
								{
									gFlags.bError=1;
									break;
								}
							}
						}
						else
						{
							for(i=0;i<6;i++)
							{
								if(ManVAIndex[i]==0xff)
								{
									gFlags.bError=1;
									break;
								}
							}
						}						
					}
					if(RomParams.exWorkTepy.bGQPrint)
					{						
						if(RomParams.exWorkTepy.bGQAuto)
						{
							for(i=0;i<4;i++)
							{
								if(Curve2Flags[i]==0)
								{
									gFlags.bError=1;
									break;
								}
							}
						}
						else
						{
							for(i=0;i<4;i++)
							{
								if(ManGQIndex[i]==0xff)
								{
									gFlags.bError=1;
									break;
								}
							}
						}						
					}
					if(RomParams.exWorkTepy.bPLKPrint)
					{
						if(bCalcH==0)
							gFlags.bError=1;
					}
					if(gFlags.bError)
					{
						EnterDlgReNum=sID_Print;
						QueryDlgCancelNum=sID_Menu;
						ShowQueryDlg(strQueryPrint1);
						if(GotoScreen==sID_Print)
							EX_ProcPrint();
					}
					else
					{
						SetScreen(sID_Print);
						EX_ProcPrint();
					}
				}
				else
				{
					EnterDlgReNum=sID_Menu;
					ShowEnterDlg(strNoPrint);
				}
			}
			if(GotoScreen==sID_APKWifi)
			{
				SetScreen(sID_APKWifi);
				Setting_AutoWifi(sID_APKWifi);
				//workScreen=sID_Menu;
			}
			if(GotoScreen==sID_wxWifi)
			{
				SetScreen(sID_wxWifi);
				Setting_AutoWifi(sID_wxWifi);
			}
			if(GotoScreen==sID_wifimima)
			{
				SetScreen(sID_wifimima);
				Setting_Wifimima();
			}
			if(GotoScreen==sID_ParamSet)
			{
				SetScreen(sID_ParamSet);
				Setting_ParamSet();			
			}
			if(GotoScreen==sID_hWorkCurrent)
			{
				SetScreen(sID_hWorkCurrent);			
				Setting_hWorkParam();
			}
			if(GotoScreen==sID_FuAnWorkCurrent)
			{
				SetScreen(sID_FuAnWorkCurrent);
				Setting_FAWorkParam();
			}
			if(GotoScreen==sID_ExperimentConfig)
			{
				SetScreen(sID_ExperimentConfig);
				Setting_ExperimentConfig();
			}
			if(GotoScreen==sID_AutoPuLangke)//返回
			{
				SetScreen(sID_AutoPuLangke);
				EX_ProcPLKCS();
			}
			if(GotoScreen==sID_AutoVA)
			{
				if(RomParams.exWorkTepy.bFAAuto)
				{
					SetScreen(sID_AutoVA);
					EX_ProcFATXQX_Auto();
				}
				else
				{
					SetScreen(sID_ManVA);
					EX_ProcFATXQX_Man();
				}
			}
			if(GotoScreen==sID_AutoGQ)
			{
				if(RomParams.exWorkTepy.bGQAuto)
				{
					SetScreen(sID_AutoGQ);
					EX_ProcGDLGQ_Auto();
				}
				else
				{
					SetScreen(sID_ManGQ);
					EX_ProcGDLGQ_Man();
				}
			}
		}
		
// 		if(ExState==3)
// 		{
// 			EX_ProcPLKCS();
// 		}
// 		else if(ExState==1)
// 		{
// 			EX_ProcFATXQX();
// 		}
// 		else if(ExState==2)
// 		{
// 			EX_ProcGDLGQ();
// 		}
// 		else if(ExState==4)
// 		{
// 			EX_ProcSetting();
// 		}
// 		else if(ExState==5)
// 		{
// 			SetScreen(17);
// 			EX_ProcPrint();
// 		}
//  		if(gFlags.bMeasure)
//  		{
// 			if(ExNum==3)//普朗克常数测量
// 			{
// 				if(GetDeltaTick(MeasureTick)>5)
// 				{
// 					MeasureTick=SystemTick;
// 					if(MeasureIndex<100)
// 					{
// 						switch(Curve2Num)
// 						{
// 						case 0:
// 							ix=50*MeasureIndex;
// 							MeasureIndex++;
// 							break;
// 						case 1:
// 							ix=100*MeasureIndex;
// 							MeasureIndex++;
// 							break;
// 						case 2:
// 							ix=200*MeasureIndex;
// 							MeasureIndex++;
// 							break;
// 						case 3:
// 							ix=300*MeasureIndex;
// 							MeasureIndex++;
// 							break;
// 						}
// 						switch(ExNum)
// 						{
// 						case 2://光电流与光强
// 							AddCurveData(6,1,Curve2Num,ix);
// 							if(ix>Curve2Max)
// 							{
// 								iy=30000/ix;
// 								Curve2Max=30000/iy;
// 								SetCurveVerticalScaling(6,1,600,iy);
// 							}
// 							break;
// 						}
// 					}
// 				}
// 			}
//  		}
	}		
}
void interrupt low_priority lowISR(void)
{
	unsigned char rx;
	
	if(RC2IE&&RC2IF)
	{
		RC2IF=0;
		rx=RCREG2;
		ATCommand_ProcRx(rx);
	}
	if(TMR0IE&&TMR0IF)
	{		
		CLRWDT();
		TMR0IF=0;
		SetTMR0();
		SystemTick++;
	}
	if(RC1IE&&RC1IF)
	{
		RC1IF=0;
		rx=RCREG1;
		ProcRxFromTFT(rx);
	}
}

