using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace 无线网络49上位机
{
    public class Calc
    {
        public static string GetBAT(byte bat)
        {
            double f;
            f = -0.000000574 * bat * bat * bat * bat + 0.0004658 * bat * bat * bat - 0.1269794 * bat * bat + 14.1424792 * bat - 545.36;
            f = f + 0.5;
            return f.ToString("F0")+"%";
        }
        public static double GetSensorType0(int addr, ushort ad)
        {
            double Uadc;
            Uadc = ad * 3.0 / 4096.0;
            return Uadc - 1.5; 
        }
        public static double GetSensorType1(int addr, ushort ad)
        {
            double Uadc;
            Uadc = ad * 3.0 / 4096.0;
            return Uadc - 1.5;
        }
        public static double GetSensorType2_15_18(ushort ad)
        {
            double Uadc;
            Uadc = ad * 3.0 / 4096.0;
            return Uadc;
        }
        const double k1112 = 2.62;
        const double b1112 = -262.93;
        const double k1314 = 0.257387;
        const double b1314 = -257.313;
        public static double GetSensorType2_11(ushort ad)//分体式1
        {
            double Uadc;
            double T, R;           
            Uadc = ad * 3.0 / 4096.0;
            if(Uadc!=0)
            {
                R = 125.0 / Uadc - 100;
                T = k1112 * R + b1112;
            }
            else
            {
                T = -100.0;
            }
            return T;
        }
        public static double GetSensorType2_12(ushort ad)//分体式2
        {
            double Uadc;
            double T, R;
            Uadc = ad * 3.0 / 4096.0;
            if (Uadc != 0)
            {
                R = 125.0 / Uadc - 100;
                T = k1112 * R + b1112;
            }
            else
            {
                T = -100.0;
            }
            return T;
        }
        public static double GetSensorType2_13(ushort ad)//一体式温度1
        {
            double Uadc;
            double T, R;
            Uadc = ad * 3.0 / 4096.0;
            if (Uadc != 0)
            {
                R = 1250.0 / Uadc - 1000;
                T = k1314 * R + b1314;
                T = T - 3.9;
            }
            else
            {
                T = -100.0;
            }
            return T;
        }
        public static double GetSensorType2_14(ushort ad)//一体式温度2
        {
            double Uadc;
            double T, R;
            Uadc = ad * 3.0 / 4096.0;
            if (Uadc != 0)
            {
                R = 1250.0 / Uadc - 1000;
                T = k1314 * R + b1314;
                T = T - 3.9;
            }
            else
            {
                T = -100.0;
            }
            return T;
        }
    }
}
