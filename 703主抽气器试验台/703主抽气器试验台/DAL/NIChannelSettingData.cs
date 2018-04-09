using System;
using System.Data;
using System.Windows.Forms;
using System.Text;
using System.Data.SqlClient;

namespace DAL
{
    [Serializable]
    public class NIChannelSettingData
    {

        public const string IDField = @"ID";

        public const string PRIMARYKEY_Field = @"ID";

        public const string 物理通道Field = @"物理通道";

        public const string 名称Field = @"名称";

        public const string 工位号Field = @"工位号";

        public const string 规格型号Field = @"规格型号";

        public const string 安装位置Field = @"安装位置";

        public const string 厂家及项目来源Field = @"厂家及项目来源";

        public const string 备注1Field = @"备注1";

        public const string 备注2Field = @"备注2";

        public const string 备注3Field = @"备注3";

        public const string 是否远传Field = @"是否远传";

        public const string 通道配置项Field = @"通道配置项";

        public const string 最小值Field = @"最小值";

        public const string 最大值Field = @"最大值";

        public const string I_4MAField = @"I_4mA";

        public const string I_20MAField = @"I_20mA";

        public const string 物理量单位Field = @"物理量单位";

        public const string CALC_KField = @"Calc_k";

        public const string CALC_BField = @"Calc_b";

        private Int32 _ID;

        private String _物理通道;

        private String _名称;

        private String _工位号;

        private String _规格型号;

        private String _安装位置;

        private String _厂家及项目来源;

        private String _备注1;

        private String _备注2;

        private String _备注3;

        private Boolean _是否远传;

        private Int32 _通道配置项;

        private Double _最小值;

        private Double _最大值;

        private Double _I_4mA;

        private Double _I_20mA;

        private String _物理量单位;

        private Double _Calc_k;

        private Double _Calc_b;

        public Int32 ID
        {
            get { return _ID; }
            set { _ID = value; }
        }
        public String 物理通道
        {
            get { return _物理通道; }
            set { _物理通道 = value; }
        }
        public String 名称
        {
            get { return _名称; }
            set { _名称 = value; }
        }
        public String 工位号
        {
            get { return _工位号; }
            set { _工位号 = value; }
        }
        public String 规格型号
        {
            get { return _规格型号; }
            set { _规格型号 = value; }
        }
        public String 安装位置
        {
            get { return _安装位置; }
            set { _安装位置 = value; }
        }
        public String 厂家及项目来源
        {
            get { return _厂家及项目来源; }
            set { _厂家及项目来源 = value; }
        }
        public String 备注1
        {
            get { return _备注1; }
            set { _备注1 = value; }
        }
        public String 备注2
        {
            get { return _备注2; }
            set { _备注2 = value; }
        }
        public String 备注3
        {
            get { return _备注3; }
            set { _备注3 = value; }
        }
        public Boolean 是否远传
        {
            get { return _是否远传; }
            set { _是否远传 = value; }
        }
        public Int32 通道配置项
        {
            get { return _通道配置项; }
            set { _通道配置项 = value; }
        }
        public Double 最小值
        {
            get { return _最小值; }
            set { _最小值 = value; }
        }
        public Double 最大值
        {
            get { return _最大值; }
            set { _最大值 = value; }
        }
        public Double I_4mA
        {
            get { return _I_4mA; }
            set { _I_4mA = value; }
        }
        public Double I_20mA
        {
            get { return _I_20mA; }
            set { _I_20mA = value; }
        }
        public String 物理量单位
        {
            get { return _物理量单位; }
            set { _物理量单位 = value; }
        }
        public Double Calc_k
        {
            get { return _Calc_k; }
            set { _Calc_k = value; }
        }
        public Double Calc_b
        {
            get { return _Calc_b; }
            set { _Calc_b = value; }
        }
        public NIChannelSettingData()
        {
            _ID = 0;
            _物理通道 = "";
            _名称 = "";
            _工位号 = "";
            _规格型号 = "";
            _安装位置 = "";
            _厂家及项目来源 = "";
            _备注1 = "";
            _备注2 = "";
            _备注3 = "";
            _是否远传 = false;
            _通道配置项 = -1;
            _最小值 = 0;
            _最大值 = 0;
            _I_4mA = 0;
            _I_20mA = 0;
            _物理量单位 = "";
            _Calc_k = 0;
            _Calc_b = 0;
        }
    }

    public class NIChannelSettingDataFactory
    {
        public static NIChannelSettingData Construct(IDataReader reader)
        {
            NIChannelSettingData data = new NIChannelSettingData();

            try { data.ID = Convert.ToInt32(reader["ID"]); }
            catch { }

            try { data.物理通道 = Convert.ToString(reader["物理通道"]); }
            catch { }

            try { data.名称 = Convert.ToString(reader["名称"]); }
            catch { }

            try { data.工位号 = Convert.ToString(reader["工位号"]); }
            catch { }

            try { data.规格型号 = Convert.ToString(reader["规格型号"]); }
            catch { }

            try { data.安装位置 = Convert.ToString(reader["安装位置"]); }
            catch { }

            try { data.厂家及项目来源 = Convert.ToString(reader["厂家及项目来源"]); }
            catch { }

            try { data.备注1 = Convert.ToString(reader["备注1"]); }
            catch { }

            try { data.备注2 = Convert.ToString(reader["备注2"]); }
            catch { }

            try { data.备注3 = Convert.ToString(reader["备注3"]); }
            catch { }

            try { data.是否远传 = Convert.ToBoolean(reader["是否远传"]); }
            catch { }

            try { data.通道配置项 = Convert.ToInt32(reader["通道配置项"]); }
            catch { }

            try { data.最小值 = Convert.ToDouble(reader["最小值"]); }
            catch { }

            try { data.最大值 = Convert.ToDouble(reader["最大值"]); }
            catch { }

            try { data.I_4mA = Convert.ToDouble(reader["I_4mA"]); }
            catch { }

            try { data.I_20mA = Convert.ToDouble(reader["I_20mA"]); }
            catch { }

            try { data.物理量单位 = Convert.ToString(reader["物理量单位"]); }
            catch { }

            try { data.Calc_k = Convert.ToDouble(reader["Calc_k"]); }
            catch { }

            try { data.Calc_b = Convert.ToDouble(reader["Calc_b"]); }
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

            try { PrimaryKey = Convert.ToInt32(dr[NIChannelSettingData.PRIMARYKEY_Field]); }
            catch { }

            return PrimaryKey;
        }
        public static NIChannelSettingData Construct(DataTable dt)
        {
            return Construct(dt, 0);
        }
        public static NIChannelSettingData Construct(DataTable dt, int rowIndex)
        {
            NIChannelSettingData data = new NIChannelSettingData();

            if (dt.Rows.Count < rowIndex + 1)

                return null;

            DataRow dr = dt.Rows[rowIndex];

            if (dr == null)

                return null;

            try { data.ID = Convert.ToInt32(dr["ID"]); }
            catch { }

            try { data.物理通道 = Convert.ToString(dr["物理通道"]); }
            catch { }

            try { data.名称 = Convert.ToString(dr["名称"]); }
            catch { }

            try { data.工位号 = Convert.ToString(dr["工位号"]); }
            catch { }

            try { data.规格型号 = Convert.ToString(dr["规格型号"]); }
            catch { }

            try { data.安装位置 = Convert.ToString(dr["安装位置"]); }
            catch { }

            try { data.厂家及项目来源 = Convert.ToString(dr["厂家及项目来源"]); }
            catch { }

            try { data.备注1 = Convert.ToString(dr["备注1"]); }
            catch { }

            try { data.备注2 = Convert.ToString(dr["备注2"]); }
            catch { }

            try { data.备注3 = Convert.ToString(dr["备注3"]); }
            catch { }

            try { data.是否远传 = Convert.ToBoolean(dr["是否远传"]); }
            catch { }

            try { data.通道配置项 = Convert.ToInt32(dr["通道配置项"]); }
            catch { }

            try { data.最小值 = Convert.ToDouble(dr["最小值"]); }
            catch { }

            try { data.最大值 = Convert.ToDouble(dr["最大值"]); }
            catch { }

            try { data.I_4mA = Convert.ToDouble(dr["I_4mA"]); }
            catch { }

            try { data.I_20mA = Convert.ToDouble(dr["I_20mA"]); }
            catch { }

            try { data.物理量单位 = Convert.ToString(dr["物理量单位"]); }
            catch { }

            try { data.Calc_k = Convert.ToDouble(dr["Calc_k"]); }
            catch { }

            try { data.Calc_b = Convert.ToDouble(dr["Calc_b"]); }
            catch { }

            return data;
        }
        public static NIChannelSettingData Construct(DataGridView dgv, int rowIndex)
        {
            NIChannelSettingData data = new NIChannelSettingData();

            if (dgv.Rows.Count < rowIndex + 1)

                return null;

            DataGridViewCellCollection dr = dgv.Rows[rowIndex].Cells;

            if (dr == null)

                return null;

            try { data.ID = Convert.ToInt32(dr["ID"]); }
            catch { }

            try { data.物理通道 = Convert.ToString(dr["物理通道"]); }
            catch { }

            try { data.名称 = Convert.ToString(dr["名称"]); }
            catch { }

            try { data.工位号 = Convert.ToString(dr["工位号"]); }
            catch { }

            try { data.规格型号 = Convert.ToString(dr["规格型号"]); }
            catch { }

            try { data.安装位置 = Convert.ToString(dr["安装位置"]); }
            catch { }

            try { data.厂家及项目来源 = Convert.ToString(dr["厂家及项目来源"]); }
            catch { }

            try { data.备注1 = Convert.ToString(dr["备注1"]); }
            catch { }

            try { data.备注2 = Convert.ToString(dr["备注2"]); }
            catch { }

            try { data.备注3 = Convert.ToString(dr["备注3"]); }
            catch { }

            try { data.是否远传 = Convert.ToBoolean(dr["是否远传"]); }
            catch { }

            try { data.通道配置项 = Convert.ToInt32(dr["通道配置项"]); }
            catch { }

            try { data.最小值 = Convert.ToDouble(dr["最小值"]); }
            catch { }

            try { data.最大值 = Convert.ToDouble(dr["最大值"]); }
            catch { }

            try { data.I_4mA = Convert.ToDouble(dr["I_4mA"]); }
            catch { }

            try { data.I_20mA = Convert.ToDouble(dr["I_20mA"]); }
            catch { }

            try { data.物理量单位 = Convert.ToString(dr["物理量单位"]); }
            catch { }

            try { data.Calc_k = Convert.ToDouble(dr["Calc_k"]); }
            catch { }

            try { data.Calc_b = Convert.ToDouble(dr["Calc_b"]); }
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
                if (dgv.Columns[i].DataPropertyName == NIChannelSettingData.PRIMARYKEY_Field)
                {
                    try { PrimaryKey = Convert.ToInt32(dr[i].Value); }
                    catch { }
                    return PrimaryKey;
                }
            }
            return PrimaryKey;
        }
        public static NIChannelSettingData Construct(DataRow dr)
        {
            NIChannelSettingData data = new NIChannelSettingData();

            try { data.ID = Convert.ToInt32(dr["ID"]); }
            catch { }

            try { data.物理通道 = Convert.ToString(dr["物理通道"]); }
            catch { }

            try { data.名称 = Convert.ToString(dr["名称"]); }
            catch { }

            try { data.工位号 = Convert.ToString(dr["工位号"]); }
            catch { }

            try { data.规格型号 = Convert.ToString(dr["规格型号"]); }
            catch { }

            try { data.安装位置 = Convert.ToString(dr["安装位置"]); }
            catch { }

            try { data.厂家及项目来源 = Convert.ToString(dr["厂家及项目来源"]); }
            catch { }

            try { data.备注1 = Convert.ToString(dr["备注1"]); }
            catch { }

            try { data.备注2 = Convert.ToString(dr["备注2"]); }
            catch { }

            try { data.备注3 = Convert.ToString(dr["备注3"]); }
            catch { }

            try { data.是否远传 = Convert.ToBoolean(dr["是否远传"]); }
            catch { }

            try { data.通道配置项 = Convert.ToInt32(dr["通道配置项"]); }
            catch { }

            try { data.最小值 = Convert.ToDouble(dr["最小值"]); }
            catch { }

            try { data.最大值 = Convert.ToDouble(dr["最大值"]); }
            catch { }

            try { data.I_4mA = Convert.ToDouble(dr["I_4mA"]); }
            catch { }

            try { data.I_20mA = Convert.ToDouble(dr["I_20mA"]); }
            catch { }

            try { data.物理量单位 = Convert.ToString(dr["物理量单位"]); }
            catch { }

            try { data.Calc_k = Convert.ToDouble(dr["Calc_k"]); }
            catch { }

            try { data.Calc_b = Convert.ToDouble(dr["Calc_b"]); }
            catch { }

            return data;
        }
        public static Int32 GetPrimaryKey(DataRow dr)
        {
            Int32 PrimaryKey = 0;

            try { PrimaryKey = Convert.ToInt32(dr[NIChannelSettingData.PRIMARYKEY_Field]); }
            catch { }
            return PrimaryKey;
        }

    }
    public class NIChannelSettingDataDBOption
    {
        public static int Insert(NIChannelSettingData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("insert into NIChannelSetting (");
            sql.Append("物理通道, ");
            sql.Append("名称, ");
            sql.Append("工位号, ");
            sql.Append("规格型号, ");
            sql.Append("安装位置, ");
            sql.Append("厂家及项目来源, ");
            sql.Append("备注1, ");
            sql.Append("备注2, ");
            sql.Append("备注3, ");
            sql.Append("是否远传, ");
            sql.Append("通道配置项, ");
            sql.Append("最小值, ");
            sql.Append("最大值, ");
            sql.Append("I_4mA, ");
            sql.Append("I_20mA, ");
            sql.Append("物理量单位, ");
            sql.Append("Calc_k, ");
            sql.Append("Calc_b");
            sql.Append(") values (");
            sql.Append("'");
            sql.Append(d.物理通道.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.名称.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.工位号.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.规格型号.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.安装位置.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.厂家及项目来源.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.备注1.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.备注2.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.备注3.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("");
            if (d.是否远传)
                sql.Append("1");
            else
                sql.Append("0");
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.通道配置项.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.最小值.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.最大值.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.I_4mA.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.I_20mA.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("'");
            sql.Append(d.物理量单位.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.Calc_k.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("");
            sql.Append(d.Calc_b.ToString());
            sql.Append("");
            sql.Append(")");
            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static int Update(NIChannelSettingData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("update NIChannelSetting set ");
            sql.Append("物理通道=");
            sql.Append("'");
            sql.Append(d.物理通道.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("名称=");
            sql.Append("'");
            sql.Append(d.名称.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("工位号=");
            sql.Append("'");
            sql.Append(d.工位号.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("规格型号=");
            sql.Append("'");
            sql.Append(d.规格型号.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("安装位置=");
            sql.Append("'");
            sql.Append(d.安装位置.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("厂家及项目来源=");
            sql.Append("'");
            sql.Append(d.厂家及项目来源.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("备注1=");
            sql.Append("'");
            sql.Append(d.备注1.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("备注2=");
            sql.Append("'");
            sql.Append(d.备注2.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("备注3=");
            sql.Append("'");
            sql.Append(d.备注3.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("是否远传=");
            sql.Append("");
            if (d.是否远传)
                sql.Append("1");
            else
                sql.Append("0");
            sql.Append("");
            sql.Append(", ");
            sql.Append("通道配置项=");
            sql.Append("");
            sql.Append(d.通道配置项.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("最小值=");
            sql.Append("");
            sql.Append(d.最小值.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("最大值=");
            sql.Append("");
            sql.Append(d.最大值.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("I_4mA=");
            sql.Append("");
            sql.Append(d.I_4mA.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("I_20mA=");
            sql.Append("");
            sql.Append(d.I_20mA.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("物理量单位=");
            sql.Append("'");
            sql.Append(d.物理量单位.ToString());
            sql.Append("'");
            sql.Append(", ");
            sql.Append("Calc_k=");
            sql.Append("");
            sql.Append(d.Calc_k.ToString());
            sql.Append("");
            sql.Append(", ");
            sql.Append("Calc_b=");
            sql.Append("");
            sql.Append(d.Calc_b.ToString());
            sql.Append("");
            sql.Append(" where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString()); sql.Append("");

            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static int Delete(NIChannelSettingData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("delete from NIChannelSetting ");
            sql.Append(" where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString());
            sql.Append("");
            return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
        }
        public static DataTable DataTableSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from NIChannelSetting ");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
        public static DataTable DataTableSelect(NIChannelSettingData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from NIChannelSetting where ID=");
            sql.Append("");
            sql.Append(d.ID.ToString());
            sql.Append("");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
        public static NIChannelSettingData Get(Int32 _id)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from NIChannelSetting where ID=");
            sql.Append("");
            sql.Append(_id.ToString());
            sql.Append("");
            DataTable dt = WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
            if (dt.Rows.Count == 0)
                return null;
            else
                return NIChannelSettingDataFactory.Construct(dt.Rows[0]);
        }
        public static DataSet DataSetSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from NIChannelSetting ");
            return WFNetLib.ADO.SQLServerOP.DataSetSQL(sql.ToString());
        }
        public static SqlDataReader ReaderSelect(NIChannelSettingData d)
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from NIChannelSetting ");
            return WFNetLib.ADO.SQLServerOP.ReaderExecuteSQL(sql.ToString());
        }

        public static DataTable UseDataTableSelect()
        {
            StringBuilder sql = new StringBuilder();
            sql.Append("select * from NIChannelSetting where 名称<>''");
            return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
        }
    }
}