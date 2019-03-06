using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.TCP;
using System.Net;
using WFNetLib.PacketProc;
using WFNetLib;

namespace 电源控制器网络管理
{
    public partial class Form2 : Form
    {
        TCPAsyncServer tcpAsyncServer;
        string strIP;
        ClientContext clientContext;
        public Form2(TCPAsyncServer _tcpAsyncServer,string _ip,ClientContext _cc)
        {
            InitializeComponent();
            tcpAsyncServer = _tcpAsyncServer;
            strIP = _ip;
            clientContext = _cc;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            tcpAsyncServer.ErrorServerEvent += new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.ReceiveServerEvent += new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent); 
        }
        void NetLog(string str)
        {
            textBox1.AppendText(str);
            WFNetLib.Log.TextLog.AddTextLog(str);
        }
        private void tcpAsyncServer_ReceiveServerEvent(object sender, ReceiveServerEventArgs e)
        {
            IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            //if (ip.Address.Equals(Form1.mcuSocketIP.Address))
            if (ip.Address.ToString()==strIP)
            {
                this.Invoke((EventHandler)(delegate
                {
                    CP1616_NoAddr_Packet rx = (CP1616_NoAddr_Packet)e.netPacket;
                    if (rx.Header.Command == 0x02)//读取网络参数
                    {
                        tabControl1.Enabled = true;
                        timer1.Enabled = false;
                        textBox6.Text = WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, 0, 6, " ");
                        byte[] bIP = new byte[4];
                        for (int i = 0; i < 4; i++)
                        {
                            bIP[i] = rx.Data[8 + i];
                        }
                        IPAddress mcuIP = new IPAddress(bIP);
                        textBox2.Text = mcuIP.ToString();

                        for (int i = 0; i < 4; i++)
                        {
                            bIP[i] = rx.Data[12 + i];
                        }
                        mcuIP = new IPAddress(bIP);
                        textBox3.Text = mcuIP.ToString();

                        for (int i = 0; i < 4; i++)
                        {
                            bIP[i] = rx.Data[16 + i];
                        }
                        mcuIP = new IPAddress(bIP);
                        textBox4.Text = mcuIP.ToString();

                        for (int i = 0; i < 4; i++)
                        {
                            bIP[i] = rx.Data[24 + i];
                        }
                        mcuIP = new IPAddress(bIP);
                        textBox5.Text = mcuIP.ToString();

                        numericUpDown2.Value = BytesOP.MakeShort(rx.Data[0x1d], rx.Data[0x1c]);

                        numericUpDown1.Value = BytesOP.MakeShort(rx.Data[0x21], rx.Data[0x20]);
                    }
                    else if (rx.Header.Command == 0x03)//设定网络参数
                    {
                        tabControl1.Enabled = true;
                        timer1.Enabled = false;
                        MessageBox.Show("设定网络参数成功，请重启设备后生效");
                    }                    
                    else if (rx.Header.Command == 0x05)//设定备用IO成功
                    {
                        tabControl1.Enabled = true;
                        timer1.Enabled = false;
                        MessageBox.Show("设定IO状态成功");
                    }
                    else if (rx.Header.Command == 0x06)//设定备用IO成功
                    {
                        tabControl1.Enabled = true;
                        timer1.Enabled = false;
                        MessageBox.Show("设定重启成功，将重新连入服务器，确定后将退出系统设定界面！");
                        this.Close();
                    }                    
                    else if (rx.Header.Command != 0x50)
                    {
                        textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                        textBox1.AppendText("控制板数据为:" + e.Client.clientEndPoint.ToString() + ":");
                        textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, " "));
                        textBox1.AppendText("\r\n");
                    }
                }));
            }
            else
            {
                this.Invoke((EventHandler)(delegate
                {
                    NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                    NetLog("收到未知IP数据" + e.Client.clientEndPoint.ToString() + ":");
                    NetLog("\r\n");
                }));
            }
        }
        private void tcpAsyncServer_ErrorServer(object sender, ErrorServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(e.Error.Message + "\r\n");
            }));
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            tcpAsyncServer.ErrorServerEvent -= new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.ReceiveServerEvent -= new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            tabControl1.Enabled = false;
            timer1.Enabled = true;
            byte[] tx = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0x02);
            tcpAsyncServer.Send(clientContext, tx);
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                textBox1.AppendText("发送到" + clientContext.clientEndPoint.ToString() + ":");
                textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(tx, " "));
                textBox1.AppendText("\r\n");
            }));
        }
        IPAddress CheckIPInput(string str)
        {
            string[] ips = str.Split('.');
            int[] ipn = new int[4];
            if (ips.Length != 4)
            {
                return null;
            }
            for (int i = 0; i < 4; i++)
            {
                if (int.TryParse(ips[i], out ipn[i]) == false)
                {
                    return null;
                }
                if (ipn[i] > 255 || ipn[i] < 0)
                {
                    return null;
                }
            }
            byte[] ipb = new byte[4];
            for (int i = 0; i < 4; i++)
                ipb[i] = (byte)ipn[i];
            return new IPAddress(ipb);
        }
        private void button2_Click(object sender, EventArgs e)
        {
            byte[] mac = WFNetLib.StringFunc.StringsFunction.strToHexByte(textBox6.Text, " ");
            if (mac == null || mac.Length!=6)
            {
                MessageBox.Show("mac地址输入有误");
                return;
            }
            IPAddress mcuIP = CheckIPInput(textBox2.Text);
            if (mcuIP == null)
            {
                MessageBox.Show("单片机板ip输入有误");
                return;
            }
            IPAddress mcuSN = CheckIPInput(textBox3.Text);
            if (mcuSN == null)
            {
                MessageBox.Show("单片机板子网掩码输入有误");
                return;
            }
            IPAddress mcuGW = CheckIPInput(textBox4.Text);
            if (mcuGW == null)
            {
                MessageBox.Show("单片机板默认网关输入有误");
                return;
            }
            IPAddress pcIP = CheckIPInput(textBox5.Text);
            if (pcIP == null)
            {
                MessageBox.Show("服务器端ip输入有误");
                return;
            }
            tabControl1.Enabled = false;
            timer1.Enabled = true;
            byte[] tx = new byte[36];
            for (int i = 0; i < 6; i++)
            {
                tx[i] = mac[i];
            }
            for (int i = 0; i < 4; i++)
            {
                tx[i+8] = mcuIP.GetAddressBytes()[i];
                tx[4 + i + 8] = mcuSN.GetAddressBytes()[i];
                tx[8 + i + 8] = mcuGW.GetAddressBytes()[i];
                tx[16 + i + 8] = pcIP.GetAddressBytes()[i];
            }
            tx[20 + 8] = BytesOP.GetLowByte((ushort)numericUpDown2.Value);
            tx[21 + 8] = BytesOP.GetHighByte((ushort)numericUpDown2.Value);
            tx[22 + 8] = 0;
            tx[23 + 8] = 0;
            tx[24 + 8] = BytesOP.GetLowByte((ushort)numericUpDown1.Value);
            tx[25 + 8] = BytesOP.GetHighByte((ushort)numericUpDown1.Value);
            tx[26 + 8] = 0;
            tx[27 + 8] = 0;
            byte[] tx03 = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0x03, tx);
            tcpAsyncServer.Send(clientContext, tx03);
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                textBox1.AppendText("发送到" + clientContext.clientEndPoint.ToString() + ":");
                textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(tx03, " "));
                textBox1.AppendText("\r\n");
            }));
        }

        private void button4_Click(object sender, EventArgs e)
        {
            tabControl1.Enabled = false;
            timer1.Enabled = true;            

            byte[] tx05 = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0x05, 1);//供电
            tcpAsyncServer.Send(clientContext, tx05);
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                textBox1.AppendText("发送到" + clientContext.clientEndPoint.ToString() + ":");
                textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(tx05, " "));
                textBox1.AppendText("\r\n");
            }));
        }

        private void button3_Click(object sender, EventArgs e)
        {
            tabControl1.Enabled = false;
            timer1.Enabled = true;

            byte[] tx05 = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0x05, 0);//断电
            tcpAsyncServer.Send(clientContext, tx05);
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                textBox1.AppendText("发送到" + clientContext.clientEndPoint.ToString() + ":");
                textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(tx05, " "));
                textBox1.AppendText("\r\n");
            }));
        }

        private void button5_Click(object sender, EventArgs e)
        {
            tabControl1.Enabled = false;
            timer1.Enabled = true;
            byte[] tx06 = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0x06);
            tcpAsyncServer.Send(clientContext, tx06);
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(DateTime.Now.ToLongTimeString() + "   :   ");
                textBox1.AppendText("发送到" + clientContext.clientEndPoint.ToString() + ":");
                textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(tx06, " "));
                textBox1.AppendText("\r\n");
            }));
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            MessageBox.Show("系统异常，即将退出,请重试");
            this.Close();
            //tabControl1.Enabled = true;  
        }
    }
}
