
namespace Desktop
{
    partial class FormMain
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
            this.lblTexto = new System.Windows.Forms.Label();
            this.txtValue = new System.Windows.Forms.TextBox();
            this.grpText = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.grpText.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblTexto
            // 
            this.lblTexto.AutoSize = true;
            this.lblTexto.Location = new System.Drawing.Point(9, 27);
            this.lblTexto.Name = "lblTexto";
            this.lblTexto.Size = new System.Drawing.Size(16, 20);
            this.lblTexto.TabIndex = 0;
            this.lblTexto.Text = "?";
            this.lblTexto.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // txtValue
            // 
            this.txtValue.Location = new System.Drawing.Point(24, 95);
            this.txtValue.Name = "txtValue";
            this.txtValue.Size = new System.Drawing.Size(251, 27);
            this.txtValue.TabIndex = 1;
            this.txtValue.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // grpText
            // 
            this.grpText.Controls.Add(this.lblTexto);
            this.grpText.Location = new System.Drawing.Point(25, 29);
            this.grpText.Name = "grpText";
            this.grpText.Size = new System.Drawing.Size(250, 60);
            this.grpText.TabIndex = 2;
            this.grpText.TabStop = false;
            this.grpText.Text = "TEXTO DIGITADO";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(95, 143);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(94, 29);
            this.button1.TabIndex = 3;
            this.button1.Text = "LIMPAR";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(300, 205);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.grpText);
            this.Controls.Add(this.txtValue);
            this.Name = "FormMain";
            this.Text = "Form1";
            this.grpText.ResumeLayout(false);
            this.grpText.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblTexto;
        private System.Windows.Forms.TextBox txtValue;
        private System.Windows.Forms.GroupBox grpText;
        private System.Windows.Forms.Button button1;
    }
}

