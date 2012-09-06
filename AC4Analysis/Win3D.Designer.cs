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
            this.panel1 = new System.Windows.Forms.Panel();
            this.timer旋转停止 = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btn开关透明
            // 
            this.btn开关透明.Location = new System.Drawing.Point(4, 519);
            this.btn开关透明.Name = "btn开关透明";
            this.btn开关透明.Size = new System.Drawing.Size(124, 23);
            this.btn开关透明.TabIndex = 0;
            this.btn开关透明.Text = "button1";
            this.btn开关透明.UseVisualStyleBackColor = true;
            this.btn开关透明.Click += new System.EventHandler(this.btn开关透明_Click);
            // 
            // btn开关灯
            // 
            this.btn开关灯.Location = new System.Drawing.Point(4, 490);
            this.btn开关灯.Name = "btn开关灯";
            this.btn开关灯.Size = new System.Drawing.Size(124, 23);
            this.btn开关灯.TabIndex = 1;
            this.btn开关灯.Text = "button2";
            this.btn开关灯.UseVisualStyleBackColor = true;
            this.btn开关灯.Click += new System.EventHandler(this.btn开关灯_Click);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(4, 4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(639, 480);
            this.panel1.TabIndex = 8;
            // 
            // timer旋转停止
            // 
            this.timer旋转停止.Interval = 250;
            this.timer旋转停止.Tick += new System.EventHandler(this.timer旋转停止_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(135, 491);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(215, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "Drag mouse right key to change view";
            // 
            // Win3D
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btn开关灯);
            this.Controls.Add(this.btn开关透明);
            this.Name = "Win3D";
            this.Size = new System.Drawing.Size(646, 546);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn开关透明;
        private System.Windows.Forms.Button btn开关灯;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Timer timer旋转停止;
        private System.Windows.Forms.Label label1;
    }
}
