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
        void SignInProc(CP1616Packet rxPacket)
        {            
            this.Invoke((EventHandler)(delegate
            {
                sensorSingIn.clearSignIn();
                listView1.Items.Clear();
                textBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:ffff") + ":收到节点名单\r\n");//WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " ")\
                for (int k = 0; k < 4; k++)
                {
                    if (rxPacket.Data[k] != 0)
                    {
                        sensorSingIn.H[k] = true;
                        sensorBAT.H[k] = rxPacket.Data[104 + k];
                        ListViewItem li= listView1.Items.Add((k + 1).ToString());
                        li.SubItems.Add("0");
                        li.SubItems.Add("0");
                        li.SubItems.Add( Calc.GetBAT(sensorBAT.H[k]));
                    }
                }
                for (int k = 0; k < 6; k++)
                {
                    if (rxPacket.Data[4+k] != 0)
                    {
                        sensorSingIn.M[k] = true;
                        sensorBAT.M[k] = rxPacket.Data[104 + 4 + k];
                        ListViewItem li = listView1.Items.Add((k + 4 + 1).ToString());
                        li.SubItems.Add("0");
                        li.SubItems.Add("0");
                        li.SubItems.Add(Calc.GetBAT(sensorBAT.M[k]));
                    }
                }
                for (int k = 0; k < 90; k++)
                {
                    if (rxPacket.Data[12+k] != 0)
                    {
                        sensorSingIn.L[k] = true;
                        sensorBAT.L[k] = rxPacket.Data[104 + 12 + k];
                        ListViewItem li = listView1.Items.Add((k + 10 + 1).ToString());
                        li.SubItems.Add("0");
                        li.SubItems.Add("0");
                        li.SubItems.Add(Calc.GetBAT(sensorBAT.L[k]));
                    }
                }                
            }));
        }

        void ADCDataProc(CP1616Packet rxPacket)
        {
            int liIndex = 0;
            int dataIndex = 0;
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:ffff") + ":收到传感器数据\r\n");//WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " ")\
                Debug.WriteLine(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rxPacket.Data, " "));
                for (int k = 0; k < 4; k++)
                {                    
                    if (sensorSingIn.H[k])
                    {
                        sensorBAT.H[k] = rxPacket.Data[dataIndex + 3];
                        ListViewItem li = listView1.Items[liIndex]; 
                        li.SubItems[3].Text = Calc.GetBAT(sensorBAT.H[k]);
                        ushort ad1,ad2=0;
                        byte[] adad=new byte[3];
                        adad[0] = rxPacket.Data[dataIndex+0];
                        adad[1] = rxPacket.Data[dataIndex+1];
                        adad[2] = rxPacket.Data[dataIndex+2];
                        ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                        ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);

                        li.SubItems[1].Text = ad1.ToString("");
                        li.SubItems[2].Text = ad2.ToString("");
                        liIndex++;
                        dataIndex = dataIndex + 4;
                        //Debug.WriteLine(debug.ToString());
                    }
                }
                for (int k = 0; k < 6; k++)
                {
                    if (sensorSingIn.M[k])
                    {
                        sensorBAT.M[k] = rxPacket.Data[dataIndex + 3];
                        ListViewItem li = listView1.Items[liIndex];
                        li.SubItems[3].Text = Calc.GetBAT(sensorBAT.M[k]);
                        ushort ad1, ad2 = 0;
                        byte[] adad = new byte[3];
                        adad[0] = rxPacket.Data[dataIndex + 0];
                        adad[1] = rxPacket.Data[dataIndex + 1];
                        adad[2] = rxPacket.Data[dataIndex + 2];
                        ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                        ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);

                        li.SubItems[1].Text = ad1.ToString("");
                        li.SubItems[2].Text = ad2.ToString("");
                        liIndex++;
                        dataIndex = dataIndex + 4;
                    }
                }
                for (int k = 0; k < 90; k++)
                {
                    if (sensorSingIn.L[k])
                    {
                        sensorBAT.L[k] = rxPacket.Data[dataIndex + 3];
                        ListViewItem li = listView1.Items[liIndex];
                        li.SubItems[3].Text = Calc.GetBAT(sensorBAT.L[k]);
                        ushort ad1, ad2 = 0;
                        byte[] adad = new byte[3];
                        adad[0] = rxPacket.Data[dataIndex + 0];
                        adad[1] = rxPacket.Data[dataIndex + 1];
                        adad[2] = rxPacket.Data[dataIndex + 2];
                        ad1 = BytesOP.MakeShort(BytesOP.GetLowNibble(adad[1]), adad[0]);
                        ad2 = BytesOP.MakeShort(BytesOP.GetHighNibble(adad[1]), adad[2]);

                        li.SubItems[1].Text = ad1.ToString("");
                        li.SubItems[2].Text = ad2.ToString("");
                        liIndex++;
                        dataIndex = dataIndex + 4;
                    }
                }
            }));
        }        
    }
}
