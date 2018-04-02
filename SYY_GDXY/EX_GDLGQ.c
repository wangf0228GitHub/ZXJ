#include "HardwareProfile.h"
#include <stdio.h>
#include "stdlib.h"
void ProcCommandFromTFT_GDLGQ( void );
unsigned char CheckWorkLED1(unsigned char sID)
{
	unsigned char i;
	gFlags.bError=0;
	CurveNum=0xff;
	for(int i=0;i<4;i++)
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
void EX_ProcGDLGQ_Auto(void)
{
	unsigned char i;
	unsigned int iy;
	float fx,fAccelerateV;
	ADGainControl_W=1;//前置小增益
	UcControl_W=1;//正向电压	
	//SetBright(0);
	CurveNum=0;
	MeasureTick=SystemTick-10000;
	while(GotoScreen==sID_AutoGQ)
	{		
 		if(TFTFlags.bWithTFTRx)
 		{
 			ProcCommandFromTFT_GDLGQ();
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
			SetTxt(sID_AutoGQ,10,DisplayLine);
		}
 		if(gFlags.bMeasure)
 		{
 			gFlags.bMeasure=0;
			if(CheckWorkLED1(sID_AutoGQ)==0)
			{
				if(CurveNum==0xff)
				{
					EnterDlgReNum=sID_AutoGQ;
					ShowEnterDlg(strPicI);
					continue;
				}
			}
			else
				continue;
			switch(CurveNum)
			{
			case 0:
				SetBright(7);
				break;
			case 1:
				SetBright(14);
				break;
			case 2:
				SetBright(21);
				break;
			case 3:
				SetBright(27);
				break;
			}
 			SwitchLED(1,1);
			SetScreen(sID_AutoGQ_Work);
			switch (CurveNum)
			{
			case 0:
				ShowPic(pID_GQCut,23,247,127,50);
				break;
			case 1:
				ShowPic(pID_GQCut,23,306,127,50);
				break;
			case 2:
				ShowPic(pID_GQCut,23,366,127,50);
				break;
			case 3:
				ShowPic(pID_GQCut,23,430,127,50);
				break;
			}
 			MeasureIndex=0;
 			fAccelerateV=0;
 			if(Curve2Flags[CurveNum]!=0)
 			{
 				DeleteCurve(sID_AutoGQ,11,CurveNum);
				DeleteCurve(sID_AutoGQ_Work,11,CurveNum);
 			}
 			for(i=0;i<101;i++)
 			{				
 				fx=fAccelerateV;///RomParams.FACorrection[CurveNum];
				fx=fx*47.62;//*4096/4.096/21
				AccelerateV=(unsigned int)(fx+0.5);
				SetCutOffV(AccelerateV);
				//__delay_20ms(20);
				__delay_20ms(75);
				ReadAD1120();
 				if(ADValue.s16<0)
 				{
 					ADValue.s16=0;
 				}
				sprintf(DisplayLine,"%.1f",fAccelerateV);
				SetTxt(sID_AutoGQ_Work,1,DisplayLine);
				fx=ADValue.s16*0.000763;
				sprintf(DisplayLine,"%.2f",fx);
				SetTxt(sID_AutoGQ_Work,10,DisplayLine);
				fAccelerateV=fAccelerateV+0.5;		

 				CurveData_GDLGQ[CurveNum][i]=ADValue.u16;
				

				ADValue.s16=ADValue.s16/4;
 				AddCurveData(sID_AutoGQ,11,CurveNum,ADValue.s16);
				AddCurveData(sID_AutoGQ_Work,11,CurveNum,ADValue.s16);
 				if(ADValue.u16>Curve2Max)
 				{
 					iy=30000/ADValue.u16;
 					Curve2Max=30000/iy;
 					SetCurveVerticalScaling(sID_AutoGQ,11,500,iy);
					SetCurveVerticalScaling(sID_AutoGQ_Work,11,500,iy);
 					fx=Curve2Max;
 					fx=fx*0.000763;
					fx=fx*4;
					fx=fx/5;
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
 				}
 				SetProgress(sID_AutoGQ_Work,9,i);
 			}
 			SetProgress(sID_AutoGQ_Work,9,100);
 			SwitchLED(1,0);
			SetBright(0);
			SetCutOffV(0);
 			Curve2Flags[CurveNum]=1;
			EnterDlgReNum=sID_AutoGQ;
			ShowEnterDlg(strCurveFinish);
 		}		
	}
	SetScreen(sID_ExperimentalProject);
}
void EX_ProcGDLGQ_Man(void)
{
	unsigned char i,key;
	unsigned int iy;
	float fx,fAccelerateV=0;;
	ADGainControl_W=1;//前置小增益
	UcControl_W=1;//正向电压
	CurveNum=0;
	MeasureTick=SystemTick-10000;
	while(GotoScreen==sID_ManGQ)
	{		
		if(TFTFlags.bWithTFTRx)
		{
			ProcCommandFromTFT_GDLGQ();
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
			SetTxt(sID_ManGQ,8,DisplayLine);
		}
		if(gFlags.bMeasure)
		{
			gFlags.bMeasure=0;
			if(CheckWorkLED1(sID_ManGQ)==0)
			{
				if(CurveNum==0xff)
				{
					EnterDlgReNum=sID_ManGQ;
					ShowEnterDlg(strPicF);
					continue;
				}
			}
			else
				continue;			
			switch(CurveNum)
			{
			case 0:
				SetBright(7);
				break;
			case 1:
				SetBright(14);
				break;
			case 2:
				SetBright(21);
				break;
			case 3:
				SetBright(27);
				break;
			}
			SwitchLED(1,1);
			SetScreen(sID_ManGQ_Work);
			switch (CurveNum)
			{
			case 0:
				ShowPic(pID_GQCut,23,247,127,50);
				break;
			case 1:
				ShowPic(pID_GQCut,23,306,127,50);
				break;
			case 2:
				ShowPic(pID_GQCut,23,366,127,50);
				break;
			case 3:
				ShowPic(pID_GQCut,23,430,127,50);
				break;
			}
			if(ManGQIndex[CurveNum]==0xff)
			{
				//sprintf(DisplayLine,"%d",ManVAIndex[CurveNum]);
				SetTxt(sID_ManGQ_Work,8,"-.-");
				SetTxt(sID_ManGQ_Work,15,"-.-");
			}
			else
			{
				sprintf(DisplayLine,"%d.0",ManGQIndex[CurveNum]);
				SetTxt(sID_ManGQ_Work,15,DisplayLine);
				fx=CurveData_GDLGQ[CurveNum][ManGQIndex[CurveNum]]*0.000763;
				sprintf(DisplayLine,"%.2f",fx);
				SetTxt(sID_ManVA_Work,8,DisplayLine);
			}
			while(GotoScreen==sID_ManGQ_Work)
			{
				if(TFTFlags.bWithTFTRx)
				{
					ProcCommandFromTFT_GDLGQ();
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
					if(ManGQIndex[CurveNum]<50 || ManGQIndex[CurveNum]==0xff)
					{
						ManGQIndex[CurveNum]++;
						sprintf(DisplayLine,"%d.0",ManGQIndex[CurveNum]);
						SetTxt(sID_ManGQ_Work,15,DisplayLine);						
						fx=ManGQIndex[CurveNum]*47.62;//*4096/4.096/21						
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
						SetTxt(sID_ManGQ_Work,8,DisplayLine);
						CurveData_GDLGQ[CurveNum][ManGQIndex[CurveNum]]=ADValue.u16;


						ADValue.s16=ADValue.s16/4;
						AddCurveData(sID_ManGQ_Work,11,CurveNum,ADValue.s16);
						AddCurveData(sID_ManGQ,11,CurveNum,ADValue.s16);
						if(ADValue.u16>Curve2Max)
						{
							iy=30000/ADValue.u16;
							Curve2Max=30000/iy;
							SetCurveVerticalScaling(sID_ManGQ,11,1000,iy);
							SetCurveVerticalScaling(sID_ManGQ_Work,11,1000,iy);
							fx=Curve2Max;
							fx=fx*0.000763;
							fx=fx*4;
							fx=fx/5;
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
						}						
					}
				}
			}
			SetBright(0);
			SetCutOffV(0);
			SetScreen(sID_ManGQ);
		}			
	}
	SetScreen(sID_ExperimentalProject);
}
void ProcCommandFromTFT_GDLGQ( void )
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
				if(TFTMsg.screen_id.u8H==sID_AutoGQ)//"光电流光强"页面
				{
					if(TFTMsg.control_id.u8H==0x07)//开始实验
					{
						gFlags.bMeasure=1;
						SetProgress(sID_AutoGQ,9,0);
						//SwitchLED(0,0);
					}
					else if(TFTMsg.control_id.u8H==0x08)//返回
					{
						SwitchLED(0,0);
						SetBright(0);
						SetCutOffV(0);
						GotoScreen=sID_ExperimentalProject;
						MeasureTick=SystemTick-100;
					}
				}
				else if(TFTMsg.screen_id.u8H==sID_ManGQ)
				{
					if(TFTMsg.control_id.u8H==6)//开始实验
					{
						gFlags.bMeasure=1;						
					}
					else if(TFTMsg.control_id.u8H==0x07)//返回
					{
						SwitchLED(0,0);
						SetBright(0);
						SetCutOffV(0);
						GotoScreen=sID_ExperimentalProject;						
						MeasureTick=SystemTick-100;
					}
				}
				if(TFTMsg.screen_id.u8H==sID_ManGQ_Work)//"伏安特性曲线"页面
				{
					if(TFTMsg.control_id.u8H==4)//
					{
						ManGQIndex[CurveNum]=0xff;
						DeleteCurve(sID_ManGQ,11,CurveNum);
						DeleteCurve(sID_ManGQ_Work,11,CurveNum);
						SetTxt(sID_ManGQ_Work,8,"-.-");
						SetTxt(sID_ManGQ_Work,15,"-.-");
						SetCutOffV(0);
					}
					else if(TFTMsg.control_id.u8H==6)//返回
					{
						GotoScreen=sID_ManGQ;
					}
				}
			}			
		}
		break;
	}
}
