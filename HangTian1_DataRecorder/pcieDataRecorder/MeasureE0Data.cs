using System;
using System.Data;
using System.Windows.Forms;
using System.Text;
using System.Data.SqlClient;

namespace pcieDataRecorder
{
	[Serializable]
	public class MeasureE0Data
	{

		public const string IDField = @"ID";

		public const string PRIMARYKEY_Field = @"ID";

		public const string SOURCEField = @"Source";

		public const string IDENTField = @"Ident";

		public const string TIMEField = @"Time";

		public const string RESERVEField = @"Reserve";

		public const string BREADField = @"bRead";

		public const string A0Field = @"A0";

		public const string A1Field = @"A1";

		public const string A2Field = @"A2";

		public const string A3Field = @"A3";

		public const string A4Field = @"A4";

		public const string A5Field = @"A5";

		public const string A6Field = @"A6";

		public const string A7Field = @"A7";

		public const string A8Field = @"A8";

		public const string A9Field = @"A9";

		public const string AAField = @"AA";

		public const string ABField = @"AB";

		public const string C0Field = @"C0";

		public const string C1Field = @"C1";

		public const string C2Field = @"C2";

		public const string C3Field = @"C3";

		public const string C4Field = @"C4";

		public const string C5Field = @"C5";

		public const string C6Field = @"C6";

		public const string C7Field = @"C7";

		private Int64 _ID;

		private Int32 _Source;

		private String _Ident;

		private DateTime _Time;

		private String _Reserve;

		private Boolean _bRead;

		private Int32 _A0;

		private Int32 _A1;

		private Int32 _A2;

		private Int32 _A3;

		private Int32 _A4;

		private Int32 _A5;

		private Int32 _A6;

		private Int32 _A7;

		private Int32 _A8;

		private Int32 _A9;

		private Int32 _AA;

		private Int32 _AB;

		private Int32 _C0;

		private Int32 _C1;

		private Int32 _C2;

		private Int32 _C3;

		private Int32 _C4;

		private Int32 _C5;

		private Int32 _C6;

		private Int32 _C7;

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
		public Int32 A0
		{
			get { return _A0; }
			set { _A0 = value; }
		}
		public Int32 A1
		{
			get { return _A1; }
			set { _A1 = value; }
		}
		public Int32 A2
		{
			get { return _A2; }
			set { _A2 = value; }
		}
		public Int32 A3
		{
			get { return _A3; }
			set { _A3 = value; }
		}
		public Int32 A4
		{
			get { return _A4; }
			set { _A4 = value; }
		}
		public Int32 A5
		{
			get { return _A5; }
			set { _A5 = value; }
		}
		public Int32 A6
		{
			get { return _A6; }
			set { _A6 = value; }
		}
		public Int32 A7
		{
			get { return _A7; }
			set { _A7 = value; }
		}
		public Int32 A8
		{
			get { return _A8; }
			set { _A8 = value; }
		}
		public Int32 A9
		{
			get { return _A9; }
			set { _A9 = value; }
		}
		public Int32 AA
		{
			get { return _AA; }
			set { _AA = value; }
		}
		public Int32 AB
		{
			get { return _AB; }
			set { _AB = value; }
		}
		public Int32 C0
		{
			get { return _C0; }
			set { _C0 = value; }
		}
		public Int32 C1
		{
			get { return _C1; }
			set { _C1 = value; }
		}
		public Int32 C2
		{
			get { return _C2; }
			set { _C2 = value; }
		}
		public Int32 C3
		{
			get { return _C3; }
			set { _C3 = value; }
		}
		public Int32 C4
		{
			get { return _C4; }
			set { _C4 = value; }
		}
		public Int32 C5
		{
			get { return _C5; }
			set { _C5 = value; }
		}
		public Int32 C6
		{
			get { return _C6; }
			set { _C6 = value; }
		}
		public Int32 C7
		{
			get { return _C7; }
			set { _C7 = value; }
		}
		public MeasureE0Data()
		{
			_ID = 0;
			_Source = 0;
			_Ident = "";
			_Time = DateTime.Now;
			_Reserve = "";
			_bRead = false;
			_A0 = 0;
			_A1 = 0;
			_A2 = 0;
			_A3 = 0;
			_A4 = 0;
			_A5 = 0;
			_A6 = 0;
			_A7 = 0;
			_A8 = 0;
			_A9 = 0;
			_AA = 0;
			_AB = 0;
			_C0 = 0;
			_C1 = 0;
			_C2 = 0;
			_C3 = 0;
			_C4 = 0;
			_C5 = 0;
			_C6 = 0;
			_C7 = 0;
		}
	}

	public class MeasureE0DataFactory
	{
		public static MeasureE0Data Construct(IDataReader reader)
		{
			MeasureE0Data data = new MeasureE0Data();

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

			try { data.A0 = Convert.ToInt32(reader["A0"]); }
			catch { }

			try { data.A1 = Convert.ToInt32(reader["A1"]); }
			catch { }

			try { data.A2 = Convert.ToInt32(reader["A2"]); }
			catch { }

			try { data.A3 = Convert.ToInt32(reader["A3"]); }
			catch { }

			try { data.A4 = Convert.ToInt32(reader["A4"]); }
			catch { }

			try { data.A5 = Convert.ToInt32(reader["A5"]); }
			catch { }

			try { data.A6 = Convert.ToInt32(reader["A6"]); }
			catch { }

			try { data.A7 = Convert.ToInt32(reader["A7"]); }
			catch { }

			try { data.A8 = Convert.ToInt32(reader["A8"]); }
			catch { }

			try { data.A9 = Convert.ToInt32(reader["A9"]); }
			catch { }

			try { data.AA = Convert.ToInt32(reader["AA"]); }
			catch { }

			try { data.AB = Convert.ToInt32(reader["AB"]); }
			catch { }

			try { data.C0 = Convert.ToInt32(reader["C0"]); }
			catch { }

			try { data.C1 = Convert.ToInt32(reader["C1"]); }
			catch { }

			try { data.C2 = Convert.ToInt32(reader["C2"]); }
			catch { }

			try { data.C3 = Convert.ToInt32(reader["C3"]); }
			catch { }

			try { data.C4 = Convert.ToInt32(reader["C4"]); }
			catch { }

			try { data.C5 = Convert.ToInt32(reader["C5"]); }
			catch { }

			try { data.C6 = Convert.ToInt32(reader["C6"]); }
			catch { }

			try { data.C7 = Convert.ToInt32(reader["C7"]); }
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

			try { PrimaryKey = Convert.ToInt64(dr[MeasureE0Data.PRIMARYKEY_Field]); }
			catch { }

			return PrimaryKey;
		}
		public static MeasureE0Data Construct(DataTable dt)
		{
			return Construct(dt, 0);
		}
		public static MeasureE0Data Construct(DataTable dt, int rowIndex)
		{
			MeasureE0Data data = new MeasureE0Data();

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

			try { data.A0 = Convert.ToInt32(dr["A0"]); }
			catch { }

			try { data.A1 = Convert.ToInt32(dr["A1"]); }
			catch { }

			try { data.A2 = Convert.ToInt32(dr["A2"]); }
			catch { }

			try { data.A3 = Convert.ToInt32(dr["A3"]); }
			catch { }

			try { data.A4 = Convert.ToInt32(dr["A4"]); }
			catch { }

			try { data.A5 = Convert.ToInt32(dr["A5"]); }
			catch { }

			try { data.A6 = Convert.ToInt32(dr["A6"]); }
			catch { }

			try { data.A7 = Convert.ToInt32(dr["A7"]); }
			catch { }

			try { data.A8 = Convert.ToInt32(dr["A8"]); }
			catch { }

			try { data.A9 = Convert.ToInt32(dr["A9"]); }
			catch { }

			try { data.AA = Convert.ToInt32(dr["AA"]); }
			catch { }

			try { data.AB = Convert.ToInt32(dr["AB"]); }
			catch { }

			try { data.C0 = Convert.ToInt32(dr["C0"]); }
			catch { }

			try { data.C1 = Convert.ToInt32(dr["C1"]); }
			catch { }

			try { data.C2 = Convert.ToInt32(dr["C2"]); }
			catch { }

			try { data.C3 = Convert.ToInt32(dr["C3"]); }
			catch { }

			try { data.C4 = Convert.ToInt32(dr["C4"]); }
			catch { }

			try { data.C5 = Convert.ToInt32(dr["C5"]); }
			catch { }

			try { data.C6 = Convert.ToInt32(dr["C6"]); }
			catch { }

			try { data.C7 = Convert.ToInt32(dr["C7"]); }
			catch { }

			return data;
		}
		public static MeasureE0Data Construct(DataGridView dgv, int rowIndex)
		{
			MeasureE0Data data = new MeasureE0Data();

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

			try { data.A0 = Convert.ToInt32(dr["A0"]); }
			catch { }

			try { data.A1 = Convert.ToInt32(dr["A1"]); }
			catch { }

			try { data.A2 = Convert.ToInt32(dr["A2"]); }
			catch { }

			try { data.A3 = Convert.ToInt32(dr["A3"]); }
			catch { }

			try { data.A4 = Convert.ToInt32(dr["A4"]); }
			catch { }

			try { data.A5 = Convert.ToInt32(dr["A5"]); }
			catch { }

			try { data.A6 = Convert.ToInt32(dr["A6"]); }
			catch { }

			try { data.A7 = Convert.ToInt32(dr["A7"]); }
			catch { }

			try { data.A8 = Convert.ToInt32(dr["A8"]); }
			catch { }

			try { data.A9 = Convert.ToInt32(dr["A9"]); }
			catch { }

			try { data.AA = Convert.ToInt32(dr["AA"]); }
			catch { }

			try { data.AB = Convert.ToInt32(dr["AB"]); }
			catch { }

			try { data.C0 = Convert.ToInt32(dr["C0"]); }
			catch { }

			try { data.C1 = Convert.ToInt32(dr["C1"]); }
			catch { }

			try { data.C2 = Convert.ToInt32(dr["C2"]); }
			catch { }

			try { data.C3 = Convert.ToInt32(dr["C3"]); }
			catch { }

			try { data.C4 = Convert.ToInt32(dr["C4"]); }
			catch { }

			try { data.C5 = Convert.ToInt32(dr["C5"]); }
			catch { }

			try { data.C6 = Convert.ToInt32(dr["C6"]); }
			catch { }

			try { data.C7 = Convert.ToInt32(dr["C7"]); }
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
				if (dgv.Columns[i].DataPropertyName == MeasureE0Data.PRIMARYKEY_Field)
				{
					try { PrimaryKey = Convert.ToInt64(dr[i].Value); }
					catch { }
					return PrimaryKey;
				}
			}
			return PrimaryKey;
		}
		public static MeasureE0Data Construct(DataRow dr)
		{
			MeasureE0Data data = new MeasureE0Data();

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

			try { data.A0 = Convert.ToInt32(dr["A0"]); }
			catch { }

			try { data.A1 = Convert.ToInt32(dr["A1"]); }
			catch { }

			try { data.A2 = Convert.ToInt32(dr["A2"]); }
			catch { }

			try { data.A3 = Convert.ToInt32(dr["A3"]); }
			catch { }

			try { data.A4 = Convert.ToInt32(dr["A4"]); }
			catch { }

			try { data.A5 = Convert.ToInt32(dr["A5"]); }
			catch { }

			try { data.A6 = Convert.ToInt32(dr["A6"]); }
			catch { }

			try { data.A7 = Convert.ToInt32(dr["A7"]); }
			catch { }

			try { data.A8 = Convert.ToInt32(dr["A8"]); }
			catch { }

			try { data.A9 = Convert.ToInt32(dr["A9"]); }
			catch { }

			try { data.AA = Convert.ToInt32(dr["AA"]); }
			catch { }

			try { data.AB = Convert.ToInt32(dr["AB"]); }
			catch { }

			try { data.C0 = Convert.ToInt32(dr["C0"]); }
			catch { }

			try { data.C1 = Convert.ToInt32(dr["C1"]); }
			catch { }

			try { data.C2 = Convert.ToInt32(dr["C2"]); }
			catch { }

			try { data.C3 = Convert.ToInt32(dr["C3"]); }
			catch { }

			try { data.C4 = Convert.ToInt32(dr["C4"]); }
			catch { }

			try { data.C5 = Convert.ToInt32(dr["C5"]); }
			catch { }

			try { data.C6 = Convert.ToInt32(dr["C6"]); }
			catch { }

			try { data.C7 = Convert.ToInt32(dr["C7"]); }
			catch { }

			return data;
		}
		public static Int64 GetPrimaryKey(DataRow dr)
		{
			Int64 PrimaryKey = 0;

			try { PrimaryKey = Convert.ToInt64(dr[MeasureE0Data.PRIMARYKEY_Field]); }
			catch { }
			return PrimaryKey;
		}

	}
	public class MeasureE0DataDBOption
	{
		public static int Insert(MeasureE0Data d)
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("insert into MeasureE0 (");
			sql.Append("Source, ");
			sql.Append("Ident, ");
			sql.Append("Time, ");
			sql.Append("Reserve, ");
			sql.Append("bRead, ");
			sql.Append("A0, ");
			sql.Append("A1, ");
			sql.Append("A2, ");
			sql.Append("A3, ");
			sql.Append("A4, ");
			sql.Append("A5, ");
			sql.Append("A6, ");
			sql.Append("A7, ");
			sql.Append("A8, ");
			sql.Append("A9, ");
			sql.Append("AA, ");
			sql.Append("AB, ");
			sql.Append("C0, ");
			sql.Append("C1, ");
			sql.Append("C2, ");
			sql.Append("C3, ");
			sql.Append("C4, ");
			sql.Append("C5, ");
			sql.Append("C6, ");
			sql.Append("C7");
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
			sql.Append("");
			sql.Append(d.A0.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A1.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A2.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A3.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A4.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A5.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A6.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A7.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A8.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.A9.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.AA.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.AB.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C0.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C1.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C2.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C3.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C4.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C5.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C6.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("");
			sql.Append(d.C7.ToString());
			sql.Append("");
			sql.Append(")");
			return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
		}
		public static int Update(MeasureE0Data d)
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("update MeasureE0 set ");
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
			sql.Append("A0=");
			sql.Append("");
			sql.Append(d.A0.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A1=");
			sql.Append("");
			sql.Append(d.A1.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A2=");
			sql.Append("");
			sql.Append(d.A2.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A3=");
			sql.Append("");
			sql.Append(d.A3.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A4=");
			sql.Append("");
			sql.Append(d.A4.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A5=");
			sql.Append("");
			sql.Append(d.A5.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A6=");
			sql.Append("");
			sql.Append(d.A6.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A7=");
			sql.Append("");
			sql.Append(d.A7.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A8=");
			sql.Append("");
			sql.Append(d.A8.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("A9=");
			sql.Append("");
			sql.Append(d.A9.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("AA=");
			sql.Append("");
			sql.Append(d.AA.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("AB=");
			sql.Append("");
			sql.Append(d.AB.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C0=");
			sql.Append("");
			sql.Append(d.C0.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C1=");
			sql.Append("");
			sql.Append(d.C1.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C2=");
			sql.Append("");
			sql.Append(d.C2.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C3=");
			sql.Append("");
			sql.Append(d.C3.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C4=");
			sql.Append("");
			sql.Append(d.C4.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C5=");
			sql.Append("");
			sql.Append(d.C5.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C6=");
			sql.Append("");
			sql.Append(d.C6.ToString());
			sql.Append("");
			sql.Append(", ");
			sql.Append("C7=");
			sql.Append("");
			sql.Append(d.C7.ToString());
			sql.Append("");
			sql.Append(" where ID=");
			sql.Append("");
			sql.Append(d.ID.ToString()); sql.Append("");

			return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
		}
		public static int Delete(MeasureE0Data d)
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("delete from MeasureE0 ");
			sql.Append(" where ID=");
			sql.Append("");
			sql.Append(d.ID.ToString());
			sql.Append("");
			return WFNetLib.ADO.SQLServerOP.NonQuerySQL(sql.ToString());
		}
		public static DataTable DataTableSelect()
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("select * from MeasureE0 ");
			return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
		}
		public static DataTable DataTableSelect(MeasureE0Data d)
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("select * from MeasureE0 where ID=");
			sql.Append("");
			sql.Append(d.ID.ToString());
			sql.Append("");
			return WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
		}
		public static MeasureE0Data Get(Int64 _id)
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("select * from MeasureE0 where ID=");
			sql.Append("");
			sql.Append(_id.ToString());
			sql.Append("");
			DataTable dt = WFNetLib.ADO.SQLServerOP.DataTableSQL(sql.ToString());
			if (dt.Rows.Count == 0)
				return null;
			else
				return MeasureE0DataFactory.Construct(dt.Rows[0]);
		}
		public static DataSet DataSetSelect()
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("select * from MeasureE0 ");
			return WFNetLib.ADO.SQLServerOP.DataSetSQL(sql.ToString());
		}
		public static SqlDataReader ReaderSelect(MeasureE0Data d)
		{
			StringBuilder sql = new StringBuilder();
			sql.Append("select * from MeasureE0 ");
			return WFNetLib.ADO.SQLServerOP.ReaderExecuteSQL(sql.ToString());
		}
	}
}