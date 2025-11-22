namespace Opt
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            label2 = new Label();
            textBox3 = new TextBox();
            label3 = new Label();
            textBox4 = new TextBox();
            label4 = new Label();
            textBox5 = new TextBox();
            label5 = new Label();
            checkBox1 = new CheckBox();
            textBox6 = new TextBox();
            label6 = new Label();
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            button4 = new Button();
            textBox7 = new TextBox();
            label7 = new Label();
            checkBox2 = new CheckBox();
            label8 = new Label();
            checkBox3 = new CheckBox();
            checkBox4 = new CheckBox();
            sendImagePossibly = new TrackBar();
            label9 = new Label();
            Vs = new Label();
            checkBox5 = new CheckBox();
            button5 = new Button();
            label10 = new Label();
            folderBrowserDialog1 = new FolderBrowserDialog();
            textBox8 = new TextBox();
            ((System.ComponentModel.ISupportInitialize)sendImagePossibly).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(56, 53);
            label1.Name = "label1";
            label1.Size = new Size(96, 28);
            label1.TabIndex = 0;
            label1.Text = "窗口宽度";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(158, 50);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(89, 34);
            textBox1.TabIndex = 1;
            textBox1.TextChanged += textBox1_TextChanged;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(355, 50);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(92, 34);
            textBox2.TabIndex = 3;
            textBox2.TextChanged += textBox2_TextChanged;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(253, 50);
            label2.Name = "label2";
            label2.Size = new Size(96, 28);
            label2.TabIndex = 2;
            label2.Text = "窗口高度";
            // 
            // textBox3
            // 
            textBox3.Location = new Point(158, 95);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(333, 34);
            textBox3.TabIndex = 5;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(56, 95);
            label3.Name = "label3";
            label3.Size = new Size(96, 28);
            label3.TabIndex = 4;
            label3.Text = "模型名称";
            // 
            // textBox4
            // 
            textBox4.Location = new Point(158, 280);
            textBox4.Name = "textBox4";
            textBox4.PasswordChar = '·';
            textBox4.Size = new Size(333, 34);
            textBox4.TabIndex = 7;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(56, 283);
            label4.Name = "label4";
            label4.Size = new Size(84, 28);
            label4.TabIndex = 6;
            label4.Text = "APIKEY";
            // 
            // textBox5
            // 
            textBox5.Location = new Point(158, 327);
            textBox5.Name = "textBox5";
            textBox5.Size = new Size(220, 34);
            textBox5.TabIndex = 9;
            textBox5.TextChanged += textBox5_TextChanged;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(56, 330);
            label5.Name = "label5";
            label5.Size = new Size(75, 28);
            label5.TabIndex = 8;
            label5.Text = "服务器";
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Location = new Point(384, 329);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(107, 32);
            checkBox1.TabIndex = 10;
            checkBox1.Text = "ollama";
            checkBox1.UseVisualStyleBackColor = true;
            checkBox1.CheckedChanged += checkBox1_CheckedChanged;
            // 
            // textBox6
            // 
            textBox6.Location = new Point(529, 71);
            textBox6.Multiline = true;
            textBox6.Name = "textBox6";
            textBox6.Size = new Size(541, 566);
            textBox6.TabIndex = 12;
            textBox6.TextChanged += textBox6_TextChanged;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(529, 40);
            label6.Name = "label6";
            label6.Size = new Size(96, 28);
            label6.TabIndex = 11;
            label6.Text = "提示文本";
            // 
            // button1
            // 
            button1.Location = new Point(56, 564);
            button1.Name = "button1";
            button1.Size = new Size(118, 42);
            button1.TabIndex = 13;
            button1.Text = "确定";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(180, 564);
            button2.Name = "button2";
            button2.Size = new Size(118, 42);
            button2.TabIndex = 14;
            button2.Text = "应用";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // button3
            // 
            button3.Location = new Point(304, 564);
            button3.Name = "button3";
            button3.Size = new Size(118, 42);
            button3.TabIndex = 15;
            button3.Text = "取消";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button4
            // 
            button4.Location = new Point(56, 621);
            button4.Name = "button4";
            button4.Size = new Size(242, 42);
            button4.TabIndex = 16;
            button4.Text = "清理图片缓存";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // textBox7
            // 
            textBox7.Location = new Point(158, 373);
            textBox7.Name = "textBox7";
            textBox7.Size = new Size(89, 34);
            textBox7.TabIndex = 18;
            textBox7.TextChanged += textBox7_TextChanged;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(56, 376);
            label7.Name = "label7";
            label7.Size = new Size(96, 28);
            label7.TabIndex = 17;
            label7.Text = "滚动次数";
            // 
            // checkBox2
            // 
            checkBox2.AutoSize = true;
            checkBox2.Location = new Point(56, 426);
            checkBox2.Name = "checkBox2";
            checkBox2.Size = new Size(122, 32);
            checkBox2.TabIndex = 19;
            checkBox2.Text = "包含图片";
            checkBox2.UseVisualStyleBackColor = true;
            checkBox2.CheckedChanged += checkBox2_CheckedChanged;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(203, 426);
            label8.Name = "label8";
            label8.Size = new Size(274, 28);
            label8.TabIndex = 20;
            label8.Text = "图片放置在Images文件夹下";
            // 
            // checkBox3
            // 
            checkBox3.AutoSize = true;
            checkBox3.Location = new Point(56, 526);
            checkBox3.Name = "checkBox3";
            checkBox3.Size = new Size(181, 32);
            checkBox3.TabIndex = 21;
            checkBox3.Text = "自动点击“登录\"";
            checkBox3.UseVisualStyleBackColor = true;
            checkBox3.CheckedChanged += checkBox3_CheckedChanged;
            // 
            // checkBox4
            // 
            checkBox4.AutoSize = true;
            checkBox4.Location = new Point(264, 376);
            checkBox4.Name = "checkBox4";
            checkBox4.Size = new Size(227, 32);
            checkBox4.TabIndex = 22;
            checkBox4.Text = "持续将窗口置于最前";
            checkBox4.UseVisualStyleBackColor = true;
            // 
            // sendImagePossibly
            // 
            sendImagePossibly.Location = new Point(243, 478);
            sendImagePossibly.Maximum = 100;
            sendImagePossibly.Minimum = 1;
            sendImagePossibly.Name = "sendImagePossibly";
            sendImagePossibly.Size = new Size(248, 80);
            sendImagePossibly.TabIndex = 23;
            sendImagePossibly.TickStyle = TickStyle.None;
            sendImagePossibly.Value = 1;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(56, 476);
            label9.Name = "label9";
            label9.Size = new Size(138, 28);
            label9.TabIndex = 24;
            label9.Text = "发送图片概率";
            // 
            // Vs
            // 
            Vs.AutoSize = true;
            Vs.Location = new Point(812, 40);
            Vs.Name = "Vs";
            Vs.Size = new Size(26, 28);
            Vs.TabIndex = 25;
            Vs.Text = "V";
            // 
            // checkBox5
            // 
            checkBox5.AutoSize = true;
            checkBox5.Location = new Point(56, 155);
            checkBox5.Name = "checkBox5";
            checkBox5.Size = new Size(122, 32);
            checkBox5.TabIndex = 26;
            checkBox5.Text = "视觉模型";
            checkBox5.UseVisualStyleBackColor = true;
            checkBox5.CheckedChanged += checkBox5_CheckedChanged;
            // 
            // button5
            // 
            button5.Location = new Point(184, 150);
            button5.Name = "button5";
            button5.Size = new Size(194, 40);
            button5.TabIndex = 27;
            button5.Text = "选择nt_data目录";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new Point(56, 206);
            label10.Name = "label10";
            label10.Size = new Size(447, 56);
            label10.TabIndex = 28;
            label10.Text = "VisionQQ需要通过ntdata内的图片文件获取新\r\n收到的图片，这个目录一般与QQ号有关";
            // 
            // textBox8
            // 
            textBox8.Location = new Point(384, 153);
            textBox8.Name = "textBox8";
            textBox8.Size = new Size(107, 34);
            textBox8.TabIndex = 29;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(13F, 28F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1109, 686);
            Controls.Add(textBox8);
            Controls.Add(label10);
            Controls.Add(button5);
            Controls.Add(checkBox5);
            Controls.Add(Vs);
            Controls.Add(label9);
            Controls.Add(sendImagePossibly);
            Controls.Add(checkBox4);
            Controls.Add(checkBox3);
            Controls.Add(label8);
            Controls.Add(checkBox2);
            Controls.Add(textBox7);
            Controls.Add(label7);
            Controls.Add(button4);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(textBox6);
            Controls.Add(label6);
            Controls.Add(checkBox1);
            Controls.Add(textBox5);
            Controls.Add(label5);
            Controls.Add(textBox4);
            Controls.Add(label4);
            Controls.Add(textBox3);
            Controls.Add(label3);
            Controls.Add(textBox2);
            Controls.Add(label2);
            Controls.Add(textBox1);
            Controls.Add(label1);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "Form1";
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "设置";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)sendImagePossibly).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private TextBox textBox1;
        private TextBox textBox2;
        private Label label2;
        private TextBox textBox3;
        private Label label3;
        private TextBox textBox4;
        private Label label4;
        private TextBox textBox5;
        private Label label5;
        private CheckBox checkBox1;
        private TextBox textBox6;
        private Label label6;
        private Button button1;
        private Button button2;
        private Button button3;
        private Button button4;
        private TextBox textBox7;
        private Label label7;
        private CheckBox checkBox2;
        private Label label8;
        private CheckBox checkBox3;
        private CheckBox checkBox4;
        private TrackBar sendImagePossibly;
        private Label label9;
        private Label Vs;
        private CheckBox checkBox5;
        private Button button5;
        private Label label10;
        private FolderBrowserDialog folderBrowserDialog1;
        private TextBox textBox8;
    }
}
