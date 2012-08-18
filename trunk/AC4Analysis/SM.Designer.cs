namespace AC4Analysis
{
    partial class SM
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.btn开关灯 = new System.Windows.Forms.Button();
            this.btn开关透明 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(3, 32);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(650, 490);
            this.panel1.TabIndex = 0;
            // 
            // btn开关灯
            // 
            this.btn开关灯.Location = new System.Drawing.Point(3, 3);
            this.btn开关灯.Name = "btn开关灯";
            this.btn开关灯.Size = new System.Drawing.Size(112, 23);
            this.btn开关灯.TabIndex = 1;
            this.btn开关灯.Text = "button1";
            this.btn开关灯.UseVisualStyleBackColor = true;
            this.btn开关灯.Click += new System.EventHandler(this.btn开关灯_Click);
            // 
            // btn开关透明
            // 
            this.btn开关透明.Location = new System.Drawing.Point(121, 3);
            this.btn开关透明.Name = "btn开关透明";
            this.btn开关透明.Size = new System.Drawing.Size(126, 23);
            this.btn开关透明.TabIndex = 2;
            this.btn开关透明.Text = "button1";
            this.btn开关透明.UseVisualStyleBackColor = true;
            this.btn开关透明.Click += new System.EventHandler(this.btn开关透明_Click);
            // 
            // SM
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btn开关透明);
            this.Controls.Add(this.btn开关灯);
            this.Controls.Add(this.panel1);
            this.Name = "SM";
            this.Size = new System.Drawing.Size(663, 528);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btn开关灯;
        private System.Windows.Forms.Button btn开关透明;

    }
}
