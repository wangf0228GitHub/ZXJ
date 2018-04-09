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
    public partial class mainForm : Form
    {
        public mainForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            newtaskForm f = new newtaskForm();
            f.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            NISettingForm f = new NISettingForm();
            f.ShowDialog();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            exportForm f = new exportForm();
            f.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            userForm1 f = new userForm1();
            f.ShowDialog();
        }

        private void mainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            
        }
    }
}
