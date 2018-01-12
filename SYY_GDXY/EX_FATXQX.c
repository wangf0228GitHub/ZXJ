#include "HardwareProfile.h"
#include <stdio.h>
#include "stdlib.h"

void ProcCommandFromTFT_FATXQX( void );
unsigned char CheckWorkLED(unsigned char sID)
{
	unsigned char i;
	gFlags.bError=0;
	CurveNum=0xff;
	for(int i=0;i<6;i++)
	{
		if(WithTFT_GetTxt(sID,2+i,&pGetButton)==0)
		{
			EnterDlgReNum=sID;
			ShowEnterDlg(strErr);
			gFlags.bError=1;
			break;
		}
		if(pGetButton!=0)
		{
			CurveNum=i;
			break;
		}
	}
	if(gFlags.bError)
		return 0xff;
	else
		return 0;
}
void EX_ProcFATXQX_Auto(void)
{
	unsigned char i;
	unsigned int iy;
	float fx,fAccelerateV;
	ADGainControl_W=1;//前置小增益
	UcControl_W=1;//正向电压
	//SetTxt(4,19,"100");
	CurveNum=0;
	MeasureTick=SystemTick-10000;
	while(GotoScreen==sID_AutoVA)
	{		
 		if(TFTFlags.bWithTFTRx)
 		{
 			ProcCommandFromTFT_FATXQX();
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
			sprintf(DisplayLine,"%.2f",I_nA);
			SetTxt(sID_AutoVA,10,DisplayLine);
		}
		if(gFlags.bMeasure)
		{
			gFlags.bMeasure=0;
			if(CheckWorkLED(sID_AutoVA)==0)
			{
				if(CurveNum==0xff)
				{
					EnterDlgReNum=sID_AutoVA;
					ShowEnterDlg(strPicF);
					continue;
				}
			}
			else
				continue;			
			SetScreen(sID_AutoVA_Work);
			SetBright(RomParams.FAWorkCurrent[CurveNum]);
			SwitchLED(CurveNum+1,1);
			switch (CurveNum)
			{
			case 0:
				ShowPic(pID_VACut,46,154,117,50);
				break;
			case 1:
				ShowPic(pID_VACut,46,210,117,50);
				break;
			case 2:
				ShowPic(pID_VACut,46,267,117,50);
				break;
			case 3:
				ShowPic(pID_VACut,46,325,117,50);
				break;
			case 4:
				ShowPic(pID_VACut,46,384,117,50);
				break;
			case 5:
				ShowPic(pID_VACut,46,444,117,50);
				break;
			}			
			MeasureIndex=0;
			fAccelerateV=0;
			if(Curve1Flags[CurveNum]!=0)
			{
				DeleteCurve(sID_AutoVA,11,CurveNum);
				DeleteCurve(sID_AutoVA_Work,11,CurveNum);
			}
			for(i=0;i<101;i++)
			{
				fx=fAccelerateV/RomParams.FACorrection[CurveNum];
				fx=fx*47.62;//*4096/4.096/21
				sprintf(DisplayLine,"%.1f",fAccelerateV);
				SetTxt(sID_AutoVA_Work,1,DisplayLine);
				AccelerateV=(unsigned int)(fx+0.5);
				SetCutOffV(AccelerateV);		
//				__delay_20ms(50);
 				__delay_20ms(75);
 				ReadAD1120();
				if(ADValue.s16<0)
				{
					ADValue.s16=0;
				}				
				fx=ADValue.s16*0.000763;
				sprintf(DisplayLine,"%.2f",fx);
				SetTxt(sID_AutoVA_Work,10,DisplayLine);
				fAccelerateV=fAccelerateV+0.5;		

				CurveData_FATX[CurveNum][i]=ADValue.u16;
				
				ADValue.s16=ADValue.s16/4;
				AddCurveData(sID_AutoVA,11,CurveNum,ADValue.s16);
				AddCurveData(sID_AutoVA_Work,11,CurveNum,ADValue.s16);
				if(ADValue.u16>Curve1Max)
				{
					iy=30000/ADValue.u16;
					Curve1Max=30000/iy;
					SetCurveVerticalScaling(sID_AutoVA,11,500,iy);
					SetCurveVerticalScaling(sID_AutoVA_Work,11,500,iy);
					fx=Curve1Max;
					fx=fx*0.000763;
					fx=fx*4;
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
				}
				SetProgress(sID_AutoVA_Work,2,i);
			}
			SetProgress(sID_AutoVA_Work,2,100);
			SwitchLED(CurveNum+1,0);
			SetBright(0);
			SetCutOffV(0);
			Curve1Flags[CurveNum]=1;
			EnterDlgReNum=sID_AutoVA;
			ShowEnterDlg(strCurveFinish);
		}	
	}
	SetScreen(sID_ExperimentalProject);
}

void EX_ProcFATXQX_Man(void)
{
	unsigned char i,key;
	unsigned int iy;
	float fx,fAccelerateV=0;;
	ADGainControl_W=1;//前置小增益
	UcControl_W=1;//正向电压
	SetTxt(4,19,"100");
	CurveNum=0;
	MeasureTick=SystemTick-10000;
	while(GotoScreen==sID_ManVA)
	{		
		if(TFTFlags.bWithTFTRx)
		{
			ProcCommandFromTFT_FATXQX();
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
			sprintf(DisplayLine,"%.2f",I_nA);
			SetTxt(sID_ManVA,1,DisplayLine);
		}
		if(gFlags.bMeasure)
		{
			gFlags.bMeasure=0;
			if(CheckWorkLED(sID_ManVA)==0)
			{
				if(CurveNum==0xff)
				{
					EnterDlgReNum=sID_ManVA;
					ShowEnterDlg(strPicF);
					continue;
				}
			}
			else
				continue;			
			SetScreen(sID_ManVA_Work);
			SetBright(RomParams.FAWorkCurrent[CurveNum]);
			SwitchLED(CurveNum+1,1);
			switch (CurveNum)
			{
			case 0:
				ShowPic(pID_VACut,46,154,117,50);
				break;
			case 1:
				ShowPic(pID_VACut,46,210,117,50);
				break;
			case 2:
				ShowPic(pID_VACut,46,267,117,50);
				break;
			case 3:
				ShowPic(pID_VACut,46,325,117,50);
				break;
			case 4:
				ShowPic(pID_VACut,46,384,117,50);
				break;
			case 5:
				ShowPic(pID_VACut,46,444,117,50);
				break;
			}
			if(ManVAIndex[CurveNum]==0xff)
			{
				//sprintf(DisplayLine,"%d",ManVAIndex[CurveNum]);
				SetTxt(sID_ManVA_Work,12,"-.-");
				SetTxt(sID_ManVA_Work,1,"-.-");
			}
			else
			{
				sprintf(DisplayLine,"%d.0",ManVAIndex[CurveNum]);
				SetTxt(sID_ManVA_Work,12,DisplayLine);
				fx=CurveData_FATX[CurveNum][ManVAIndex[CurveNum]]*0.000763;
				sprintf(DisplayLine,"%.2f",fx);
				SetTxt(sID_ManVA_Work,1,DisplayLine);
			}
			while(GotoScreen==sID_ManVA_Work)
			{
				if(TFTFlags.bWithTFTRx)
				{
					ProcCommandFromTFT_FATXQX();
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
				key=KeyCheck();
				if(key==KeyUp)
				{
					if(ManVAIndex[CurveNum]<50 || ManVAIndex[CurveNum]==0xff)
					{
						ManVAIndex[CurveNum]++;
						sprintf(DisplayLine,"%d.0",ManVAIndex[CurveNum]);
						SetTxt(sID_ManVA_Work,12,DisplayLine);						
						fx=ManVAIndex[CurveNum]*47.62;//*4096/4.096/21
						fx=fx/RomParams.FACorrection[CurveNum];
						AccelerateV=(unsigned int)(fx+0.5);
						SetCutOffV(AccelerateV);
						__delay_20ms(100);
						ReadAD1120();
						if(ADValue.s16<0)
						{
							ADValue.s16=0;
						}						
						fx=ADValue.s16*0.000763;
						sprintf(DisplayLine,"%.2f",fx);
						SetTxt(sID_ManVA_Work,1,DisplayLine);
						CurveData_FATX[CurveNum][ManVAIndex[CurveNum]]=ADValue.u16;


						ADValue.s16=ADValue.s16/4;
						AddCurveData(sID_ManVA_Work,8,CurveNum,ADValue.s16);
						AddCurveData(sID_ManVA,8,CurveNum,ADValue.s16);
						if(ADValue.u16>Curve1Max)
						{
							iy=30000/ADValue.u16;
							Curve1Max=30000/iy;
							SetCurveVerticalScaling(sID_ManVA,8,1000,iy);
							SetCurveVerticalScaling(sID_ManVA_Work,8,1000,iy);
							fx=Curve1Max;
							fx=fx*0.000763;
							fx=fx*4;
							fx=fx/5;
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
						}						
					}
				}
			}
			SetScreen(sID_ManVA);
			SetBright(0);
			SetCutOffV(0);
		}			
	}
	SetScreen(sID_ExperimentalProject);
}
void ProcCommandFromTFT_FATXQX( void )
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
				if(TFTMsg.screen_id.u8H==sID_AutoVA)//"伏安特性曲线"页面
				{
					if(TFTMsg.control_id.u8H==0x08)//开始实验
					{
						gFlags.bMeasure=1;
						SetProgress(sID_AutoVA_Work,2,0);
						//SwitchLED(0,0);
					}
					else if(TFTMsg.control_id.u8H==0x09)//返回
					{
						SwitchLED(0,0);
						SetBright(0);
						SetCutOffV(0);
						GotoScreen=sID_ExperimentalProject;
						MeasureTick=SystemTick-100;
					}
				}
				if(TFTMsg.screen_id.u8H==sID_ManVA)//"伏安特性曲线"页面
				{
					if(TFTMsg.control_id.u8H==11)//开始实验
					{
						gFlags.bMeasure=1;
					}
					else if(TFTMsg.control_id.u8H==9)//返回
					{
						SwitchLED(0,0);
						SetBright(0);
						SetCutOffV(0);
						GotoScreen=sID_ExperimentalProject;						
						MeasureTick=SystemTick-100;
					}
				}
				if(TFTMsg.screen_id.u8H==sID_ManVA_Work)//"伏安特性曲线"页面
				{
					if(TFTMsg.control_id.u8H==6)//
					{
						ManVAIndex[CurveNum]=0xff;
						DeleteCurve(sID_ManVA,8,CurveNum);
						DeleteCurve(sID_ManVA_Work,8,CurveNum);
						SetTxt(sID_ManVA_Work,12,"-.-");
						SetTxt(sID_ManVA_Work,1,"-.-");
						SetCutOffV(0);
					}
					else if(TFTMsg.control_id.u8H==9)//返回
					{
						GotoScreen=sID_ManVA;
					}
				}
			}			
		}
		break;
	}
}
