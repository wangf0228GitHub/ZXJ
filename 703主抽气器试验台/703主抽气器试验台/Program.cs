using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace _703主抽气器试验台
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
            //Application.Run(new loginForm());
            WFNetLib.ADO.SQLServerOP.ConnectionString=@"Data Source=.\SQL2008;Initial Catalog=703主抽气器试验台;Persist Security Info=True;User ID=sa;Password=1001001";
            Application.Run(new loginForm());
            //Application.Run(new mainForm());
        }
    }
}
