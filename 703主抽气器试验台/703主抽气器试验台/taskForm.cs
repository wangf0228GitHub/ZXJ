using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WFNetLib;
using NationalInstruments.DAQmx;
using NationalInstruments;

namespace _703主抽气器试验台
{
    public partial class taskForm : Form
    {
        private Task myTask;
        private Task runningTask;
        private AnalogMultiChannelReader myAnalogReader;
        private AnalogWaveform<double>[] data;
        private AsyncCallback myAsyncCallback;
        public taskForm()
        {
            InitializeComponent();
            DataTable dt = WFNetLib.ADO.SQLServerOP.DataTableSQL("select TOP 1 * from ExInfo order by id desc");
            exInfo = DAL.ExInfoDataFactory.Construct(dt.Rows[0]);
        }
        bool bSave = false;
        DAL.ExDataData[] exDataList;
        int exDataListIndex;
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            if (bSave)
            {
                bSave = false;
                toolStripButton1.Text = "开始存储";
            }
            else
            {
                bSave = true;
                toolStripButton1.Text = "停止存储";
            }
        }
        DAL.ExInfoData exInfo;
        DataTable exDataTable;
        List<DAL.NIChannelSettingData> aiList;
        private void taskForm_Load(object sender, EventArgs e)
        {
            this.Text = this.Text + "----" + exInfo.Title;
            timer1.Enabled = true;
        }
        private void AnalogInCallback(IAsyncResult ar)
        {
            try
            {
                if (runningTask != null && runningTask == ar.AsyncState)
                {
                    // Read the available data from the channels
                    data = myAnalogReader.EndReadWaveform(ar);

                    // Plot your data here
                    int currentLineIndex = 0;
                    foreach (AnalogWaveform<double> waveform in data)
                    {
                        double value = 0;
                        for (int sample = 0; sample < waveform.Samples.Count; ++sample)
                        {
                            value += waveform.Samples[sample].Value;
                        }
                        value = value / waveform.Samples.Count;
                        //value = value *1000;
                        value = aiList[currentLineIndex].Calc_k * value + aiList[currentLineIndex].Calc_b;
                        if (value > double.Parse(exDataTable.Rows[currentLineIndex]["最大值"].ToString()))
                        {
                            dataGridView1.Rows[currentLineIndex].DefaultCellStyle.BackColor = Color.Red;
                        }
                        else if (value < double.Parse(exDataTable.Rows[currentLineIndex]["最小值"].ToString()))
                        {
                            dataGridView1.Rows[currentLineIndex].DefaultCellStyle.BackColor = Color.Green;
                        }
                        else
                        {
                            dataGridView1.Rows[currentLineIndex].DefaultCellStyle.BackColor = SystemColors.Control;
                        }
                        if (bSave)
                        {
                            SaveData(aiList[currentLineIndex].物理通道, value);
                        }
                        exDataTable.Rows[currentLineIndex]["测量值"] = value.ToString("F2");
                        currentLineIndex++;
                    }
                    if (bSave)
                    {
                        exDataListIndex++;
                        if (exDataListIndex >= exInfo.SaveNS)
                        {
                            SaveDataToSQL();
                            exDataListIndex = 0;
                        }
                    }
                    else
                    {
                        exDataListIndex = 0;
                    }
                    myAnalogReader.BeginMemoryOptimizedReadWaveform(exInfo.SampleRete, myAsyncCallback, myTask, data);
                }
            }
            catch (DaqException exception)
            {
                // Display Errors
                MessageBox.Show(exception.Message);
                myTask.Dispose();
                runningTask = null;
            }

        }
        void SaveData(string niChannel, double value)
        {
            switch (niChannel)
            {
                case "9188Mod1/ai0":
                    exDataList[exDataListIndex].AI01 = value;
                    break;
                case "9188Mod1/ai1":
                    exDataList[exDataListIndex].AI02 = value;
                    break;
                case "9188Mod1/ai2":
                    exDataList[exDataListIndex].AI03 = value;
                    break;
                case "9188Mod1/ai3":
                    exDataList[exDataListIndex].AI04 = value;
                    break;
                case "9188Mod1/ai4":
                    exDataList[exDataListIndex].AI05 = value;
                    break;
                case "9188Mod1/ai5":
                    exDataList[exDataListIndex].AI06 = value;
                    break;
                case "9188Mod1/ai6":
                    exDataList[exDataListIndex].AI07 = value;
                    break;
                case "9188Mod1/ai7":
                    exDataList[exDataListIndex].AI08 = value;
                    break;
                case "9188Mod1/ai8":
                    exDataList[exDataListIndex].AI09 = value;
                    break;
                case "9188Mod1/ai9":
                    exDataList[exDataListIndex].AI10 = value;
                    break;
                case "9188Mod1/ai10":
                    exDataList[exDataListIndex].AI11 = value;
                    break;
                case "9188Mod1/ai11":
                    exDataList[exDataListIndex].AI12 = value;
                    break;
                case "9188Mod1/ai12":
                    exDataList[exDataListIndex].AI13 = value;
                    break;
                case "9188Mod1/ai13":
                    exDataList[exDataListIndex].AI14 = value;
                    break;
                case "9188Mod1/ai14":
                    exDataList[exDataListIndex].AI15 = value;
                    break;
                case "9188Mod1/ai15":
                    exDataList[exDataListIndex].AI16 = value;
                    break;
                case "9188Mod2/ai0":
                    exDataList[exDataListIndex].AI17 = value;
                    break;
                case "9188Mod2/ai1":
                    exDataList[exDataListIndex].AI18 = value;
                    break;
                case "9188Mod2/ai2":
                    exDataList[exDataListIndex].AI19 = value;
                    break;
                case "9188Mod2/ai3":
                    exDataList[exDataListIndex].AI20 = value;
                    break;
                case "9188Mod2/ai4":
                    exDataList[exDataListIndex].AI21 = value;
                    break;
                case "9188Mod2/ai5":
                    exDataList[exDataListIndex].AI22 = value;
                    break;
                case "9188Mod2/ai6":
                    exDataList[exDataListIndex].AI23 = value;
                    break;
                case "9188Mod2/ai7":
                    exDataList[exDataListIndex].AI24 = value;
                    break;
                case "9188Mod2/ai8":
                    exDataList[exDataListIndex].AI25 = value;
                    break;
                case "9188Mod2/ai9":
                    exDataList[exDataListIndex].AI26 = value;
                    break;
                case "9188Mod2/ai10":
                    exDataList[exDataListIndex].AI27 = value;
                    break;
                case "9188Mod2/ai11":
                    exDataList[exDataListIndex].AI28 = value;
                    break;
                case "9188Mod2/ai12":
                    exDataList[exDataListIndex].AI29 = value;
                    break;
                case "9188Mod2/ai13":
                    exDataList[exDataListIndex].AI30 = value;
                    break;
                case "9188Mod2/ai14":
                    exDataList[exDataListIndex].AI31 = value;
                    break;
                case "9188Mod2/ai15":
                    exDataList[exDataListIndex].AI32 = value;
                    break;
                case "9188Mod3/ai0":
                    exDataList[exDataListIndex].AI33 = value;
                    break;
                case "9188Mod3/ai1":
                    exDataList[exDataListIndex].AI34 = value;
                    break;
                case "9188Mod3/ai2":
                    exDataList[exDataListIndex].AI35 = value;
                    break;
                case "9188Mod3/ai3":
                    exDataList[exDataListIndex].AI36 = value;
                    break;
                case "9188Mod3/ai4":
                    exDataList[exDataListIndex].AI37 = value;
                    break;
                case "9188Mod3/ai5":
                    exDataList[exDataListIndex].AI38 = value;
                    break;
                case "9188Mod3/ai6":
                    exDataList[exDataListIndex].AI39 = value;
                    break;
                case "9188Mod3/ai7":
                    exDataList[exDataListIndex].AI40 = value;
                    break;
                case "9188Mod3/ai8":
                    exDataList[exDataListIndex].AI41 = value;
                    break;
                case "9188Mod3/ai9":
                    exDataList[exDataListIndex].AI42 = value;
                    break;
                case "9188Mod3/ai10":
                    exDataList[exDataListIndex].AI43 = value;
                    break;
                case "9188Mod3/ai11":
                    exDataList[exDataListIndex].AI44 = value;
                    break;
                case "9188Mod3/ai12":
                    exDataList[exDataListIndex].AI45 = value;
                    break;
                case "9188Mod3/ai13":
                    exDataList[exDataListIndex].AI46 = value;
                    break;
                case "9188Mod3/ai14":
                    exDataList[exDataListIndex].AI47 = value;
                    break;
                case "9188Mod3/ai15":
                    exDataList[exDataListIndex].AI48 = value;
                    break;
                case "9188Mod4/ai0":
                    exDataList[exDataListIndex].AI49 = value;
                    break;
                case "9188Mod4/ai1":
                    exDataList[exDataListIndex].AI50 = value;
                    break;
                case "9188Mod4/ai2":
                    exDataList[exDataListIndex].AI51 = value;
                    break;
                case "9188Mod4/ai3":
                    exDataList[exDataListIndex].AI52 = value;
                    break;
                case "9188Mod4/ai4":
                    exDataList[exDataListIndex].AI53 = value;
                    break;
                case "9188Mod4/ai5":
                    exDataList[exDataListIndex].AI54 = value;
                    break;
                case "9188Mod4/ai6":
                    exDataList[exDataListIndex].AI55 = value;
                    break;
                case "9188Mod4/ai7":
                    exDataList[exDataListIndex].AI56 = value;
                    break;
                case "9188Mod4/ai8":
                    exDataList[exDataListIndex].AI57 = value;
                    break;
                case "9188Mod4/ai9":
                    exDataList[exDataListIndex].AI58 = value;
                    break;
                case "9188Mod4/ai10":
                    exDataList[exDataListIndex].AI59 = value;
                    break;
                case "9188Mod4/ai11":
                    exDataList[exDataListIndex].AI60 = value;
                    break;
                case "9188Mod4/ai12":
                    exDataList[exDataListIndex].AI61 = value;
                    break;
                case "9188Mod4/ai13":
                    exDataList[exDataListIndex].AI62 = value;
                    break;
                case "9188Mod4/ai14":
                    exDataList[exDataListIndex].AI63 = value;
                    break;
                case "9188Mod4/ai15":
                    exDataList[exDataListIndex].AI64 = value;
                    break;
            }
        }
        void SaveDataToSQL()
        {
            DAL.ExDataData exData4Save = new DAL.ExDataData();
            for (int i = 0; i < exDataList.Length; i++)
            {
                exData4Save.AI01 += exDataList[i].AI01;
                exData4Save.AI02 += exDataList[i].AI02;
                exData4Save.AI03 += exDataList[i].AI03;
                exData4Save.AI04 += exDataList[i].AI04;
                exData4Save.AI05 += exDataList[i].AI05;
                exData4Save.AI06 += exDataList[i].AI06;
                exData4Save.AI07 += exDataList[i].AI07;
                exData4Save.AI08 += exDataList[i].AI08;
                exData4Save.AI09 += exDataList[i].AI09;
                exData4Save.AI10 += exDataList[i].AI10;
                exData4Save.AI11 += exDataList[i].AI01;
                exData4Save.AI12 += exDataList[i].AI12;
                exData4Save.AI13 += exDataList[i].AI13;
                exData4Save.AI14 += exDataList[i].AI14;
                exData4Save.AI15 += exDataList[i].AI15;
                exData4Save.AI16 += exDataList[i].AI16;
                exData4Save.AI17 += exDataList[i].AI17;
                exData4Save.AI18 += exDataList[i].AI18;
                exData4Save.AI19 += exDataList[i].AI19;
                exData4Save.AI20 += exDataList[i].AI20;
                exData4Save.AI21 += exDataList[i].AI21;
                exData4Save.AI22 += exDataList[i].AI22;
                exData4Save.AI23 += exDataList[i].AI23;
                exData4Save.AI24 += exDataList[i].AI24;
                exData4Save.AI25 += exDataList[i].AI25;
                exData4Save.AI26 += exDataList[i].AI26;
                exData4Save.AI27 += exDataList[i].AI27;
                exData4Save.AI28 += exDataList[i].AI28;
                exData4Save.AI29 += exDataList[i].AI29;
                exData4Save.AI30 += exDataList[i].AI30;
                exData4Save.AI31 += exDataList[i].AI31;
                exData4Save.AI32 += exDataList[i].AI32;
                exData4Save.AI33 += exDataList[i].AI33;
                exData4Save.AI34 += exDataList[i].AI34;
                exData4Save.AI35 += exDataList[i].AI35;
                exData4Save.AI36 += exDataList[i].AI36;
                exData4Save.AI37 += exDataList[i].AI37;
                exData4Save.AI38 += exDataList[i].AI38;
                exData4Save.AI39 += exDataList[i].AI39;
                exData4Save.AI40 += exDataList[i].AI40;
                exData4Save.AI41 += exDataList[i].AI41;
                exData4Save.AI42 += exDataList[i].AI42;
                exData4Save.AI43 += exDataList[i].AI43;
                exData4Save.AI44 += exDataList[i].AI44;
                exData4Save.AI45 += exDataList[i].AI45;
                exData4Save.AI46 += exDataList[i].AI46;
                exData4Save.AI47 += exDataList[i].AI47;
                exData4Save.AI48 += exDataList[i].AI48;
                exData4Save.AI49 += exDataList[i].AI49;
                exData4Save.AI50 += exDataList[i].AI50;
                exData4Save.AI51 += exDataList[i].AI51;
                exData4Save.AI52 += exDataList[i].AI52;
                exData4Save.AI53 += exDataList[i].AI53;
                exData4Save.AI54 += exDataList[i].AI54;
                exData4Save.AI55 += exDataList[i].AI55;
                exData4Save.AI56 += exDataList[i].AI56;
                exData4Save.AI57 += exDataList[i].AI57;
                exData4Save.AI58 += exDataList[i].AI58;
                exData4Save.AI59 += exDataList[i].AI59;
                exData4Save.AI60 += exDataList[i].AI60;
                exData4Save.AI61 += exDataList[i].AI61;
                exData4Save.AI62 += exDataList[i].AI62;
                exData4Save.AI63 += exDataList[i].AI63;
                exData4Save.AI64 += exDataList[i].AI64;
            }
            exData4Save.AI01 = exData4Save.AI01 / exDataList.Length;
            exData4Save.AI02 = exData4Save.AI02 / exDataList.Length;
            exData4Save.AI03 = exData4Save.AI03 / exDataList.Length;
            exData4Save.AI04 = exData4Save.AI04 / exDataList.Length;
            exData4Save.AI05 = exData4Save.AI05 / exDataList.Length;
            exData4Save.AI06 = exData4Save.AI06 / exDataList.Length;
            exData4Save.AI07 = exData4Save.AI07 / exDataList.Length;
            exData4Save.AI08 = exData4Save.AI08 / exDataList.Length;
            exData4Save.AI09 = exData4Save.AI09 / exDataList.Length;
            exData4Save.AI10 = exData4Save.AI10 / exDataList.Length;
            exData4Save.AI11 = exData4Save.AI01 / exDataList.Length;
            exData4Save.AI12 = exData4Save.AI12 / exDataList.Length;
            exData4Save.AI13 = exData4Save.AI13 / exDataList.Length;
            exData4Save.AI14 = exData4Save.AI14 / exDataList.Length;
            exData4Save.AI15 = exData4Save.AI15 / exDataList.Length;
            exData4Save.AI16 = exData4Save.AI16 / exDataList.Length;
            exData4Save.AI17 = exData4Save.AI17 / exDataList.Length;
            exData4Save.AI18 = exData4Save.AI18 / exDataList.Length;
            exData4Save.AI19 = exData4Save.AI19 / exDataList.Length;
            exData4Save.AI20 = exData4Save.AI20 / exDataList.Length;
            exData4Save.AI21 = exData4Save.AI21 / exDataList.Length;
            exData4Save.AI22 = exData4Save.AI22 / exDataList.Length;
            exData4Save.AI23 = exData4Save.AI23 / exDataList.Length;
            exData4Save.AI24 = exData4Save.AI24 / exDataList.Length;
            exData4Save.AI25 = exData4Save.AI25 / exDataList.Length;
            exData4Save.AI26 = exData4Save.AI26 / exDataList.Length;
            exData4Save.AI27 = exData4Save.AI27 / exDataList.Length;
            exData4Save.AI28 = exData4Save.AI28 / exDataList.Length;
            exData4Save.AI29 = exData4Save.AI29 / exDataList.Length;
            exData4Save.AI30 = exData4Save.AI30 / exDataList.Length;
            exData4Save.AI31 = exData4Save.AI31 / exDataList.Length;
            exData4Save.AI32 = exData4Save.AI32 / exDataList.Length;
            exData4Save.AI33 = exData4Save.AI33 / exDataList.Length;
            exData4Save.AI34 = exData4Save.AI34 / exDataList.Length;
            exData4Save.AI35 = exData4Save.AI35 / exDataList.Length;
            exData4Save.AI36 = exData4Save.AI36 / exDataList.Length;
            exData4Save.AI37 = exData4Save.AI37 / exDataList.Length;
            exData4Save.AI38 = exData4Save.AI38 / exDataList.Length;
            exData4Save.AI39 = exData4Save.AI39 / exDataList.Length;
            exData4Save.AI40 = exData4Save.AI40 / exDataList.Length;
            exData4Save.AI41 = exData4Save.AI41 / exDataList.Length;
            exData4Save.AI42 = exData4Save.AI42 / exDataList.Length;
            exData4Save.AI43 = exData4Save.AI43 / exDataList.Length;
            exData4Save.AI44 = exData4Save.AI44 / exDataList.Length;
            exData4Save.AI45 = exData4Save.AI45 / exDataList.Length;
            exData4Save.AI46 = exData4Save.AI46 / exDataList.Length;
            exData4Save.AI47 = exData4Save.AI47 / exDataList.Length;
            exData4Save.AI48 = exData4Save.AI48 / exDataList.Length;
            exData4Save.AI49 = exData4Save.AI49 / exDataList.Length;
            exData4Save.AI50 = exData4Save.AI50 / exDataList.Length;
            exData4Save.AI51 = exData4Save.AI51 / exDataList.Length;
            exData4Save.AI52 = exData4Save.AI52 / exDataList.Length;
            exData4Save.AI53 = exData4Save.AI53 / exDataList.Length;
            exData4Save.AI54 = exData4Save.AI54 / exDataList.Length;
            exData4Save.AI55 = exData4Save.AI55 / exDataList.Length;
            exData4Save.AI56 = exData4Save.AI56 / exDataList.Length;
            exData4Save.AI57 = exData4Save.AI57 / exDataList.Length;
            exData4Save.AI58 = exData4Save.AI58 / exDataList.Length;
            exData4Save.AI59 = exData4Save.AI59 / exDataList.Length;
            exData4Save.AI60 = exData4Save.AI60 / exDataList.Length;
            exData4Save.AI61 = exData4Save.AI61 / exDataList.Length;
            exData4Save.AI62 = exData4Save.AI62 / exDataList.Length;
            exData4Save.AI63 = exData4Save.AI63 / exDataList.Length;
            exData4Save.AI64 = exData4Save.AI64 / exDataList.Length;

            exData4Save.ExID = exInfo.ID;
            exData4Save.DataTime = DateTime.Now;
            DAL.ExDataDataDBOption.Insert(exData4Save);
        }

        private void taskForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            runningTask = null;
            myTask.Dispose();
        }

        private void taskForm_Shown(object sender, EventArgs e)
        {
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Enabled = false;            
            exDataList = new DAL.ExDataData[exInfo.SaveNS];
            for (int i = 0; i < exInfo.SaveNS; i++)
            {
                exDataList[i] = new DAL.ExDataData();
            }
            exDataListIndex = 0;
            exDataTable = new DataTable();
            exDataTable.Columns.Add("序号");
            //exDataTable.Columns.Add("物理通道");
            exDataTable.Columns.Add("名称");
            exDataTable.Columns.Add("工位号");
            exDataTable.Columns.Add("安装位置");
            exDataTable.Columns.Add("测量值");
            exDataTable.Columns.Add("最小值");
            exDataTable.Columns.Add("最大值");
            exDataTable.Columns.Add("物理量单位");
            string[] aiNameList = exInfo.NI9188Mod.Split('|');
            string strSQL = "select * from  NIChannelSetting where ( ";
            if (aiNameList.Length == 0)
            {
                MessageBox.Show("未选择任何传感器");
                this.Close();
                return;
            }
            foreach (string ai in aiNameList)
            {
                strSQL += "ID=" + ai + " OR ";
            }
            strSQL = strSQL.Substring(0, strSQL.Length - 4);
            strSQL += ")";
            aiList = new List<DAL.NIChannelSettingData>();
            DataTable aidt = WFNetLib.ADO.SQLServerOP.DataTableSQL(strSQL);
            int index = 1;
            try
            {
                myTask = new Task();
                for (int i = 0; i < aidt.Rows.Count; i++)
                {
                    DAL.NIChannelSettingData ai = DAL.NIChannelSettingDataFactory.Construct(aidt.Rows[i]);
                    aiList.Add(ai);
                    DataRow dr = exDataTable.NewRow();
                    dr["序号"] = index++;
                    //dr["物理通道"] = ai.物理通道;
                    dr["名称"] = ai.名称;
                    dr["工位号"] = ai.工位号;
                    dr["安装位置"] = ai.安装位置;
                    dr["最小值"] = ai.最小值;
                    dr["最大值"] = ai.最大值;
                    dr["物理量单位"] = ai.物理量单位;
                    exDataTable.Rows.Add(dr);
                    myTask.AIChannels.CreateCurrentChannel(ai.物理通道, "",//ai.名称 + "_" + ai.工位号,
                                (AITerminalConfiguration)(-1), 0.004,
                                0.020, AICurrentUnits.Amps);
                }
                myTask.Timing.ConfigureSampleClock("", exInfo.SampleRete,
                        SampleClockActiveEdge.Rising, SampleQuantityMode.ContinuousSamples, exInfo.SampleRete);

                // Verify the Task
                myTask.Control(TaskAction.Verify);

                runningTask = myTask;
                myAnalogReader = new AnalogMultiChannelReader(myTask.Stream);
                myAsyncCallback = new AsyncCallback(AnalogInCallback);


                myAnalogReader.SynchronizeCallbacks = true;
                myAnalogReader.BeginReadWaveform(exInfo.SampleRete, myAsyncCallback,
                    myTask);
                dataGridView1.DataSource = exDataTable;
            }
            catch (System.Exception ex)
            {
                // Display Errors
                MessageBox.Show(ex.Message);
                myTask.Dispose();
                runningTask = null;
                this.Close();
            }
        }
    }
}
