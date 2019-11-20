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
            CP1616PacketHead.bIsDebugOut = true;
            CP1616PacketHead.CalcHeaderLen();
        }
        _SensorSignIn sensorSingIn;
        _SensorBAT sensorBAT;
        private void btNetStart_Click(object sender, EventArgs e)
        {
            if (btNetStart.Text == "启动网络")
            {
                this.Uart.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(this.Uart_DataReceived);
                Uart.PortName=cbCom.Text;
                if (WFGlobal.OpenSerialPort(ref Uart) == false)
                    return;                
                Properties.Settings.Default.PortName = cbCom.Text;
                Properties.Settings.Default.Save();
                RxPacket = new CP1616Packet();
                this.Uart.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.Uart_DataReceived);                
                lNetStatus.Text = "网络启动";
                btNetStart.Text = "停止网络";
                bStopNet = false;
                btSetID.Enabled = false;             
            }
            else
            {
                btNetStart.Enabled = true;
                btNetStart.Text = "启动网络";
                btSetID.Enabled = true;
                //this.Uart.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(this.Uart_DataReceived);
                Uart.Close();                
                MessageBox.Show("网络已停止");
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
                    if (RxPacket.Header.Command == 0x20)
                    {
                        ADCDataProc();                   
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

        private void btSetID_Click(object sender, EventArgs e)
        {
//             this.Uart.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(this.Uart_DataReceived);
//             Uart.PortName = cbCom.Text;
//             if (WFGlobal.OpenSerialPort(ref Uart) == false)
//                 return;
//             Uart.ReadTimeout = 15000;//12s唤醒，3s通信
//             SetIDForm sf = new SetIDForm(Uart);
//             sf.ShowDialog();
//             Uart.ReadTimeout = 200;
//             Uart.Close();
        }
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            
        }
    }
}
