using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib.StringFunc;
using System.Net.Sockets;

namespace 解调仪调试
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void listView2_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
		{
			// 取消掉正在调整的事件 
			e.Cancel = true;
			// 把新宽度恢复到之前的宽度 
			e.NewWidth = this.listView2.Columns[e.ColumnIndex].Width; 
		}

		private void listView1_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
		{
			// 取消掉正在调整的事件 
			e.Cancel = true;
			// 把新宽度恢复到之前的宽度 
			e.NewWidth = this.listView1.Columns[e.ColumnIndex].Width;
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			tcpTempBuffer = new byte[1024];
			tcpReceiveBuffer = new byte[10240];
			ReceiveServerEvent += new TCPReceiveEvent(tcpRxFrameProc);
		}

		private void btSendCommand_Click(object sender, EventArgs e)
		{
			byte[] tx;
			try
			{
				tx = StringsFunction.strToHexByte(tbTxData.Text, "");
				if (tx == null || tx.Length != 8)
				{
					MessageBox.Show("数据发送区数据格式不合法，应为8字节，共16个字符");
					return;
				}
			}
			catch (System.Exception ex)
			{
				MessageBox.Show("数据发送区数据格式不合法:"+ex.Message);
				return;
			}
			if ((tcpClient == null) || (!tcpClient.Connected))
			{
				MessageBox.Show("未连接网络");
				btConnect.Text = "连接";
				btConnect.BackColor = Color.Lime;
				btSendCommand.Enabled = false;
				btStartSave.Enabled = false;
				timerSave.Enabled = false;
				return;
			}
			NetworkStream stream = tcpClient.GetStream();
			stream.Write(tx, 0, tx.Length);
			int x = int.Parse(tbTxCount.Text);
			x += tx.Length;
			tbTxCount.Text = x.ToString();
		}

		private void toolStripSplitButton1_ButtonClick(object sender, EventArgs e)
		{
			tbRxCount.Text = "0"; 
		}

		private void toolStripSplitButton2_ButtonClick(object sender, EventArgs e)
		{
			tbTxCount.Text = "0";
		}

		private void lbFPGA_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch (lbFPGA.SelectedIndex)
			{
				//    // 无操作
				//    case 0:tbTxData.Text="0000000000000000");break;
				//    //1.停止工作（复位）
				//    case 1:tbTxData.Text="0001000000000000");break;
				//    //2.开始工作（解除复位）
				//    case 2:tbTxData.Text="0001000000000001");break;
				//3.启动FPGA至ARM解调数据传输
				case 0: tbTxData.Text="0001000000000002"; break;
				//    //4.停止FPGA至ARM解调数据传输
				//    case 4:tbTxData.Text="0001000000000003");break;
				//5.通道1锁相（有返回状态）
				case 1: tbTxData.Text="0001000000000004"; break;
				//6.通道2锁相
				case 2: tbTxData.Text="0001000000000005"; break;
				//7.通道3锁相
				case 3: tbTxData.Text="0001000000000006"; break;
				//8.通道4锁相
				case 4: tbTxData.Text="0001000000000007"; break;
				//9.监测通道1干涉信号
				case 5: tbTxData.Text="0001000000000008"; break;
				//10.监测通道2干涉信号
				case 6: tbTxData.Text="0001000000000009"; break;
				//11.监测通道3干涉信号
				case 7: tbTxData.Text="000100000000000A"; break;
				//12.监测通道4干涉信号
				case 8: tbTxData.Text="000100000000000B"; break;
				//13.监测通道1椭圆拟合信号
				case 9: tbTxData.Text="000100000000000C"; break;
				//14.监测通道2椭圆拟合信号
				case 10: tbTxData.Text="000100000000000D"; break;
				//15.监测通道3椭圆拟合信号
				case 11: tbTxData.Text="000100000000000E"; break;
				//16.监测通道4椭圆拟合信号
				case 12: tbTxData.Text="000100000000000F"; break;
				//    //17.测试专用0x2000
				//    case 17:tbTxData.Text="200000000000000F");break;
				// 无操作
				default: tbTxData.Text="0000000000000000"; break;
			}
		}

		private void lbARM_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch (lbARM.SelectedIndex)
			{
				//1.内部时钟
				case 0: tbTxData.Text="0010000000000000"; break;
				//2.外部时钟
				case 1: tbTxData.Text="0010000000000001"; break;				
				default: break;
			}
		}
		string chnConfig_parent, chnConfig_child1, chnConfig_child2;
		private void lbChannel_SelectedIndexChanged(object sender, EventArgs e)
		{
			lbMode.Items.Clear();
			lbValue.Items.Clear();
			lMode.Visible=true;
			lValue.Visible=true;
			lbMode.Visible=true;
			lbValue.Visible=true;			
			switch (lbChannel.SelectedIndex)
			{
				case 0: //1.通道1标定信号添加
					chnConfig_parent ="0002";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lMode.Text="频率控制字";
					lbMode.Items.Add("1. 1Hz");
					lbMode.Items.Add("2. 10Hz");
					lbMode.Items.Add("3. 100Hz");
					lbMode.Items.Add("4. 1kHz");
					lbMode.Items.Add("5. 10kHz");
					// 通道设置选项框2
					lValue.Text="幅度控制寄存器";
					lbValue.Items.Add("1. 00");
					lbValue.Items.Add("2. 20");
					lbValue.Items.Add("3. 40");
					lbValue.Items.Add("4. 60");
					lbValue.Items.Add("5. FE");
					break;

				case 1: //2.通道2标定信号添加
					chnConfig_parent ="0003";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lMode.Text="频率控制字";
					lbMode.Items.Add("1. 1Hz");
					lbMode.Items.Add("2. 10Hz");
					lbMode.Items.Add("3. 100Hz");
					lbMode.Items.Add("4. 1kHz");
					lbMode.Items.Add("5. 10kHz");
					// 通道设置选项框2
					lValue.Text="幅度控制寄存器";
					lbValue.Items.Add("1. 00");
					lbValue.Items.Add("2. 20");
					lbValue.Items.Add("3. 40");
					lbValue.Items.Add("4. 60");
					lbValue.Items.Add("5. FE");
					break;


				case 2: //3.通道3标定信号添加
					chnConfig_parent ="0004";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;					
					// 通道设置选项框1
					lMode.Text="频率控制字";
					lbMode.Items.Add("1. 1Hz");
					lbMode.Items.Add("2. 10Hz");
					lbMode.Items.Add("3. 100Hz");
					lbMode.Items.Add("4. 1kHz");
					lbMode.Items.Add("5. 10kHz");
					// 通道设置选项框2
					lValue.Text="幅度控制寄存器";
					lbValue.Items.Add("1. 00");
					lbValue.Items.Add("2. 20");
					lbValue.Items.Add("3. 40");
					lbValue.Items.Add("4. 60");
					lbValue.Items.Add("5. FE");
					break;

				case 3:    //4.通道4标定信号添加
					chnConfig_parent ="0005";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lMode.Text="频率控制字";
					lbMode.Items.Add("1. 1Hz");
					lbMode.Items.Add("2. 10Hz");
					lbMode.Items.Add("3. 100Hz");
					lbMode.Items.Add("4. 1kHz");
					lbMode.Items.Add("5. 10kHz");
					// 通道设置选项框2
					lValue.Text="幅度控制寄存器";
					lbValue.Items.Add("1. 00");
					lbValue.Items.Add("2. 20");
					lbValue.Items.Add("3. 40");
					lbValue.Items.Add("4. 60");
					lbValue.Items.Add("5. FE");
					break;

				case 4://5.通道1标定信号卸载
					tbTxData.Text ="0006FFFFFFFFFFFF";
					lMode.Visible=false;
					lValue.Visible=false;
					lbMode.Visible=false;
					lbValue.Visible=false;
					break;

				case 5://6.通道2标定信号卸载
					tbTxData.Text ="0007FFFFFFFFFFFF";
					lMode.Visible=false;
					lValue.Visible=false;
					lbMode.Visible=false;
					lbValue.Visible=false;
					break;

				case 6://7.通道3标定信号卸载
					tbTxData.Text ="0008FFFFFFFFFFFF";
					lMode.Visible=false;
					lValue.Visible=false;
					lbMode.Visible=false;
					lbValue.Visible=false;
					break;

				case 7: //8.通道4标定信号卸载
					tbTxData.Text ="0009FFFFFFFFFFFF";
					lMode.Visible=false;
					lValue.Visible=false;
					lbMode.Visible=false;
					lbValue.Visible=false;
					break;


				case 8: //9.通道1-C值设置
					chnConfig_parent ="0011";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;					
					// 通道设置选项框1
					lMode.Text="模式控制字";
					lbMode.Items.Add("1. 手动");
					lbMode.Items.Add("2. 自动");
					// 通道设置选项框2
					lValue.Text="   C值寄存器";
					lbValue.Items.Add("1.");
					lbValue.Items.Add("2.");
					lbValue.Items.Add("3.");
					lbValue.Items.Add("4.");
					lbValue.Items.Add("5.");
					break;

				case 9://10.通道2-C值设置
					chnConfig_parent ="0012";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;	
					// 通道设置选项框1
					lMode.Text="模式控制字";
					lbMode.Items.Add("1. 手动");
					lbMode.Items.Add("2. 自动");
					// 通道设置选项框2
					lValue.Text="   C值寄存器";
					lbValue.Items.Add("1.");
					lbValue.Items.Add("2.");
					lbValue.Items.Add("3.");
					lbValue.Items.Add("4.");
					lbValue.Items.Add("5.");
					break;

				case 10://11.通道3-C值设置
					chnConfig_parent ="0013";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lMode.Text="模式控制字";
					lbMode.Items.Add("1. 手动");
					lbMode.Items.Add("2. 自动");
					// 通道设置选项框2
					lValue.Text="   C值寄存器";
					lbValue.Items.Add("1.");
					lbValue.Items.Add("2.");
					lbValue.Items.Add("3.");
					lbValue.Items.Add("4.");
					lbValue.Items.Add("5.");
					break;

				case 11://12.通道4-C值设置
					chnConfig_parent ="0014";
					chnConfig_child1  ="";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lMode.Text="模式控制字";
					lbMode.Items.Add("1. 手动");
					lbMode.Items.Add("2. 自动");
					// 通道设置选项框2
					lValue.Text="   C值寄存器";
					lbValue.Items.Add("1.");
					lbValue.Items.Add("2.");
					lbValue.Items.Add("3.");
					lbValue.Items.Add("4.");
					lbValue.Items.Add("5.");
					break;

				case 12://13.通道1-载波幅度
					chnConfig_parent ="0015";
					chnConfig_child1  ="FFFFFFFFF";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lValue.Visible=false;
					lbValue.Visible=false;
					// 通道设置选项框2
					lMode.Text="满量程控制寄存器";
					lbMode.Items.Add("1. 0x000 (8.66mA)");
					lbMode.Items.Add("2. 0x100");
					lbMode.Items.Add("3. 0x200 (20.0mA)");
					lbMode.Items.Add("4. 0x300");
					lbMode.Items.Add("5. 0x3FF (31.66mA)");
					break;

				case 13://14.通道2-载波幅度
					chnConfig_parent ="0016";
					chnConfig_child1  ="FFFFFFFFF";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lValue.Visible = false;
					lbValue.Visible = false;
					// 通道设置选项框2
					lMode.Text="满量程控制寄存器";
					lbMode.Items.Add("1. 0x000 (8.66mA)");
					lbMode.Items.Add("2. 0x100");
					lbMode.Items.Add("3. 0x200 (20.0mA)");
					lbMode.Items.Add("4. 0x300");
					lbMode.Items.Add("5. 0x3FF (31.66mA)");
					break;

				case 14://15.通道3-载波幅度
					chnConfig_parent ="0017";
					chnConfig_child1  ="FFFFFFFFF";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lValue.Visible = false;
					lbValue.Visible = false;
					// 通道设置选项框2
					lMode.Text="满量程控制寄存器";
					lbMode.Items.Add("1. 0x000 (8.66mA)");
					lbMode.Items.Add("2. 0x100");
					lbMode.Items.Add("3. 0x200 (20.0mA)");
					lbMode.Items.Add("4. 0x300");
					lbMode.Items.Add("5. 0x3FF (31.66mA)");
					break;

				case 15: //16.通道4-载波幅度
					chnConfig_parent ="0018";
					chnConfig_child1  ="FFFFFFFFF";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lValue.Visible = false;
					lbValue.Visible = false;
					// 通道设置选项框2
					lMode.Text="满量程控制寄存器";
					lbMode.Items.Add("1. 0x000 (8.66mA)");
					lbMode.Items.Add("2. 0x100");
					lbMode.Items.Add("3. 0x200 (20.0mA)");
					lbMode.Items.Add("4. 0x300");
					lbMode.Items.Add("5. 0x3FF (31.66mA)");
					break;

				case 16://17.光电转换增益设置
					chnConfig_parent ="0019";
					chnConfig_child1  ="FFFFFF";
					chnConfig_child2  ="";
					tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
					// 通道设置选项框1
					lValue.Visible = false;
					lbValue.Visible = false;
					// 通道设置选项框2
					lMode.Text="ADA435控制寄存器";
					lbMode.Items.Add("1.");
					lbMode.Items.Add("2.");
					lbMode.Items.Add("3.");
					lbMode.Items.Add("4.");
					lbMode.Items.Add("5.");
					break;

				// 无操作
				default: break;
			}
		}
		
		private void lbMode_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch (lbChannel.SelectedIndex)
			{
				case 0: //通道1标定信号添加
					switch (lbMode.SelectedIndex)
					{ //频率控制字共40位
						case 0: // 1Hz
							chnConfig_child1 = "000001AD7F";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: // 10Hz
							chnConfig_child1 = "000010C6F7";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: // 100Hz
							chnConfig_child1 = "0000A7C5AC";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: // 1kHz
							chnConfig_child1 = "00068DB8BA";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: // 10kHz
							chnConfig_child1 = "004189374B";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 1: //通道2标定信号添加
					switch (lbMode.SelectedIndex)
					{ //频率控制字共40位
						case 0: // 1Hz
							chnConfig_child1 = "000001AD7F";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: // 10Hz
							chnConfig_child1 = "000010C6F7";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: // 100Hz
							chnConfig_child1 = "0000A7C5AC";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: // 1kHz
							chnConfig_child1 = "00068DB8BA";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: // 10kHz
							chnConfig_child1 = "004189374B";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 2: //通道3标定信号添加
					switch (lbMode.SelectedIndex)
					{ //频率控制字共40位
						case 0: // 1Hz
							chnConfig_child1 = "000001AD7F";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: // 10Hz
							chnConfig_child1 = "000010C6F7";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: // 100Hz
							chnConfig_child1 = "0000A7C5AC";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: // 1kHz
							chnConfig_child1 = "00068DB8BA";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: // 10kHz
							chnConfig_child1 = "004189374B";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 3: //通道4标定信号添加
					switch (lbMode.SelectedIndex)
					{ //频率控制字共40位
						case 0: // 1Hz
							chnConfig_child1 = "000001AD7F";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: // 10Hz
							chnConfig_child1 = "000010C6F7";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: // 100Hz
							chnConfig_child1 = "0000A7C5AC";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: // 1kHz
							chnConfig_child1 = "00068DB8BA";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: // 10kHz
							chnConfig_child1 = "004189374B";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 8: //通道1C值设置
					switch (lbMode.SelectedIndex)
					{ //模式控制字,共2位
						case 0: //手动
							chnConfig_child1 = "0";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //自动
							chnConfig_child1 = "1";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 9: //通道2C值设置
					switch (lbMode.SelectedIndex)
					{ //模式控制字,共2位
						case 0: //手动
							chnConfig_child1 = "0";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //自动
							chnConfig_child1 = "1";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 10: //通道3C值设置
					switch (lbMode.SelectedIndex)
					{ //模式控制字,共2位
						case 0: //手动
							chnConfig_child1 = "0";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //自动
							chnConfig_child1 = "1";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 11: //通道4C值设置
					switch (lbMode.SelectedIndex)
					{ //模式控制字,共2位
						case 0: //手动
							chnConfig_child1 = "0";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //自动
							chnConfig_child1 = "1";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 12: //通道1载波幅度
					switch (lbMode.SelectedIndex)
					{ //满量程控制寄存器：10bit
						case 0: //
							chnConfig_child2 = "000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "100";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "200";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "300";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "3FF";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 13: //通道2载波幅度
					switch (lbMode.SelectedIndex)
					{ //满量程控制寄存器：10bit
						case 0: //
							chnConfig_child2 = "000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "100";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "200";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "300";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "3FF";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 14: //通道3载波幅度
					switch (lbMode.SelectedIndex)
					{ //满量程控制寄存器：10bit
						case 0: //
							chnConfig_child2 = "000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "100";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "200";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "300";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "3FF";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 15: //通道4载波幅度
					switch (lbMode.SelectedIndex)
					{ //满量程控制寄存器：10bit
						case 0: //
							chnConfig_child2 = "000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "100";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "200";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "300";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "3FF";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 16: //光电转换增益设置
					switch (lbMode.SelectedIndex)
					{ //ADA4350控制寄存器:24bit
						case 0: //
							chnConfig_child2 = "000000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "100000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "200000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "300000";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "FFFFFF";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				default: break;
			}
		}

		private void lbValue_SelectedIndexChanged(object sender, EventArgs e)
		{
			switch (lbChannel.SelectedIndex)
			{
				case 0: //通道1标定信号添加
					switch (lbValue.SelectedIndex)
					{ //幅度控制寄存器,最低位插入1位无效位0，共8位
						case 0: //
							chnConfig_child2 = "00";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "20";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: //
							chnConfig_child2 = "40";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: //
							chnConfig_child2 = "60";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: //
							chnConfig_child2 = "FE";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 1: //通道2标定信号添加
					switch (lbValue.SelectedIndex)
					{ //幅度控制寄存器,最低位插入1位无效位0，共8位
						case 0: //
							chnConfig_child2 = "00";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "20";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: //
							chnConfig_child2 = "40";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: //
							chnConfig_child2 = "60";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: //
							chnConfig_child2 = "FE";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 2: //通道3标定信号添加
					switch (lbValue.SelectedIndex)
					{ //幅度控制寄存器,最低位插入1位无效位0，共8位
						case 0: //
							chnConfig_child2 = "00";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "20";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: //
							chnConfig_child2 = "40";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: //
							chnConfig_child2 = "60";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: //
							chnConfig_child2 = "FE";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 3: //通道4标定信号添加
					switch (lbValue.SelectedIndex)
					{ //幅度控制寄存器,最低位插入1位无效位0，共8位
						case 0: //
							chnConfig_child2 = "00";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "20";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2: //
							chnConfig_child2 = "40";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3: //
							chnConfig_child2 = "60";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4: //
							chnConfig_child2 = "FE";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 8: //通道1C值设置
					switch (lbValue.SelectedIndex)
					{ //C值寄存器,共46位
						case 0: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 9: //通道2C值设置
					switch (lbValue.SelectedIndex)
					{ //C值寄存器,共46位
						case 0: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 10: //通道3C值设置
					switch (lbValue.SelectedIndex)
					{ //C值寄存器,共46位
						case 0: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;
				case 11: //通道4C值设置
					switch (lbValue.SelectedIndex)
					{ //C值寄存器,共46位
						case 0: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 1: //
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 2:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 3:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						case 4:
							chnConfig_child2 = "";
							tbTxData.Text = chnConfig_parent + chnConfig_child1 + chnConfig_child2;
							break;
						default: break;
					}
					break;				
				default: 
					break;
			}
		}
	}
}
