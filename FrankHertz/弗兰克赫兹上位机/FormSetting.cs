using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace 弗兰克赫兹上位机
{
    public partial class FormSetting : Form
    {
        FormMain fMain;
        public FormSetting(FormMain _f)
        {
            InitializeComponent();
            fMain = _f;
        }

        private void FormSetting_Load(object sender, EventArgs e)
        {
            switch (fMain.stepV)
            {
                case 2://0.16,2
                    rbStepV016.Checked = true;
                    break;
                case 5://0.4,5
                    rbStepV040.Checked = true;
                    break;
                case 10://0.8,10
                    rbStepV080.Checked = true;
                    break;
            }
            switch (fMain.stepS)
            {
                case 2000://0.16,2
                    rbStepS2000.Checked = true;
                    break;
                case 1000://0.4,5
                    rbStepS1000.Checked = true;
                    break;
                case 500://0.8,10
                    rbStepS500.Checked = true;
                    break;
            }
            if (fMain.bYaGuan != 0)
                rbYaGuan.Checked = true;
            else
                rbNaiGuan.Checked = true;
            tbUF.Text = fMain.UF.ToString("f02");
            tbUG1K.Text = fMain.UG1K.ToString("f02");
            tbUG2A.Text = fMain.UG2A.ToString("f02");
        }

        private void FormSetting_FormClosing(object sender, FormClosingEventArgs e)
        {
                        
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("是否保存实验参数", "保存实验参数", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                double b1, b2, b3;
                if (!double.TryParse(tbUF.Text, out b1))
                {
                    MessageBox.Show("灯丝电压输入有误");
                    return;
                }
                if (!double.TryParse(tbUG1K.Text, out b2))
                {
                    MessageBox.Show("控制栅电压输入有误");
                    return;
                }
                if (!double.TryParse(tbUG2A.Text, out b3))
                {
                    MessageBox.Show("拒斥电压输入有误");
                    return;
                }
                fMain.UF = b1;
                fMain.UG1K = b2;
                fMain.UG2A = b3;
                if (rbStepV016.Checked)
                    fMain.stepV = 2;
                if (rbStepV040.Checked)
                    fMain.stepV = 5;
                if (rbStepV080.Checked)
                    fMain.stepV = 10;
                if (rbStepS2000.Checked)
                    fMain.stepS = 2000;
                if (rbStepS1000.Checked)
                    fMain.stepS = 1000;
                if (rbStepS500.Checked)
                    fMain.stepS = 500;
                if (rbYaGuan.Checked)
                    fMain.bYaGuan = 1;
                else
                    fMain.bYaGuan = 0;
                this.DialogResult = DialogResult.OK;
            }
        }
    }
}
