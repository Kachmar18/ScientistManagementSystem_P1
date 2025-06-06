using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;

namespace ScientistManagementSystem_C_
{
    public partial class mainForm : Form
    {
        private List<ScientificTeacher> scientificTeachers = new List<ScientificTeacher>();
        private ScientificTeacherContainer container = new ScientificTeacherContainer();
        
        public mainForm()
        {
            InitializeComponent();
        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            cmbStatistics.Items.Clear();
            cmbStatistics.Items.Add("Середнє навантаження");
            cmbStatistics.Items.Add("Середній стаж роботи");
            cmbStatistics.Items.Add("Пошук за дисципліною");
            cmbStatistics.SelectedIndex = 0;
        }

        private void проПрограмуToolStripMenuItem_Click(object sender, EventArgs e)
        {
            aboutForm aboutForm = new aboutForm();
            aboutForm.ShowDialog();
        }

        private void вихідToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void відкритиФайлToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog ofd = new OpenFileDialog())
            {
                ofd.Filter = "XML files (*.xml)|*.xml";
                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    scientificTeachers = FormHelper.LoadFromXml(ofd.FileName);
                    container = new ScientificTeacherContainer();
                    container.AddRange(scientificTeachers);
                    LoadScientificTeachersIntoGrid();
                    MessageBox.Show("Дані успішно завантажено з XML.", "Завантаження");
                }
            }


        }

        private void зберегтиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog sfd = new SaveFileDialog())
            {
                sfd.Filter = "XML files (*.xml)|*.xml";
                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    FormHelper.SaveToXml(sfd.FileName, scientificTeachers);
                    MessageBox.Show("Дані успішно збережено у XML.", "Збереження");
                }
            }

        } 



        private void btnShowStatistics_Click(object sender, EventArgs e)
        {
            if (cmbStatistics.SelectedItem == null)
            {
                MessageBox.Show("Будь ласка, виберіть тип статистики.");
                return;
            }

            string selected = cmbStatistics.SelectedItem.ToString();

            switch (selected)
            {
                case "Середнє навантаження":
                    double avgLoad = container.GetAverageLoad();
                    MessageBox.Show($"Середнє навантаження: {avgLoad:F1} годин", "Статистика");
                    break;

                case "Середній стаж роботи":
                    double avgExp = container.GetAverageExperience();
                    MessageBox.Show($"Середній стаж роботи: {avgExp:F1} років", "Статистика");
                    break;

                case "Пошук за дисципліною":
                    string subject = FormHelper.PromptInput("Введіть назву предмету для пошуку:", "Фільтр для предметів");
                    if (!string.IsNullOrWhiteSpace(subject))
                    {
                        ShowTeachersBySubject(subject.Trim());
                    }
                    break;

                default:
                    MessageBox.Show("Невідомий варіант");
                    break;
            }
        }

        private void ShowTeachersBySubject(string subject)
        {
            var filtered = container.GetTeachersBySubject(subject);
            if (filtered.Count == 0)
            {
                MessageBox.Show("Не знайдено жодного викладача для цього предмету.");
                return;
            }

            StringBuilder sb = new StringBuilder();
            foreach (var t in filtered)
            {
                sb.AppendLine(t.Display());
                sb.AppendLine("-------------------------");
            }

            MessageBox.Show(sb.ToString(), $"Викладачі, що викладають: {subject}");
        }

               

        private void btnAddStaff_Click(object sender, EventArgs e)
        {
            addStaffForm form = new addStaffForm();
            if (form.ShowDialog() == DialogResult.OK)
            {
                var newTeacher = form.NewTeacher;
                if (newTeacher != null)
                {
                    scientificTeachers.Add(newTeacher);
                    container.Add(newTeacher);
                    LoadScientificTeachersIntoGrid();
                }
            }
        }

        private void btnEditStaff_Click(object sender, EventArgs e)
        {
            if (dataGridView.SelectedRows.Count == 0)
            {
                MessageBox.Show("Будь ласка, оберіть рядок для редагування.");
                return;
            }

            int rowIndex = dataGridView.SelectedRows[0].Index;

            if (rowIndex >= 0 && rowIndex < scientificTeachers.Count)
            {
                var teacherToEdit = scientificTeachers[rowIndex];
                editStaffForm form = new editStaffForm();

                form.LoadTeacherForEdit(teacherToEdit);

                if (form.ShowDialog() == DialogResult.OK)
                {
                    var updatedTeacher = form.EditedTeacher;

                    if (updatedTeacher != null)
                    {
                        scientificTeachers[rowIndex] = updatedTeacher;

                        container = new ScientificTeacherContainer();
                        container.AddRange(scientificTeachers);

                        LoadScientificTeachersIntoGrid();
                    }
                }
            }
            else
            {
                MessageBox.Show("Помилка: обраний рядок не відповідає запису у списку.");
            }
        }

        private void btnDeleteStaff_Click(object sender, EventArgs e)
        {

            if (dataGridView.SelectedRows.Count == 0)
            {
                MessageBox.Show("Будь ласка, оберіть рядок для видалення.");
                return;
            }

            int rowIndex = dataGridView.SelectedRows[0].Index;

            if (rowIndex >= 0 && rowIndex < scientificTeachers.Count)
            {
                var result = MessageBox.Show("Ви впевнені, що хочете видалити цього працівника?", "Підтвердження", MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    scientificTeachers.RemoveAt(rowIndex);

                    container = new ScientificTeacherContainer();
                    container.AddRange(scientificTeachers);

                    LoadScientificTeachersIntoGrid();
                }
            }
            else
            {
                MessageBox.Show("Помилка: обраний рядок не відповідає запису у списку.");
            }
        }


        private void btnTestPolymorphism_Click(object sender, EventArgs e)
        {
            Scientist baseScientist = new Scientist(
                new Article[]
                {
            new Article("Petrov", "Science Journal", "NanoTech", 2020)
                },
                3, 1, AcademicDegree.PhD
            );

            ShowInfo(baseScientist); // викликається Scientist.Display()

            baseScientist = new ScientificTeacher(
                "Ivanov", "Oleh", "Petrovych",
                new Article[]
                {
            new Article("Ivanov", "AI Journal", "Machine Learning", 2022)
                },
                2, 2, AcademicDegree.DoctorTechnical,
                new List<string> { "AI", "ML" },
                620,
                new List<string> { "Group1", "Group2" },
                12
            );

            ShowInfo(baseScientist); // викликається Scientist.Display()


            //Scientist refScientist;             // Посилання на базовий клас


            //refScientist = baseScientist/ Вказуємо на базовий об’єкт
            //ShowInfo(refScientist); // Викликає Scientist.Display() 

            
            //refScientist = derivedScientist; // Вказуємо на похідний об’єкт
            //ShowInfo(refScientist); // Викликає ScientificTeacher.Display()
        }

        private void ShowInfo(Scientist s)
        {
            // Це пізнє зв’язування: компілятор не знає заздалегідь, який саме Display() викликати
            MessageBox.Show(s.Display(), $"Виклик через посилання (тип об’єкта: {s.GetType().Name})");
        }


        private void btnCleanDataGried_Click(object sender, EventArgs e)
        {
            var result = MessageBox.Show("Ви впевнені, що хочете очистити всі дані?", "Підтвердження", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes)
            {
                scientificTeachers.Clear();
                container = new ScientificTeacherContainer();
                dataGridView.Rows.Clear();
                dataGridView.Columns.Clear();
            }
        }


        private void LoadScientificTeachersIntoGrid()
        {
            dataGridView.Rows.Clear();
            dataGridView.Columns.Clear();

            dataGridView.Columns.Add("FullName", "Full Name");
            dataGridView.Columns.Add("Degree", "Degree");
            dataGridView.Columns.Add("Reports", "Reports");
            dataGridView.Columns.Add("Patents", "Patents");
            dataGridView.Columns.Add("Articles", "Publications");
            dataGridView.Columns.Add("Subjects", "Subjects");
            dataGridView.Columns.Add("Hours", "Annual Hours");
            dataGridView.Columns.Add("Groups", "Groups");
            dataGridView.Columns.Add("Experience", "Experience");

            foreach (var st in scientificTeachers)
            {
                dataGridView.Rows.Add(
                    $"{st.LastName} {st.FirstName} {st.MiddleName}",
                    st.Degree.ToString(),
                    st.ConferenceReports,
                    st.Patents,
                    st.Publications.Length,
                    string.Join(", ", st.TeacherData.Subjects),
                    st.TeacherData.AnnualHours,
                    string.Join(", ", st.TeacherData.Groups),
                    st.TeacherData.ExperienceYears
                );
            }

            // 🔽 Налаштування стилю
            FormHelper.ApplyDataGridStyle(dataGridView);
        }

        private void btnTestOperations_Click(object sender, EventArgs e)
        {
            // ➤ Тест Scientist
            Scientist originalSci = new Scientist(
                new Article[] { new Article("TestAuthor", "TestJournal", "TestTitle", 2021) },
                5, 2, AcademicDegree.PhD);

            Scientist copiedSci = new Scientist();
            copiedSci.CopyFrom(originalSci);

            Scientist movedSci = Scientist.Move(ref originalSci);

            MessageBox.Show("Scientist COPY:\n" + copiedSci.ToString(), "Scientist CopyFrom");
            MessageBox.Show("Scientist MOVE:\n" + movedSci.ToString(), "Scientist Move");

            // ➤ Тест Teacher
            Teacher originalTeacher = new Teacher(
                new List<string> { "Math", "Physics" },
                500,
                new List<string> { "Group1", "Group2" },
                10);

            Teacher copiedTeacher = new Teacher();
            copiedTeacher.CopyFrom(originalTeacher);

            Teacher movedTeacher = Teacher.Move(ref originalTeacher);

            MessageBox.Show("Teacher COPY:\n" + copiedTeacher.ToString(), "Teacher CopyFrom");
            MessageBox.Show("Teacher MOVE:\n" + movedTeacher.ToString(), "Teacher Move");

            // ➤ Тест ScientificTeacher
            ScientificTeacher originalST = new ScientificTeacher(
                "Ivanov", "Petro", "Mykolaiovych",
                new Article[] { new Article("Ivanov", "Journal", "Title", 2022) },
                3, 1, AcademicDegree.DoctorTechnical,
                new List<string> { "CS", "AI" },
                700,
                new List<string> { "GroupA" },
                15);

            ScientificTeacher copiedST = new ScientificTeacher(originalST);
            copiedST.SetPersonalData("Copied", "Person", "Example");

            MessageBox.Show("ScientificTeacher COPY:\n" + copiedST.ToString(), "ScientificTeacher CopyFrom");

            // SetAll demo (на основі Scientist)
            copiedST.SetAll(
                new Article[] { new Article("New", "NewJournal", "NewTitle", 2023) },
                10, 5, AcademicDegree.PhDM);

            MessageBox.Show("ScientificTeacher after SetAll:\n" + copiedST.ToString(), "ScientificTeacher SetAll");
        }
    }
}
