using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace AC4Analysis
{
    public partial class map : UserControl
    {
        public map()
        {
            InitializeComponent();
        }
        public byte[] CulData;
        List<ushort[]> SubMapList = new List<ushort[]>();
        Bitmap[] Texs;
        Color[] pal = new Color[256];
        public bool Check(TreeNode node)
        {
            if (node.Parent != null)
                return false;
            if (node.Nodes.Count != 36)
                return false;
            TreeNode SubMapNode = node.Nodes[5];
            GetSubMapList(SubMapNode);
            TreeNode SubMapIDNode = node.Nodes[6];
            TreeNode TexsNode = node.Nodes[7];
            GetTexs(TexsNode.Nodes[0]);
            TreeNode MapPalNode = node.Nodes[8];
            return true;
        }
        void GetSubMapList(TreeNode node)
        {
            _L1 tmp = (_L1)node.Tag;
            int add = (int)tmp.add;
            int SubMapCount = (int)tmp.size / 0x200;
            for (int i = 0; i < SubMapCount; i++)
            {
                ushort[] SubMap = new ushort[0x100];
                for (int j = 0; j < 0x100; j++)
                {
                    SubMap[j] = (ushort)(CulData[add + i + 0x200 + j * 2] + (CulData[add + i + 0x200 + j * 2 + 1] - 0x10) * 0x100);
                }
                SubMapList.Add(SubMap);
            }
        }
        void GetTexs(TreeNode node)
        { 
        }
    }
}
