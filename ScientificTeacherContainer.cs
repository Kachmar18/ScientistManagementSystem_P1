using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScientistManagementSystem_C_
{
    public class ScientificTeacherContainer : IEnumerable<ScientificTeacher>
    {
        private List<ScientificTeacher> _teachers = new List<ScientificTeacher>();

        public void Add(ScientificTeacher teacher)
        {
            _teachers.Add(teacher);
        }

        public void AddRange(IEnumerable<ScientificTeacher> list)
        {
            _teachers.AddRange(list);
        }

        public ScientificTeacher this[int index] => _teachers[index];

        public int Count => _teachers.Count;

        public void DisplayAll(Action<string> displayMethod)
        {
            foreach (var teacher in _teachers)
            {
                displayMethod(teacher.Display());
            }
        }

        // ---------- СТАТИСТИКА ----------
        public double GetAverageLoad()
        {
            if (_teachers.Count == 0) return 0;
            return _teachers.Average(t => t.TeacherData.AnnualHours);
        }

        public double GetAverageExperience()
        {
            if (_teachers.Count == 0) return 0;
            return _teachers.Average(t => t.TeacherData.ExperienceYears);
        }

        public List<ScientificTeacher> GetTeachersBySubject(string subject)
        {
            return _teachers
                .Where(t => t.TeacherData.Subjects.Contains(subject, StringComparer.OrdinalIgnoreCase))
                .ToList();
        }

        // ---------- ІТЕРАТОР ----------
        public IEnumerator<ScientificTeacher> GetEnumerator()
        {
            foreach (var t in _teachers)
                yield return t;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
