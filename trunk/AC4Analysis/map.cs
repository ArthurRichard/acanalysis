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
            TreeNode MapPalNode = node.Nodes[8];
            return true;
        }
        void GetSubMapList(TreeNode node)
        { 
        }
    }
}
