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
    public partial class editStaffForm : Form
    {
        public ScientificTeacher EditedTeacher { get; private set; }

        public editStaffForm()
        {
            InitializeComponent();
        }

        private void editStaffForm_Load(object sender, EventArgs e)
        {
            FormHelper.contentCmbDegree(cmbDegree);
        }

        public void LoadTeacherForEdit(ScientificTeacher teacher)
        {
            txtLastName.Text = teacher.LastName;
            txtFirstName.Text = teacher.FirstName;
            txtMiddleName.Text = teacher.MiddleName;

            txtPublications.Lines = teacher.Publications
                .Select(a => $"{a.Authors};{a.JournalName};{a.Title};{a.Year}")
                .ToArray();

            txtReports.Text = teacher.ConferenceReports.ToString();
            txtPatents.Text = teacher.Patents.ToString();
            cmbDegree.SelectedItem = teacher.Degree.ToString();

            txtSubjects.Text = string.Join(", ", teacher.TeacherData.Subjects);
            txtHours.Text = teacher.TeacherData.AnnualHours.ToString();
            txtGroups.Text = string.Join(", ", teacher.TeacherData.Groups);
            txtExperience.Text = teacher.TeacherData.ExperienceYears.ToString();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            try
            {
                string lastName = txtLastName.Text.Trim();
                string firstName = txtFirstName.Text.Trim();
                string middleName = txtMiddleName.Text.Trim();

                if (!ValidationHelper.ValidateNonEmpty(lastName, "Прізвище") || lastName.Length < 2)
                {
                    MessageBox.Show("Прізвище повинно містити щонайменше 2 символи.");
                    return;
                }
                if (!ValidationHelper.ValidateNonEmpty(firstName, "Ім'я") || firstName.Length < 2)
                {
                    MessageBox.Show("Ім'я повинно містити щонайменше 2 символи.");
                    return;
                }
                if (!ValidationHelper.ValidateNonEmpty(middleName, "По батькові") || middleName.Length < 2)
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
                        if (year < 1900 || year > DateTime.Now.Year)
                        {
                            MessageBox.Show("Рік публікації має бути між 1900 та поточним роком.");
                            return;
                        }
                        articles.Add(new Article(parts[0].Trim(), parts[1].Trim(), parts[2].Trim(), year));
                    }
                    else
                    {
                        MessageBox.Show("Невірний формат публікації. Використовуйте: автор;журнал;назва;рік");
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
                    MessageBox.Show("Будь ласка, введіть хоча б один предмет (через кому).");
                    return;
                }

                List<string> groups = txtGroups.Text.Split(',')
                    .Select(s => s.Trim())
                    .Where(s => !string.IsNullOrEmpty(s))
                    .ToList();

                if (groups.Count == 0)
                {
                    MessageBox.Show("Будь ласка, введіть хоча б одну групу (через кому).");
                    return;
                }

                EditedTeacher = new ScientificTeacher(
                    lastName, firstName, middleName,
                    articles.ToArray(), reports, patents, degree,
                    subjects, hours, groups, experience
                );

                DialogResult = DialogResult.OK;
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Помилка збереження: " + ex.Message);
            }
        }

        private void btnGoBack_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
