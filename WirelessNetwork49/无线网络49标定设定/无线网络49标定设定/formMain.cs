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

namespace 无线网络49上位机
{
    public delegate void UartRxProc(CP1616Packet rxPacket);
    public partial class formMain : Form
    {
        public formMain()
        {
            InitializeComponent();
        }
        bool OpenUart()
        {
            Uart.PortName = cbCom.Text;
            RxPacket = new CP1616Packet();
            if (WFGlobal.OpenSerialPort(ref Uart) == false)
                return false;
            Properties.Settings.Default.PortName = cbCom.Text;
            Properties.Settings.Default.Save();
            
            return true;

        }        
        private void button1_Click(object sender, EventArgs e)
        {
            if (!OpenUart())
                return;
            SetIDForm f = new SetIDForm(Uart);
            uartRxProc = new UartRxProc(f.UartRxProc);
            //this.Uart.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(f.Uart_DataReceived);
            f.ShowDialog();
            //this.Uart.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(f.Uart_DataReceived);
            Uart.Close();
            uartRxProc = null;
        }
        CP1616Packet RxPacket;
        UartRxProc uartRxProc;
        private void formMain_Load(object sender, EventArgs e)
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

        private void button2_Click(object sender, EventArgs e)
        {
            if (!OpenUart())
                return;
            Form1 f = new Form1(Uart);
            uartRxProc = new UartRxProc(f.UartRxProc);
            //this.Uart.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(f.Uart_DataReceived);
            f.ShowDialog();
            //this.Uart.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(f.Uart_DataReceived);
            Uart.Close();
            uartRxProc = null;
        }

        private void Uart_DataReceived(object sender, SerialDataReceivedEventArgs e)
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
                    if(uartRxProc!=null)
                        uartRxProc(RxPacket);
                    RxPacket = new CP1616Packet();
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (!OpenUart())
                return;
            SetCalibrationForm f = new SetCalibrationForm(Uart);
            uartRxProc = new UartRxProc(f.UartRxProc);
            //this.Uart.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(f.Uart_DataReceived);
            f.ShowDialog();
            //this.Uart.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(f.Uart_DataReceived);
            Uart.Close();
            uartRxProc = null;
        }
    }
}
