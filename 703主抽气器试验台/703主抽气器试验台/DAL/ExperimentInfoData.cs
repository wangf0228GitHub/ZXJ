using System;
using System.Data;
using System.Windows.Forms;
using System.Text;
using System.Data.SqlClient;

namespace DAL
{
    [Serializable]
    public class ExInfoData
    {

        public const string IDField = @"ID";

        public const string PRIMARYKEY_Field = @"ID";

        public const string TITLEField = @"Title";

        public const string SAMPLERETEField = @"SampleRete";

        public const string SAMPLES2READField = @"Samples2Read";

        public const string SAVENSField = @"SaveNS";

        public const string ETIMEField = @"ETime";

        public const string WORKERField = @"Worker";

        public const string NI9188MODField = @"NI9188Mod";

        private Int32 _ID;

        private String _Title;

        private Int32 _SampleRete;

        private Int32 _Samples2Read;

        private Int32 _SaveNS;

        private DateTime _ETime;

        private String _Worker;

        private String _NI9188Mod;

        public Int32 ID
        {
            get { return _ID; }
            set { _ID = value; }
        }
        public String Title
        {
            get { return _Title; }
            set { _Title = value; }
        }
        public Int32 SampleRete
        {
            get { return _SampleRete; }
            set { _SampleRete = value; }
        }
        public Int32 Samples2Read
        {
            get { return _Samples2Read; }
            set { _Samples2Read = value; }
        }
        public Int32 SaveNS
        {
            get { return _SaveNS; }
            set { _SaveNS = value; }
        }
        public DateTime ETime
        {
            get { return _ETime; }
            set { _ETime = value; }
        }
        public String Worker
        {
            get { return _Worker; }
            set { _Worker = value; }
        }
        public String NI9188Mod
        {
            get { return _NI9188Mod; }
            set { _NI9188Mod = value; }
        }
        public ExInfoData()
        {
            _ID = 0;
            _Title = "";
            _SampleRete = 0;
            _Samples2Read = 0;
            _SaveNS = 0;
            _ETime = DateTime.Now;
            _Worker = "";
            _NI9188Mod = "";
        }
    }

    public class ExInfoDataFactory
    {
        public static ExInfoData Construct(IDataReader reader)
        {
            ExInfoData data = new ExInfoData();

            try { data.ID = Convert.ToInt32(reader["ID"]); }
            catch { }

            try { data.Title = Convert.ToString(reader["Title"]); }
            catch { }

            try { data.SampleRete = Convert.ToInt32(reader["SampleRete"]); }
            catch { }

            try { data.Samples2Read = Convert.ToInt32(reader["Samples2Read"]); }
            catch { }

            try { data.SaveNS = Convert.ToInt32(reader["SaveNS"]); }
            catch { }

            try { data.ETime = Convert.ToDateTime(reader["ETime"]); }
            catch { }

            try { data.Worker = Convert.ToString(reader["Worker"]); }
            catch { }

            try { data.NI9188Mod = Convert.ToString(reader["NI9188Mod"]); }
            catch { }

            return data;
        }
        public static Int32 GetPrimaryKey(DataTable dt)
        {
            return GetPrimaryKey(dt, 0);
        }
        public static Int32 GetPrimaryKey(DataTable dt, int rowIndex)
        {
            Int32 PrimaryKey = 0;

            if (dt.Rows.Count < rowIndex + 1)

                return 0;

            DataRow dr = dt.Rows[rowIndex];

            if (dr == null)

                return 0;

            try { PrimaryKey = Convert.ToInt32(dr[ExInfoData.PRIMARYKEY_Field]); }
            catch { }

            return PrimaryKey;
        }
        public static ExInfoData Construct(DataTable dt)
        {
            return Construct(dt, 0);
        }
        public static ExInfoData Construct(DataTable dt, int rowIndex)
        {
            ExInfoData data = new ExInfoData();

            if (dt.Rows.Count < rowIndex + 1)

                return null;

            DataRow dr = dt.Rows[rowIndex];

            if (dr == null)

                return null;

            try { data.ID = Convert.ToInt32(dr["ID"]); }
            catch { }

            try { data.Title = Convert.ToString(dr["Title"]); }
            catch { }

            try { data.SampleRete = Convert.ToInt32(dr["SampleRete"]); }
            catch { }

            try { data.Samples2Read = Convert.ToInt32(dr["Samples2Read"]); }
            catch { }

            try { data.SaveNS = Convert.ToInt32(dr["SaveNS"]); }
            catch { }

            try { data.ETime = Convert.ToDateTime(dr["ETime"]); }
            catch { }

            try { data.Worker = Convert.ToString(dr["Worker"]); }
            catch { }

            try { data.NI9188Mod = Convert.ToString(dr["NI9188Mod"]); }
            catch { }

            return data;
        }
        public static ExInfoData Construct(DataGridView dgv, int rowIndex)
        {
            ExInfoData data = new ExInfoData();

            if (dgv.Rows.Count < rowIndex + 1)

                return null;

            DataGridViewCellCollection dr = dgv.Rows[rowIndex].Cells;

            if (dr == null)

                return null;

            try { data.ID = Convert.ToInt32(dr["ID"]); }
            catch { }

            try { data.Title = Convert.ToString(dr["Title"]); }
            catch { }

            try { data.SampleRete = Convert.ToInt32(dr["SampleRete"]); }
            catch { }

            try { data.Samples2Read = Convert.ToInt32(dr["Samples2Read"]); }
            catch { }

            try { data.SaveNS = Convert.ToInt32(dr["SaveNS"]); }
            catch { }

            try { data.ETime = Convert.ToDateTime(dr["ETime"]); }
            catch { }

            try { data.Worker = Convert.ToString(dr["Worker"]); }
            catch { }

            try { data.NI9188Mod = Convert.ToString(dr["NI9188Mod"]); }
            catch { }

            return data;
        }
        public static Int32 GetPrimaryKey(DataGridView dgv, int rowIndex)
        {
            Int32 PrimaryKey = 0;

            if (dgv.Rows.Count < rowIndex + 1)

                return 0;

            DataGridViewCellCollection dr = dgv.Rows[rowIndex].Cells;

            if (dr == null)

                return 0;

            for (int i = 0; i < dgv.Columns.Count; i++)
            {
                if (dgv.Columns[i].DataPropertyName == ExInfoData.PRIMARYKEY_Field)
                {
                    try { PrimaryKey = Convert.ToInt32(dr[i].Value); }
                    catch { }
                    return PrimaryKey;
                }
            }
            return PrimaryKey;
        }
        public static ExInfoData Construct(DataRow dr)
        {
            ExInfoData data = new ExInfoData();

            try { data.ID = Convert.ToInt32(dr["ID"]); }
            catch { }

            try { data.Title = Convert.ToString(dr["Title"]); }
            catch { }

            try { data.SampleRete = Convert.ToInt32(dr["SampleRete"]); }
            catch { }

            try { data.Samples2Read = Convert.ToInt32(dr["Samples2Read"]); }
            catch { }

            try { data.SaveNS = Convert.ToInt32(dr["SaveNS"]); }
            catch { }

            try { data.ETime = Convert.ToDateTime(dr["ETime"]); }
            catch { }

            try { data.Worker = Convert.ToString(dr["Worker"]); }
            catch { }

            try { data.NI9188Mod = Convert.ToString(dr["NI9188Mod"]); }
            catch { }

            return data;
        }
        public static Int32 GetPrimaryKey(DataRow dr)
        {
            Int32 PrimaryKey = 0;

            try { PrimaryKey = Convert.ToInt32(dr[ExInfoData.PRIMARYKEY_Field]); }
            catch { }
            return PrimaryKey;
        }

    }
    public class ExInfoDataDBOption
    {
        public static int Insert(ExInfoData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("insert into ExInfo (");
            sql.Append("Title, ");
            sql.Append("SampleRete, ");
            sql.Append("Samples2Read, ");
            sql.Append("SaveNS, ");
            sql.Append("ETime, ");
            sql.Append("Worker, ");
            sql.Append("NI9188Mod");
            sql.Append(") values (");
            sql.Append("'");
            sql.Append(d.Title.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.SampleRete.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.Samples2Read.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.SaveNS.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.ETime.ToString("yyyy-MM-dd HH:mm:ss"));
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.Worker.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.NI9188Mod.ToString());
            sql.Append("'");
            sql.Append(")");
            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static int Update(ExInfoData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("update ExInfo set ");
            sql.Append("Title=");
            sql.Append("'");
            sql.Append(d.Title.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("SampleRete=");
            sql.Append("");
            sql.Append(d.SampleRete.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("Samples2Read=");
            sql.Append("");
            sql.Append(d.Samples2Read.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("SaveNS=");
            sql.Append("");
            sql.Append(d.SaveNS.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("ETime=");
            sql.Append("'");
            sql.Append(d.ETime.ToString("yyyy-MM-dd HH:mm:ss"));
            sql.Append("'");
            sql.Append(", ");
            sql.Append("Worker=");
            sql.Append("'");
            sql.Append(d.Worker.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("NI9188Mod=");
            sql.Append("'");
            sql.Append(d.NI9188Mod.ToString());
            sql.Append("'");
            sql.Append(" where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString()); sql.Append("");

            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static int Delete(ExInfoData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("delete from ExInfo ");
            sql.Append(" where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString());
            sql.Append("");
            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static DataTable DataTableSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExInfo ");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
        public static DataTable DataTableSelect(ExInfoData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExInfo where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString());
            sql.Append("");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
        public static ExInfoData Get(Int32 _id)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExInfo where ID=");
            sql.Append("");
            sql.Append(_id.ToString());
            sql.Append("");
            DataTable dt = WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
            if (dt.Rows.Count == 0)
                return null;
            else
                return ExInfoDataFactory.Construct(dt.Rows[0]);
        }
        public static DataSet DataSetSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExInfo ");
            return WFNetLib.ADO.SQLServerOP.DataSetSQL(sql.ToString());
        }
        public static SqlDataReader ReaderSelect(ExInfoData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from ExInfo ");
            return WFNetLib.ADO.SQLServerOP.ReaderExecuteSQL(sql.ToString());
        }
    }
}