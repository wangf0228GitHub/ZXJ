using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.PacketProc;
using WFNetLib;
using System.Diagnostics;

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
                        li.SubItems.Add(sensorBAT.H[k].ToString());
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
                        li.SubItems.Add(sensorBAT.M[k].ToString());
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
                        li.SubItems.Add(sensorBAT.L[k].ToString());
                    }
                }
                if (listView1.Items.Count == 0)//空网络
                {
                    Uart.Close();
                    btNetStart.Text = "启动网络";
                    MessageBox.Show("当前网络没有发现任何无线节点，网络自动停止");
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
                        if (chart1.Series[0].Points.Count > 5120*4)
                            chart1.Series[0].Points.Clear();
//                         StringBuilder debug = new StringBuilder();
//                         debug.Append(WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " "));
//                         debug.Append("\r\n");
                        //double u1=0.0, u2=0.0;
                        for (int i = 0; i < 7680; i += 3)
                        {
                            adad[0]=RxPacket.Data[dataIndex+i];
                            adad[1]=RxPacket.Data[dataIndex+i+1];
                            adad[2]=RxPacket.Data[dataIndex+i+2];
                            
                            ad1=BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                            ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);
//                             debug.Append(ad1.ToString("X4"));
//                             debug.Append(" ");
//                             debug.Append(ad2.ToString("X4"));
//                             debug.Append(" ");
//                             Uadc1 = ad1 * 3.0 / 4096.0;
//                             Uadc2 = ad2 * 3.0 / 4096.0;
//                             u1 = Uadc1 - 1.5;
//                             u2 = Uadc2 - 1.5;
                            if (i == 0)
                            {
                                double u = ad1 * 3.0 / 4096.0;
                                Debug.WriteLine((k + 1).ToString() + ":" + u.ToString("F03") + "V");
                            }
                            
                            chart1.Series[0].Points.AddY(Calc.GetSensorType0(k, ad1));
                            chart1.Series[0].Points.AddY(Calc.GetSensorType0(k, ad2));
                        }
                        li.SubItems[1].Text = Calc.GetSensorType0(k, ad2).ToString("F02");
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
                        if (chart2.Series[0].Points.Count > 320 * 4)
                            chart2.Series[0].Points.Clear();
                        //                         StringBuilder debug = new StringBuilder();
                        //                         debug.Append(WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " "));
                        //                         debug.Append("\r\n");
                        //double u1=0.0, u2=0.0;
                        for (int i = 0; i < 480; i += 3)
                        {
                            adad[0] = RxPacket.Data[dataIndex + i];
                            adad[1] = RxPacket.Data[dataIndex + i + 1];
                            adad[2] = RxPacket.Data[dataIndex + i + 2];
                            ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                            ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);
                            //                             debug.Append(ad1.ToString("X4"));
                            //                             debug.Append(" ");
                            //                             debug.Append(ad2.ToString("X4"));
                            //                             debug.Append(" ");
                            
//                             Uadc1 = ad1 * 3.0 / 4096.0;
//                             Uadc2 = ad2 * 3.0 / 4096.0;
//                             u1 = Uadc1 - 1.5;
//                             u2 = Uadc2 - 1.5;
                            if (i == 0)
                            {
                                double u = ad1 * 3.0 / 4096.0;
                                Debug.WriteLine((k + 5).ToString() + ":" + u.ToString("F03") + "V");
                            }                            
                            chart2.Series[0].Points.AddY(Calc.GetSensorType1(k, ad1));
                            chart2.Series[0].Points.AddY(Calc.GetSensorType1(k, ad2));
                        }
                        li.SubItems[1].Text = Calc.GetSensorType1(k, ad2).ToString("F02");
                        liIndex++;
                        dataIndex = dataIndex + 481;
                        //Debug.WriteLine(debug.ToString());
                    }
                }
                bool bNeedDebug = false;
                for (int k = 0; k < 90; k++)
                {
                    if(k>7)//模拟网络中仅启用低速的前8个地址：11~18
                        break;
                    if (sensorSingIn.L[k])
                    {
                        ListViewItem li = listView1.Items[liIndex];
                        sensorBAT.L[k] = RxPacket.Data[dataIndex + 60];
                        li.SubItems[2].Text = Calc.GetBAT(sensorBAT.L[k]);
                        ushort ad1, ad2 = 0;
                        byte[] adad = new byte[3];
                        if (k < 4)//温度
                        {
                            if (chart3.Series[k].Points.Count > 40 * 4)
                            {
                                //for (int i = 0; i < chart3.Series.Count; i ++)
                                chart3.Series[k].Points.Clear();
                            }
                            //                         StringBuilder debug = new StringBuilder();
                            //                         debug.Append(WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " "));
                            //                         debug.Append("\r\n");                            
                            double T=0;
                            int pointIndex;
                            for (int i = 0; i < 60; i += 3)
                            {
                                adad[0] = RxPacket.Data[dataIndex + i];
                                adad[1] = RxPacket.Data[dataIndex + i + 1];
                                adad[2] = RxPacket.Data[dataIndex + i + 2];
                                ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                                ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);
                                //                             debug.Append(ad1.ToString("X4"));
                                //                             debug.Append(" ");
                                //                             debug.Append(ad2.ToString("X4"));
                                //                             debug.Append(" ");
//                                 Uadc1 = ad1 * 3.0 / 4096.0;
//                                 Uadc2 = ad2 * 3.0 / 4096.0;
                                if (i == 0)
                                {
                                    double u = ad1 * 3.0 / 4096.0;
                                    Debug.WriteLine((k + 11).ToString() + ":" + u.ToString("F03") + "V");
                                }
                                
                                switch (k)
                                {
                                    case 0:
                                        T = Calc.GetSensorType2_11(ad1);
                                        break;
                                    case 1:
                                        T = Calc.GetSensorType2_12(ad1);
                                        break;
                                    case 2:
                                        T = Calc.GetSensorType2_13(ad1);
                                        break;
                                    case 3:
                                        T = Calc.GetSensorType2_14(ad1);
                                        break;
                                }
                                pointIndex = chart3.Series[k].Points.AddY(T);
                                if (T == -100)
                                {
                                    chart3.Series[k].Points[pointIndex].IsEmpty = true;
                                }
                                switch (k)
                                {
                                    case 0:
                                        T = Calc.GetSensorType2_11(ad2);
                                        break;
                                    case 1:
                                        T = Calc.GetSensorType2_12(ad2);
                                        break;
                                    case 2:
                                        T = Calc.GetSensorType2_13(ad2);
                                        break;
                                    case 3:
                                        T = Calc.GetSensorType2_14(ad2);
                                        break;
                                }
                                pointIndex = chart3.Series[k].Points.AddY(T);
                                if (T == -100)
                                {
                                    chart3.Series[k].Points[pointIndex].IsEmpty = true;
                                }                                
                            }
                            li.SubItems[1].Text = T.ToString("F01");
                        }
                        else//压力
                        {
                            if (chart4.Series[k-4].Points.Count > 40 * 4)
                            {
                                //for (int i = 0; i < chart3.Series.Count; i ++)
                                chart4.Series[k-4].Points.Clear();
                            }
                            //                         StringBuilder debug = new StringBuilder();
                            //                         debug.Append(WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " "));
                            //                         debug.Append("\r\n");
                            for (int i = 0; i < 60; i += 3)
                            {
                                adad[0] = RxPacket.Data[dataIndex + i];
                                adad[1] = RxPacket.Data[dataIndex + i + 1];
                                adad[2] = RxPacket.Data[dataIndex + i + 2];
                                ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                                ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);
                                //                             debug.Append(ad1.ToString("X4"));
                                //                             debug.Append(" ");
                                //                             debug.Append(ad2.ToString("X4"));
                                //                             debug.Append(" ");
//                                 Uadc1 = ad1 * 3.0 / 4096.0;
//                                 Uadc2 = ad2 * 3.0 / 4096.0;
                                if (i == 0)
                                {
                                    double u = ad1 * 3.0 / 4096.0;
                                    Debug.WriteLine((k + 11).ToString() + ":" + u.ToString("F03") + "V");
                                }
                                chart4.Series[k-4].Points.AddY(Calc.GetSensorType2_15_18(ad1));
                                chart4.Series[k - 4].Points.AddY(Calc.GetSensorType2_15_18(ad2));
                            }
                            li.SubItems[1].Text = Calc.GetSensorType2_15_18(ad2).ToString("F01");
                        }
                        if(bNeedDebug)
                        {
                            StringBuilder debug = new StringBuilder();
                            debug.Append(WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " "));
                            debug.Append("\r\n");
                            Debug.WriteLine(debug.ToString());
                        }
                        liIndex++;
                        dataIndex = dataIndex + 61;
                        //Debug.WriteLine(debug.ToString());
                    }
                }
            }));
        }
    }
}
