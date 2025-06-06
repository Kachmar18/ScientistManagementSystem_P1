using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScientistManagementSystem_C_
{
    [Serializable]
    public class ScientificTeacher : Scientist, ITeacher
    {
        public Teacher TeacherData { get; set; }

        public string LastName { get; set; }
        public string FirstName { get; set; }
        public string MiddleName { get; set; }

        public ScientificTeacher()
        {
            TeacherData = new Teacher();
            LastName = string.Empty;
            FirstName = string.Empty;
            MiddleName = string.Empty;
        }

        public ScientificTeacher(string lastName, string firstName, string middleName,
            Article[] publications, int reports, int patents, AcademicDegree degree,
            List<string> subjects, int hours, List<string> groups, int experienceYears)
            : base(publications, reports, patents, degree)
        {
            LastName = lastName;
            FirstName = firstName;
            MiddleName = middleName;
            TeacherData = new Teacher(subjects, hours, groups, experienceYears);
        }

        // Copy constructor
        public ScientificTeacher(ScientificTeacher other)
            : base(other)
        {
            TeacherData = new Teacher(other.TeacherData);
            LastName = other.LastName;
            FirstName = other.FirstName;
            MiddleName = other.MiddleName;
        }
        ~ScientificTeacher() { }


        public override string ToString()
        {
            return $"{LastName} {FirstName} {MiddleName}\n{base.ToString()}\n{TeacherData.ToString()}";
        }

        public static ScientificTeacher Parse(string[] lines)
        {
            throw new NotImplementedException();
        }

        public void SetPersonalData(string last, string first, string middle)
        {
            LastName = last;
            FirstName = first;
            MiddleName = middle;
        }

        public override string Display()
        {
            return $"[ScientificTeacher] {LastName} {FirstName} {MiddleName}\n" +
                   base.Display() + "\n" +
                   $"Subjects: {string.Join(", ", TeacherData.Subjects)}, Hours: {TeacherData.AnnualHours}, " +
                   $"Groups: {string.Join(", ", TeacherData.Groups)}, Experience: {TeacherData.ExperienceYears}";
        }


        // Реалізація інтерфейсу ITeacher через delegation
        public List<string> Subjects { get => TeacherData.Subjects; set => TeacherData.Subjects = value; }
        public int AnnualHours { get => TeacherData.AnnualHours; set => TeacherData.AnnualHours = value; }
        public List<string> Groups { get => TeacherData.Groups; set => TeacherData.Groups = value; }
        public int ExperienceYears { get => TeacherData.ExperienceYears; set => TeacherData.ExperienceYears = value; }

        public string GetTeacherInfo()
        {
            return TeacherData.ToString();
        }

    }
}
