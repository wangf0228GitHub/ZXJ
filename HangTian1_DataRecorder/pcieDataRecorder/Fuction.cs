using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WFNetLib;
using WFNetLib.StringFunc;

namespace pcieDataRecorder
{
    public class Fuction
    {
        public static void AnalyzeE0Data(ref MeasureE0Data e0, byte[] data, uint len)
        {
            for (uint i = 0; i < len; i += 3)
            {
                int adc = BytesOP.MakeShort(data[i + 1], data[i + 2]);
                switch (data[i])
                {
                    case 0xa0:
                        e0.A0 = adc;
                        break;
                    case 0xa1:
                        e0.A1 = adc;
                        break;
                    case 0xa2:
                        e0.A2 = adc;
                        break;
                    case 0xa3:
                        e0.A3 = adc;
                        break;
                    case 0xa4:
                        e0.A4 = adc;
                        break;
                    case 0xa5:
                        e0.A5 = adc;
                        break;
                    case 0xa6:
                        e0.A6 = adc;
                        break;
                    case 0xa7:
                        e0.A7 = adc;
                        break;
                    case 0xa8:
                        e0.A8 = adc;
                        break;
                    case 0xa9:
                        e0.A9 = adc;
                        break;
                    case 0xaa:
                        e0.A10 = adc;
                        break;
                    case 0xab:
                        e0.A11 = adc;
                        break;
                    case 0xc0:
                        e0.C0 = adc;
                        break;
                    case 0xc1:
                        e0.C1 = adc;
                        break;
                    case 0xc2:
                        e0.C2 = adc;
                        break;
                    case 0xc3:
                        e0.C3 = adc;
                        break;
                    case 0xc4:
                        e0.C4 = adc;
                        break;
                    case 0xc5:
                        e0.C5 = adc;
                        break;
                    case 0xc6:
                        e0.C6 = adc;
                        break;
                    case 0xc7:
                        e0.C7 = adc;
                        break;                    
                }
            }
        }
        public static void AnalyzeE1Data(ref MeasureE1Data e1, byte[] data, uint len)
        {
            for (uint i = 0; i < len;)
            {
                switch (data[i])
                {
                    case 0xb8:
                        e1.B8 = StringsFunction.byteToHexStr(data,(int)(i+1),9,"");
                        i = i + 1 + 9;
                        break;
                    case 0xb9:
                        e1.B9 = StringsFunction.byteToHexStr(data, (int)(i + 1), 9, "");
                        i = i + 1 + 9;
                        break;
                    case 0xba:
                        e1.B10 = StringsFunction.byteToHexStr(data, (int)(i + 1), 9, "");
                        i = i + 1 + 9;
                        break;
                    case 0xbb:
                        e1.B11 = StringsFunction.byteToHexStr(data, (int)(i + 1), 9, "");
                        i = i + 1 + 9;
                        break;

                    case 0xbc:
                        e1.B12 = StringsFunction.byteToHexStr(data, (int)(i + 1), 8, "");
                        i = i + 1 + 8;
                        break;
                    case 0xbd:
                        e1.B13 = StringsFunction.byteToHexStr(data, (int)(i + 1), 8, "");
                        i = i + 1 + 8;
                        break;
                    case 0xbe:
                        e1.B14 = StringsFunction.byteToHexStr(data, (int)(i + 1), 8, "");
                        i = i + 1 + 8;
                        break;
                    case 0xbf:
                        e1.B15 = StringsFunction.byteToHexStr(data, (int)(i + 1), 8, "");
                        i = i + 1 + 8;
                        break;

                    case 0xc0:
                        e1.C0 = StringsFunction.byteToHexStr(data, (int)(i + 1), 5, "");
                        i = i + 1 + 5;
                        break;
                    case 0xc1:
                        e1.C1 = StringsFunction.byteToHexStr(data, (int)(i + 1), 5, "");
                        i = i + 1 + 5;
                        break;
                    case 0xc2:
                        e1.C2 = StringsFunction.byteToHexStr(data, (int)(i + 1), 5, "");
                        i = i + 1 + 5;
                        break;
                    case 0xc3:
                        e1.C3 = StringsFunction.byteToHexStr(data, (int)(i + 1), 5, "");
                        i = i + 1 + 5;
                        break;

                    case 0xc4:
                        e1.C4 = StringsFunction.byteToHexStr(data, (int)(i + 1), 2, "");
                        i = i + 1 + 2;
                        break;
                    case 0xc5:
                        e1.C5 = StringsFunction.byteToHexStr(data, (int)(i + 1), 2, "");
                        i = i + 1 + 2;
                        break;
                    case 0xc6:
                        e1.C6 = StringsFunction.byteToHexStr(data, (int)(i + 1), 2, "");
                        i = i + 1 + 2;
                        break;
                    case 0xc7:
                        e1.C7 = StringsFunction.byteToHexStr(data, (int)(i + 1), 2, "");
                        i = i + 1 + 2;
                        break;

                    case 0xc8:
                        e1.C8 = StringsFunction.byteToHexStr(data, (int)(i + 1), 9, "");
                        i = i + 1 + 9;
                        break;
                    case 0xc9:
                        e1.C9 = StringsFunction.byteToHexStr(data, (int)(i + 1), 9, "");
                        i = i + 1 + 9;
                        break;
                    case 0xca:
                        e1.C10 = StringsFunction.byteToHexStr(data, (int)(i + 1), 10, "");
                        i = i + 1 + 10;
                        break;
                    case 0xcb:
                        e1.C11 = StringsFunction.byteToHexStr(data, (int)(i + 1), 10, "");
                        i = i + 1 + 10;
                        break;

                    case 0xcc:
                        e1.C12 = StringsFunction.byteToHexStr(data, (int)(i + 1), 3, "");
                        i = i + 1 + 3;
                        break;
                    case 0xcd:
                        e1.C13 = StringsFunction.byteToHexStr(data, (int)(i + 1), 3, "");
                        i = i + 1 + 3;
                        break;
                }
            }
        }
    }
}
