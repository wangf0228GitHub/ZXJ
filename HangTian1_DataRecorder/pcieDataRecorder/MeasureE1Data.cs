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

		public const string BAField = @"BA";

		public const string BBField = @"BB";

		public const string BCField = @"BC";

		public const string BDField = @"BD";

		public const string BEField = @"BE";

		public const string BFField = @"BF";

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

		public const string CAField = @"CA";

		public const string CBField = @"CB";

		public const string CCField = @"CC";

		public const string CDField = @"CD";

		private Int64 _ID;

		private Int32 _Source;

		private String _Ident;

		private DateTime _Time;

		private String _Reserve;

		private Boolean _bRead;

		private String _B8;

		private String _B9;

		private String _BA;

		private String _BB;

		private String _BC;

		private String _BD;

		private String _BE;

		private String _BF;

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

		private String _CA;

		private String _CB;

		private String _CC;

		private String _CD;

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
		public String BA
		{
			get { return _BA; }
			set { _BA = value; }
		}
		public String BB
		{
			get { return _BB; }
			set { _BB = value; }
		}
		public String BC
		{
			get { return _BC; }
			set { _BC = value; }
		}
		public String BD
		{
			get { return _BD; }
			set { _BD = value; }
		}
		public String BE
		{
			get { return _BE; }
			set { _BE = value; }
		}
		public String BF
		{
			get { return _BF; }
			set { _BF = value; }
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
		public String CA
		{
			get { return _CA; }
			set { _CA = value; }
		}
		public String CB
		{
			get { return _CB; }
			set { _CB = value; }
		}
		public String CC
		{
			get { return _CC; }
			set { _CC = value; }
		}
		public String CD
		{
			get { return _CD; }
			set { _CD = value; }
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
			_BA = "";
			_BB = "";
			_BC = "";
			_BD = "";
			_BE = "";
			_BF = "";
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
			_CA = "";
			_CB = "";
			_CC = "";
			_CD = "";
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

			try { data.BA = Convert.ToString(reader["BA"]); }
			catch { }

			try { data.BB = Convert.ToString(reader["BB"]); }
			catch { }

			try { data.BC = Convert.ToString(reader["BC"]); }
			catch { }

			try { data.BD = Convert.ToString(reader["BD"]); }
			catch { }

			try { data.BE = Convert.ToString(reader["BE"]); }
			catch { }

			try { data.BF = Convert.ToString(reader["BF"]); }
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

			try { data.CA = Convert.ToString(reader["CA"]); }
			catch { }

			try { data.CB = Convert.ToString(reader["CB"]); }
			catch { }

			try { data.CC = Convert.ToString(reader["CC"]); }
			catch { }

			try { data.CD = Convert.ToString(reader["CD"]); }
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

			try { data.BA = Convert.ToString(dr["BA"]); }
			catch { }

			try { data.BB = Convert.ToString(dr["BB"]); }
			catch { }

			try { data.BC = Convert.ToString(dr["BC"]); }
			catch { }

			try { data.BD = Convert.ToString(dr["BD"]); }
			catch { }

			try { data.BE = Convert.ToString(dr["BE"]); }
			catch { }

			try { data.BF = Convert.ToString(dr["BF"]); }
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

			try { data.CA = Convert.ToString(dr["CA"]); }
			catch { }

			try { data.CB = Convert.ToString(dr["CB"]); }
			catch { }

			try { data.CC = Convert.ToString(dr["CC"]); }
			catch { }

			try { data.CD = Convert.ToString(dr["CD"]); }
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

			try { data.BA = Convert.ToString(dr["BA"]); }
			catch { }

			try { data.BB = Convert.ToString(dr["BB"]); }
			catch { }

			try { data.BC = Convert.ToString(dr["BC"]); }
			catch { }

			try { data.BD = Convert.ToString(dr["BD"]); }
			catch { }

			try { data.BE = Convert.ToString(dr["BE"]); }
			catch { }

			try { data.BF = Convert.ToString(dr["BF"]); }
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

			try { data.CA = Convert.ToString(dr["CA"]); }
			catch { }

			try { data.CB = Convert.ToString(dr["CB"]); }
			catch { }

			try { data.CC = Convert.ToString(dr["CC"]); }
			catch { }

			try { data.CD = Convert.ToString(dr["CD"]); }
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

			try { data.BA = Convert.ToString(dr["BA"]); }
			catch { }

			try { data.BB = Convert.ToString(dr["BB"]); }
			catch { }

			try { data.BC = Convert.ToString(dr["BC"]); }
			catch { }

			try { data.BD = Convert.ToString(dr["BD"]); }
			catch { }

			try { data.BE = Convert.ToString(dr["BE"]); }
			catch { }

			try { data.BF = Convert.ToString(dr["BF"]); }
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

			try { data.CA = Convert.ToString(dr["CA"]); }
			catch { }

			try { data.CB = Convert.ToString(dr["CB"]); }
			catch { }

			try { data.CC = Convert.ToString(dr["CC"]); }
			catch { }

			try { data.CD = Convert.ToString(dr["CD"]); }
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
			sql.Append("BA, ");
			sql.Append("BB, ");
			sql.Append("BC, ");
			sql.Append("BD, ");
			sql.Append("BE, ");
			sql.Append("BF, ");
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
			sql.Append("CA, ");
			sql.Append("CB, ");
			sql.Append("CC, ");
			sql.Append("CD");
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
			sql.Append(d.BA.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.BB.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.BC.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.BD.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.BE.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.BF.ToString());
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
			sql.Append(d.CA.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.CB.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.CC.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("'");
			sql.Append(d.CD.ToString());
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
			sql.Append("BA=");
			sql.Append("'");
			sql.Append(d.BA.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("BB=");
			sql.Append("'");
			sql.Append(d.BB.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("BC=");
			sql.Append("'");
			sql.Append(d.BC.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("BD=");
			sql.Append("'");
			sql.Append(d.BD.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("BE=");
			sql.Append("'");
			sql.Append(d.BE.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("BF=");
			sql.Append("'");
			sql.Append(d.BF.ToString());
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
			sql.Append("CA=");
			sql.Append("'");
			sql.Append(d.CA.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("CB=");
			sql.Append("'");
			sql.Append(d.CB.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("CC=");
			sql.Append("'");
			sql.Append(d.CC.ToString());
			sql.Append("'");
			sql.Append(", ");
			sql.Append("CD=");
			sql.Append("'");
			sql.Append(d.CD.ToString());
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