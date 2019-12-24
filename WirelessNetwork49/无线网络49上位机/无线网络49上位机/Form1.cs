using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using WFNetLib;
using WFNetLib.PacketProc;
using System.Diagnostics;
using System.Threading;

namespace 无线网络49上位机
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            CP1616PacketHead.Addr_SIZE = 0;
            CP1616PacketHead.DataLen_SIZE = 2;
            CP1616PacketHead.bCheckVerify = false;
            CP1616PacketHead.bIsDebugOut = false;
            CP1616PacketHead.CalcHeaderLen();
        }
        _SensorSignIn sensorSingIn;
        _SensorBAT sensorBAT;
        byte waitCommand;
        byte startResult;
        private void btNetStart_Click(object sender, EventArgs e)
        {
            if (btNetStart.Text == "启动网络")
            {                
                Uart.PortName=cbCom.Text;
                RxPacket = new CP1616Packet();
                if (WFGlobal.OpenSerialPort(ref Uart) == false)
                    return;
                Properties.Settings.Default.PortName = cbCom.Text;
                Properties.Settings.Default.Save();                
                sensorSingIn.clearSignIn();
                listView1.Items.Clear();
                chart1.Series[0].Points.Clear();
                chart2.Series[0].Points.Clear();
                chart3.Series[0].Points.Clear();
                chart4.Series[0].Points.Clear();
                chart3.Series[1].Points.Clear();
                chart4.Series[1].Points.Clear();
                chart3.Series[2].Points.Clear();
                chart4.Series[2].Points.Clear();
                chart3.Series[3].Points.Clear();
                chart4.Series[3].Points.Clear();
                bStopNet = false;
                for (int i = 0; i < 3; i++)
                {
                    startResult = 0;
                    waitCommand = 1;
                    CP1616Packet.CP1616ComSend(ref Uart, waitCommand, 0, (ushort)0);
                    int x = 0;
                    while (true)
                    {
                        Thread.Sleep(1);
                        if (startResult != 0)
                            break;
                        x++;
                        if (x > 1000)
                        {
                            startResult = 0xff;
                            break;
                        }
                    }
                    if (startResult == 0xff)//超时了
                    {

                    }
                    else
                    {
                        break;

                    }
                }
                if (startResult == 0xff)
                {
                    MessageBox.Show("网络控制器未做应答!!!");
                    Uart.Close();
                    btNetStart.Text = "启动网络";
                    return;
                }                
                else if (startResult == 2)
                {
                    bStopNet = false;
                    btNetStart.Text = "停止网络";
                    MessageBox.Show("网络已经启动，等待接入");
                }
                else if (startResult == 3)
                {
                    bStopNet = false;
                    btNetStart.Text = "停止网络";
                    MessageBox.Show("标定网络已经启动，将自动转为测量网络，等待接入");
                }
                else
                {
                    WaitSometingForm.WaitSometing_Init();
                    waitCommand = 0x10;//点名完成
                    if (!WaitSometingForm.WaitSometing(10, 3000, "等待无线节点组网，预计时长25s"))
                    {
                        waitCommand = 0;
                        Uart.Close();
                        MessageBox.Show("组网失败");
                        return;
                    }
                    if (listView1.Items.Count != 0)
                    {
                        WaitSometingForm.WaitSometing_Init();
                        waitCommand = 0x20;//等待测量数据
                        if (!WaitSometingForm.WaitSometing(10, 500, "等待网络数据，预计时长3s"))
                        {
                            waitCommand = 0;
                            MessageBox.Show("组网失败");
                            Uart.Close();
                            bStopNet = false;
                            return;
                        }
                        bStopNet = false;
                        btNetStart.Text = "停止网络";
                        MessageBox.Show("网络启动成功");
                    }
                    else
                    {
                        waitCommand = 0;
                        MessageBox.Show("当前网络没有发现任何无线节点，网络自动停止");
                        Uart.Close();
                        btNetStart.Text = "启动网络";
                        return;
                    }
                }
            }
            else
            {
                bStopNet = true;
                WaitSometingForm.WaitSometing_Init();
                waitCommand = 0x02;//等待网络停止
                if (!WaitSometingForm.WaitSometing(10, 500, "等待网络停止，预计时长5s"))
                {
                    waitCommand = 0;
                    MessageBox.Show("网络停止失败");
                    return;
                }
                MessageBox.Show("网络已停止");
                Uart.Close();
                btNetStart.Text = "启动网络";
            }
        }
        bool bStopNet = false;
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            cbCom.Items.Clear();
            cbCom.Items.AddRange(ports);
            cbCom.Items.Add("刷新");
            cbCom.SelectedIndex = 0;
            if (Properties.Settings.Default.PortName != "")
            {
                for(int i=0;i<cbCom.Items.Count;i++)
                {
                    if(cbCom.Items[i].ToString()==Properties.Settings.Default.PortName)
                    {
                        cbCom.SelectedIndex = i;
                        break;
                    }
                }
            }
            sensorSingIn = new _SensorSignIn();
            sensorBAT = new _SensorBAT();
//             double yValue = 50.0;
//             Random random = new Random();
//             for (int pointIndex = 0; pointIndex < 20000; pointIndex++)
//             {
//                 yValue = yValue + (random.NextDouble() * 10.0 - 5.0);
//                 chart1.Series[0].Points.AddY(yValue);
//             }

//             RxPacket = new CP1616Packet();
//             this.Uart.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.Uart_DataReceived);
        }

        private void cbCom_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbCom.SelectedIndex == cbCom.Items.Count - 1)
            {
                string[] ports = SerialPort.GetPortNames();
                Array.Sort(ports);
                cbCom.Items.Clear();
                cbCom.Items.AddRange(ports);
                cbCom.Items.Add("刷新");
                cbCom.SelectedIndex = 0;
                if (Properties.Settings.Default.PortName != "")
                {
                    for (int i = 0; i < cbCom.Items.Count; i++)
                    {
                        if (cbCom.Items[i].ToString() == Properties.Settings.Default.PortName)
                        {
                            cbCom.SelectedIndex = i;
                            break;
                        }
                    }
                }
            }
        }

        private void listView1_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            // 取消掉正在调整的事件 
            e.Cancel = true;
            // 把新宽度恢复到之前的宽度 
            e.NewWidth = this.listView1.Columns[e.ColumnIndex].Width; 
        }

        private void listView1_Resize(object sender, EventArgs e)
        {
            listView1.Columns[2].Width = listView1.ClientSize.Width - listView1.Columns[0].Width - listView1.Columns[1].Width;
        }
        CP1616Packet RxPacket;
        void Uart_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int irx;
            byte rx;
            while (true)
            {
                try
                {
                    irx = Uart.ReadByte();
                }
                catch
                {
                    return;
                }
                if (!Uart.IsOpen)
                    return;
                if (irx == -1)
                    return;
                rx = (byte)irx;
                if (RxPacket.DataPacketed(rx))
                {
                    byte[] data = new byte[2];
                    data[0] = RxPacket.Header.Command;
                    if (waitCommand == RxPacket.Header.Command)
                    {
                        WaitSometingForm.bGenerateSometing = true;
                    }
                    if (bStopNet)
                    {
                        data[1] = 0x02;//要求关闭网络
                        CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);
                    }
                    else if (RxPacket.Header.Command == 1)//标定网络启动确认
                    {
                        startResult = RxPacket.Data[0];
                    }
                    else if (RxPacket.Header.Command == 0x22)//标定网络，请求转换为测量网络
                    {
                        this.Invoke((EventHandler)(delegate
                        {
                            textBox1.AppendText(DateTime.Now.ToString("HH:mm:ss:ffff") + ":标定网络转换为测量网络\r\n");
                        })); 
                        startResult = 3;
                        data[1] = 0x03;
                        CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);
                    }
                    else if (RxPacket.Header.Command == 0x10)
                    {
                        data[1] = 0x00;
                        CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);
                        SignInProc();                        
                    }
                    else if (RxPacket.Header.Command == 0x20)
                    {
                        startResult = 2;
                        if (listView1.Items.Count == 0)
                        {
                            data[1] = 0x01;//请求传感器名单
                            CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);
                        }
                        else
                        {
                            data[1] = 0x00;
                            CP1616Packet.CP1616ComSend(ref Uart, 3, 0, data);
                            ADCDataProc();
                        }
                        this.Invoke((EventHandler)(delegate
                        {
                            if (btNetStart.Text == "启动网络")
                            {
                                btNetStart.Text = "停止网络";
                            }
                        }));
                    }
                    RxPacket = new CP1616Packet();
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 10000)
                textBox1.Clear();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Uart.Close();
        }
    }
}
