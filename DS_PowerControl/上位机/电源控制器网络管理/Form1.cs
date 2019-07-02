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

namespace 电源控制器网络管理
{
    public partial class Form1 : Form
    {
        TCPAsyncServer tcpAsyncServer = null;
        public Form1()
        {
            InitializeComponent();
            tcpAsyncServer = new TCPAsyncServer();
            tcpAsyncServer.SaveDataProcessCallback = new SaveDataProcessCallbackDelegate(CP1616_NoAddr_Packet.SaveDataProcessCallbackProc);
            tcpAsyncServer.ErrorServerEvent += new TCPErrorEvent(tcpAsyncServer_ErrorServer);
            tcpAsyncServer.AcceptServerEvent += new TCPAcceptEvent(tcpAsyncServer_AcceptServer);
            tcpAsyncServer.DisconnectServerEvent += new TCPDisconnectEvent(tcpAsyncServer_DisconnectServer);
            tcpAsyncServer.ReceiveServerEvent += new TCPReceiveEvent(tcpAsyncServer_ReceiveServerEvent);

            if (!int.TryParse(tbPort.Text, out tcpAsyncServer.TCPServerPort))
            {
                MessageBox.Show("输入的端口号格式有问题!!");
                return;
            }
            toolStripButton1.Text = "停止";
            tcpAsyncServer.Start();
            NetLog(DateTime.Now.ToLongTimeString() + "   :   ");
            NetLog("服务器启动\r\n");
            NetLog("\r\n");
            listView1_Resize(null, null);
        }
        void NetLog(string str)
        {
            textBox1.AppendText(str);
            WFNetLib.Log.TextLog.AddTextLog(str);
        }

        private void listView1_Resize(object sender, EventArgs e)
        {
            int w = listView1.ClientSize.Width;
            for (int i = 0; i < listView1.Columns.Count-1; i++)
            {
                w = w - listView1.Columns[i].Width;
            }
            listView1.Columns[listView1.Columns.Count - 1].Width = w;
        }
        private void tcpAsyncServer_ErrorServer(object sender, ErrorServerEventArgs e)
        {
            try
            {
                this.Invoke((EventHandler)(delegate
                            {
                                NetLog(e.Error.Message + "\r\n");

                            }));
            }
            catch { }
        }
        private void tcpAsyncServer_AcceptServer(object sender, AcceptServerEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(DateTime.Now.ToLongTimeString() + ":");
                NetLog("接入:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                NetLog("\r\n");
                bool bExist=false;
                IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
                foreach (ListViewItem li in listView1.Items)
                {
                    if (li.Text == ip.Address.ToString())
                    {
                        bExist = true;
                        li.SubItems[1].Text = ip.Port.ToString();
                        li.Tag = e.Client;
                        break;
                    }
                }
                if (!bExist)
                {
                    ListViewItem li = listView1.Items.Add(ip.Address.ToString());
                    li.SubItems.Add(ip.Port.ToString());
                    li.SubItems.Add("");
                    li.SubItems.Add("");
                    li.SubItems.Add("");
                    li.SubItems.Add("");
                    li.SubItems.Add("");
                    li.SubItems.Add("");
                    li.Tag = e.Client;
                }
            }));

        }
        private void tcpAsyncServer_DisconnectServer(object sender, DisconnectEventArgs e)
        {
            this.Invoke((EventHandler)(delegate
            {
                NetLog(DateTime.Now.ToLongTimeString() + ":");
                NetLog("断开:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                NetLog("\r\n");
                IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
                foreach (ListViewItem li in listView1.Items)
                {
                    if (li.Text == ip.Address.ToString())
                    {
                        listView1.Items.Remove(li);
                        break;
                    }
                }
            }));          
        }
        private void tcpAsyncServer_ReceiveServerEvent(object sender, ReceiveServerEventArgs e)
        {
            CP1616_NoAddr_Packet rx = (CP1616_NoAddr_Packet)e.netPacket;
            IPEndPoint ip = (IPEndPoint)e.Client.ClientSocket.RemoteEndPoint;
            this.Invoke((EventHandler)(delegate
            {
                textBox1.AppendText(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, " ")+"\r\n");
                if (rx.Header.Command == 0x50)//握手电源控制器状态上报
                {
                    double f;
                    byte[] fb = new byte[4];
                    int indexLi = -1;
                    for (int i = 0; i < listView1.Items.Count; i++)
                    {
                        if (listView1.Items[i].Text == ip.Address.ToString())
                        {
                            indexLi = i;
                            break;
                        }
                    }
                    if (indexLi == -1)
                    {
                        NetLog(DateTime.Now.ToLongTimeString() + ":");
                        NetLog("未处理ip数据:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                        NetLog("\r\n");
                        return;
                    }
                    string strLog = e.Client.ClientSocket.RemoteEndPoint.ToString()+":";
                    //MS8607
                    if (rx.Data[12] > 10)
                    {
                        listView1.Items[indexLi].SubItems[2].Text = "xxx.x";
                        listView1.Items[indexLi].SubItems[3].Text = "xxx.x";
                        listView1.Items[indexLi].SubItems[4].Text = "xxx.x";
                    }
                    else
                    {
                        f = BitConverter.ToSingle(rx.Data, 0);
                        listView1.Items[indexLi].SubItems[2].Text = f.ToString("F2");
                        strLog += f.ToString("F2") + ",";
                        f = BitConverter.ToSingle(rx.Data, 4);
                        //f = f;
                        listView1.Items[indexLi].SubItems[3].Text = f.ToString("F2");
                        strLog += f.ToString("F2") + ",";
                        f = BitConverter.ToSingle(rx.Data, 8);
                        listView1.Items[indexLi].SubItems[4].Text = f.ToString("F2");
                        strLog += f.ToString("F2") + ",";
                    }
                    if (rx.Data[13] == 0)
                    {
                        listView1.Items[indexLi].SubItems[5].Text = "漏水";                        
                    }
                    else
                    {
                        listView1.Items[indexLi].SubItems[5].Text = "正常";
                    }
                    strLog += listView1.Items[indexLi].SubItems[5].Text + ",";
                    if (rx.Data[14] == 0)
                    {
                        listView1.Items[indexLi].SubItems[6].Text = "漏水";
                    }
                    else
                    {
                        listView1.Items[indexLi].SubItems[6].Text = "正常";
                    }
                    strLog += listView1.Items[indexLi].SubItems[5].Text + ",";
                    if (rx.Data[15] == 0)
                    {
                        listView1.Items[indexLi].SubItems[7].Text = "断电";
                    }
                    else
                    {
                        listView1.Items[indexLi].SubItems[7].Text = "供电";
                    }
                    strLog += listView1.Items[indexLi].SubItems[5].Text;
                    NetLog(DateTime.Now.ToLongTimeString() + ":");
                    NetLog(strLog);
                    NetLog("\r\n");
                }
                else
                {
                    NetLog(DateTime.Now.ToLongTimeString() + ":");
                    NetLog("未知指令数据:" + e.Client.ClientSocket.RemoteEndPoint.ToString());
                    NetLog("\r\n");
                    NetLog(WFNetLib.StringFunc.StringsFunction.byteToHexStr(rx.Data, " "));
                    NetLog("\r\n");
                }
            }));
            
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 32000)
                textBox1.Clear();
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0)
            {
                MessageBox.Show("请选中某个控制板");
                return;
            }
            ListViewItem li = listView1.SelectedItems[0];
            Form2 f = new Form2(tcpAsyncServer,li.Text,(ClientContext)li.Tag);
            f.ShowDialog();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            tcpAsyncServer.Stop();
        }  
    }
}
