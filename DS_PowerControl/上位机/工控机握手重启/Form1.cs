using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib;
using WFNetLib.PacketProc;
using System.IO.Ports;

namespace 工控机握手重启
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "工作串口为" + serialPort1.PortName;
            CP1616PacketHead.Addr_SIZE = 1;
            CP1616PacketHead.DataLen_SIZE = 1;
            CP1616PacketHead.CalcHeaderLen();
            while (!WFGlobal.OpenSerialPort(ref serialPort1, "工控机握手监测"));            
            RxCount = 0;
            TxCount = 0;
            HandWork();
            timer1.Enabled = true;
        }
        int RxCount, TxCount;
        void HandWork()
        {
            CP1616Packet cp1616Packet = CP1616Packet.CP1616ComProc(ref serialPort1, 0x01, 0x01, null, 3);
            if (cp1616Packet != null)
            {
                RxCount++;
                TxCount++;
            }
            else
            {
                TxCount++;

            }
            this.Invoke((EventHandler)(delegate
            {
                label3.Text = TxCount.ToString();
                label4.Text = RxCount.ToString();
            }));
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            HandWork();
            timer1.Enabled = true;
        }
    }
}
