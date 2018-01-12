using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace 光电效应PC端
{
    public class CurveData
    {
        public string XueHao;
        public string ZuoWeiHao;
        public string BanJi;
        public byte exWorkTepy;
        public float[,] VAData;
        public int[] VADataCount;
        public bool[] bVAExist;
        public float[,] GQData;
        public int[] GQDataCount;
        public bool[] bGQExist;
        public float[] PLKData;
        public bool bPLKExist;
        public CurveData()
        {
            VAData = new float[6, 101];
            bVAExist = new bool[6];
            for (int i = 0; i < 6; i++)
                bVAExist[i] = false;
            GQData = new float[4, 101];
            bGQExist = new bool[4];
            for (int i = 0; i < 4; i++)
                bGQExist[i] = false;
            PLKData = new float[9];
            bPLKExist = false;
            VADataCount = new int[6];
            GQDataCount = new int[4];

        }
    }
}
