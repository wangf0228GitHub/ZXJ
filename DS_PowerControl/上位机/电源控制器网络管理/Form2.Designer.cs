namespace 电源控制器网络管理
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.button4 = new System.Windows.Forms.Button();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.button5 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.rbp1on = new System.Windows.Forms.RadioButton();
            this.rbp1off = new System.Windows.Forms.RadioButton();
            this.rbp2on = new System.Windows.Forms.RadioButton();
            this.rbp2off = new System.Windows.Forms.RadioButton();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.tabControl1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.textBox1);
            this.splitContainer1.Size = new System.Drawing.Size(507, 354);
            this.splitContainer1.SplitterDistance = 261;
            this.splitContainer1.TabIndex = 1;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(507, 261);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.button2);
            this.tabPage2.Controls.Add(this.button1);
            this.tabPage2.Controls.Add(this.groupBox2);
            this.tabPage2.Controls.Add(this.groupBox1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(499, 235);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "网络参数";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(335, 146);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(97, 52);
            this.button2.TabIndex = 4;
            this.button2.Text = "写入";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(231, 146);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(98, 52);
            this.button1.TabIndex = 4;
            this.button1.Text = "读取";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.textBox5);
            this.groupBox2.Controls.Add(this.numericUpDown2);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Location = new System.Drawing.Point(231, 16);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(201, 115);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "服务器端网络参数";
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(53, 29);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(109, 21);
            this.textBox5.TabIndex = 3;
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(53, 69);
            this.numericUpDown2.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.numericUpDown2.Minimum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(109, 21);
            this.numericUpDown2.TabIndex = 2;
            this.numericUpDown2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDown2.Value = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 71);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 0;
            this.label5.Text = "端口";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(20, 32);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(17, 12);
            this.label8.TabIndex = 0;
            this.label8.Text = "IP";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox4);
            this.groupBox1.Controls.Add(this.textBox3);
            this.groupBox1.Controls.Add(this.textBox2);
            this.groupBox1.Controls.Add(this.numericUpDown1);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(16, 16);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 182);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "单片机板网络参数";
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(77, 97);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(100, 21);
            this.textBox4.TabIndex = 3;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(77, 62);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 21);
            this.textBox3.TabIndex = 3;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(77, 29);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 21);
            this.textBox2.TabIndex = 3;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(77, 142);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(100, 21);
            this.numericUpDown1.TabIndex = 2;
            this.numericUpDown1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDown1.Value = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 144);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "本机端口";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 100);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "默认网关";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "子网掩码";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(44, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.button3);
            this.tabPage3.Controls.Add(this.button4);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(499, 235);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "IO端口";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(52, 60);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(159, 71);
            this.button4.TabIndex = 1;
            this.button4.Text = "供电";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.button5);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage4.Size = new System.Drawing.Size(499, 235);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "设备重启";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(67, 60);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(143, 64);
            this.button5.TabIndex = 0;
            this.button5.Text = "设备重启";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // textBox1
            // 
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox1.Location = new System.Drawing.Point(0, 0);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox1.Size = new System.Drawing.Size(507, 89);
            this.textBox1.TabIndex = 0;
            // 
            // timer1
            // 
            this.timer1.Interval = 30000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // rbp1on
            // 
            this.rbp1on.AutoSize = true;
            this.rbp1on.Location = new System.Drawing.Point(34, 30);
            this.rbp1on.Name = "rbp1on";
            this.rbp1on.Size = new System.Drawing.Size(47, 16);
            this.rbp1on.TabIndex = 0;
            this.rbp1on.TabStop = true;
            this.rbp1on.Text = "打开";
            this.rbp1on.UseVisualStyleBackColor = true;
            // 
            // rbp1off
            // 
            this.rbp1off.AutoSize = true;
            this.rbp1off.Location = new System.Drawing.Point(34, 62);
            this.rbp1off.Name = "rbp1off";
            this.rbp1off.Size = new System.Drawing.Size(47, 16);
            this.rbp1off.TabIndex = 0;
            this.rbp1off.TabStop = true;
            this.rbp1off.Text = "关闭";
            this.rbp1off.UseVisualStyleBackColor = true;
            // 
            // rbp2on
            // 
            this.rbp2on.AutoSize = true;
            this.rbp2on.Location = new System.Drawing.Point(34, 30);
            this.rbp2on.Name = "rbp2on";
            this.rbp2on.Size = new System.Drawing.Size(47, 16);
            this.rbp2on.TabIndex = 0;
            this.rbp2on.TabStop = true;
            this.rbp2on.Text = "打开";
            this.rbp2on.UseVisualStyleBackColor = true;
            // 
            // rbp2off
            // 
            this.rbp2off.AutoSize = true;
            this.rbp2off.Location = new System.Drawing.Point(34, 62);
            this.rbp2off.Name = "rbp2off";
            this.rbp2off.Size = new System.Drawing.Size(47, 16);
            this.rbp2off.TabIndex = 0;
            this.rbp2off.TabStop = true;
            this.rbp2off.Text = "关闭";
            this.rbp2off.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(270, 60);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(157, 71);
            this.button3.TabIndex = 1;
            this.button3.Text = "断电";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(507, 354);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form2";
            this.Text = "Form2";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form2_FormClosing);
            this.Load += new System.EventHandler(this.Form2_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.tabPage3.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.RadioButton rbp1on;
        private System.Windows.Forms.RadioButton rbp1off;
        private System.Windows.Forms.RadioButton rbp2on;
        private System.Windows.Forms.RadioButton rbp2off;
    }
}