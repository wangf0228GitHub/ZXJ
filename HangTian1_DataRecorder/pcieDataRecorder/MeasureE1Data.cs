using System;
using System.Data;
using System.Windows.Forms;
using System.Text;
using System.Data.SqlClient;

namespace pcieDataRecorder
{
    [Serializable]
    public class MeasureE1Data
    {

        public const string IDField = @"ID";

        public const string PRIMARYKEY_Field = @"ID";

        public const string SOURCEField = @"Source";

        public const string IDENTField = @"Ident";

        public const string TIMEField = @"Time";

        public const string RESERVEField = @"Reserve";

        public const string BREADField = @"bRead";

        public const string B8Field = @"B8";

        public const string B9Field = @"B9";

        public const string B10Field = @"B10";

        public const string B11Field = @"B11";

        public const string B12Field = @"B12";

        public const string B13Field = @"B13";

        public const string B14Field = @"B14";

        public const string B15Field = @"B15";

        public const string C0Field = @"C0";

        public const string C1Field = @"C1";

        public const string C2Field = @"C2";

        public const string C3Field = @"C3";

        public const string C4Field = @"C4";

        public const string C5Field = @"C5";

        public const string C6Field = @"C6";

        public const string C7Field = @"C7";

        public const string C8Field = @"C8";

        public const string C9Field = @"C9";

        public const string C10Field = @"C10";

        public const string C11Field = @"C11";

        public const string C12Field = @"C12";

        public const string C13Field = @"C13";

        private Int64 _ID;

        private Int32 _Source;

        private String _Ident;

        private DateTime _Time;

        private String _Reserve;

        private Boolean _bRead;

        private String _B8;

        private String _B9;

        private String _B10;

        private String _B11;

        private String _B12;

        private String _B13;

        private String _B14;

        private String _B15;

        private String _C0;

        private String _C1;

        private String _C2;

        private String _C3;

        private String _C4;

        private String _C5;

        private String _C6;

        private String _C7;

        private String _C8;

        private String _C9;

        private String _C10;

        private String _C11;

        private String _C12;

        private String _C13;

        public Int64 ID
        {
            get { return _ID; }
            set { _ID = value; }
        }
        public Int32 Source
        {
            get { return _Source; }
            set { _Source = value; }
        }
        public String Ident
        {
            get { return _Ident; }
            set { _Ident = value; }
        }
        public DateTime Time
        {
            get { return _Time; }
            set { _Time = value; }
        }
        public String Reserve
        {
            get { return _Reserve; }
            set { _Reserve = value; }
        }
        public Boolean bRead
        {
            get { return _bRead; }
            set { _bRead = value; }
        }
        public String B8
        {
            get { return _B8; }
            set { _B8 = value; }
        }
        public String B9
        {
            get { return _B9; }
            set { _B9 = value; }
        }
        public String B10
        {
            get { return _B10; }
            set { _B10 = value; }
        }
        public String B11
        {
            get { return _B11; }
            set { _B11 = value; }
        }
        public String B12
        {
            get { return _B12; }
            set { _B12 = value; }
        }
        public String B13
        {
            get { return _B13; }
            set { _B13 = value; }
        }
        public String B14
        {
            get { return _B14; }
            set { _B14 = value; }
        }
        public String B15
        {
            get { return _B15; }
            set { _B15 = value; }
        }
        public String C0
        {
            get { return _C0; }
            set { _C0 = value; }
        }
        public String C1
        {
            get { return _C1; }
            set { _C1 = value; }
        }
        public String C2
        {
            get { return _C2; }
            set { _C2 = value; }
        }
        public String C3
        {
            get { return _C3; }
            set { _C3 = value; }
        }
        public String C4
        {
            get { return _C4; }
            set { _C4 = value; }
        }
        public String C5
        {
            get { return _C5; }
            set { _C5 = value; }
        }
        public String C6
        {
            get { return _C6; }
            set { _C6 = value; }
        }
        public String C7
        {
            get { return _C7; }
            set { _C7 = value; }
        }
        public String C8
        {
            get { return _C8; }
            set { _C8 = value; }
        }
        public String C9
        {
            get { return _C9; }
            set { _C9 = value; }
        }
        public String C10
        {
            get { return _C10; }
            set { _C10 = value; }
        }
        public String C11
        {
            get { return _C11; }
            set { _C11 = value; }
        }
        public String C12
        {
            get { return _C12; }
            set { _C12 = value; }
        }
        public String C13
        {
            get { return _C13; }
            set { _C13 = value; }
        }
        public MeasureE1Data()
        {
            _ID = 0;
            _Source = 0;
            _Ident = "";
            _Time = DateTime.Now;
            _Reserve = "";
            _bRead = false;
            _B8 = "";
            _B9 = "";
            _B10 = "";
            _B11 = "";
            _B12 = "";
            _B13 = "";
            _B14 = "";
            _B15 = "";
            _C0 = "";
            _C1 = "";
            _C2 = "";
            _C3 = "";
            _C4 = "";
            _C5 = "";
            _C6 = "";
            _C7 = "";
            _C8 = "";
            _C9 = "";
            _C10 = "";
            _C11 = "";
            _C12 = "";
            _C13 = "";
        }
    }

    public class MeasureE1DataFactory
    {
        public static MeasureE1Data Construct(IDataReader reader)
        {
            MeasureE1Data data = new MeasureE1Data();

            try { data.ID = Convert.ToInt64(reader["ID"]); }
            catch { }

            try { data.Source = Convert.ToInt32(reader["Source"]); }
            catch { }

            try { data.Ident = Convert.ToString(reader["Ident"]); }
            catch { }

            try { data.Time = Convert.ToDateTime(reader["Time"]); }
            catch { }

            try { data.Reserve = Convert.ToString(reader["Reserve"]); }
            catch { }

            try { data.bRead = Convert.ToBoolean(reader["bRead"]); }
            catch { }

            try { data.B8 = Convert.ToString(reader["B8"]); }
            catch { }

            try { data.B9 = Convert.ToString(reader["B9"]); }
            catch { }

            try { data.B10 = Convert.ToString(reader["B10"]); }
            catch { }

            try { data.B11 = Convert.ToString(reader["B11"]); }
            catch { }

            try { data.B12 = Convert.ToString(reader["B12"]); }
            catch { }

            try { data.B13 = Convert.ToString(reader["B13"]); }
            catch { }

            try { data.B14 = Convert.ToString(reader["B14"]); }
            catch { }

            try { data.B15 = Convert.ToString(reader["B15"]); }
            catch { }

            try { data.C0 = Convert.ToString(reader["C0"]); }
            catch { }

            try { data.C1 = Convert.ToString(reader["C1"]); }
            catch { }

            try { data.C2 = Convert.ToString(reader["C2"]); }
            catch { }

            try { data.C3 = Convert.ToString(reader["C3"]); }
            catch { }

            try { data.C4 = Convert.ToString(reader["C4"]); }
            catch { }

            try { data.C5 = Convert.ToString(reader["C5"]); }
            catch { }

            try { data.C6 = Convert.ToString(reader["C6"]); }
            catch { }

            try { data.C7 = Convert.ToString(reader["C7"]); }
            catch { }

            try { data.C8 = Convert.ToString(reader["C8"]); }
            catch { }

            try { data.C9 = Convert.ToString(reader["C9"]); }
            catch { }

            try { data.C10 = Convert.ToString(reader["C10"]); }
            catch { }

            try { data.C11 = Convert.ToString(reader["C11"]); }
            catch { }

            try { data.C12 = Convert.ToString(reader["C12"]); }
            catch { }

            try { data.C13 = Convert.ToString(reader["C13"]); }
            catch { }

            return data;
        }
        public static Int64 GetPrimaryKey(DataTable dt)
        {
            return GetPrimaryKey(dt, 0);
        }
        public static Int64 GetPrimaryKey(DataTable dt, int rowIndex)
        {
            Int64 PrimaryKey = 0;

            if (dt.Rows.Count < rowIndex + 1)

                return 0;

            DataRow dr = dt.Rows[rowIndex];

            if (dr == null)

                return 0;

            try { PrimaryKey = Convert.ToInt64(dr[MeasureE1Data.PRIMARYKEY_Field]); }
            catch { }

            return PrimaryKey;
        }
        public static MeasureE1Data Construct(DataTable dt)
        {
            return Construct(dt, 0);
        }
        public static MeasureE1Data Construct(DataTable dt, int rowIndex)
        {
            MeasureE1Data data = new MeasureE1Data();

            if (dt.Rows.Count < rowIndex + 1)

                return null;

            DataRow dr = dt.Rows[rowIndex];

            if (dr == null)

                return null;

            try { data.ID = Convert.ToInt64(dr["ID"]); }
            catch { }

            try { data.Source = Convert.ToInt32(dr["Source"]); }
            catch { }

            try { data.Ident = Convert.ToString(dr["Ident"]); }
            catch { }

            try { data.Time = Convert.ToDateTime(dr["Time"]); }
            catch { }

            try { data.Reserve = Convert.ToString(dr["Reserve"]); }
            catch { }

            try { data.bRead = Convert.ToBoolean(dr["bRead"]); }
            catch { }

            try { data.B8 = Convert.ToString(dr["B8"]); }
            catch { }

            try { data.B9 = Convert.ToString(dr["B9"]); }
            catch { }

            try { data.B10 = Convert.ToString(dr["B10"]); }
            catch { }

            try { data.B11 = Convert.ToString(dr["B11"]); }
            catch { }

            try { data.B12 = Convert.ToString(dr["B12"]); }
            catch { }

            try { data.B13 = Convert.ToString(dr["B13"]); }
            catch { }

            try { data.B14 = Convert.ToString(dr["B14"]); }
            catch { }

            try { data.B15 = Convert.ToString(dr["B15"]); }
            catch { }

            try { data.C0 = Convert.ToString(dr["C0"]); }
            catch { }

            try { data.C1 = Convert.ToString(dr["C1"]); }
            catch { }

            try { data.C2 = Convert.ToString(dr["C2"]); }
            catch { }

            try { data.C3 = Convert.ToString(dr["C3"]); }
            catch { }

            try { data.C4 = Convert.ToString(dr["C4"]); }
            catch { }

            try { data.C5 = Convert.ToString(dr["C5"]); }
            catch { }

            try { data.C6 = Convert.ToString(dr["C6"]); }
            catch { }

            try { data.C7 = Convert.ToString(dr["C7"]); }
            catch { }

            try { data.C8 = Convert.ToString(dr["C8"]); }
            catch { }

            try { data.C9 = Convert.ToString(dr["C9"]); }
            catch { }

            try { data.C10 = Convert.ToString(dr["C10"]); }
            catch { }

            try { data.C11 = Convert.ToString(dr["C11"]); }
            catch { }

            try { data.C12 = Convert.ToString(dr["C12"]); }
            catch { }

            try { data.C13 = Convert.ToString(dr["C13"]); }
            catch { }

            return data;
        }
        public static MeasureE1Data Construct(DataGridView dgv, int rowIndex)
        {
            MeasureE1Data data = new MeasureE1Data();

            if (dgv.Rows.Count < rowIndex + 1)

                return null;

            DataGridViewCellCollection dr = dgv.Rows[rowIndex].Cells;

            if (dr == null)

                return null;

            try { data.ID = Convert.ToInt64(dr["ID"]); }
            catch { }

            try { data.Source = Convert.ToInt32(dr["Source"]); }
            catch { }

            try { data.Ident = Convert.ToString(dr["Ident"]); }
            catch { }

            try { data.Time = Convert.ToDateTime(dr["Time"]); }
            catch { }

            try { data.Reserve = Convert.ToString(dr["Reserve"]); }
            catch { }

            try { data.bRead = Convert.ToBoolean(dr["bRead"]); }
            catch { }

            try { data.B8 = Convert.ToString(dr["B8"]); }
            catch { }

            try { data.B9 = Convert.ToString(dr["B9"]); }
            catch { }

            try { data.B10 = Convert.ToString(dr["B10"]); }
            catch { }

            try { data.B11 = Convert.ToString(dr["B11"]); }
            catch { }

            try { data.B12 = Convert.ToString(dr["B12"]); }
            catch { }

            try { data.B13 = Convert.ToString(dr["B13"]); }
            catch { }

            try { data.B14 = Convert.ToString(dr["B14"]); }
            catch { }

            try { data.B15 = Convert.ToString(dr["B15"]); }
            catch { }

            try { data.C0 = Convert.ToString(dr["C0"]); }
            catch { }

            try { data.C1 = Convert.ToString(dr["C1"]); }
            catch { }

            try { data.C2 = Convert.ToString(dr["C2"]); }
            catch { }

            try { data.C3 = Convert.ToString(dr["C3"]); }
            catch { }

            try { data.C4 = Convert.ToString(dr["C4"]); }
            catch { }

            try { data.C5 = Convert.ToString(dr["C5"]); }
            catch { }

            try { data.C6 = Convert.ToString(dr["C6"]); }
            catch { }

            try { data.C7 = Convert.ToString(dr["C7"]); }
            catch { }

            try { data.C8 = Convert.ToString(dr["C8"]); }
            catch { }

            try { data.C9 = Convert.ToString(dr["C9"]); }
            catch { }

            try { data.C10 = Convert.ToString(dr["C10"]); }
            catch { }

            try { data.C11 = Convert.ToString(dr["C11"]); }
            catch { }

            try { data.C12 = Convert.ToString(dr["C12"]); }
            catch { }

            try { data.C13 = Convert.ToString(dr["C13"]); }
            catch { }

            return data;
        }
        public static Int64 GetPrimaryKey(DataGridView dgv, int rowIndex)
        {
            Int64 PrimaryKey = 0;

            if (dgv.Rows.Count < rowIndex + 1)

                return 0;

            DataGridViewCellCollection dr = dgv.Rows[rowIndex].Cells;

            if (dr == null)

                return 0;

            for (int i = 0; i < dgv.Columns.Count; i++)
            {
                if (dgv.Columns[i].DataPropertyName == MeasureE1Data.PRIMARYKEY_Field)
                {
                    try { PrimaryKey = Convert.ToInt64(dr[i].Value); }
                    catch { }
                    return PrimaryKey;
                }
            }
            return PrimaryKey;
        }
        public static MeasureE1Data Construct(DataRow dr)
        {
            MeasureE1Data data = new MeasureE1Data();

            try { data.ID = Convert.ToInt64(dr["ID"]); }
            catch { }

            try { data.Source = Convert.ToInt32(dr["Source"]); }
            catch { }

            try { data.Ident = Convert.ToString(dr["Ident"]); }
            catch { }

            try { data.Time = Convert.ToDateTime(dr["Time"]); }
            catch { }

            try { data.Reserve = Convert.ToString(dr["Reserve"]); }
            catch { }

            try { data.bRead = Convert.ToBoolean(dr["bRead"]); }
            catch { }

            try { data.B8 = Convert.ToString(dr["B8"]); }
            catch { }

            try { data.B9 = Convert.ToString(dr["B9"]); }
            catch { }

            try { data.B10 = Convert.ToString(dr["B10"]); }
            catch { }

            try { data.B11 = Convert.ToString(dr["B11"]); }
            catch { }

            try { data.B12 = Convert.ToString(dr["B12"]); }
            catch { }

            try { data.B13 = Convert.ToString(dr["B13"]); }
            catch { }

            try { data.B14 = Convert.ToString(dr["B14"]); }
            catch { }

            try { data.B15 = Convert.ToString(dr["B15"]); }
            catch { }

            try { data.C0 = Convert.ToString(dr["C0"]); }
            catch { }

            try { data.C1 = Convert.ToString(dr["C1"]); }
            catch { }

            try { data.C2 = Convert.ToString(dr["C2"]); }
            catch { }

            try { data.C3 = Convert.ToString(dr["C3"]); }
            catch { }

            try { data.C4 = Convert.ToString(dr["C4"]); }
            catch { }

            try { data.C5 = Convert.ToString(dr["C5"]); }
            catch { }

            try { data.C6 = Convert.ToString(dr["C6"]); }
            catch { }

            try { data.C7 = Convert.ToString(dr["C7"]); }
            catch { }

            try { data.C8 = Convert.ToString(dr["C8"]); }
            catch { }

            try { data.C9 = Convert.ToString(dr["C9"]); }
            catch { }

            try { data.C10 = Convert.ToString(dr["C10"]); }
            catch { }

            try { data.C11 = Convert.ToString(dr["C11"]); }
            catch { }

            try { data.C12 = Convert.ToString(dr["C12"]); }
            catch { }

            try { data.C13 = Convert.ToString(dr["C13"]); }
            catch { }

            return data;
        }
        public static Int64 GetPrimaryKey(DataRow dr)
        {
            Int64 PrimaryKey = 0;

            try { PrimaryKey = Convert.ToInt64(dr[MeasureE1Data.PRIMARYKEY_Field]); }
            catch { }
            return PrimaryKey;
        }

    }
    public class MeasureE1DataDBOption
    {
        public static int Insert(MeasureE1Data d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("insert into MeasureE1 (");
            sql.Append("Source, ");
            sql.Append("Ident, ");
            sql.Append("Time, ");
            sql.Append("Reserve, ");
            sql.Append("bRead, ");
            sql.Append("B8, ");
            sql.Append("B9, ");
            sql.Append("B10, ");
            sql.Append("B11, ");
            sql.Append("B12, ");
            sql.Append("B13, ");
            sql.Append("B14, ");
            sql.Append("B15, ");
            sql.Append("C0, ");
            sql.Append("C1, ");
            sql.Append("C2, ");
            sql.Append("C3, ");
            sql.Append("C4, ");
            sql.Append("C5, ");
            sql.Append("C6, ");
            sql.Append("C7, ");
            sql.Append("C8, ");
            sql.Append("C9, ");
            sql.Append("C10, ");
            sql.Append("C11, ");
            sql.Append("C12, ");
            sql.Append("C13");
            sql.Append(") values (");
            sql.Append("");
            sql.Append(d.Source.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.Ident.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.Time.ToString("yyyy-MM-dd HH:mm:ss"));
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.Reserve.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("");
            if (d.bRead)
                sql.Append("1");
            else
                sql.Append("0");
            sql.Append("");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B8.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B9.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B10.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B11.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B12.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B13.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B14.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.B15.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C0.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C1.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C2.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C3.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C4.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C5.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C6.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C7.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C8.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C9.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C10.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C11.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C12.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.C13.ToString());
            sql.Append("'");
            sql.Append(")");
            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static int Update(MeasureE1Data d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("update MeasureE1 set ");
            sql.Append("Source=");
            sql.Append("");
            sql.Append(d.Source.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("Ident=");
            sql.Append("'");
            sql.Append(d.Ident.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("Time=");
            sql.Append("'");
            sql.Append(d.Time.ToString("yyyy-MM-dd HH:mm:ss"));
            sql.Append("'");
            sql.Append(", ");
            sql.Append("Reserve=");
            sql.Append("'");
            sql.Append(d.Reserve.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("bRead=");
            sql.Append("");
            if (d.bRead)
                sql.Append("1");
            else
                sql.Append("0");
            sql.Append("");
            sql.Append(", ");
            sql.Append("B8=");
            sql.Append("'");
            sql.Append(d.B8.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("B9=");
            sql.Append("'");
            sql.Append(d.B9.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("B10=");
            sql.Append("'");
            sql.Append(d.B10.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("B11=");
            sql.Append("'");
            sql.Append(d.B11.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("B12=");
            sql.Append("'");
            sql.Append(d.B12.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("B13=");
            sql.Append("'");
            sql.Append(d.B13.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("B14=");
            sql.Append("'");
            sql.Append(d.B14.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("B15=");
            sql.Append("'");
            sql.Append(d.B15.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C0=");
            sql.Append("'");
            sql.Append(d.C0.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C1=");
            sql.Append("'");
            sql.Append(d.C1.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C2=");
            sql.Append("'");
            sql.Append(d.C2.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C3=");
            sql.Append("'");
            sql.Append(d.C3.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C4=");
            sql.Append("'");
            sql.Append(d.C4.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C5=");
            sql.Append("'");
            sql.Append(d.C5.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C6=");
            sql.Append("'");
            sql.Append(d.C6.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C7=");
            sql.Append("'");
            sql.Append(d.C7.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C8=");
            sql.Append("'");
            sql.Append(d.C8.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C9=");
            sql.Append("'");
            sql.Append(d.C9.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C10=");
            sql.Append("'");
            sql.Append(d.C10.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C11=");
            sql.Append("'");
            sql.Append(d.C11.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C12=");
            sql.Append("'");
            sql.Append(d.C12.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("C13=");
            sql.Append("'");
            sql.Append(d.C13.ToString());
            sql.Append("'");
            sql.Append(" where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString()); sql.Append("");

            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static int Delete(MeasureE1Data d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("delete from MeasureE1 ");
            sql.Append(" where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString());
            sql.Append("");
            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static DataTable DataTableSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from MeasureE1 ");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
        public static DataTable DataTableSelect(MeasureE1Data d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from MeasureE1 where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString());
            sql.Append("");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
        public static MeasureE1Data Get(Int64 _id)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from MeasureE1 where ID=");
            sql.Append("");
            sql.Append(_id.ToString());
            sql.Append("");
            DataTable dt = WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
            if (dt.Rows.Count == 0)
                return null;
            else
                return MeasureE1DataFactory.Construct(dt.Rows[0]);
        }
        public static DataSet DataSetSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from MeasureE1 ");
            return WFNetLib.ADO.SQLServerOP.DataSetSQL(sql.ToString());
        }
        public static SqlDataReader ReaderSelect(MeasureE1Data d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from MeasureE1 ");
            return WFNetLib.ADO.SQLServerOP.ReaderExecuteSQL(sql.ToString());
        }
    }
}