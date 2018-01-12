using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.TCP;
using WFNetLib.PacketProc;
using System.Net;
using WFNetLib;

namespace 地声数据监测
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        bool bPic=false;
        WFNetLib.TCP.ClientContext PicClientContext;
        IPEndPoint PicSocketIP;
        TCPAsyncServer tcpAsyncServer = null;
        private void Form1_Load(object sender, EventArgs e)
        {
            tcpAsyncServer = new TCPAsyncServer();
            tcpAsyncServer.SaveDataProcessCallback = new SaveDataProcessCallbackDelegate(CP1616_NoAddr_Packet.SaveDataProcessCallbackProc);
            tcpAsyncServer.ErrorServerEvent += new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.AcceptServerEvent += new TCPAcceptEvent(tcpAsyncServer_AcceptServer);
            tcpAsyncServer.DisconnectServerEvent += new TCPDisconnectEvent(tcpAsyncServer_DisconnectServer);
            tcpAsyncServer.ReceiveServerEvent += new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent);
            tcpAsyncServer.TCPServerPort = 6000;
            PicSocketIP = new IPEndPoint(new IPAddress(new byte[4]{192,168,1,205}), 5000);
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            if (toolStripButton1.Text == "开始")
            {
                toolStripButton1.Text = "停止";                
                tcpAsyncServer.Start();
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("服务器启动\r\n");  
                NetLog("\r\n");                    
                //this.Text = tcpAsyncServer.TCPServerName + ":" + tcpAsyncServer.TCPServerPort;
            }
            else
            {
                toolStripButton1.Text = "开始";
                tcpAsyncServer.Stop();
                NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                NetLog("服务器停止\r\n");
                NetLog("\r\n"); 
                bPic = false;
                timer1.Enabled = false;
            }
        }
        void NetLog(string str)
        {
            textBox1.AppendText(str);
            WFNetLib.Log.TextLog.AddTextLog(str);
        }
        private void tcpAsyncServer_ReceiveServerEvent(object sender, ReceiveServerEventArgs e)
        {
            IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            if (ip.Address.Equals(PicSocketIP.Address))
            {
                this.Invoke((EventHandler)(delegate
                {
                    NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                    NetLog("收到PIC采集板数据" + e.Client.clientEndPoint.ToString() + ":");
                    CP1616_NoAddr_Packet rx = (CP1616_NoAddr_Packet)e.netPacket;
                    NetLog(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, " "));
                    NetLog("\r\n");
                    double f;
                    byte[] fb = new byte[4];
                    int fbIndex;
                    string str;
                    //温度
                    f=BytesOP.MakeShort(rx.Data[0],rx.Data[1]);
                    f=f/100;
                    listView1.Items[0].SubItems[1].Text = f.ToString("F2");
                    //电子罗盘
                    fbIndex=2;
                    for (int i = 0; i < 4; i++)
                    {
                        fb[i] = rx.Data[fbIndex + 3 - i];
                    }
                    f = BitConverter.ToSingle(fb,0);
                    listView1.Items[1].SubItems[1].Text = f.ToString("F2");

                    fbIndex = 6;
                    for (int i = 0; i < 4; i++)
                    {
                        fb[i] = rx.Data[fbIndex + 3 - i];
                    }
                    f = BitConverter.ToSingle(fb, 0);
                    listView1.Items[2].SubItems[1].Text = f.ToString("F2");

                    fbIndex = 10;
                    for (int i = 0; i < 4; i++)
                    {
                        fb[i] = rx.Data[fbIndex + 3 - i];
                    }
                    f = BitConverter.ToSingle(fb, 0);
                    listView1.Items[3].SubItems[1].Text = f.ToString("F2");

                    //授时
                    str = Encoding.UTF8.GetString(rx.Data,14,10);
                    listView1.Items[4].SubItems[1].Text = str;

                    str = Encoding.UTF8.GetString(rx.Data, 24, 6);
                    listView1.Items[5].SubItems[1].Text = str;

                    //MS8607
                    f = BitConverter.ToSingle(rx.Data, 30);
                    listView1.Items[6].SubItems[1].Text = f.ToString("F2");

                    f = BitConverter.ToSingle(rx.Data, 34);
                    listView1.Items[7].SubItems[1].Text = f.ToString("F2");

                    f = BitConverter.ToSingle(rx.Data, 38);
                    listView1.Items[8].SubItems[1].Text = f.ToString("F2");
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
        private void tcpAsyncServer_AcceptServer(object sender, AcceptServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(DateTime.Now.ToLongTimeString() + ":");
                NetLog("Accept:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                NetLog("\r\n");

            }));
            IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            if (ip.Address.Equals(PicSocketIP.Address))
            //if(ip.Address.Address==PicSocketIP.Address.Address)
            {                
                bPic = true;
                PicClientContext = e.Client;
                PicSocketIP.Port = ip.Port;
                this.Invoke((EventHandler)(delegate
                {
                    timer1.Enabled = true;
                    NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                    NetLog("PIC采集板接入");
                    NetLog("\r\n");

                }));
            }
            
        }
        private void tcpAsyncServer_DisconnectServer(object sender, DisconnectEventArgs e)
        {
            IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            if (ip.Address.Equals(PicSocketIP.Address))
            {
                if (ip.Port == PicSocketIP.Port)
                {
                    bPic = false;
                    this.Invoke((EventHandler)(delegate
                    {
                        timer1.Enabled = false;
                        NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                        NetLog("PIC采集板断开");
                        NetLog("\r\n");
                    }));
                }
                else
                {
                    this.Invoke((EventHandler)(delegate
                    {
                        NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                        NetLog("上一个PIC采集板IP断开");
                        NetLog("\r\n");
                    }));
                }
            }            
            else
            {
                this.Invoke((EventHandler)(delegate
                {
                    timer1.Enabled = false;
                    NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                    NetLog("未知ip断开");
                    NetLog("\r\n");
                }));
            } 
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 32000)
                textBox1.Clear();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (bPic)
            {
                byte[] tx = CP1616_NoAddr_Packet.MakeCP1616_NoAddr_Packet(0x01);
                this.Invoke((EventHandler)(delegate
                {
                    NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
                    NetLog("发送到" + PicClientContext.clientEndPoint.ToString() + ":");
                    NetLog(WFNetLib.StringFunc.StringsFunction.byteToHexStr(tx, " "));
                    NetLog("\r\n");
                }));
                tcpAsyncServer.Send(PicClientContext, tx);
            }
            else
                timer1.Enabled = false;
        }
    }
}
