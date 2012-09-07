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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cb光源开关 = new System.Windows.Forms.CheckBox();
            this.cb透明开关 = new System.Windows.Forms.CheckBox();
            this.btn重置视角 = new System.Windows.Forms.Button();
            this.rdbView模式选择1 = new System.Windows.Forms.RadioButton();
            this.rdbView模式选择2 = new System.Windows.Forms.RadioButton();
            this.tp观察模式操作说明 = new System.Windows.Forms.ToolTip(this.components);
            this.tp飞行模式操作说明 = new System.Windows.Forms.ToolTip(this.components);
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(4, 4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(639, 480);
            this.panel1.TabIndex = 8;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(139, 490);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(47, 21);
            this.textBox1.TabIndex = 10;
            this.textBox1.Text = "1.0";
            this.textBox1.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBox1_KeyUp);
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
            // btn重置视角
            // 
            this.btn重置视角.Location = new System.Drawing.Point(111, 518);
            this.btn重置视角.Name = "btn重置视角";
            this.btn重置视角.Size = new System.Drawing.Size(75, 23);
            this.btn重置视角.TabIndex = 14;
            this.btn重置视角.Text = "Reset view";
            this.btn重置视角.UseVisualStyleBackColor = true;
            this.btn重置视角.Click += new System.EventHandler(this.btn重置视角_Click);
            // 
            // rdbView模式选择1
            // 
            this.rdbView模式选择1.AutoSize = true;
            this.rdbView模式选择1.Checked = true;
            this.rdbView模式选择1.Location = new System.Drawing.Point(196, 494);
            this.rdbView模式选择1.Name = "rdbView模式选择1";
            this.rdbView模式选择1.Size = new System.Drawing.Size(77, 16);
            this.rdbView模式选择1.TabIndex = 15;
            this.rdbView模式选择1.TabStop = true;
            this.rdbView模式选择1.Text = "View mode";
            this.rdbView模式选择1.UseVisualStyleBackColor = true;
            this.rdbView模式选择1.CheckedChanged += new System.EventHandler(this.rdbView模式选择1_CheckedChanged);
            // 
            // rdbView模式选择2
            // 
            this.rdbView模式选择2.AutoSize = true;
            this.rdbView模式选择2.Location = new System.Drawing.Point(196, 517);
            this.rdbView模式选择2.Name = "rdbView模式选择2";
            this.rdbView模式选择2.Size = new System.Drawing.Size(77, 16);
            this.rdbView模式选择2.TabIndex = 16;
            this.rdbView模式选择2.Text = "Free mode";
            this.rdbView模式选择2.UseVisualStyleBackColor = true;
            this.rdbView模式选择2.CheckedChanged += new System.EventHandler(this.rdbView模式选择2_CheckedChanged);
            // 
            // tp观察模式操作说明
            // 
            this.tp观察模式操作说明.AutoPopDelay = 5000;
            this.tp观察模式操作说明.InitialDelay = 200;
            this.tp观察模式操作说明.ReshowDelay = 100;
            // 
            // tp飞行模式操作说明
            // 
            this.tp飞行模式操作说明.AutoPopDelay = 5000;
            this.tp飞行模式操作说明.InitialDelay = 200;
            this.tp飞行模式操作说明.ReshowDelay = 100;
            // 
            // Win3D
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rdbView模式选择2);
            this.Controls.Add(this.rdbView模式选择1);
            this.Controls.Add(this.btn重置视角);
            this.Controls.Add(this.cb透明开关);
            this.Controls.Add(this.cb光源开关);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.panel1);
            this.Name = "Win3D";
            this.Size = new System.Drawing.Size(646, 546);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox cb光源开关;
        private System.Windows.Forms.CheckBox cb透明开关;
        private System.Windows.Forms.Button btn重置视角;
        private System.Windows.Forms.RadioButton rdbView模式选择1;
        private System.Windows.Forms.RadioButton rdbView模式选择2;
        private System.Windows.Forms.ToolTip tp观察模式操作说明;
        private System.Windows.Forms.ToolTip tp飞行模式操作说明;
    }
}
