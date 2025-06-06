using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScientistManagementSystem_C_
{
    [Serializable]
    public class Teacher : ITeacher
    {
        public List<string> Subjects { get; set; }
        public int AnnualHours { get; set; }
        public List<string> Groups { get; set; }
        public int ExperienceYears { get; set; }

        public Teacher() { }

        public Teacher(List<string> subjects, int annualHours, List<string> groups, int experienceYears)
        {
            Subjects = subjects;
            AnnualHours = annualHours;
            Groups = groups;
            ExperienceYears = experienceYears;
        }

        // Copy constructor
        public Teacher(Teacher other)
        {
            Subjects = new List<string>(other.Subjects);
            AnnualHours = other.AnnualHours;
            Groups = new List<string>(other.Groups);
            ExperienceYears = other.ExperienceYears;
        }

        ~Teacher(){ }

        public void SetSubjects(List<string> subjects) => Subjects = subjects;
        public List<string> GetSubjects() => Subjects;

        public void SetAnnualHours(int hours) => AnnualHours = hours;
        public int GetAnnualHours() => AnnualHours;

        public void SetGroups(List<string> groups) => Groups = groups;
        public List<string> GetGroups() => Groups;

        public void SetExperienceYears(int years) => ExperienceYears = years;
        public int GetExperienceYears() => ExperienceYears;


        // метод для зміни значень полів
        public void SetAll(List<string> subjects, int hours, List<string> groups, int experience)
        {
            Subjects = subjects;
            AnnualHours = hours;
            Groups = groups;
            ExperienceYears = experience;
        }

        //перевантаження операції присвоєння
        public void CopyFrom(Teacher other)
        {
            Subjects = new List<string>(other.Subjects);
            AnnualHours = other.AnnualHours;
            Groups = new List<string>(other.Groups);
            ExperienceYears = other.ExperienceYears;
        }

        //імітація переміщення вручну
        public static Teacher Move(ref Teacher other)
        {
            Teacher moved = new Teacher(other.Subjects, other.AnnualHours, other.Groups, other.ExperienceYears);
            other.Subjects = null;
            other.AnnualHours = 0;
            other.Groups = null;
            other.ExperienceYears = 0;
            return moved;
        }

        public override string ToString()
        {
            return $"Subjects: {string.Join(", ", Subjects)}, Hours: {AnnualHours}, Groups: {string.Join(", ", Groups)}, Experience: {ExperienceYears}";
        }

    }
}
