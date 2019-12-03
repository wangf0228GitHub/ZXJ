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
    public partial class formMain : Form
    {
        public formMain()
        {
            InitializeComponent();
        }
        CP1616Packet RxPacket;
        private void button1_Click(object sender, EventArgs e)
        {
            this.Uart.DataReceived -= new System.IO.Ports.SerialDataReceivedEventHandler(this.Uart_DataReceived);
            Uart.PortName = cbCom.Text;
            if (WFGlobal.OpenSerialPort(ref Uart) == false)
                return;
            CP1616Packet start = CP1616Packet.CP1616ComProc(ref Uart, 1, 0, (ushort)0);
            if (start == null)
            {
                Uart.Close();
                MessageBox.Show("与网络控制器通信失败");
                return;
            }
            Properties.Settings.Default.PortName = cbCom.Text;
            Properties.Settings.Default.Save();
            RxPacket = new CP1616Packet();
        }

        private void Uart_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {

        }

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
    }
}
