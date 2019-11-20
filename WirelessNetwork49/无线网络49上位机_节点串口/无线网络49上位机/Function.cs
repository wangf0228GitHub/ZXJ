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
        void ADCDataProc()
        {
            int liIndex = 0;
            int dataIndex = 0;
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:ffff") + ":收到传感器数据\r\n");//WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " ")\
                //ListViewItem li = listView1.Items[liIndex];
                sensorBAT.H[0] = RxPacket.Data[dataIndex + 7680];
                //li.SubItems[2].Text = sensorBAT.H[0].ToString();
                ushort ad1, ad2 = 0;
                byte[] adad = new byte[3];
                if (chart1.Series[0].Points.Count > 5120 * 4)
                    chart1.Series[0].Points.Clear();
                //                         StringBuilder debug = new StringBuilder();
                //                         debug.Append(WFNetLib.StringFunc.StringsFunction.byteToHexStr(RxPacket.Data, " "));
                //                         debug.Append("\r\n");
                for (int i = 0; i < 7680; i += 3)
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
                    chart1.Series[0].Points.AddY(ad1);
                    chart1.Series[0].Points.AddY(ad2);
                }
                //li.SubItems[1].Text = ad2.ToString();
                liIndex++;
                dataIndex = dataIndex + 7681;
            }));
        }
    }
}
