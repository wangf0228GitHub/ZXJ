using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace pcieDataRecorder
{
	public partial class Form1 : Form
	{
		const int TRUE = 1;
		const int FALSE = 0;
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			IntPtr pCH368 = CH368.CH367mOpenDevice(0, FALSE, TRUE, 0x00);
			MessageBox.Show(pCH368.ToString());
		}

		private void button1_Click(object sender, EventArgs e)
		{
			
		}
	}
}
