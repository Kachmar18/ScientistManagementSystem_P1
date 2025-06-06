using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScientistManagementSystem_C_
{
    public interface ITeacher
    {
        List<string> Subjects { get; set; }
        int AnnualHours { get; set; }
        List<string> Groups { get; set; }
        int ExperienceYears { get; set; }

        string ToString();
    }
}
