using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
namespace AC4Analysis
{
    public struct _L1
    {
        public uint add;
        public uint size;
    }
    public partial class AC4Analysis : Form
    {
        public enum _Mode
        {
            AC4,
            AC0
        }
        public AC4Analysis()
        {
            InitializeComponent();
            Notes.load();
            InitRenderThread(smwin.GetHwnd());
        }
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitRenderThread(IntPtr hwnd);
        [DllImport("AC4_3DWIN.DLL", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CloseRenderThread();
        uint culsize = 0;
        uint culadd = 0;
        public string cdpfilename;
        public byte[] culdata;
        GIM gimwin = new GIM();
        SM smwin = new SM();
        EE eewin = new EE();
        Text textwin = new Text();
        map mapwin = new map();
        public static _Mode mode = _Mode.AC4;
        private void 打开tbl_Click(object sender, EventArgs e)
        {
           // try
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.FileName = "Data.TBL";
                if (!ofd.ShowDialog().Equals(DialogResult.OK))
                    return;
                cdpfilename = System.IO.Path.GetDirectoryName(ofd.FileName) + "\\" + System.IO.Path.GetFileNameWithoutExtension(ofd.FileName) + ".cdp";
                if (!File.Exists(cdpfilename))
                {
                    mode = _Mode.AC0;
                    cdpfilename = System.IO.Path.GetDirectoryName(ofd.FileName) + "\\" + System.IO.Path.GetFileNameWithoutExtension(ofd.FileName) + ".pac";
                    if (!File.Exists(cdpfilename))
                    {
                        MessageBox.Show("未找到tbl对应的data文件");
                        return;
                    }
                }
                else
                    mode = _Mode.AC4;
                if (string.IsNullOrEmpty(cdpfilename))
                {
                    MessageBox.Show("未打开TBL");
                    return;
                }
                FileStream fs = new FileStream(ofd.FileName, FileMode.Open);
                BinaryReader br = new BinaryReader(fs);
                FileInfo fileInfo = new FileInfo(ofd.FileName);
                FileStream fsc = new FileStream(cdpfilename, FileMode.Open);
                BinaryReader brc = new BinaryReader(fsc);

                uint L1Size = (uint)fileInfo.Length / 8;
                if (mode == _Mode.AC0)
                {
                    L1Size = br.ReadUInt32();
                    br.ReadUInt32();
                }
                for (int i = 0; i < L1Size; i++)
                {
                    _L1 L1 = new _L1();
                    if (mode == _Mode.AC4)
                        L1.add = br.ReadUInt32() * 0x800;
                    else
                        L1.add = br.ReadUInt32();
                    L1.size = br.ReadUInt32();
                    TreeNode tn = new TreeNode();
                    tn.Name = L1.add.ToString();
                    tn.Text = string.Format("{0:X8}", L1.add);
                    tn.Tag = L1;
                    uint subNum = CheckAddList(L1.add, L1.size, brc, tn);
                    if (subNum > 0)
                        tn.Text = string.Format("{0:X8} {1} {2}", L1.add, subNum, Notes.Get(L1.add));
                    treeView1.Nodes.Add(tn);
                    progressBar1.Value =  i*100 / (int)L1Size;
                }
                fs.Close();
                fsc.Close();
                progressBar1.Value = 100;
            }
            //catch (Exception error)
            //{
            //    MessageBox.Show(error.Message);
            //}
        }
        bool isEE(byte[] Data, int size)
        {
            if (size < 0x70)
                return false;
            int EEsize = (Data[0] + Data[1] * 0x100 + Data[2] * 0x10000)*0x10+0x20;
            if (EEsize != size)
                return false;
            else
                return true;
        }
        string GetDataHead(uint add, int size, BinaryReader brc)
        {
            brc.BaseStream.Seek(add, SeekOrigin.Begin);
            byte[] Data = new byte[4];
            brc.BaseStream.Read(Data, 0, 4);
            string Head = System.Text.Encoding.ASCII.GetString(Data, 0, 4).ToString(); 
            switch (Head)
            {
                case "SM \0":
                    {
                        return "SM";
                    }
                case "GIM\0":
                    {
                        return "GIM";
                    }
            }
            if (isEE(Data, size))
                return "Images";
            return "";
        }
        byte[] GetNextNodeData(TreeNode node)
        {
            if (node.NextNode == null)
                return null;
            _L1 tmp = (_L1)node.NextNode.Tag;
            TreeNode pnode = node.NextNode.Parent;
            uint totaladd = tmp.add;
            while (pnode != null)
            {
                _L1 tmpp = (_L1)pnode.Tag;
                totaladd += tmpp.add;
                pnode = pnode.Parent;
            }
            FileStream fsc = new FileStream(cdpfilename, FileMode.Open);
            byte[] NextNodeData = new byte[(int)tmp.size];
            fsc.Seek((int)totaladd, SeekOrigin.Begin);
            fsc.Read(NextNodeData, 0, (int)tmp.size);
            fsc.Close();
            return NextNodeData;
        }
        private void treeView1_DoubleClick(object sender, EventArgs e)
        {
            if (treeView1.SelectedNode == null)
                return;
            panel1.VerticalScroll.Value = 0;
            panel1.HorizontalScroll.Value = 0;
            _L1 tmp = (_L1)treeView1.SelectedNode.Tag;
            culsize = tmp.size;
            tb大小.Text = string.Format("{0:X8}",tmp.size);
            tb相对地址.Text = string.Format("{0:X8}", tmp.add);
            TreeNode pnode = treeView1.SelectedNode.Parent;
            uint totaladd = tmp.add;
            while (pnode != null)
            {
                _L1 tmpp = (_L1)pnode.Tag;
                totaladd += tmpp.add;
                pnode = pnode.Parent;
            }
            culadd = totaladd;
            tb绝对地址.Text = string.Format("{0:X8}", totaladd);
            FileStream fsc = new FileStream(cdpfilename, FileMode.Open);
            culdata = new byte[culsize];
            fsc.Seek((int)culadd, SeekOrigin.Begin);
            fsc.Read(culdata, 0, (int)culsize);
            fsc.Close();

            panel1.Controls.Clear();
            mapwin.CulData = culdata;
            if (mapwin.Check(treeView1.SelectedNode))
            {
                panel1.Controls.Add(mapwin);
                return;
            }
            string Head = System.Text.Encoding.ASCII.GetString(culdata,0,4).ToString();
            switch (Head)
            {
                case "SM \0":
                    {
                        smwin.data = culdata;
                        smwin.Analysis_SM();
                        panel1.Controls.Add(smwin);
                        return;
                    }
                case "GIM\0":
                    {
                        textwin = new Text();
                        if (textwin.check(culdata))
                        {
                            textwin.TextData = GetNextNodeData(treeView1.SelectedNode);
                            textwin.FontData = culdata;
                            textwin.Analysis();
                            panel1.Controls.Add(textwin);
                            return;
                        }
                        gimwin.data = culdata;
                        gimwin.Analysis_GIM();
                        gimwin.add = totaladd;
                        gimwin.cdpfilename = cdpfilename;
                        panel1.Controls.Add(gimwin);
                        return;
                    }
            }
            if (culsize>0x70)
            if (isEE(culdata, (int)culsize))
            {
                eewin = new EE();
                eewin.data = culdata;
                eewin.Analysis_EE();
                panel1.Controls.Add(eewin);
                return;
            }
        }
        private uint CheckAddList(uint add, uint size, BinaryReader brc, TreeNode pnode)
        {
            brc.BaseStream.Seek(add, SeekOrigin.Begin);
            uint subNum = brc.ReadUInt32();
            if (subNum == 0xFFFFFFFF)
                return 0;
            if (subNum == 0)
                return 0;
            if (subNum * 4 > size)
                return 0;
            uint lastAdd = 0;
            for (int i = 0; i < subNum; i++)
            {
                uint culadd = brc.ReadUInt32();
                if (culadd == 0)
                    continue;
                if (culadd < lastAdd)
                    return 0;
                if (culadd < (subNum * 4 + 4))
                    return 0;
                if (culadd >= size)
                    return 0;
                if (culadd == 0xFFFFFFFF)
                    return 0;
                lastAdd = culadd;
            }
            brc.BaseStream.Seek(add, SeekOrigin.Begin);
            subNum = brc.ReadUInt32();
            TreeNode[] nodes = new TreeNode[subNum];
            for (int i = 0; i < subNum; i++)
            {
                brc.BaseStream.Seek(add + i * 4 + 4, SeekOrigin.Begin);
                uint culadd = brc.ReadUInt32();
                if (lastAdd == 0)
                {
                    lastAdd = culadd;
                    continue;
                }
                if (i != 0)
                {
                    _L1 tmp = new _L1();
                    tmp.add = lastAdd;
                    tmp.size = culadd - lastAdd;
                    if (tmp.size == 0)
                    {
                        lastAdd = culadd;
                        continue;
                    }
                    nodes[i - 1] = new TreeNode();

                    uint subNum2 = CheckAddList(tmp.add + add, tmp.size, brc, nodes[i - 1]);
                    nodes[i - 1].Name = tmp.add.ToString();

                    nodes[i - 1].Text = string.Format("{0:X8},{1} {2} {3}", tmp.add, subNum2, GetDataHead(add + tmp.add, (int)tmp.size, brc), Notes.Get(add + tmp.add));

                    nodes[i - 1].Tag = tmp;
                }
                lastAdd = culadd;
            }
            if (lastAdd != 0)
            {
                _L1 tmp2 = new _L1();
                tmp2.add = lastAdd;
                tmp2.size = size - lastAdd;
                nodes[subNum - 1] = new TreeNode();
                uint subNum3 = CheckAddList(tmp2.add + add, tmp2.size, brc, nodes[subNum - 1]);
                nodes[subNum - 1].Name = tmp2.add.ToString();
                nodes[subNum - 1].Text = string.Format("{0:X8},{1} {2} {3}", tmp2.add, subNum3, GetDataHead(add + tmp2.add, (int)tmp2.size, brc), Notes.Get(add + tmp2.add));
                nodes[subNum - 1].Tag = tmp2;
            }
            foreach (TreeNode node in nodes)
            {
                if (node!=null)
                pnode.Nodes.Add(node);
            }
            return subNum;
        }

        private void btn另存当前数据段_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(cdpfilename))
            {
                MessageBox.Show("未打开TBL");
                return;
            }
            if (culsize == 0)
                return;
            FileStream fsc = new FileStream(cdpfilename, FileMode.Open);
            byte [] saveFile=new byte[culsize];
            fsc.Seek((int)culadd, SeekOrigin.Begin);
            fsc.Read(saveFile,0 , (int)culsize);
            fsc.Close();
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.FileName = tb绝对地址.Text;
            if (!sfd.ShowDialog().Equals(DialogResult.OK))
                return;
            FileStream fs = new FileStream(sfd.FileName, FileMode.Create);
            fs.Write(saveFile, 0,(int) culsize);
            fs.Close();
        }

        private void btnSaveNote_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(tbNote.Text))
                return;
            Notes.Set(tb绝对地址.Text, tbNote.Text);
            Notes.Save();
            treeView1.SelectedNode.Text += tbNote.Text;
        }

        private void AC4Analysis_FormClosing(object sender, FormClosingEventArgs e)
        {
            CloseRenderThread();
        }
    }
}
