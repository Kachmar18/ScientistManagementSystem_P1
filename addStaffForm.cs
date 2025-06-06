using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ScientistManagementSystem_C_
{
    public partial class addStaffForm : Form
    {
        public ScientificTeacher NewTeacher { get; private set; }

        public addStaffForm()
        {
            InitializeComponent();
        }
        private void infoStaffForm_Load(object sender, EventArgs e)
        {
            FormHelper.contentCmbDegree(cmbDegree);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            try
            {
                string lastName = txtLastName.Text.Trim();
                string firstName = txtFirstName.Text.Trim();
                string middleName = txtMiddleName.Text.Trim();

                if (!ValidationHelper.ValidateNonEmpty(lastName, "Прізвище") ||
                    lastName.Length < 2)
                {
                    MessageBox.Show("Прізвище повинно містити щонайменше 2 символи.");
                    return;
                }

                if (!ValidationHelper.ValidateNonEmpty(firstName, "Ім'я") ||
                    firstName.Length < 2)
                {
                    MessageBox.Show("Ім'я повинно містити щонайменше 2 символи.");
                    return;
                }

                if (!ValidationHelper.ValidateNonEmpty(middleName, "По батькові") ||
                    middleName.Length < 2)
                {
                    MessageBox.Show("По батькові повинно містити щонайменше 2 символи.");
                    return;
                }

                List<Article> articles = new List<Article>();
                foreach (string line in txtPublications.Lines)
                {
                    string[] parts = line.Split(';');
                    if (parts.Length == 4 && int.TryParse(parts[3], out int year))
                    {
                        articles.Add(new Article(parts[0], parts[1], parts[2], year));
                    }
                    else
                    {
                        MessageBox.Show("Помилка у форматі публікації. Формат: автор;журнал;назва;рік");
                        return;
                    }
                }

                if (!ValidationHelper.ValidatePositiveInt(txtReports.Text, out int reports, "Кількість виступів") ||
                    !ValidationHelper.ValidatePositiveInt(txtPatents.Text, out int patents, "Кількість патентів") ||
                    !ValidationHelper.ValidatePositiveInt(txtHours.Text, out int hours, "Навантаження (годин)") ||
                    !ValidationHelper.ValidatePositiveInt(txtExperience.Text, out int experience, "Стаж роботи"))
                {
                    return;
                }

                if (cmbDegree.SelectedItem == null ||
                    !Enum.TryParse(cmbDegree.SelectedItem.ToString(), out AcademicDegree degree))
                {
                    MessageBox.Show("Будь ласка, оберіть вчений ступінь.");
                    return;
                }

                List<string> subjects = txtSubjects.Text.Split(',')
                    .Select(s => s.Trim())
                    .Where(s => !string.IsNullOrEmpty(s))
                    .ToList();

                if (subjects.Count == 0)
                {
                    MessageBox.Show("Будь ласка, введіть хоча б один предмет.");
                    return;
                }

                List<string> groups = txtGroups.Text.Split(',')
                    .Select(s => s.Trim())
                    .Where(s => !string.IsNullOrEmpty(s))
                    .ToList();

                if (groups.Count == 0)
                {
                    MessageBox.Show("Будь ласка, введіть хоча б одну групу.");
                    return;
                }

                NewTeacher = new ScientificTeacher(
                    lastName, firstName, middleName,
                    articles.ToArray(), reports, patents, degree,
                    subjects, hours, groups, experience
                );

                DialogResult = DialogResult.OK;
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Неочікувана помилка: " + ex.Message);
            }
        }

        private void btnGoBack_Click(object sender, EventArgs e)
        {
            Dispose();
        }
    }
}
