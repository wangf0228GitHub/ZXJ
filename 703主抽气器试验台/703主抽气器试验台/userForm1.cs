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
    public partial class userForm1 : Form
    {
        public userForm1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "" || textBox2.Text == "" || textBox3.Text == "")
            {
                MessageBox.Show("用户名或密码均不可为空");
                return;
            }
            if (textBox2.Text != textBox3.Text)
            {
                MessageBox.Show("两次输入密码不同");
                return;
            }
            _703主抽气器试验台.Properties.Settings.Default.user = textBox1.Text;
            _703主抽气器试验台.Properties.Settings.Default.psw = textBox2.Text;
            _703主抽气器试验台.Properties.Settings.Default.Save();
            MessageBox.Show("修改成功!!");
	        this.Close();
        }
    }
}
