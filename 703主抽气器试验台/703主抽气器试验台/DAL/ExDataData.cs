using System;
using System.Data;
using System.Windows.Forms;
using System.Text;
using System.Data.SqlClient;

namespace DAL
{
    [Serializable]
    public class ExDataData
    {

        public const string EXIDField = @"ExID";

        public const string DATATIMEField = @"DataTime";

        public const string AI01Field = @"AI01";

        public const string AI02Field = @"AI02";

        public const string AI03Field = @"AI03";

        public const string AI04Field = @"AI04";

        public const string AI05Field = @"AI05";

        public const string AI06Field = @"AI06";

        public const string AI07Field = @"AI07";

        public const string AI08Field = @"AI08";

        public const string AI09Field = @"AI09";

        public const string AI10Field = @"AI10";

        public const string AI11Field = @"AI11";

        public const string AI12Field = @"AI12";

        public const string AI13Field = @"AI13";

        public const string AI14Field = @"AI14";

        public const string AI15Field = @"AI15";

        public const string AI16Field = @"AI16";

        public const string AI17Field = @"AI17";

        public const string AI18Field = @"AI18";

        public const string AI19Field = @"AI19";

        public const string AI20Field = @"AI20";

        public const string AI21Field = @"AI21";

        public const string AI22Field = @"AI22";

        public const string AI23Field = @"AI23";

        public const string AI24Field = @"AI24";

        public const string AI25Field = @"AI25";

        public const string AI26Field = @"AI26";

        public const string AI27Field = @"AI27";

        public const string AI28Field = @"AI28";

        public const string AI29Field = @"AI29";

        public const string AI30Field = @"AI30";

        public const string AI31Field = @"AI31";

        public const string AI32Field = @"AI32";

        public const string AI33Field = @"AI33";

        public const string AI34Field = @"AI34";

        public const string AI35Field = @"AI35";

        public const string AI36Field = @"AI36";

        public const string AI37Field = @"AI37";

        public const string AI38Field = @"AI38";

        public const string AI39Field = @"AI39";

        public const string AI40Field = @"AI40";

        public const string AI41Field = @"AI41";

        public const string AI42Field = @"AI42";

        public const string AI43Field = @"AI43";

        public const string AI44Field = @"AI44";

        public const string AI45Field = @"AI45";

        public const string AI46Field = @"AI46";

        public const string AI47Field = @"AI47";

        public const string AI48Field = @"AI48";

        public const string AI49Field = @"AI49";

        public const string AI50Field = @"AI50";

        public const string AI51Field = @"AI51";

        public const string AI52Field = @"AI52";

        public const string AI53Field = @"AI53";

        public const string AI54Field = @"AI54";

        public const string AI55Field = @"AI55";

        public const string AI56Field = @"AI56";

        public const string AI57Field = @"AI57";

        public const string AI58Field = @"AI58";

        public const string AI59Field = @"AI59";

        public const string AI60Field = @"AI60";

        public const string AI61Field = @"AI61";

        public const string AI62Field = @"AI62";

        public const string AI63Field = @"AI63";

        public const string AI64Field = @"AI64";

        private Int32 _ExID;

        private DateTime _DataTime;

        private Double _AI01;

        private Double _AI02;

        private Double _AI03;

        private Double _AI04;

        private Double _AI05;

        private Double _AI06;

        private Double _AI07;

        private Double _AI08;

        private Double _AI09;

        private Double _AI10;

        private Double _AI11;

        private Double _AI12;

        private Double _AI13;

        private Double _AI14;

        private Double _AI15;

        private Double _AI16;

        private Double _AI17;

        private Double _AI18;

        private Double _AI19;

        private Double _AI20;

        private Double _AI21;

        private Double _AI22;

        private Double _AI23;

        private Double _AI24;

        private Double _AI25;

        private Double _AI26;

        private Double _AI27;

        private Double _AI28;

        private Double _AI29;

        private Double _AI30;

        private Double _AI31;

        private Double _AI32;

        private Double _AI33;

        private Double _AI34;

        private Double _AI35;

        private Double _AI36;

        private Double _AI37;

        private Double _AI38;

        private Double _AI39;

        private Double _AI40;

        private Double _AI41;

        private Double _AI42;

        private Double _AI43;

        private Double _AI44;

        private Double _AI45;

        private Double _AI46;

        private Double _AI47;

        private Double _AI48;

        private Double _AI49;

        private Double _AI50;

        private Double _AI51;

        private Double _AI52;

        private Double _AI53;

        private Double _AI54;

        private Double _AI55;

        private Double _AI56;

        private Double _AI57;

        private Double _AI58;

        private Double _AI59;

        private Double _AI60;

        private Double _AI61;

        private Double _AI62;

        private Double _AI63;

        private Double _AI64;

        public Int32 ExID
        {
            get { return _ExID; }
            set { _ExID = value; }
        }
        public DateTime DataTime
        {
            get { return _DataTime; }
            set { _DataTime = value; }
        }
        public Double AI01
        {
            get { return _AI01; }
            set { _AI01 = value; }
        }
        public Double AI02
        {
            get { return _AI02; }
            set { _AI02 = value; }
        }
        public Double AI03
        {
            get { return _AI03; }
            set { _AI03 = value; }
        }
        public Double AI04
        {
            get { return _AI04; }
            set { _AI04 = value; }
        }
        public Double AI05
        {
            get { return _AI05; }
            set { _AI05 = value; }
        }
        public Double AI06
        {
            get { return _AI06; }
            set { _AI06 = value; }
        }
        public Double AI07
        {
            get { return _AI07; }
            set { _AI07 = value; }
        }
        public Double AI08
        {
            get { return _AI08; }
            set { _AI08 = value; }
        }
        public Double AI09
        {
            get { return _AI09; }
            set { _AI09 = value; }
        }
        public Double AI10
        {
            get { return _AI10; }
            set { _AI10 = value; }
        }
        public Double AI11
        {
            get { return _AI11; }
            set { _AI11 = value; }
        }
        public Double AI12
        {
            get { return _AI12; }
            set { _AI12 = value; }
        }
        public Double AI13
        {
            get { return _AI13; }
            set { _AI13 = value; }
        }
        public Double AI14
        {
            get { return _AI14; }
            set { _AI14 = value; }
        }
        public Double AI15
        {
            get { return _AI15; }
            set { _AI15 = value; }
        }
        public Double AI16
        {
            get { return _AI16; }
            set { _AI16 = value; }
        }
        public Double AI17
        {
            get { return _AI17; }
            set { _AI17 = value; }
        }
        public Double AI18
        {
            get { return _AI18; }
            set { _AI18 = value; }
        }
        public Double AI19
        {
            get { return _AI19; }
            set { _AI19 = value; }
        }
        public Double AI20
        {
            get { return _AI20; }
            set { _AI20 = value; }
        }
        public Double AI21
        {
            get { return _AI21; }
            set { _AI21 = value; }
        }
        public Double AI22
        {
            get { return _AI22; }
            set { _AI22 = value; }
        }
        public Double AI23
        {
            get { return _AI23; }
            set { _AI23 = value; }
        }
        public Double AI24
        {
            get { return _AI24; }
            set { _AI24 = value; }
        }
        public Double AI25
        {
            get { return _AI25; }
            set { _AI25 = value; }
        }
        public Double AI26
        {
            get { return _AI26; }
            set { _AI26 = value; }
        }
        public Double AI27
        {
            get { return _AI27; }
            set { _AI27 = value; }
        }
        public Double AI28
        {
            get { return _AI28; }
            set { _AI28 = value; }
        }
        public Double AI29
        {
            get { return _AI29; }
            set { _AI29 = value; }
        }
        public Double AI30
        {
            get { return _AI30; }
            set { _AI30 = value; }
        }
        public Double AI31
        {
            get { return _AI31; }
            set { _AI31 = value; }
        }
        public Double AI32
        {
            get { return _AI32; }
            set { _AI32 = value; }
        }
        public Double AI33
        {
            get { return _AI33; }
            set { _AI33 = value; }
        }
        public Double AI34
        {
            get { return _AI34; }
            set { _AI34 = value; }
        }
        public Double AI35
        {
            get { return _AI35; }
            set { _AI35 = value; }
        }
        public Double AI36
        {
            get { return _AI36; }
            set { _AI36 = value; }
        }
        public Double AI37
        {
            get { return _AI37; }
            set { _AI37 = value; }
        }
        public Double AI38
        {
            get { return _AI38; }
            set { _AI38 = value; }
        }
        public Double AI39
        {
            get { return _AI39; }
            set { _AI39 = value; }
        }
        public Double AI40
        {
            get { return _AI40; }
            set { _AI40 = value; }
        }
        public Double AI41
        {
            get { return _AI41; }
            set { _AI41 = value; }
        }
        public Double AI42
        {
            get { return _AI42; }
            set { _AI42 = value; }
        }
        public Double AI43
        {
            get { return _AI43; }
            set { _AI43 = value; }
        }
        public Double AI44
        {
            get { return _AI44; }
            set { _AI44 = value; }
        }
        public Double AI45
        {
            get { return _AI45; }
            set { _AI45 = value; }
        }
        public Double AI46
        {
            get { return _AI46; }
            set { _AI46 = value; }
        }
        public Double AI47
        {
            get { return _AI47; }
            set { _AI47 = value; }
        }
        public Double AI48
        {
            get { return _AI48; }
            set { _AI48 = value; }
        }
        public Double AI49
        {
            get { return _AI49; }
            set { _AI49 = value; }
        }
        public Double AI50
        {
            get { return _AI50; }
            set { _AI50 = value; }
        }
        public Double AI51
        {
            get { return _AI51; }
            set { _AI51 = value; }
        }
        public Double AI52
        {
            get { return _AI52; }
            set { _AI52 = value; }
        }
        public Double AI53
        {
            get { return _AI53; }
            set { _AI53 = value; }
        }
        public Double AI54
        {
            get { return _AI54; }
            set { _AI54 = value; }
        }
        public Double AI55
        {
            get { return _AI55; }
            set { _AI55 = value; }
        }
        public Double AI56
        {
            get { return _AI56; }
            set { _AI56 = value; }
        }
        public Double AI57
        {
            get { return _AI57; }
            set { _AI57 = value; }
        }
        public Double AI58
        {
            get { return _AI58; }
            set { _AI58 = value; }
        }
        public Double AI59
        {
            get { return _AI59; }
            set { _AI59 = value; }
        }
        public Double AI60
        {
            get { return _AI60; }
            set { _AI60 = value; }
        }
        public Double AI61
        {
            get { return _AI61; }
            set { _AI61 = value; }
        }
        public Double AI62
        {
            get { return _AI62; }
            set { _AI62 = value; }
        }
        public Double AI63
        {
            get { return _AI63; }
            set { _AI63 = value; }
        }
        public Double AI64
        {
            get { return _AI64; }
            set { _AI64 = value; }
        }
        public ExDataData()
        {
            _ExID = 0;
            _DataTime = DateTime.Now;
            _AI01 = 0;
            _AI02 = 0;
            _AI03 = 0;
            _AI04 = 0;
            _AI05 = 0;
            _AI06 = 0;
            _AI07 = 0;
            _AI08 = 0;
            _AI09 = 0;
            _AI10 = 0;
            _AI11 = 0;
            _AI12 = 0;
            _AI13 = 0;
            _AI14 = 0;
            _AI15 = 0;
            _AI16 = 0;
            _AI17 = 0;
            _AI18 = 0;
            _AI19 = 0;
            _AI20 = 0;
            _AI21 = 0;
            _AI22 = 0;
            _AI23 = 0;
            _AI24 = 0;
            _AI25 = 0;
            _AI26 = 0;
            _AI27 = 0;
            _AI28 = 0;
            _AI29 = 0;
            _AI30 = 0;
            _AI31 = 0;
            _AI32 = 0;
            _AI33 = 0;
            _AI34 = 0;
            _AI35 = 0;
            _AI36 = 0;
            _AI37 = 0;
            _AI38 = 0;
            _AI39 = 0;
            _AI40 = 0;
            _AI41 = 0;
            _AI42 = 0;
            _AI43 = 0;
            _AI44 = 0;
            _AI45 = 0;
            _AI46 = 0;
            _AI47 = 0;
            _AI48 = 0;
            _AI49 = 0;
            _AI50 = 0;
            _AI51 = 0;
            _AI52 = 0;
            _AI53 = 0;
            _AI54 = 0;
            _AI55 = 0;
            _AI56 = 0;
            _AI57 = 0;
            _AI58 = 0;
            _AI59 = 0;
            _AI60 = 0;
            _AI61 = 0;
            _AI62 = 0;
            _AI63 = 0;
            _AI64 = 0;
        }
    }

    public class ExDataDataFactory
    {
        public static ExDataData Construct(IDataReader reader)
        {
            ExDataData data = new ExDataData();

            try { data.ExID = Convert.ToInt32(reader["ExID"]); }
            catch { }

            try { data.DataTime = Convert.ToDateTime(reader["DataTime"]); }
            catch { }

            try { data.AI01 = Convert.ToDouble(reader["AI01"]); }
            catch { }

            try { data.AI02 = Convert.ToDouble(reader["AI02"]); }
            catch { }

            try { data.AI03 = Convert.ToDouble(reader["AI03"]); }
            catch { }

            try { data.AI04 = Convert.ToDouble(reader["AI04"]); }
            catch { }

            try { data.AI05 = Convert.ToDouble(reader["AI05"]); }
            catch { }

            try { data.AI06 = Convert.ToDouble(reader["AI06"]); }
            catch { }

            try { data.AI07 = Convert.ToDouble(reader["AI07"]); }
            catch { }

            try { data.AI08 = Convert.ToDouble(reader["AI08"]); }
            catch { }

            try { data.AI09 = Convert.ToDouble(reader["AI09"]); }
            catch { }

            try { data.AI10 = Convert.ToDouble(reader["AI10"]); }
            catch { }

            try { data.AI11 = Convert.ToDouble(reader["AI11"]); }
            catch { }

            try { data.AI12 = Convert.ToDouble(reader["AI12"]); }
            catch { }

            try { data.AI13 = Convert.ToDouble(reader["AI13"]); }
            catch { }

            try { data.AI14 = Convert.ToDouble(reader["AI14"]); }
            catch { }

            try { data.AI15 = Convert.ToDouble(reader["AI15"]); }
            catch { }

            try { data.AI16 = Convert.ToDouble(reader["AI16"]); }
            catch { }

            try { data.AI17 = Convert.ToDouble(reader["AI17"]); }
            catch { }

            try { data.AI18 = Convert.ToDouble(reader["AI18"]); }
            catch { }

            try { data.AI19 = Convert.ToDouble(reader["AI19"]); }
            catch { }

            try { data.AI20 = Convert.ToDouble(reader["AI20"]); }
            catch { }

            try { data.AI21 = Convert.ToDouble(reader["AI21"]); }
            catch { }

            try { data.AI22 = Convert.ToDouble(reader["AI22"]); }
            catch { }

            try { data.AI23 = Convert.ToDouble(reader["AI23"]); }
            catch { }

            try { data.AI24 = Convert.ToDouble(reader["AI24"]); }
            catch { }

            try { data.AI25 = Convert.ToDouble(reader["AI25"]); }
            catch { }

            try { data.AI26 = Convert.ToDouble(reader["AI26"]); }
            catch { }

            try { data.AI27 = Convert.ToDouble(reader["AI27"]); }
            catch { }

            try { data.AI28 = Convert.ToDouble(reader["AI28"]); }
            catch { }

            try { data.AI29 = Convert.ToDouble(reader["AI29"]); }
            catch { }

            try { data.AI30 = Convert.ToDouble(reader["AI30"]); }
            catch { }

            try { data.AI31 = Convert.ToDouble(reader["AI31"]); }
            catch { }

            try { data.AI32 = Convert.ToDouble(reader["AI32"]); }
            catch { }

            try { data.AI33 = Convert.ToDouble(reader["AI33"]); }
            catch { }

            try { data.AI34 = Convert.ToDouble(reader["AI34"]); }
            catch { }

            try { data.AI35 = Convert.ToDouble(reader["AI35"]); }
            catch { }

            try { data.AI36 = Convert.ToDouble(reader["AI36"]); }
            catch { }

            try { data.AI37 = Convert.ToDouble(reader["AI37"]); }
            catch { }

            try { data.AI38 = Convert.ToDouble(reader["AI38"]); }
            catch { }

            try { data.AI39 = Convert.ToDouble(reader["AI39"]); }
            catch { }

            try { data.AI40 = Convert.ToDouble(reader["AI40"]); }
            catch { }

            try { data.AI41 = Convert.ToDouble(reader["AI41"]); }
            catch { }

            try { data.AI42 = Convert.ToDouble(reader["AI42"]); }
            catch { }

            try { data.AI43 = Convert.ToDouble(reader["AI43"]); }
            catch { }

            try { data.AI44 = Convert.ToDouble(reader["AI44"]); }
            catch { }

            try { data.AI45 = Convert.ToDouble(reader["AI45"]); }
            catch { }

            try { data.AI46 = Convert.ToDouble(reader["AI46"]); }
            catch { }

            try { data.AI47 = Convert.ToDouble(reader["AI47"]); }
            catch { }

            try { data.AI48 = Convert.ToDouble(reader["AI48"]); }
            catch { }

            try { data.AI49 = Convert.ToDouble(reader["AI49"]); }
            catch { }

            try { data.AI50 = Convert.ToDouble(reader["AI50"]); }
            catch { }

            try { data.AI51 = Convert.ToDouble(reader["AI51"]); }
            catch { }

            try { data.AI52 = Convert.ToDouble(reader["AI52"]); }
            catch { }

            try { data.AI53 = Convert.ToDouble(reader["AI53"]); }
            catch { }

            try { data.AI54 = Convert.ToDouble(reader["AI54"]); }
            catch { }

            try { data.AI55 = Convert.ToDouble(reader["AI55"]); }
            catch { }

            try { data.AI56 = Convert.ToDouble(reader["AI56"]); }
            catch { }

            try { data.AI57 = Convert.ToDouble(reader["AI57"]); }
            catch { }

            try { data.AI58 = Convert.ToDouble(reader["AI58"]); }
            catch { }

            try { data.AI59 = Convert.ToDouble(reader["AI59"]); }
            catch { }

            try { data.AI60 = Convert.ToDouble(reader["AI60"]); }
            catch { }

            try { data.AI61 = Convert.ToDouble(reader["AI61"]); }
            catch { }

            try { data.AI62 = Convert.ToDouble(reader["AI62"]); }
            catch { }

            try { data.AI63 = Convert.ToDouble(reader["AI63"]); }
            catch { }

            try { data.AI64 = Convert.ToDouble(reader["AI64"]); }
            catch { }

            return data;
        }
        public static ExDataData Construct(DataTable dt)
        {
            return Construct(dt, 0);
        }
        public static ExDataData Construct(DataTable dt, int rowIndex)
        {
            ExDataData data = new ExDataData();

            if (dt.Rows.Count < rowIndex + 1)

                return null;

            DataRow dr = dt.Rows[rowIndex];

            if (dr == null)

                return null;

            try { data.ExID = Convert.ToInt32(dr["ExID"]); }
            catch { }

            try { data.DataTime = Convert.ToDateTime(dr["DataTime"]); }
            catch { }

            try { data.AI01 = Convert.ToDouble(dr["AI01"]); }
            catch { }

            try { data.AI02 = Convert.ToDouble(dr["AI02"]); }
            catch { }

            try { data.AI03 = Convert.ToDouble(dr["AI03"]); }
            catch { }

            try { data.AI04 = Convert.ToDouble(dr["AI04"]); }
            catch { }

            try { data.AI05 = Convert.ToDouble(dr["AI05"]); }
            catch { }

            try { data.AI06 = Convert.ToDouble(dr["AI06"]); }
            catch { }

            try { data.AI07 = Convert.ToDouble(dr["AI07"]); }
            catch { }

            try { data.AI08 = Convert.ToDouble(dr["AI08"]); }
            catch { }

            try { data.AI09 = Convert.ToDouble(dr["AI09"]); }
            catch { }

            try { data.AI10 = Convert.ToDouble(dr["AI10"]); }
            catch { }

            try { data.AI11 = Convert.ToDouble(dr["AI11"]); }
            catch { }

            try { data.AI12 = Convert.ToDouble(dr["AI12"]); }
            catch { }

            try { data.AI13 = Convert.ToDouble(dr["AI13"]); }
            catch { }

            try { data.AI14 = Convert.ToDouble(dr["AI14"]); }
            catch { }

            try { data.AI15 = Convert.ToDouble(dr["AI15"]); }
            catch { }

            try { data.AI16 = Convert.ToDouble(dr["AI16"]); }
            catch { }

            try { data.AI17 = Convert.ToDouble(dr["AI17"]); }
            catch { }

            try { data.AI18 = Convert.ToDouble(dr["AI18"]); }
            catch { }

            try { data.AI19 = Convert.ToDouble(dr["AI19"]); }
            catch { }

            try { data.AI20 = Convert.ToDouble(dr["AI20"]); }
            catch { }

            try { data.AI21 = Convert.ToDouble(dr["AI21"]); }
            catch { }

            try { data.AI22 = Convert.ToDouble(dr["AI22"]); }
            catch { }

            try { data.AI23 = Convert.ToDouble(dr["AI23"]); }
            catch { }

            try { data.AI24 = Convert.ToDouble(dr["AI24"]); }
            catch { }

            try { data.AI25 = Convert.ToDouble(dr["AI25"]); }
            catch { }

            try { data.AI26 = Convert.ToDouble(dr["AI26"]); }
            catch { }

            try { data.AI27 = Convert.ToDouble(dr["AI27"]); }
            catch { }

            try { data.AI28 = Convert.ToDouble(dr["AI28"]); }
            catch { }

            try { data.AI29 = Convert.ToDouble(dr["AI29"]); }
            catch { }

            try { data.AI30 = Convert.ToDouble(dr["AI30"]); }
            catch { }

            try { data.AI31 = Convert.ToDouble(dr["AI31"]); }
            catch { }

            try { data.AI32 = Convert.ToDouble(dr["AI32"]); }
            catch { }

            try { data.AI33 = Convert.ToDouble(dr["AI33"]); }
            catch { }

            try { data.AI34 = Convert.ToDouble(dr["AI34"]); }
            catch { }

            try { data.AI35 = Convert.ToDouble(dr["AI35"]); }
            catch { }

            try { data.AI36 = Convert.ToDouble(dr["AI36"]); }
            catch { }

            try { data.AI37 = Convert.ToDouble(dr["AI37"]); }
            catch { }

            try { data.AI38 = Convert.ToDouble(dr["AI38"]); }
            catch { }

            try { data.AI39 = Convert.ToDouble(dr["AI39"]); }
            catch { }

            try { data.AI40 = Convert.ToDouble(dr["AI40"]); }
            catch { }

            try { data.AI41 = Convert.ToDouble(dr["AI41"]); }
            catch { }

            try { data.AI42 = Convert.ToDouble(dr["AI42"]); }
            catch { }

            try { data.AI43 = Convert.ToDouble(dr["AI43"]); }
            catch { }

            try { data.AI44 = Convert.ToDouble(dr["AI44"]); }
            catch { }

            try { data.AI45 = Convert.ToDouble(dr["AI45"]); }
            catch { }

            try { data.AI46 = Convert.ToDouble(dr["AI46"]); }
            catch { }

            try { data.AI47 = Convert.ToDouble(dr["AI47"]); }
            catch { }

            try { data.AI48 = Convert.ToDouble(dr["AI48"]); }
            catch { }

            try { data.AI49 = Convert.ToDouble(dr["AI49"]); }
            catch { }

            try { data.AI50 = Convert.ToDouble(dr["AI50"]); }
            catch { }

            try { data.AI51 = Convert.ToDouble(dr["AI51"]); }
            catch { }

            try { data.AI52 = Convert.ToDouble(dr["AI52"]); }
            catch { }

            try { data.AI53 = Convert.ToDouble(dr["AI53"]); }
            catch { }

            try { data.AI54 = Convert.ToDouble(dr["AI54"]); }
            catch { }

            try { data.AI55 = Convert.ToDouble(dr["AI55"]); }
            catch { }

            try { data.AI56 = Convert.ToDouble(dr["AI56"]); }
            catch { }

            try { data.AI57 = Convert.ToDouble(dr["AI57"]); }
            catch { }

            try { data.AI58 = Convert.ToDouble(dr["AI58"]); }
            catch { }

            try { data.AI59 = Convert.ToDouble(dr["AI59"]); }
            catch { }

            try { data.AI60 = Convert.ToDouble(dr["AI60"]); }
            catch { }

            try { data.AI61 = Convert.ToDouble(dr["AI61"]); }
            catch { }

            try { data.AI62 = Convert.ToDouble(dr["AI62"]); }
            catch { }

            try { data.AI63 = Convert.ToDouble(dr["AI63"]); }
            catch { }

            try { data.AI64 = Convert.ToDouble(dr["AI64"]); }
            catch { }

            return data;
        }
        public static ExDataData Construct(DataGridView dgv, int rowIndex)
        {
            ExDataData data = new ExDataData();

            if (dgv.Rows.Count < rowIndex + 1)

                return null;

            DataGridViewCellCollection dr = dgv.Rows[rowIndex].Cells;

            if (dr == null)

                return null;

            try { data.ExID = Convert.ToInt32(dr["ExID"]); }
            catch { }

            try { data.DataTime = Convert.ToDateTime(dr["DataTime"]); }
            catch { }

            try { data.AI01 = Convert.ToDouble(dr["AI01"]); }
            catch { }

            try { data.AI02 = Convert.ToDouble(dr["AI02"]); }
            catch { }

            try { data.AI03 = Convert.ToDouble(dr["AI03"]); }
            catch { }

            try { data.AI04 = Convert.ToDouble(dr["AI04"]); }
            catch { }

            try { data.AI05 = Convert.ToDouble(dr["AI05"]); }
            catch { }

            try { data.AI06 = Convert.ToDouble(dr["AI06"]); }
            catch { }

            try { data.AI07 = Convert.ToDouble(dr["AI07"]); }
            catch { }

            try { data.AI08 = Convert.ToDouble(dr["AI08"]); }
            catch { }

            try { data.AI09 = Convert.ToDouble(dr["AI09"]); }
            catch { }

            try { data.AI10 = Convert.ToDouble(dr["AI10"]); }
            catch { }

            try { data.AI11 = Convert.ToDouble(dr["AI11"]); }
            catch { }

            try { data.AI12 = Convert.ToDouble(dr["AI12"]); }
            catch { }

            try { data.AI13 = Convert.ToDouble(dr["AI13"]); }
            catch { }

            try { data.AI14 = Convert.ToDouble(dr["AI14"]); }
            catch { }

            try { data.AI15 = Convert.ToDouble(dr["AI15"]); }
            catch { }

            try { data.AI16 = Convert.ToDouble(dr["AI16"]); }
            catch { }

            try { data.AI17 = Convert.ToDouble(dr["AI17"]); }
            catch { }

            try { data.AI18 = Convert.ToDouble(dr["AI18"]); }
            catch { }

            try { data.AI19 = Convert.ToDouble(dr["AI19"]); }
            catch { }

            try { data.AI20 = Convert.ToDouble(dr["AI20"]); }
            catch { }

            try { data.AI21 = Convert.ToDouble(dr["AI21"]); }
            catch { }

            try { data.AI22 = Convert.ToDouble(dr["AI22"]); }
            catch { }

            try { data.AI23 = Convert.ToDouble(dr["AI23"]); }
            catch { }

            try { data.AI24 = Convert.ToDouble(dr["AI24"]); }
            catch { }

            try { data.AI25 = Convert.ToDouble(dr["AI25"]); }
            catch { }

            try { data.AI26 = Convert.ToDouble(dr["AI26"]); }
            catch { }

            try { data.AI27 = Convert.ToDouble(dr["AI27"]); }
            catch { }

            try { data.AI28 = Convert.ToDouble(dr["AI28"]); }
            catch { }

            try { data.AI29 = Convert.ToDouble(dr["AI29"]); }
            catch { }

            try { data.AI30 = Convert.ToDouble(dr["AI30"]); }
            catch { }

            try { data.AI31 = Convert.ToDouble(dr["AI31"]); }
            catch { }

            try { data.AI32 = Convert.ToDouble(dr["AI32"]); }
            catch { }

            try { data.AI33 = Convert.ToDouble(dr["AI33"]); }
            catch { }

            try { data.AI34 = Convert.ToDouble(dr["AI34"]); }
            catch { }

            try { data.AI35 = Convert.ToDouble(dr["AI35"]); }
            catch { }

            try { data.AI36 = Convert.ToDouble(dr["AI36"]); }
            catch { }

            try { data.AI37 = Convert.ToDouble(dr["AI37"]); }
            catch { }

            try { data.AI38 = Convert.ToDouble(dr["AI38"]); }
            catch { }

            try { data.AI39 = Convert.ToDouble(dr["AI39"]); }
            catch { }

            try { data.AI40 = Convert.ToDouble(dr["AI40"]); }
            catch { }

            try { data.AI41 = Convert.ToDouble(dr["AI41"]); }
            catch { }

            try { data.AI42 = Convert.ToDouble(dr["AI42"]); }
            catch { }

            try { data.AI43 = Convert.ToDouble(dr["AI43"]); }
            catch { }

            try { data.AI44 = Convert.ToDouble(dr["AI44"]); }
            catch { }

            try { data.AI45 = Convert.ToDouble(dr["AI45"]); }
            catch { }

            try { data.AI46 = Convert.ToDouble(dr["AI46"]); }
            catch { }

            try { data.AI47 = Convert.ToDouble(dr["AI47"]); }
            catch { }

            try { data.AI48 = Convert.ToDouble(dr["AI48"]); }
            catch { }

            try { data.AI49 = Convert.ToDouble(dr["AI49"]); }
            catch { }

            try { data.AI50 = Convert.ToDouble(dr["AI50"]); }
            catch { }

            try { data.AI51 = Convert.ToDouble(dr["AI51"]); }
            catch { }

            try { data.AI52 = Convert.ToDouble(dr["AI52"]); }
            catch { }

            try { data.AI53 = Convert.ToDouble(dr["AI53"]); }
            catch { }

            try { data.AI54 = Convert.ToDouble(dr["AI54"]); }
            catch { }

            try { data.AI55 = Convert.ToDouble(dr["AI55"]); }
            catch { }

            try { data.AI56 = Convert.ToDouble(dr["AI56"]); }
            catch { }

            try { data.AI57 = Convert.ToDouble(dr["AI57"]); }
            catch { }

            try { data.AI58 = Convert.ToDouble(dr["AI58"]); }
            catch { }

            try { data.AI59 = Convert.ToDouble(dr["AI59"]); }
            catch { }

            try { data.AI60 = Convert.ToDouble(dr["AI60"]); }
            catch { }

            try { data.AI61 = Convert.ToDouble(dr["AI61"]); }
            catch { }

            try { data.AI62 = Convert.ToDouble(dr["AI62"]); }
            catch { }

            try { data.AI63 = Convert.ToDouble(dr["AI63"]); }
            catch { }

            try { data.AI64 = Convert.ToDouble(dr["AI64"]); }
            catch { }

            return data;
        }
        public static ExDataData Construct(DataRow dr)
        {
            ExDataData data = new ExDataData();

            try { data.ExID = Convert.ToInt32(dr["ExID"]); }
            catch { }

            try { data.DataTime = Convert.ToDateTime(dr["DataTime"]); }
            catch { }

            try { data.AI01 = Convert.ToDouble(dr["AI01"]); }
            catch { }

            try { data.AI02 = Convert.ToDouble(dr["AI02"]); }
            catch { }

            try { data.AI03 = Convert.ToDouble(dr["AI03"]); }
            catch { }

            try { data.AI04 = Convert.ToDouble(dr["AI04"]); }
            catch { }

            try { data.AI05 = Convert.ToDouble(dr["AI05"]); }
            catch { }

            try { data.AI06 = Convert.ToDouble(dr["AI06"]); }
            catch { }

            try { data.AI07 = Convert.ToDouble(dr["AI07"]); }
            catch { }

            try { data.AI08 = Convert.ToDouble(dr["AI08"]); }
            catch { }

            try { data.AI09 = Convert.ToDouble(dr["AI09"]); }
            catch { }

            try { data.AI10 = Convert.ToDouble(dr["AI10"]); }
            catch { }

            try { data.AI11 = Convert.ToDouble(dr["AI11"]); }
            catch { }

            try { data.AI12 = Convert.ToDouble(dr["AI12"]); }
            catch { }

            try { data.AI13 = Convert.ToDouble(dr["AI13"]); }
            catch { }

            try { data.AI14 = Convert.ToDouble(dr["AI14"]); }
            catch { }

            try { data.AI15 = Convert.ToDouble(dr["AI15"]); }
            catch { }

            try { data.AI16 = Convert.ToDouble(dr["AI16"]); }
            catch { }

            try { data.AI17 = Convert.ToDouble(dr["AI17"]); }
            catch { }

            try { data.AI18 = Convert.ToDouble(dr["AI18"]); }
            catch { }

            try { data.AI19 = Convert.ToDouble(dr["AI19"]); }
            catch { }

            try { data.AI20 = Convert.ToDouble(dr["AI20"]); }
            catch { }

            try { data.AI21 = Convert.ToDouble(dr["AI21"]); }
            catch { }

            try { data.AI22 = Convert.ToDouble(dr["AI22"]); }
            catch { }

            try { data.AI23 = Convert.ToDouble(dr["AI23"]); }
            catch { }

            try { data.AI24 = Convert.ToDouble(dr["AI24"]); }
            catch { }

            try { data.AI25 = Convert.ToDouble(dr["AI25"]); }
            catch { }

            try { data.AI26 = Convert.ToDouble(dr["AI26"]); }
            catch { }

            try { data.AI27 = Convert.ToDouble(dr["AI27"]); }
            catch { }

            try { data.AI28 = Convert.ToDouble(dr["AI28"]); }
            catch { }

            try { data.AI29 = Convert.ToDouble(dr["AI29"]); }
            catch { }

            try { data.AI30 = Convert.ToDouble(dr["AI30"]); }
            catch { }

            try { data.AI31 = Convert.ToDouble(dr["AI31"]); }
            catch { }

            try { data.AI32 = Convert.ToDouble(dr["AI32"]); }
            catch { }

            try { data.AI33 = Convert.ToDouble(dr["AI33"]); }
            catch { }

            try { data.AI34 = Convert.ToDouble(dr["AI34"]); }
            catch { }

            try { data.AI35 = Convert.ToDouble(dr["AI35"]); }
            catch { }

            try { data.AI36 = Convert.ToDouble(dr["AI36"]); }
            catch { }

            try { data.AI37 = Convert.ToDouble(dr["AI37"]); }
            catch { }

            try { data.AI38 = Convert.ToDouble(dr["AI38"]); }
            catch { }

            try { data.AI39 = Convert.ToDouble(dr["AI39"]); }
            catch { }

            try { data.AI40 = Convert.ToDouble(dr["AI40"]); }
            catch { }

            try { data.AI41 = Convert.ToDouble(dr["AI41"]); }
            catch { }

            try { data.AI42 = Convert.ToDouble(dr["AI42"]); }
            catch { }

            try { data.AI43 = Convert.ToDouble(dr["AI43"]); }
            catch { }

            try { data.AI44 = Convert.ToDouble(dr["AI44"]); }
            catch { }

            try { data.AI45 = Convert.ToDouble(dr["AI45"]); }
            catch { }

            try { data.AI46 = Convert.ToDouble(dr["AI46"]); }
            catch { }

            try { data.AI47 = Convert.ToDouble(dr["AI47"]); }
            catch { }

            try { data.AI48 = Convert.ToDouble(dr["AI48"]); }
            catch { }

            try { data.AI49 = Convert.ToDouble(dr["AI49"]); }
            catch { }

            try { data.AI50 = Convert.ToDouble(dr["AI50"]); }
            catch { }

            try { data.AI51 = Convert.ToDouble(dr["AI51"]); }
            catch { }

            try { data.AI52 = Convert.ToDouble(dr["AI52"]); }
            catch { }

            try { data.AI53 = Convert.ToDouble(dr["AI53"]); }
            catch { }

            try { data.AI54 = Convert.ToDouble(dr["AI54"]); }
            catch { }

            try { data.AI55 = Convert.ToDouble(dr["AI55"]); }
            catch { }

            try { data.AI56 = Convert.ToDouble(dr["AI56"]); }
            catch { }

            try { data.AI57 = Convert.ToDouble(dr["AI57"]); }
            catch { }

            try { data.AI58 = Convert.ToDouble(dr["AI58"]); }
            catch { }

            try { data.AI59 = Convert.ToDouble(dr["AI59"]); }
            catch { }

            try { data.AI60 = Convert.ToDouble(dr["AI60"]); }
            catch { }

            try { data.AI61 = Convert.ToDouble(dr["AI61"]); }
            catch { }

            try { data.AI62 = Convert.ToDouble(dr["AI62"]); }
            catch { }

            try { data.AI63 = Convert.ToDouble(dr["AI63"]); }
            catch { }

            try { data.AI64 = Convert.ToDouble(dr["AI64"]); }
            catch { }

            return data;
        }
    }
    public class ExDataDataDBOption
    {
        public static int Insert(ExDataData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("insert into ExData (");
            sql.Append("ExID, ");
            sql.Append("DataTime, ");
            sql.Append("AI01, ");
            sql.Append("AI02, ");
            sql.Append("AI03, ");
            sql.Append("AI04, ");
            sql.Append("AI05, ");
            sql.Append("AI06, ");
            sql.Append("AI07, ");
            sql.Append("AI08, ");
            sql.Append("AI09, ");
            sql.Append("AI10, ");
            sql.Append("AI11, ");
            sql.Append("AI12, ");
            sql.Append("AI13, ");
            sql.Append("AI14, ");
            sql.Append("AI15, ");
            sql.Append("AI16, ");
            sql.Append("AI17, ");
            sql.Append("AI18, ");
            sql.Append("AI19, ");
            sql.Append("AI20, ");
            sql.Append("AI21, ");
            sql.Append("AI22, ");
            sql.Append("AI23, ");
            sql.Append("AI24, ");
            sql.Append("AI25, ");
            sql.Append("AI26, ");
            sql.Append("AI27, ");
            sql.Append("AI28, ");
            sql.Append("AI29, ");
            sql.Append("AI30, ");
            sql.Append("AI31, ");
            sql.Append("AI32, ");
            sql.Append("AI33, ");
            sql.Append("AI34, ");
            sql.Append("AI35, ");
            sql.Append("AI36, ");
            sql.Append("AI37, ");
            sql.Append("AI38, ");
            sql.Append("AI39, ");
            sql.Append("AI40, ");
            sql.Append("AI41, ");
            sql.Append("AI42, ");
            sql.Append("AI43, ");
            sql.Append("AI44, ");
            sql.Append("AI45, ");
            sql.Append("AI46, ");
            sql.Append("AI47, ");
            sql.Append("AI48, ");
            sql.Append("AI49, ");
            sql.Append("AI50, ");
            sql.Append("AI51, ");
            sql.Append("AI52, ");
            sql.Append("AI53, ");
            sql.Append("AI54, ");
            sql.Append("AI55, ");
            sql.Append("AI56, ");
            sql.Append("AI57, ");
            sql.Append("AI58, ");
            sql.Append("AI59, ");
            sql.Append("AI60, ");
            sql.Append("AI61, ");
            sql.Append("AI62, ");
            sql.Append("AI63, ");
            sql.Append("AI64");
            sql.Append(") values (");
            sql.Append("");
            sql.Append(d.ExID.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.DataTime.ToString("yyyy-MM-dd HH:mm:ss"));
            sql.Append("'");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI01.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI02.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI03.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI04.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI05.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI06.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI07.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI08.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI09.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI10.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI11.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI12.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI13.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI14.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI15.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI16.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI17.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI18.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI19.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI20.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI21.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI22.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI23.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI24.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI25.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI26.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI27.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI28.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI29.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI30.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI31.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI32.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI33.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI34.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI35.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI36.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI37.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI38.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI39.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI40.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI41.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI42.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI43.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI44.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI45.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI46.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI47.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI48.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI49.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI50.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI51.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI52.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI53.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI54.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI55.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI56.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI57.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI58.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI59.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI60.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI61.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI62.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI63.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.AI64.ToString());
            sql.Append("");
            sql.Append(")");
            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static DataTable DataTableSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExData ");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
        public static DataSet DataSetSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExData ");
            return WFNetLib.ADO.SQLServerOP.DataSetSQL(sql.ToString());
        }
        public static SqlDataReader ReaderSelect(ExDataData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExData ");
            return WFNetLib.ADO.SQLServerOP.ReaderExecuteSQL(sql.ToString());
        }
    }
}