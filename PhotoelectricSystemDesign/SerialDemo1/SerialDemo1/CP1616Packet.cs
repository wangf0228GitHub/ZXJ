using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SerialDemo1
{
    public class CP1616Packet
    {
        public byte[] HeaderData;
        public byte[] CommandData;
        public int RxCount;        
        public static Int32 BUFFER_SIZE = 1024;
        public static Int32 HEAD_SIZE = 5;
        public CP1616Packet()
        {            
            RxCount = 0;
            HeaderData = new byte[HEAD_SIZE];
        }
        public void Reset()
        {
            RxCount = 0;
            HeaderData = new byte[HEAD_SIZE];
        }
        public byte[] MakeCP1616Packet(byte com)
        {
            return MakeCP1616Packet(com, null);
        }
        public byte[] MakeCP1616Packet(byte com, byte[] data)
        {
            int nIndex = 0;
            byte[] txbuffer;
            if (data != null)
            {
                txbuffer = new byte[HEAD_SIZE + data.Length + 2];
                txbuffer[nIndex++] = 0x16;
                txbuffer[nIndex++] = 0x16;
                txbuffer[nIndex++] = com;                
                txbuffer[nIndex++] = BytesOP.GetHighByte((UInt16)data.Length);
                txbuffer[nIndex++] = BytesOP.GetLowByte((UInt16)data.Length);                
                for (int i = 0; i < data.Length; i++)
                {
                    txbuffer[i + HEAD_SIZE] = data[i];
                }
                txbuffer[HEAD_SIZE + data.Length] = BytesOP.GetVerify_byteSum(txbuffer, 0,HEAD_SIZE + data.Length);
                txbuffer[HEAD_SIZE + data.Length + 1] = 0x0d;
            }
            else
            {
                txbuffer = new byte[HEAD_SIZE + 2];
                txbuffer[nIndex++] = 0x16;
                txbuffer[nIndex++] = 0x16;
                txbuffer[nIndex++] = com;
                txbuffer[nIndex++] = 0;
                txbuffer[nIndex++] = 0;
                txbuffer[HEAD_SIZE] = BytesOP.GetVerify_byteSum(txbuffer, 0,HEAD_SIZE);
                txbuffer[HEAD_SIZE + 1] = 0x0d;
            }
            return txbuffer;
        }
        public bool DataPacketed(byte rx)
        {
            //判断读取的字节数+缓冲区已有字节数是否超过缓冲区总大小
            if (RxCount < HEAD_SIZE)
            {
                HeaderData[RxCount++] = rx;
                if (RxCount == HEAD_SIZE)//判断帧长度
                {
                    int len = BytesOP.MakeShort(HeaderData[CP1616Packet.HEAD_SIZE - 2], HeaderData[CP1616Packet.HEAD_SIZE - 1]);
                    CommandData = new byte[len + 2];
                }
                else if (RxCount == 1)
                {
                    if (HeaderData[0] != 0x16)
                    {
                        RxCount = 0;                        
                    }
                }
                else if (RxCount == 2)
                {
                    if (HeaderData[1] != 0x16)
                    {
                        RxCount = 0;                       
                    }
                }                
            }
            else
            {
                CommandData[RxCount - CP1616Packet.HEAD_SIZE] = rx;
                RxCount++;
                if (RxCount == (CP1616Packet.HEAD_SIZE + CommandData.Length))
                {
                    if (CommandData[CommandData.Length - 1] == 0x0d)
                    {
                        byte s1 = BytesOP.GetVerify_byteSum(HeaderData,0,HEAD_SIZE);
                        byte s2 = BytesOP.GetVerify_byteSum(CommandData, 0,CommandData.Length - 2);
                        s1 = (byte)(s1 + s2);
                        if (s1 == CommandData[CommandData.Length - 2])
                            return true;
                        else
                        {
                            RxCount = 0;
                            return false;
                        }
                    }
                    else
                    {
                        RxCount = 0;
                        return false;
                    }
                }
            }
            return false;
        }
    }
}
