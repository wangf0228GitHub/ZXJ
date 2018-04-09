using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace _703主抽气器试验台
{
    public partial class NIChannelSetForm : Form
    {
        int ChannelIndex;
        DAL.NIChannelSettingData ai;
        public NIChannelSetForm(int index)
        {
            InitializeComponent();
            ChannelIndex = index;
            ai = DAL.NIChannelSettingDataDBOption.Get(ChannelIndex);
        }

        private void NIChannelSetForm_Load(object sender, EventArgs e)
        {
            textBox1.Text = ai.物理通道;
            textBox2.Text = ai.名称;
            textBox3.Text = ai.工位号;
            textBox4.Text = ai.安装位置;
            numericUpDown1.Value = (decimal)ai.I_4mA;
            numericUpDown2.Value = (decimal)ai.I_20mA;
            numericUpDown3.Value = (decimal)ai.最小值;
            numericUpDown4.Value = (decimal)ai.最大值;
            textBox7.Text = ai.物理量单位;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ai.物理通道 = textBox1.Text;
            ai.名称 = textBox2.Text;
            ai.工位号 = textBox3.Text;
            ai.安装位置 = textBox4.Text;
            ai.I_4mA = (double)numericUpDown1.Value;
            ai.I_20mA = (double)numericUpDown2.Value;
            ai.最小值 = (double)numericUpDown3.Value;
            ai.最大值 = (double)numericUpDown4.Value;
            ai.物理量单位 = textBox7.Text;
            ai.Calc_k = (ai.I_20mA - ai.I_4mA) / (0.02 - 0.004);
            ai.Calc_b = ai.I_4mA - ai.Calc_k * 0.004;
            DAL.NIChannelSettingDataDBOption.Update(ai);
            DialogResult = DialogResult.OK;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
