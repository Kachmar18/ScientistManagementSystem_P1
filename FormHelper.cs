using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace ScientistManagementSystem_C_
{
    public static class FormHelper
    {
        public static void contentCmbDegree(ComboBox cmbDegree)
        {
            cmbDegree.Items.Clear();
            cmbDegree.Items.Add("PhD");
            cmbDegree.Items.Add("PhDM");
            cmbDegree.Items.Add("Candidate Technical");
            cmbDegree.Items.Add("Doctor Technical");
            cmbDegree.SelectedIndex = 0;
        }

        public static void ApplyDataGridStyle(DataGridView dataGridView)
        {
            DataGridViewCellStyle headerStyle = new DataGridViewCellStyle();
            headerStyle.BackColor = Color.LightGray;
            headerStyle.Font = new Font("Arsenal", 10F, FontStyle.Bold);
            headerStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;

            dataGridView.ColumnHeadersDefaultCellStyle = headerStyle;
            dataGridView.EnableHeadersVisualStyles = false;

            dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridView.DefaultCellStyle.Font = new Font("Arsenal", 11F, FontStyle.Regular);
            dataGridView.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleLeft;
            dataGridView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
            dataGridView.AlternatingRowsDefaultCellStyle.BackColor = Color.FromArgb(240, 240, 240);
        }



        public static void SaveToXml(string path, List<ScientificTeacher> teachers)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<ScientificTeacher>));
            using (FileStream fs = new FileStream(path, FileMode.Create))
            {
                serializer.Serialize(fs, teachers);
            }
        }

        public static List<ScientificTeacher> LoadFromXml(string path)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<ScientificTeacher>));
            using (FileStream fs = new FileStream(path, FileMode.Open))
            {
                return (List<ScientificTeacher>)serializer.Deserialize(fs);
            }
        }

        public static string PromptInput(string message, string title)
        {
            Form prompt = new Form()
            {
                Width = 400,
                Height = 150,
                Text = title,
                StartPosition = FormStartPosition.CenterParent
            };

            Label textLabel = new Label() { Left = 20, Top = 20, Text = message, Width = 340 };
            TextBox inputBox = new TextBox() { Left = 20, Top = 50, Width = 340 };
            Button confirmation = new Button() { Text = "OK", Left = 280, Width = 80, Top = 80, DialogResult = DialogResult.OK };

            prompt.Controls.Add(textLabel);
            prompt.Controls.Add(inputBox);
            prompt.Controls.Add(confirmation);
            prompt.AcceptButton = confirmation;

            return prompt.ShowDialog() == DialogResult.OK ? inputBox.Text : "";
        }

    }
}
