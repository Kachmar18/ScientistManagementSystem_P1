#include "ResearchTeachingStaff.h"
#include <sstream>
#include <iostream>

// Constructor
ResearchTeachingStaff::ResearchTeachingStaff(
    const std::string& last,
    const std::string& first,
    const std::string& middle,
    const std::vector<Article>& pubs,
    int presentations,
    int patents,
    AcademicDegree deg,
    const std::vector<std::string>& disc,
    unsigned int hours,
    const std::vector<std::string>& grps,
    unsigned int exp
) : Scientist(pubs, presentations, patents, deg),
Teacher(disc, hours, grps, exp),
lastName(last),
firstName(first),
middleName(middle) {}

// Copy constructor
ResearchTeachingStaff::ResearchTeachingStaff(const ResearchTeachingStaff& other)
    : Scientist(other),
    Teacher(other),
    lastName(other.lastName),
    firstName(other.firstName),
    middleName(other.middleName) {}

// Move constructor
ResearchTeachingStaff::ResearchTeachingStaff(ResearchTeachingStaff&& other) noexcept
    : Scientist(std::move(other)),
    Teacher(std::move(other)),
    lastName(std::move(other.lastName)),
    firstName(std::move(other.firstName)),
    middleName(std::move(other.middleName)) {}

// Destructor
ResearchTeachingStaff::~ResearchTeachingStaff() {}

// Assignment operators
ResearchTeachingStaff& ResearchTeachingStaff::operator=(const ResearchTeachingStaff& other) {
    if (this != &other) {
        Scientist::operator=(other);
        Teacher::operator=(other);
        lastName = other.lastName;
        firstName = other.firstName;
        middleName = other.middleName;
    }
    return *this;
}

ResearchTeachingStaff& ResearchTeachingStaff::operator=(ResearchTeachingStaff&& other) noexcept {
    if (this != &other) {
        Scientist::operator=(std::move(other));
        Teacher::operator=(std::move(other));
        lastName = std::move(other.lastName);
        firstName = std::move(other.firstName);
        middleName = std::move(other.middleName);
    }
    return *this;
}

// In ResearchTeachingStaff.cpp
std::ostream& operator<<(std::ostream& os, const ResearchTeachingStaff& rts) {
    os << "Name: " << rts.getFullName() << "\n";
    os << "--- Scientific Information ---\n";
    os << static_cast<const Scientist&>(rts);
    os << "\n--- Teaching Information ---\n";
    os << static_cast<const Teacher&>(rts);
    return os;
}

std::istream& operator>>(std::istream& is, ResearchTeachingStaff& rts) {
    std::cout << "Enter personal information:\n";
    std::cout << "Last name: ";
    std::getline(is, rts.lastName);
    std::cout << "First name: ";
    std::getline(is, rts.firstName);
    std::cout << "Middle name: ";
    std::getline(is, rts.middleName);

    // Call base class stream operators
    is >> static_cast<Scientist&>(rts);
    is.ignore(); // Clear newline
    is >> static_cast<Teacher&>(rts);

    return is;
}

// Getters
std::string ResearchTeachingStaff::getLastName() const { return lastName; }
std::string ResearchTeachingStaff::getFirstName() const { return firstName; }
std::string ResearchTeachingStaff::getMiddleName() const { return middleName; }

// Setters
void ResearchTeachingStaff::setLastName(const std::string& last) { lastName = last; }
void ResearchTeachingStaff::setFirstName(const std::string& first) { firstName = first; }
void ResearchTeachingStaff::setMiddleName(const std::string& middle) { middleName = middle; }

// Combined information
std::string ResearchTeachingStaff::getFullName() const {
    std::ostringstream oss;
    oss << lastName << " " << firstName << " " << middleName;
    return oss.str();
}


void ResearchTeachingStaff::displayInfo() const {
    std::cout << "=== Research Teaching Staff ===\n";
    std::cout << "Name: " << getFullName() << "\n";

    // Call base class implementations
    Scientist::displayInfo();
    Teacher::displayInfo();
}



void ResearchTeachingStaff::serialize(std::ostream& os) const {
    // Personal info
    os << lastName << "\n" << firstName << "\n" << middleName << "\n";

    // Scientist info
    os << getPublications().size() << "\n";
    for (const auto& pub : getPublications()) {
        os << pub.getAuthors().size() << "\n";
        for (const auto& author : pub.getAuthors()) {
            os << author << "\n";
        }
        os << pub.getJournalTitle() << "\n";
        os << pub.getArticleTitle() << "\n";
        os << pub.getPublicationYear() << "\n";
    }
    os << getConferencePresentations() << "\n";
    os << getPatentsCount() << "\n";
    os << static_cast<int>(getAcademicDegree()) << "\n";

    // Teacher info
    os << getDisciplines().size() << "\n";
    for (const auto& disc : getDisciplines()) {
        os << disc << "\n";
    }
    os << getYearlyHours() << "\n";
    os << getGroups().size() << "\n";
    for (const auto& group : getGroups()) {
        os << group << "\n";
    }
    os << getWorkExperience() << "\n";
}

void ResearchTeachingStaff::deserialize(std::istream& is) {
    // Personal info
    std::getline(is, lastName);
    std::getline(is, firstName);
    std::getline(is, middleName);

    // Scientist info
    std::vector<Article> publications;
    int pubCount;
    is >> pubCount;
    is.ignore();
    for (int i = 0; i < pubCount; ++i) {
        int authorCount;
        is >> authorCount;
        is.ignore();
        std::vector<std::string> authors;
        for (int j = 0; j < authorCount; ++j) {
            std::string author;
            std::getline(is, author);
            authors.push_back(author);
        }
        std::string journal, title;
        int year;
        std::getline(is, journal);
        std::getline(is, title);
        is >> year;
        is.ignore();
        publications.emplace_back(authors, journal, title, year);
    }
    setPublications(publications);

    int presentations, patents, degree;
    is >> presentations >> patents >> degree;
    is.ignore();
    setConferencePresentations(presentations);
    setPatentsCount(patents);
    setAcademicDegree(static_cast<AcademicDegree>(degree));

    // Teacher info
    std::vector<std::string> disciplines;
    int discCount;
    is >> discCount;
    is.ignore();
    for (int i = 0; i < discCount; ++i) {
        std::string disc;
        std::getline(is, disc);
        disciplines.push_back(disc);
    }
    setDisciplines(disciplines);

    unsigned int hours;
    is >> hours;
    is.ignore();
    setYearlyHours(hours);

    std::vector<std::string> groups;
    int groupCount;
    is >> groupCount;
    is.ignore();
    for (int i = 0; i < groupCount; ++i) {
        std::string group;
        std::getline(is, group);
        groups.push_back(group);
    }
    setGroups(groups);

    unsigned int exp;
    is >> exp;
    is.ignore();
    setWorkExperience(exp);
}