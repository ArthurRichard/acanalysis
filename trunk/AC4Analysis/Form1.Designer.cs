namespace AC4Analysis
{
    partial class AC4Analysis
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AC4Analysis));
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.btn打开tbl = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tb绝对地址 = new System.Windows.Forms.TextBox();
            this.tb相对地址 = new System.Windows.Forms.TextBox();
            this.tb大小 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btn另存当前数据段 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.label4 = new System.Windows.Forms.Label();
            this.tbNote = new System.Windows.Forms.TextBox();
            this.btnSaveNote = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.treeView1.LabelEdit = true;
            this.treeView1.Location = new System.Drawing.Point(12, 12);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(308, 664);
            this.treeView1.TabIndex = 0;
            this.treeView1.DoubleClick += new System.EventHandler(this.treeView1_DoubleClick);
            // 
            // btn打开tbl
            // 
            this.btn打开tbl.Location = new System.Drawing.Point(326, 11);
            this.btn打开tbl.Name = "btn打开tbl";
            this.btn打开tbl.Size = new System.Drawing.Size(91, 23);
            this.btn打开tbl.TabIndex = 1;
            this.btn打开tbl.Text = "Open tbl File";
            this.btn打开tbl.UseVisualStyleBackColor = true;
            this.btn打开tbl.Click += new System.EventHandler(this.打开tbl_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(563, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "Address";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(715, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "SubAddress";
            // 
            // tb绝对地址
            // 
            this.tb绝对地址.Location = new System.Drawing.Point(609, 13);
            this.tb绝对地址.Name = "tb绝对地址";
            this.tb绝对地址.Size = new System.Drawing.Size(100, 21);
            this.tb绝对地址.TabIndex = 4;
            // 
            // tb相对地址
            // 
            this.tb相对地址.Location = new System.Drawing.Point(784, 11);
            this.tb相对地址.Name = "tb相对地址";
            this.tb相对地址.Size = new System.Drawing.Size(100, 21);
            this.tb相对地址.TabIndex = 5;
            // 
            // tb大小
            // 
            this.tb大小.Location = new System.Drawing.Point(929, 11);
            this.tb大小.Name = "tb大小";
            this.tb大小.Size = new System.Drawing.Size(100, 21);
            this.tb大小.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(894, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "Size";
            // 
            // btn另存当前数据段
            // 
            this.btn另存当前数据段.Location = new System.Drawing.Point(423, 11);
            this.btn另存当前数据段.Name = "btn另存当前数据段";
            this.btn另存当前数据段.Size = new System.Drawing.Size(109, 23);
            this.btn另存当前数据段.TabIndex = 9;
            this.btn另存当前数据段.Text = "Save Select Data";
            this.btn另存当前数据段.UseVisualStyleBackColor = true;
            this.btn另存当前数据段.Click += new System.EventHandler(this.btn另存当前数据段_Click);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.AutoScroll = true;
            this.panel1.Location = new System.Drawing.Point(327, 75);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(789, 629);
            this.panel1.TabIndex = 10;
            // 
            // progressBar1
            // 
            this.progressBar1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.progressBar1.Location = new System.Drawing.Point(13, 682);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(307, 22);
            this.progressBar1.TabIndex = 11;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(563, 43);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 12;
            this.label4.Text = "Note";
            // 
            // tbNote
            // 
            this.tbNote.Location = new System.Drawing.Point(610, 40);
            this.tbNote.Name = "tbNote";
            this.tbNote.Size = new System.Drawing.Size(100, 21);
            this.tbNote.TabIndex = 13;
            // 
            // btnSaveNote
            // 
            this.btnSaveNote.Location = new System.Drawing.Point(717, 37);
            this.btnSaveNote.Name = "btnSaveNote";
            this.btnSaveNote.Size = new System.Drawing.Size(75, 23);
            this.btnSaveNote.TabIndex = 14;
            this.btnSaveNote.Text = "Save Note";
            this.btnSaveNote.UseVisualStyleBackColor = true;
            this.btnSaveNote.Click += new System.EventHandler(this.btnSaveNote_Click);
            // 
            // AC4Analysis
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1124, 716);
            this.Controls.Add(this.btnSaveNote);
            this.Controls.Add(this.tbNote);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btn另存当前数据段);
            this.Controls.Add(this.tb大小);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tb相对地址);
            this.Controls.Add(this.tb绝对地址);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn打开tbl);
            this.Controls.Add(this.treeView1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "AC4Analysis";
            this.Text = "AC4Analysis v1.7.0";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AC4Analysis_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.Button btn打开tbl;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tb绝对地址;
        private System.Windows.Forms.TextBox tb相对地址;
        private System.Windows.Forms.TextBox tb大小;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btn另存当前数据段;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tbNote;
        private System.Windows.Forms.Button btnSaveNote;
    }
}

