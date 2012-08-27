namespace AC4Analysis
{
    partial class Win3D
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

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btn开关透明 = new System.Windows.Forms.Button();
            this.btn开关灯 = new System.Windows.Forms.Button();
            this.btn向左旋转 = new System.Windows.Forms.Button();
            this.btn向上旋转 = new System.Windows.Forms.Button();
            this.btn向右旋转 = new System.Windows.Forms.Button();
            this.btn向下旋转 = new System.Windows.Forms.Button();
            this.btn拉近 = new System.Windows.Forms.Button();
            this.btn拉远 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.timer旋转停止 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // btn开关透明
            // 
            this.btn开关透明.Location = new System.Drawing.Point(4, 487);
            this.btn开关透明.Name = "btn开关透明";
            this.btn开关透明.Size = new System.Drawing.Size(124, 23);
            this.btn开关透明.TabIndex = 0;
            this.btn开关透明.Text = "button1";
            this.btn开关透明.UseVisualStyleBackColor = true;
            this.btn开关透明.Click += new System.EventHandler(this.btn开关透明_Click);
            // 
            // btn开关灯
            // 
            this.btn开关灯.Location = new System.Drawing.Point(4, 458);
            this.btn开关灯.Name = "btn开关灯";
            this.btn开关灯.Size = new System.Drawing.Size(124, 23);
            this.btn开关灯.TabIndex = 1;
            this.btn开关灯.Text = "button2";
            this.btn开关灯.UseVisualStyleBackColor = true;
            this.btn开关灯.Click += new System.EventHandler(this.btn开关灯_Click);
            // 
            // btn向左旋转
            // 
            this.btn向左旋转.Location = new System.Drawing.Point(144, 475);
            this.btn向左旋转.Name = "btn向左旋转";
            this.btn向左旋转.Size = new System.Drawing.Size(44, 23);
            this.btn向左旋转.TabIndex = 2;
            this.btn向左旋转.Text = "Left";
            this.btn向左旋转.UseVisualStyleBackColor = true;
            this.btn向左旋转.Click += new System.EventHandler(this.btn向左旋转_Click);
            // 
            // btn向上旋转
            // 
            this.btn向上旋转.Location = new System.Drawing.Point(194, 458);
            this.btn向上旋转.Name = "btn向上旋转";
            this.btn向上旋转.Size = new System.Drawing.Size(42, 23);
            this.btn向上旋转.TabIndex = 3;
            this.btn向上旋转.Text = "Up";
            this.btn向上旋转.UseVisualStyleBackColor = true;
            this.btn向上旋转.Click += new System.EventHandler(this.btn向上旋转_Click);
            // 
            // btn向右旋转
            // 
            this.btn向右旋转.Location = new System.Drawing.Point(242, 475);
            this.btn向右旋转.Name = "btn向右旋转";
            this.btn向右旋转.Size = new System.Drawing.Size(45, 23);
            this.btn向右旋转.TabIndex = 4;
            this.btn向右旋转.Text = "Right";
            this.btn向右旋转.UseVisualStyleBackColor = true;
            this.btn向右旋转.Click += new System.EventHandler(this.btn向右旋转_Click);
            // 
            // btn向下旋转
            // 
            this.btn向下旋转.Location = new System.Drawing.Point(194, 487);
            this.btn向下旋转.Name = "btn向下旋转";
            this.btn向下旋转.Size = new System.Drawing.Size(42, 23);
            this.btn向下旋转.TabIndex = 5;
            this.btn向下旋转.Text = "Down";
            this.btn向下旋转.UseVisualStyleBackColor = true;
            this.btn向下旋转.Click += new System.EventHandler(this.btn向下旋转_Click);
            // 
            // btn拉近
            // 
            this.btn拉近.Location = new System.Drawing.Point(293, 458);
            this.btn拉近.Name = "btn拉近";
            this.btn拉近.Size = new System.Drawing.Size(45, 23);
            this.btn拉近.TabIndex = 6;
            this.btn拉近.Text = "Near";
            this.btn拉近.UseVisualStyleBackColor = true;
            this.btn拉近.Click += new System.EventHandler(this.btn拉近_Click);
            // 
            // btn拉远
            // 
            this.btn拉远.Location = new System.Drawing.Point(293, 487);
            this.btn拉远.Name = "btn拉远";
            this.btn拉远.Size = new System.Drawing.Size(45, 23);
            this.btn拉远.TabIndex = 7;
            this.btn拉远.Text = "Far";
            this.btn拉远.UseVisualStyleBackColor = true;
            this.btn拉远.Click += new System.EventHandler(this.btn拉远_Click);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(4, 4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(540, 448);
            this.panel1.TabIndex = 8;
            // 
            // timer旋转停止
            // 
            this.timer旋转停止.Interval = 250;
            this.timer旋转停止.Tick += new System.EventHandler(this.timer旋转停止_Tick);
            // 
            // Win3D
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btn拉远);
            this.Controls.Add(this.btn拉近);
            this.Controls.Add(this.btn向下旋转);
            this.Controls.Add(this.btn向右旋转);
            this.Controls.Add(this.btn向上旋转);
            this.Controls.Add(this.btn向左旋转);
            this.Controls.Add(this.btn开关灯);
            this.Controls.Add(this.btn开关透明);
            this.Name = "Win3D";
            this.Size = new System.Drawing.Size(562, 513);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn开关透明;
        private System.Windows.Forms.Button btn开关灯;
        private System.Windows.Forms.Button btn向左旋转;
        private System.Windows.Forms.Button btn向上旋转;
        private System.Windows.Forms.Button btn向右旋转;
        private System.Windows.Forms.Button btn向下旋转;
        private System.Windows.Forms.Button btn拉近;
        private System.Windows.Forms.Button btn拉远;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Timer timer旋转停止;
    }
}
