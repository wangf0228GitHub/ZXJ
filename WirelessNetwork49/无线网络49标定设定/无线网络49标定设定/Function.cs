using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.PacketProc;
using WFNetLib;
using System.Diagnostics;
using System.Threading;

namespace 无线网络49上位机
{
    public partial class Form1 : Form
    {        
        void SignInProc()
        {            
            this.Invoke((EventHandler)(delegate
            {
                sensorSingIn.clearSignIn();
                listView1.Items.Clear();
                lNetStatus.Text = "收到网络节点名单";
                textBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:ffff") + ":收到节点名单\r\n");//WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " ")\
                for (int k = 0; k < 4; k++)
                {
                    if (RxPacket.Data[k] != 0)
                    {
                        sensorSingIn.H[k] = true;
                        sensorBAT.H[k] = RxPacket.Data[104 + k];
                        ListViewItem li= listView1.Items.Add((k + 1).ToString());
                        li.SubItems.Add("0");
                        li.SubItems.Add( Calc.GetBAT(sensorBAT.H[k]));
                    }
                }
                for (int k = 0; k < 6; k++)
                {
                    if (RxPacket.Data[4+k] != 0)
                    {
                        sensorSingIn.M[k] = true;
                        sensorBAT.M[k] = RxPacket.Data[104 + 4 + k];
                        ListViewItem li = listView1.Items.Add((k + 4 + 1).ToString());
                        li.SubItems.Add("0");
                        li.SubItems.Add(Calc.GetBAT(sensorBAT.M[k]));
                    }
                }
                for (int k = 0; k < 90; k++)
                {
                    if (RxPacket.Data[12+k] != 0)
                    {
                        sensorSingIn.L[k] = true;
                        sensorBAT.L[k] = RxPacket.Data[104 + 12 + k];
                        ListViewItem li = listView1.Items.Add((k + 10 + 1).ToString());
                        li.SubItems.Add("0");
                        li.SubItems.Add(Calc.GetBAT(sensorBAT.L[k]));
                    }
                }                
            }));
        }
        
        void ADCDataProc()
        {
            int liIndex = 0;
            int dataIndex = 0;
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:ffff") + ":收到传感器数据\r\n");//WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " ")\
                for (int k = 0; k < 4; k++)
                {                    
                    if (sensorSingIn.H[k])
                    {
                        ListViewItem li = listView1.Items[liIndex];                                               
                        sensorBAT.H[k] = RxPacket.Data[dataIndex+7680];
                        li.SubItems[2].Text = Calc.GetBAT(sensorBAT.H[k]);
                        ushort ad1,ad2=0;
                        byte[] adad=new byte[3];
                        adad[0] = RxPacket.Data[0];
                        adad[1] = RxPacket.Data[1];
                        adad[2] = RxPacket.Data[2];
                        ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                        ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);

                        li.SubItems[1].Text = ad1.ToString("");
                        liIndex++;
                        dataIndex = dataIndex + 7681;
                        //Debug.WriteLine(debug.ToString());
                    }
                }
                for (int k = 0; k < 6; k++)
                {
                    if (sensorSingIn.M[k])
                    {
                        ListViewItem li = listView1.Items[liIndex];
                        sensorBAT.M[k] = RxPacket.Data[dataIndex + 480];
                        li.SubItems[2].Text = Calc.GetBAT(sensorBAT.M[k]);
                        ushort ad1, ad2 = 0;
                        byte[] adad = new byte[3];
                        adad[0] = RxPacket.Data[0];
                        adad[1] = RxPacket.Data[1];
                        adad[2] = RxPacket.Data[2];
                        ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                        ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);
                        li.SubItems[1].Text = ad1.ToString();
                        liIndex++;
                        dataIndex = dataIndex + 481;
                        //Debug.WriteLine(debug.ToString());
                    }
                }
                for (int k = 0; k < 90; k++)
                {
                    if (sensorSingIn.L[k])
                    {
                        ListViewItem li = listView1.Items[liIndex];
                        sensorBAT.L[k] = RxPacket.Data[dataIndex + 60];
                        li.SubItems[2].Text = Calc.GetBAT(sensorBAT.M[k]);
                        ushort ad1, ad2 = 0;
                        byte[] adad = new byte[3];
                        adad[0] = RxPacket.Data[0];
                        adad[1] = RxPacket.Data[1];
                        adad[2] = RxPacket.Data[2];
                        ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                        ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);
                        li.SubItems[1].Text = ad1.ToString();
                        liIndex++;
                        dataIndex = dataIndex + 601;
                        //Debug.WriteLine(debug.ToString());
                    }
                }
            }));
        }
        bool bSignIn = false;
        void waitWakeUp(object LockWatingThread)//等待唤醒完成，20s
        {
            bSignIn = false;
            int x=0;
            while (true)
            {                
                Thread.Sleep(1);
                x++;
                if (x >= 1000)
                {
                    x = 0;
                    waitProc.SetProcessBarPerformStep();
                }
                if (bSignIn)
                    return;
            }
        }
        bool bDataComing = false;
        void waitSignIn(object LockWatingThread)//等待点名完成，10s
        {
            bDataComing = false;
            int x = 0;
            while (true)
            {
                Thread.Sleep(1);
                x++;
                if (x >= 1000)
                {
                    x = 0;
                    waitProc.SetProcessBarPerformStep();
                }
                if (bDataComing)
                    return;
            }
        }
    }
}
