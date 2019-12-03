using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib;
using System.Threading;
using ULONG = System.UInt32;
using System.Runtime.InteropServices;
using System.Diagnostics;
using WFNetLib.Log;
using WFNetLib.StringFunc;
namespace pcieDataRecorder
{
	public partial class Form1 : Form
	{
		const int TRUE = 1;
		const int FALSE = 0;
        IntPtr pCH368;
        ULONG CH368Index = 0;
        IntPtr mBaseAddr;
        IntPtr mMemAddr;
        ULONG oIntLine;
		public Form1()
		{
			InitializeComponent();
		}        
		private void Form1_Load(object sender, EventArgs e)
		{
			//IntPtr pCH368 = CH368.CH367mOpenDevice(0, FALSE, TRUE, 0x00);
			//MessageBox.Show(pCH368.ToString());
            //MeasureE0DataDBOption e0 = new MeasureE0DataDBOption();
            //MeasureE0DataDBOption.Insert(new MeasureE0Data());
            this.Enabled = false;
            startTimer.Enabled = true;
		}
        CH368.mPCH367_INT_ROUTINE _CH368IntProc;
        bool bLog = true;
        void CH368IntProc()
        {
            byte[] readHeaderList = new byte[7];
            byte[] readDataList = new byte[0x100];
            byte read = 0;
            /************************************************************************/
            /*  读ram                                                               */
            /************************************************************************/
            //拉低片选
            if (CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xf8,0xb0) == 0)
            {
                MessageBox.Show("1");
                return;
            }
            //读7个字节,判断是否为有效帧
//             CH368.CH367mAccessBlock(CH368Index, CH368.mFuncReadMemByte, mMemAddr, readList, 64);
//             this.Invoke((EventHandler)(delegate { textBox1.Text = StringsFunction.byteToHexStr(readList, 0, (int)64, " "); }));
            //Debug.WriteLine(StringsFunction.byteToHexStr(readList, 0, (int)9, " "));
            if (CH368.CH367mAccessBlock(CH368Index, CH368.mFuncReadMemByte, mMemAddr, readHeaderList, 7) == 0)
            {
                MessageBox.Show("2");
                return;
            }
            if (bLog)
            {
                this.Invoke((EventHandler)(delegate 
                {
					textBox1.AppendText(DateTime.Now.ToString() + ":");
                    textBox1.AppendText(StringsFunction.byteToHexStr(readHeaderList, 0, 7, " ")); 
                }));
                //Debug.WriteLine(StringsFunction.byteToHexStr(readList, 0, 7, " "));
            }
            
            if (readHeaderList[0] == 0xfa && readHeaderList[1] == 0xf3 && readHeaderList[2] == 0x30)
            {
                //Debug.WriteLine(StringsFunction.byteToHexStr(readList, 0, 7, " "));
                uint readDataLen = BytesOP.MakeShort(readHeaderList[5], readHeaderList[6]);
                if (CH368.CH367mAccessBlock(CH368Index, CH368.mFuncReadMemByte, mMemAddr + 7, readDataList, readDataLen) == 0)
                {
                    MessageBox.Show("3");
                    return;
                }                
                if (bLog)
                {
                    this.Invoke((EventHandler)(delegate
                    {						
                        textBox1.AppendText(StringsFunction.byteToHexStr(readDataList, 0, (int)readDataLen, " "));
                    }));
                }
                if (readHeaderList[3] == 0xe0 || readHeaderList[3] == 0xe2)
                {
                    MeasureE0Data e0 = new MeasureE0Data();
                    e0.Source = readHeaderList[3];
                    Fuction.AnalyzeE0Data(ref e0, readDataList, readDataLen);
                    e0.Time = DateTime.Now;
					MeasureE0DataDBOption.Insert(e0);
                }
                else if (readHeaderList[3] == 0xe1 || readHeaderList[3] == 0xe3)
                {
                    MeasureE1Data e1 = new MeasureE1Data();
                    e1.Source = readHeaderList[3];
                    Fuction.AnalyzeE1Data(ref e1, readDataList, readDataLen);
                    e1.Time = DateTime.Now;
                    MeasureE1DataDBOption.Insert(e1);
                }
                //Debug.WriteLine(StringsFunction.byteToHexStr(readList, 0, (int)len, " "));
            }
            if (bLog)
            {                
                this.Invoke((EventHandler)(delegate
                {
					textBox1.AppendText("\r\n");
// 					bLog = false;
//                     timerLog.Enabled = true;
                }));
            }
            //拉高片选 
            if (CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xf8, 0xb1) == 0)
            {
                MessageBox.Show("4");
                return;
            }
            /************************************************************************/
            /*  完成读取，告知单片机                                                */
            /************************************************************************/
            //拉低SCS，表示在处理完成
            if (CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xe8, 0x03) == 0)
            {
                MessageBox.Show("5");
                return;
            }
            //等待单片机退出通信流程
            while (true)
            {
                if (CH368.CH367mReadIoByte(CH368Index, mBaseAddr + 0xf8, ref read) == 0)
                {
                    MessageBox.Show("10");
                    return;
                }
                if (BytesOP.GetBit(read, 3))
                    break;
            }
             //SCS 高电平 
            if(CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xe8, 0x07)==0)
            {
                MessageBox.Show("12");
                return;
            }
        }
        void InitPCIE()
        {
            byte[] readList=new byte[0x100];
            byte read=0;
            //获得中断号
            CH368.CH367mGetIntLine(CH368Index, ref oIntLine);
            //取得操作基地址
            CH368.CH367mGetIoBaseAddr(CH368Index,out mBaseAddr);
            CH368.CH368mGetMemBaseAddr(CH368Index, out mMemAddr);
            //RAM CE 高电平 A15
            CH368.CH367mReadIoByte(CH368Index, mBaseAddr + 0xf8, ref read);
            BytesOP.SetBit(ref read, 0);
            BytesOP.ClrBit(ref read, 2);//清中断标志
            CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xf8, read);
            //8位数据总线
            CH368.CH367mReadIoByte(CH368Index, mBaseAddr + 0xfa, ref read);
            BytesOP.ClrBit(ref read, 6);
            CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xfa, read);
            //SCS 高电平 
            CH368.CH367mReadIoByte(CH368Index, mBaseAddr + 0xe8, ref read);
            BytesOP.SetBit(ref read, 2);
            CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xe8, read);
            //配置中断服务程序
            _CH368IntProc=new CH368.mPCH367_INT_ROUTINE(CH368IntProc);
            CH368.CH367mSetIntRoutine(CH368Index, _CH368IntProc);
            //低电平中断
            read = 0xe2;
            CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xeb, read);
            //首次判断
//             CH368.CH367mReadIoByte(CH368Index, mBaseAddr + 0xf8, ref read);
//             if (!BytesOP.GetBit(read, 3))
//             {
//                 CH368.CH367mReadIoByte(CH368Index, mBaseAddr + 0xe8, ref read);
//                 BytesOP.ClrBit(ref read, 2);//拉低SCS
//                 CH368.CH367mWriteIoByte(CH368Index, mBaseAddr + 0xe8, read);
//                 while (true)
//                 {
//                     CH368.CH367mReadIoByte(CH368Index, mBaseAddr + 0xf8, ref read);
//                     if (BytesOP.GetBit(read, 3))
//                         break;
//                 }
//             }
            //CH368.CH367mAccessBlock(CH368Index, CH368.mFuncReadIoByte, mBaseAddr->mCH367IoPort[mAddr], read, 1);
        }
		private void button1_Click(object sender, EventArgs e)
		{
			
		}
        WaitingProc wp;
        private void startTimer_Tick(object sender, EventArgs e)
        {
            startTimer.Enabled = false;
            pCH368 = CH368.CH367mOpenDevice(CH368Index, TRUE, TRUE, 0x00);
			if (pCH368 == (IntPtr)(-1))
			{
				wp = new WaitingProc();
				WaitingProcFunc wpf = new WaitingProcFunc(WaitingPCIE);
				wp.Execute(wpf, "等待连接采集卡", WaitingType.With_ConfirmCancel, "未连接到采集卡，取消将退出软件，是否取消？");
			}
			else
			{
				this.Invoke((EventHandler)(delegate
				{
					this.Enabled=true;
				}));
				InitPCIE();
			}
        }
        void WaitingPCIE(object LockWatingThread)
        {
            while(true)
            {
                pCH368 = CH368.CH367mOpenDevice(CH368Index, TRUE, TRUE, 0x00);
                if (pCH368 != (IntPtr)(-1))
                {
                    this.Invoke((EventHandler)(delegate
                    {
                        InitPCIE();
                    }));
                    return;
                }
                Thread.Sleep(1000);                
                lock (LockWatingThread)
                {
                    wp.SetProcessBarPerformStep();
                    if (wp.HasBeenCancelled())
                    {
                        this.Invoke((EventHandler)(delegate
                        {
                            this.Close();                           
                        }));
                        return;
                    }
                }
            }
        }

        private void timerLog_Tick(object sender, EventArgs e)
        {
            timerLog.Enabled = false;
            bLog = true;
        }

		private void textBox1_TextChanged(object sender, EventArgs e)
		{
			if (textBox1.Text.Length > 20000)
				textBox1.Clear();
		}
	}
}
