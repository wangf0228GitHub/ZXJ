using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace pcieDataRecorder
{
	static class Program
	{
		/// <summary>
		/// 应用程序的主入口点。
		/// </summary>
		[STAThread]
		static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
            WFNetLib.ADO.SQLServerOP.ConnectionString = @"Data Source=.\sql2008;Initial Catalog=detect;Integrated Security=True";
			Application.Run(new Form1());
		}
	}
}
