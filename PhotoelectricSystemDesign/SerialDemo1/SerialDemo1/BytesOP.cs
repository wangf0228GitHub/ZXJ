using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SerialDemo1
{
    public class BytesOP
    {
        static public byte GetLowByte(ushort x)
        {
            return (byte)(x & 0xff);
        }
        static public byte GetHighByte(ushort x)
        {
            return (byte)((x >> 8) & 0xff);
        }
        public static ushort MakeShort(byte h, byte l)
        {
            return (ushort)((((ushort)h) << 8) + l);
        }
        public static byte GetVerify_byteSum(byte[] pBuff, int start, int count)
        {
            byte sum = 0;
            for (int i = 0; i < count; i++)
                sum = (byte)(sum + pBuff[i + start]);
            return sum;
        }
    }
}
