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
            this.panel1 = new System.Windows.Forms.Panel();
            this.timer旋转停止 = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cb光源开关 = new System.Windows.Forms.CheckBox();
            this.cb透明开关 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
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
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(428, 495);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(215, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "Drag mouse right key to change view";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(139, 490);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(47, 21);
            this.textBox1.TabIndex = 10;
            this.textBox1.Text = "10.0";
            this.textBox1.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBox1_KeyUp);
            this.textBox1.MouseLeave += new System.EventHandler(this.textBox1_MouseLeave);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(74, 495);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 11;
            this.label2.Text = "Move step:";
            // 
            // cb光源开关
            // 
            this.cb光源开关.AutoSize = true;
            this.cb光源开关.Location = new System.Drawing.Point(14, 494);
            this.cb光源开关.Name = "cb光源开关";
            this.cb光源开关.Size = new System.Drawing.Size(54, 16);
            this.cb光源开关.TabIndex = 12;
            this.cb光源开关.Text = "Light";
            this.cb光源开关.UseVisualStyleBackColor = true;
            this.cb光源开关.CheckedChanged += new System.EventHandler(this.cb光源开关_CheckedChanged);
            // 
            // cb透明开关
            // 
            this.cb透明开关.AutoSize = true;
            this.cb透明开关.Location = new System.Drawing.Point(14, 518);
            this.cb透明开关.Name = "cb透明开关";
            this.cb透明开关.Size = new System.Drawing.Size(90, 16);
            this.cb透明开关.TabIndex = 13;
            this.cb透明开关.Text = "Transparent";
            this.cb透明开关.UseVisualStyleBackColor = true;
            this.cb透明开关.CheckedChanged += new System.EventHandler(this.cb透明开关_CheckedChanged);
            // 
            // Win3D
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.cb透明开关);
            this.Controls.Add(this.cb光源开关);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.panel1);
            this.Name = "Win3D";
            this.Size = new System.Drawing.Size(646, 546);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Timer timer旋转停止;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox cb光源开关;
        private System.Windows.Forms.CheckBox cb透明开关;
    }
}
