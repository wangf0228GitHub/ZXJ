using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace 无线网络49上位机
{
    public class _SensorSignIn
    {
        public bool[] H;
        public bool[] M;
        public bool[] L;
        public _SensorSignIn()
        {
            H = new bool[4];
            M = new bool[8];
            L = new bool[92];
        }
        public void clearSignIn()
        {
            for (int i = 0; i < 4; i++)
                H[i] = false;
            for (int i = 0; i < 8; i++)
                M[i] = false;
            for (int i = 0; i < 92; i++)
                L[i] = false;
        }
    }
    public class _SensorBAT
    {
        public byte[] H;
        public byte[] M;
        public byte[] L;
        public _SensorBAT()
        {
            H = new byte[4];
            M = new byte[8];
            L = new byte[92];
        }
        public void clearBAT()
        {
            for (int i = 0; i < 4; i++)
                H[i] = 0;
            for (int i = 0; i < 8; i++)
                M[i] = 0;
            for (int i = 0; i < 92; i++)
                L[i] = 0;
        }
    }
    public class Class
    {
    }
}
