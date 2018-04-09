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
    public partial class loginForm : Form
    {
        public loginForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == Properties.Settings.Default.user && textBox2.Text == Properties.Settings.Default.psw)
            {
                this.Hide();
                mainForm f = new mainForm();
                f.ShowDialog();
                this.Close();
            }
            else
                MessageBox.Show("请输入正确的用户名及密码！");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
