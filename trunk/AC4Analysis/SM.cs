using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

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
            public Int32 不明整数参数1;     // 不明 多为0x00
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
                //初始旋转.x = -初始旋转.x;
                //初始旋转.y = -初始旋转.y;


                关键帧动画信息偏址 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20);
                网格数据列表偏址 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20 + 4);
                不明浮点参数1 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20 + 8);
                不明整数参数1 = BitConverter.ToInt32(_数据, _起始偏址 + 0x20 + 12);

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
            cboxPart.Items.Clear();
            cboxPart.Items.Add("整体显示, 顶点:" + (顶点列表.Count / 3) + ", 部件:" + 顶点列表.Count);
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

                cboxPart.Items.Add("部件" + i +
                                 ", 顶点数:" + 部件列表[i].顶点数 +
                                 ", 父:" + 部件列表[i].父部件索引 +
                                 ", 子:" + 部件列表[i].子部件数 +
                                 ", 位置:" + 部件列表[i].初始位置.x + ", " + 部件列表[i].初始位置.y + ", " + 部件列表[i].初始位置.z +
                                 ", 旋转:" + ((部件列表[i].初始旋转.x / Math.PI)*180f).ToString("f2") + ", " + ((部件列表[i].初始旋转.y / Math.PI)*180f).ToString("f2") + ", " + ((部件列表[i].初始旋转.z / Math.PI)*180f).ToString("f2") + 
                                 ";");
                cbox单独设置.Items.Add("部件" + i);
            }



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
            }
        }

        private void btn导出_Click(object sender, EventArgs e)
        {  
            //OpenFileDialog 打开文件对话框 = new OpenFileDialog();
            
        }


    }
}
