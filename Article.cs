using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScientistManagementSystem_C_
{
    [Serializable]
    public class Article
    {
        public string Authors { get; set; }
        public string JournalName { get; set; }
        public string Title { get; set; }
        public int Year { get; set; }

        public Article(string authors, string journalName, string title, int year)
        {
            Authors = authors;
            JournalName = journalName;
            Title = title;
            Year = year;
        }

        public Article(Article other)
        {
            Authors = other.Authors;
            JournalName = other.JournalName;
            Title = other.Title;
            Year = other.Year;
        }

        public Article() { }

        public override string ToString()
        {
            return $"{Authors};{JournalName};{Title};{Year}";
        }

        public static Article Parse(string input)
        {
            if (string.IsNullOrWhiteSpace(input))
                throw new ArgumentException("Input string is empty.");

            string[] parts = input.Split(';');
            if (parts.Length != 4)
                throw new FormatException("Invalid format. Expected: authors;journal;title;year");

            if (!int.TryParse(parts[3], out int year))
                throw new FormatException("Invalid year format.");

            return new Article(parts[0].Trim(), parts[1].Trim(), parts[2].Trim(), year);
        }
    }
}
