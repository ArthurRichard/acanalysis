using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.IO;

using System.Runtime.InteropServices;
namespace AC4Analysis
{
    public partial class SM : UserControl
    {
        
        public byte[] data;
        public struct V3F
        {
            public float x, y, z;
            public void 设置(Int32 _索引, Single _数值)
            {
                switch(_索引)
                {
                    case 0: x = _数值; break;
                    case 1: y = _数值; break;
                    case 2: z = _数值; break;
                    default: break;
                }
            }
            public float 获取(Int32 _索引)
            {
                switch (_索引)
                {
                    case 0: return x;
                    case 1: return y;
                    case 2: return z;
                    default: return x;
                }
            }
        }
        public struct V4F
        {
            public float x, y, z, w;
            public void 设置(Int32 _索引, Single _数值)
            {
                switch (_索引)
                {
                    case 0: x = _数值; break;
                    case 1: y = _数值; break;
                    case 2: z = _数值; break;
                    case 3: w = _数值; break;
                    default: break;
                }
            }
            public float 获取(Int32 _索引)
            {
                switch (_索引)
                {
                    case 0: return x;
                    case 1: return y;
                    case 2: return z;
                    case 3: return w;
                    default: return x;
                }
            }
        }
        public struct 关键帧
        {
            public Int32 关键帧数;
            public Int32 不明关键帧信息偏址1;
            public Int32 关键帧数据偏址;
            public Int32 预留;

            public V3F[] 位置;
            public V3F[] 旋转;
            public V3F[] 缩放;
        }

        public class 部件信息
        {
            // 0x00
            public V4F 初始位置 = new V4F();
            // 0x10
            public V4F 初始旋转 = new V4F();
            // 0x20
            public Int32 关键帧动画信息偏址;      // 不明 多为0x00
            public Int32 网格数据列表偏址;       // 网格数据偏址
            public Single 不明浮点参数1;     // 不明 一个单精浮点
            public Int32 部件类型;          
            // 0x30
            public Int32 子部件数;     // 子部件数量
            public Int32 子部件列表偏址;    // 子部件偏址
            public Int32 关键帧动画数;      // 不明 多为0x00
            public Int32 不明整数参数2;      // 不明 多为0xFF

            // 以下数据非模型数据，分析后记录得出
            public Int32 父部件索引;          // 父对象索引
            public Int32 顶点起始索引;       // 起始顶点
            public Int32 顶点数;         // 顶点数

            public 关键帧 关键帧数据 = new 关键帧(); 

            public void 读取部件信息(Byte[] _数据, Int32 _起始偏址, Int32 _父部件索引)
            {
                for (Int32 i = 0; i < 4; i++)
                {
                    初始位置.设置(i, BitConverter.ToSingle(_数据, _起始偏址 + sizeof(Single) * i));
                    初始旋转.设置(i, BitConverter.ToSingle(_数据, _起始偏址 + 0x10 + sizeof(Single) * i));
                }

                关键帧动画信息偏址 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20);
                网格数据列表偏址 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20 + 4);
                不明浮点参数1 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20 + 8);
                部件类型 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20 + 12);

                子部件数 = BitConverter.ToInt32(_数据, _起始偏址 + 0x30);
                子部件列表偏址 = BitConverter.ToInt32(_数据, _起始偏址 + 0x30 + 4);
                关键帧动画数 = BitConverter.ToInt32(_数据, _起始偏址 + 0x30 + 8);
                不明整数参数2 = BitConverter.ToInt32(_数据, _起始偏址 + 0x30 + 12);

                父部件索引 = _父部件索引;

                if (关键帧动画信息偏址 > 0)
                {
                    关键帧数据.关键帧数 = BitConverter.ToInt32(_数据, 关键帧动画信息偏址);
                    关键帧数据.不明关键帧信息偏址1 = BitConverter.ToInt32(_数据, 关键帧动画信息偏址 + 4);
                    关键帧数据.关键帧数据偏址  = BitConverter.ToInt32(_数据, 关键帧动画信息偏址 + 8);
                    关键帧数据.预留 = BitConverter.ToInt32(_数据, 关键帧动画信息偏址 + 12);

                    关键帧数据.位置 = new V3F[关键帧数据.关键帧数];
                    关键帧数据.旋转 = new V3F[关键帧数据.关键帧数];
                    关键帧数据.缩放 = new V3F[关键帧数据.关键帧数];

                    for(Int32 i=0;i<关键帧数据.关键帧数;i++)
                    {
                        for (Int32 j = 0; j < 3; j++)
                        {
                            关键帧数据.位置[i].设置(j, BitConverter.ToSingle(_数据, 关键帧数据.关键帧数据偏址 + i * 36 + 0  + sizeof(Single)*j));
                            关键帧数据.旋转[i].设置(j, BitConverter.ToSingle(_数据, 关键帧数据.关键帧数据偏址 + i * 36 + 12 + sizeof(Single) * j));
                            关键帧数据.缩放[i].设置(j, BitConverter.ToSingle(_数据, 关键帧数据.关键帧数据偏址 + i * 36 + 24 + sizeof(Single) * j));
                        }
                    }
                }
            }
        }
        List<Single> 顶点列表 = new List<Single>();
        List<Single> 法线列表 = new List<Single>();
        List<Single> 纹理位置列表 = new List<Single>();
        List<部件信息> 部件列表 = new List<部件信息>();

        float[] Vesout;
        float[] Norout;
        float[] Texout;
        float[] PartTR;
        int[] PartInfo;
        
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Set3DData(float[] VecsIn, float[] NorsIn, int VecSizeIn, float[] TexsIn, int TexsSizeIn);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPartData(float[] PartTRIn, int[] PartInfoIn, int PartSizeIn);

        private void 载入部件(Int32 _起始偏址, Int32 _父部件索引)
        {
            部件信息 当前部件 = new 部件信息();
            当前部件.读取部件信息(data, _起始偏址, _父部件索引);
            部件列表.Add(当前部件);

            Int32 当前索引 = 部件列表.Count - 1;

            部件列表[当前索引].顶点起始索引= 顶点列表.Count / 3;
            载入网格(当前部件.网格数据列表偏址 );
            部件列表[当前索引].顶点数 = 顶点列表.Count / 3 - 部件列表[当前索引].顶点起始索引;

            for (Int32 i = 0; i < 当前部件.子部件数 ; i++)
            {
                载入部件(BitConverter.ToInt32(data, 当前部件.子部件列表偏址  + sizeof(Int32) * i), 当前索引);
            }
        }

        private void 载入网格(Int32 _起始偏址)
        {
            Int32 网格偏址 = BitConverter.ToInt32(data, _起始偏址 + 4);
            while (BitConverter.ToInt32(data, 网格偏址) == 0x1000000A || BitConverter.ToInt32(data, 网格偏址) == 0x10000008)
            {
                if (data[网格偏址] == 0x0A)
                {
                    for (Int32 i = 2; i > -1; i--)
                    {
                        Int32 纹理位置偏址 = 网格偏址 + 20 + i * 8;      // UV数据起始位置
                        纹理位置列表.Add((Single)BitConverter.ToInt16(data, 纹理位置偏址) / 0x1000);
                        纹理位置列表.Add((Single)BitConverter.ToInt16(data, 纹理位置偏址 + 2) / 0x1000);

                        Int32 法线偏址 = 网格偏址 + 144 + i * 8;        // Normal数据起始位置
                        法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址) / 0x1000);
                        法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址 + 2) / 0x1000);
                        法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址 + 4) / 0x1000);

                        Int32 顶点偏址 = 网格偏址 + 76 + i * 16;        // Vertex数据起始位置
                        顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址));
                        顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址 + 4));
                        顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址 + 8));
                    }

                    for (Int32 i = 1; i < 4; i++)
                    {
                        Int32 纹理位置偏址 = 网格偏址 + 20 + i * 8;      // UV数据起始位置
                        纹理位置列表.Add((Single)BitConverter.ToInt16(data, 纹理位置偏址) / 0x1000);
                        纹理位置列表.Add((Single)BitConverter.ToInt16(data, 纹理位置偏址 + 2) / 0x1000);

                        Int32 法线偏址 = 网格偏址 + 144 + i * 8;        // Normal数据起始位置
                        法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址) / 0x1000);
                        法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址 + 2) / 0x1000);
                        法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址 + 4) / 0x1000);

                        Int32 顶点偏址 = 网格偏址 + 76 + i * 16;        // Vertex数据起始位置
                        顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址));
                        顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址 + 4));
                        顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址 + 8));
                    }
                    网格偏址 += 256;
                }
                else
                {
                    if (data[网格偏址] == 0x08)
                    {
                        for (Int32 i = 2; i > -1; i--)
                        {
                            Int32 纹理位置偏址 = 网格偏址 + 24 + i * 8;      // UV数据起始位置
                            纹理位置列表.Add((Single)BitConverter.ToInt16(data, 纹理位置偏址) / 0x1000);
                            纹理位置列表.Add((Single)BitConverter.ToInt16(data, 纹理位置偏址 + 2) / 0x1000);

                            Int32 法线偏址 = 网格偏址 + 120 + i * 8;        // Normal数据起始位置
                            法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址) / 0x1000);
                            法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址 + 2) / 0x1000);
                            法线列表.Add(-(Single)BitConverter.ToInt16(data, 法线偏址 + 4) / 0x1000);

                            Int32 顶点偏址 = 网格偏址 + 68 + i * 16;        // Vertex数据起始位置
                            顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址));
                            顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址 + 4));
                            顶点列表.Add(BitConverter.ToSingle(data, 顶点偏址 + 8));
                            
                        }
                        网格偏址 += 224;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        public String 获取部件类型名称(Int32 _编号)
        {
            switch (_编号)
            {
                case 0: return "body";
                case 1: return "elevator_left";
                case 2: return "elevator_right";
                case 3: return "rudder_left";
                case 4: return "rudder_right";
                case 5: return "low speed ailerons_left";
                case 6: return "low speed ailerons_right";
                case 7: return "left_flap";
                case 8: return "right_flap";
                case 9: return "vector tail spray_left";
                case 10: return "vector tail spray_right";
                case 11: return "canard_left";
                case 12: return "canard_right";
                case 13: return "spoiler_left";
                case 14: return "spoiler_right";
                case 15: return "tailpipe";
                case 16: return "speedbrakes";
                case 17: return "auxiliary air intake";
                case 18: return "leading edge flap(slat)";
                case 19: return "variable wing(folding wings)";
                case 20: return "variable wing joint";
                case 22: return "engine fan";
                case 27: return "before landing lights?";
                case 28: return "after the left landing gear lights?";
                case 29: return "right after landing lights?";
                case 30: return "body light bar";
                case 31: return "pilot";
                case 33: return "Conventional Arms door";
                case 34: return "special military equipment hatch";
                case 40: return "landing gear trap";
                case 41: return "landing gear";
                case 42: return "tail hook";
                case 43: return "front";
                case 44: return "_rear left";
                case 45: return "_rear right";
                case 50: return "weapons pylons 1";
                case 51: return "weapons pylons 2";
                case 52: return "weapons pylons 3";
                case 53: return "weapons pylons 4";
                case 54: return "weapons pylons 5";
                case 55: return "weapons pylons 6";
                case 58: return "special rack 1";
                case 59: return "special rack 2";
                case 60: return "special rack 3";
                case 61: return "special rack 4";
                case 62: return "special rack 5";
                case 63: return "special rack 6";
                case 97: return "aerial refueling door";
                case 98: return "tail hook";
                default: return "unknown" + _编号.ToString();
            }
        }
        public SM()
        {
            InitializeComponent();
        }
        public IntPtr GetHwnd()
        {
            return panel1.Handle;
        }
        public void Analysis_SM()
        {
            if (data == null)
                return;

            顶点列表  = new List<Single>();
            法线列表 = new List<Single>();
            纹理位置列表 = new List<Single>();
            部件列表 = new List<部件信息>();
            Int32 临时偏址 = 0;
            临时偏址 = BitConverter.ToInt32(data, 20);              // Model.Offset

            载入部件(临时偏址, -1);
            /*
            float[] Vesout = new float[Verts.Count];
            float[] Norout = new float[Verts.Count];
            float[] Texout = new float[TexCoords.Count];
            float[] PartTR = new float[Parts.Count*6];
            int[] PartInfo = new int[Parts.Count*3];
            */

            Vesout = new float[顶点列表.Count];
            Norout = new float[法线列表.Count];
            Texout = new float[纹理位置列表.Count];
            PartTR = new float[部件列表.Count * 6];
            PartInfo = new int[部件列表.Count * 3];

            for (int i = 0; i < 纹理位置列表.Count; i++)
            {
                Texout[i] = 纹理位置列表[i];
            }
            for (int i = 0; i < 顶点列表.Count; i++)
            {
                Vesout[i] = 顶点列表[i];
                Norout[i] = 法线列表[i];
            }

            tb关键帧.Visible = false;
            cboxPart.Items.Clear();
            cbox单独设置.Items.Clear();
            cboxPart.Items.Add("Show All: Vertices " + (顶点列表.Count / 3) + ", Parts: " + 部件列表.Count);
            cbox单独设置.Items.Add("");
            cboxPart.SelectedIndex = 0;
            for (int i = 0; i < 部件列表.Count; i++)
            {
                PartTR[i * 6 + 0] = 部件列表[i].初始位置.x;
                PartTR[i * 6 + 1] = 部件列表[i].初始位置.y;
                PartTR[i * 6 + 2] = 部件列表[i].初始位置.z;

                PartTR[i * 6 + 3] = 部件列表[i].初始旋转.x;
                PartTR[i * 6 + 4] = 部件列表[i].初始旋转.y;
                PartTR[i * 6 + 5] = 部件列表[i].初始旋转.z;

                PartInfo[i * 3] = 部件列表[i].子部件数;
                PartInfo[i * 3 + 1] = 部件列表[i].顶点起始索引;
                PartInfo[i * 3 + 2] = 部件列表[i].顶点数;

                /*cboxPart.Items.Add("部件" + i +
                                 ", 顶点数:" + 部件列表[i].顶点数 +
                                 ", 父:" + 部件列表[i].父部件索引 +
                                 ", 子:" + 部件列表[i].子部件数 +
                                 ", 位置:" + 部件列表[i].初始位置.x + ", " + 部件列表[i].初始位置.y + ", " + 部件列表[i].初始位置.z +
                                 ", 旋转:" + ((部件列表[i].初始旋转.x / Math.PI)*180f).ToString("f2") + ", " + ((部件列表[i].初始旋转.y / Math.PI)*180f).ToString("f2") + ", " + ((部件列表[i].初始旋转.z / Math.PI)*180f).ToString("f2") + 
                                 ";");*/
                cboxPart.Items.Add("mmbr" + i +
                                 ", Type:" + 获取部件类型名称(部件列表[i].部件类型) +
                                 ", Father:" + 部件列表[i].父部件索引 +
                                 ", Children:" + 部件列表[i].子部件数 +
                                 ", Animation Number:" + 部件列表[i].关键帧动画数  +
                                 ", Integer of 2:" + 部件列表[i].不明整数参数2 +
                                 ", Keyframes:" + 部件列表[i].关键帧数据.关键帧数 +
                                 ", Floating-Point 1:" + 部件列表[i].不明浮点参数1 +
                                 ";");
                cbox单独设置.Items.Add("member" + i);
            }
            cboxPart.SelectedIndex = 0;
            cbox单独设置.SelectedIndex = 0;


            Set3DData(Vesout, Norout, Vesout.Length, Texout, Texout.Length);
            SetPartData(PartTR, PartInfo, 部件列表.Count);

            RenderPart(0);

            //Verts.Clear();
            //Normals.Clear();
            //TexCoords.Clear();
            //Parts.Clear();

        }

        private Int32 RenderPart(Int32 PartID)
        {
            Int32 mNextID = PartID + 1;
            Int32 mSubCount = PartInfo[PartID*3];

            for (Int32 i = 0; i < mSubCount; i++)
            {
                mNextID = RenderPart(mNextID);
            }
            return mNextID;
        }



        private void cboxPart_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboxPart.SelectedIndex > 0)
            {
                Int32 sel = cboxPart.SelectedIndex - 1;
                if (sel > 部件列表.Count - 1)
                    sel = 部件列表.Count - 1;

                cbox单独设置.SelectedIndex = cboxPart.SelectedIndex;

                float[] mPartTR = new float[6];
                int[] mPartInfo = new int[3];

                mPartTR[0] = 部件列表[sel].初始位置.x;
                mPartTR[1] = 部件列表[sel].初始位置.y;
                mPartTR[2] = 部件列表[sel].初始位置.z;

                mPartTR[3] = 部件列表[sel].初始旋转.x;
                mPartTR[4] = 部件列表[sel].初始旋转.y;
                mPartTR[5] = 部件列表[sel].初始旋转.z;

                mPartInfo[0] = 0;
                mPartInfo[1] = 部件列表[sel].顶点起始索引;
                mPartInfo[2] = 部件列表[sel].顶点数;

                txt位置X.Text = 部件列表[sel].初始位置.x.ToString();
                txt位置Y.Text = 部件列表[sel].初始位置.y.ToString();
                txt位置Z.Text = 部件列表[sel].初始位置.z.ToString();

                txt旋转X.Text = 部件列表[sel].初始旋转.x.ToString();
                txt旋转Y.Text = 部件列表[sel].初始旋转.y.ToString();
                txt旋转Z.Text = 部件列表[sel].初始旋转.z.ToString();
                
                SetPartData(mPartTR, mPartInfo, 1);
            }
            else
            {
                SetPartData(PartTR, PartInfo, 部件列表.Count);
            }

        }
        public void Set3Dwin(Control control)
        {
            panel1.Controls.Add(control);
        }
        public void Unset3Dwin()
        {
            panel1.Controls.Clear();
        }

        private void btn应用位置旋转_Click(object sender, EventArgs e)
        {
            if (cbox单独设置.SelectedIndex > 0)
            {
                Int32 sel = cbox单独设置.SelectedIndex - 1;
                if (sel > 部件列表.Count - 1)
                    sel = 部件列表.Count - 1;

                PartTR[sel * 6 + 0] = Convert.ToSingle(txt位置X.Text);
                PartTR[sel * 6 + 1] = Convert.ToSingle(txt位置Y.Text);
                PartTR[sel * 6 + 2] = Convert.ToSingle(txt位置Z.Text);

                PartTR[sel * 6 + 3] = Convert.ToSingle(txt旋转X.Text);
                PartTR[sel * 6 + 4] = Convert.ToSingle(txt旋转Y.Text);
                PartTR[sel * 6 + 5] = Convert.ToSingle(txt旋转Z.Text);

                SetPartData(PartTR, PartInfo, 部件列表.Count);
            }
        }

        private void cbox单独设置_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ((cbox单独设置.SelectedIndex != cboxPart.SelectedIndex) && cbox单独设置.SelectedIndex != 0)
            {
                Int32 sel = cbox单独设置.SelectedIndex - 1;
                if (sel > 部件列表.Count - 1)
                    sel = 部件列表.Count - 1;
                if (sel > -1)
                {
                    txt部件类型.Text = 获取部件类型名称(部件列表[sel].部件类型);
                }
                else
                {
                    txt部件类型.Text = "";
                }

                float[] mPartTR = new float[6];
                int[] mPartInfo = new int[3];

                mPartTR[0] = 部件列表[sel].初始位置.x;
                mPartTR[1] = 部件列表[sel].初始位置.y;
                mPartTR[2] = 部件列表[sel].初始位置.z;

                mPartTR[3] = 部件列表[sel].初始旋转.x;
                mPartTR[4] = 部件列表[sel].初始旋转.y;
                mPartTR[5] = 部件列表[sel].初始旋转.z;

                mPartInfo[0] = 0;
                mPartInfo[1] = 部件列表[sel].顶点起始索引;
                mPartInfo[2] = 部件列表[sel].顶点数;

                txt位置X.Text = 部件列表[sel].初始位置.x.ToString();
                txt位置Y.Text = 部件列表[sel].初始位置.y.ToString();
                txt位置Z.Text = 部件列表[sel].初始位置.z.ToString();

                txt旋转X.Text = 部件列表[sel].初始旋转.x.ToString();
                txt旋转Y.Text = 部件列表[sel].初始旋转.y.ToString();
                txt旋转Z.Text = 部件列表[sel].初始旋转.z.ToString();

                if (部件列表[sel].关键帧动画数 > 0)
                {
                    tb关键帧.Enabled = true;
                    tb关键帧.Visible = true;
                }
                else
                {
                    tb关键帧.Enabled = false;
                    tb关键帧.Visible = false;
                }
            }
        }

        private void btn导出_Click(object sender, EventArgs e)
        {
            StreamWriter file = new System.IO.StreamWriter("C:\\Users\\Arthur\\geo.obj"); //Obj Exporter
            int count = 0;
            bool ligne = true;
            file.WriteLine("o acmodel");
            file.WriteLine();
            foreach (float s in 顶点列表)
            {
                if (ligne == true)
                {
                    count = 0;
                    file.Write("v " + s);
                    ligne = false;
                }
                else
                {
                    if (count<=1)
                    {
                        count++;
                        file.Write(" " + s);
                    }
                    else
                    {
                        ligne = true;
                        file.WriteLine();
                    }      
                }
            }
            file.Close();
        }

        private void tb关键帧_Scroll(object sender, EventArgs e)
        {
            if (cbox单独设置.SelectedIndex != 0)
            {
                Int32 sel = cbox单独设置.SelectedIndex - 1;
                if (sel > 部件列表.Count - 1)
                    sel = 部件列表.Count - 1;
                if (sel > -1)
                {
                    
                }
                else
                {
                    sel = 0;
                    tb关键帧.Visible = false;
                }
                Int32 当前部件类型 = 部件列表[sel].部件类型;

                for (sel = 0; sel < 部件列表.Count; sel++)
                {
                    if (部件列表[sel].关键帧动画数 > 0 && 部件列表[sel].部件类型 == 当前部件类型)
                    {
                        Single 当前帧 = Convert.ToSingle(tb关键帧.Value) / Convert.ToSingle(tb关键帧.Maximum);
                        for (Int32 i = 0; i < 部件列表[sel].关键帧数据.关键帧数; i++)
                        {
                            Single 关键帧阀值 = Convert.ToSingle(i) / Convert.ToSingle(部件列表[sel].关键帧数据.关键帧数);
                            if (当前帧 >= 关键帧阀值)
                            {
                                Single 过渡点 = (当前帧 - 关键帧阀值) * Convert.ToSingle(部件列表[sel].关键帧数据.关键帧数);
                                if (i == 部件列表[sel].关键帧数据.关键帧数 - 1)
                                {
                                    PartTR[sel * 6 + 0] = 部件列表[sel].关键帧数据.位置[i].x;
                                    PartTR[sel * 6 + 1] = 部件列表[sel].关键帧数据.位置[i].y;
                                    PartTR[sel * 6 + 2] = 部件列表[sel].关键帧数据.位置[i].z;

                                    PartTR[sel * 6 + 3] = 部件列表[sel].关键帧数据.旋转[i].x;
                                    PartTR[sel * 6 + 4] = 部件列表[sel].关键帧数据.旋转[i].y;
                                    PartTR[sel * 6 + 5] = 部件列表[sel].关键帧数据.旋转[i].z;
                                }
                                else
                                {
                                    PartTR[sel * 6 + 0] = 部件列表[sel].关键帧数据.位置[i].x + (部件列表[sel].关键帧数据.位置[i + 1].x - 部件列表[sel].关键帧数据.位置[i].x) * 过渡点;
                                    PartTR[sel * 6 + 1] = 部件列表[sel].关键帧数据.位置[i].y + (部件列表[sel].关键帧数据.位置[i + 1].y - 部件列表[sel].关键帧数据.位置[i].y) * 过渡点;
                                    PartTR[sel * 6 + 2] = 部件列表[sel].关键帧数据.位置[i].z + (部件列表[sel].关键帧数据.位置[i + 1].z - 部件列表[sel].关键帧数据.位置[i].z) * 过渡点;

                                    PartTR[sel * 6 + 3] = 部件列表[sel].关键帧数据.旋转[i].x + (部件列表[sel].关键帧数据.旋转[i + 1].x - 部件列表[sel].关键帧数据.旋转[i].x) * 过渡点;
                                    PartTR[sel * 6 + 4] = 部件列表[sel].关键帧数据.旋转[i].y + (部件列表[sel].关键帧数据.旋转[i + 1].y - 部件列表[sel].关键帧数据.旋转[i].y) * 过渡点;
                                    PartTR[sel * 6 + 5] = 部件列表[sel].关键帧数据.旋转[i].z + (部件列表[sel].关键帧数据.旋转[i + 1].z - 部件列表[sel].关键帧数据.旋转[i].z) * 过渡点;
                                }

                                txt位置X.Text = PartTR[sel * 6 + 0].ToString();
                                txt位置Y.Text = PartTR[sel * 6 + 1].ToString();
                                txt位置Z.Text = PartTR[sel * 6 + 2].ToString();

                                txt旋转X.Text = PartTR[sel * 6 + 3].ToString();
                                txt旋转Y.Text = PartTR[sel * 6 + 4].ToString();
                                txt旋转Z.Text = PartTR[sel * 6 + 5].ToString();

                                //break;
                            }
                        }
                    }
                }

                SetPartData(PartTR, PartInfo, 部件列表.Count);
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void txt部件类型_TextChanged(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void txt旋转Z_TextChanged(object sender, EventArgs e)
        {

        }

        private void txt旋转Y_TextChanged(object sender, EventArgs e)
        {

        }

        private void txt旋转X_TextChanged(object sender, EventArgs e)
        {

        }

        private void txt位置Z_TextChanged(object sender, EventArgs e)
        {

        }

        private void txt位置Y_TextChanged(object sender, EventArgs e)
        {

        }

        private void txt位置X_TextChanged(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }


    }
}
