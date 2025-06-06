using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ScientistManagementSystem_C_
{
    public static class ValidationHelper
    {
        public static bool ValidatePositiveInt(string input, out int result, string fieldName) //число >= 0
        {
            if (!int.TryParse(input, out result) || result < 0)
            {
                MessageBox.Show($"Поле \"{fieldName}\" повинно містити додатнє число.", "Помилка валідації");
                return false;
            }
            return true;
        }

        public static bool ValidateNonEmpty(string input, string fieldName) // чи рядок непорожній
        {
            if (string.IsNullOrWhiteSpace(input))
            {
                MessageBox.Show($"Поле \"{fieldName}\" не може бути порожнім.", "Помилка валідації");
                return false;
            }
            return true;
        }
    }
}
