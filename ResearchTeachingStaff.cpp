#include "ResearchTeachingStaff.h"


ResearchTeachingStaff::ResearchTeachingStaff(
    const std::vector<Article>& pubs, int confPres, int patents, Degree degree,
    const std::vector<std::string>& disc, int hours,
    const std::vector<std::string>& grps, int experience,
    const std::string& lName, const std::string& fName,
    const std::string& mName)
    : Scientist(pubs, confPres, patents, degree),
    Teacher(disc, hours, grps, experience),
    lastName(lName),
    firstName(fName),
    middleName(mName) {}

ResearchTeachingStaff::ResearchTeachingStaff(const ResearchTeachingStaff& other)
    : Scientist(other),
    Teacher(other),
    lastName(other.lastName),
    firstName(other.firstName),
    middleName(other.middleName) {}

ResearchTeachingStaff::ResearchTeachingStaff(ResearchTeachingStaff&& other) noexcept
    : Scientist(std::move(other)),
    Teacher(std::move(other)),
    lastName(std::move(other.lastName)),
    firstName(std::move(other.firstName)),
    middleName(std::move(other.middleName)) {}

ResearchTeachingStaff::~ResearchTeachingStaff() {}

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

std::string ResearchTeachingStaff::getLastName() const {
    return lastName;
}

std::string ResearchTeachingStaff::getFirstName() const {
    return firstName;
}

std::string ResearchTeachingStaff::getMiddleName() const {
    return middleName;
}

void ResearchTeachingStaff::setLastName(const std::string& lName) {
    lastName = lName;
}

void ResearchTeachingStaff::setFirstName(const std::string& fName) {
    firstName = fName;
}

void ResearchTeachingStaff::setMiddleName(const std::string& mName) {
    middleName = mName;
}

std::ostream& operator<<(std::ostream& os, const ResearchTeachingStaff& staff) {
    os << "Name: " << staff.firstName << " " << staff.middleName << " " << staff.lastName << "\n"
        << "Teaching Info:\n"
        << "  Disciplines: ";
    for (const auto& disc : staff.getDisciplines()) {
        os << disc << ", ";
    }
    os << "\n  Annual Hours: " << staff.getAnnualHours()
        << "\n  Years of Experience: " << staff.getYearsOfExperience()
        << "\nResearch Info:\n"
        << "  Publications: " << staff.getPublications().size()
        << "\n  Conference Presentations: " << staff.getConferencePresentations()
        << "\n  Patents: " << staff.getPatentsCount()
        << "\n  Degree: ";

    switch (staff.getAcademicDegree()) {
    case Degree::NONE: os << "None"; break;
    case Degree::CANDIDATE_TECHNICAL: os << "Candidate of Technical Sciences"; break;
    case Degree::CANDIDATE_PHYSICAL_MATHEMATICAL: os << "Candidate of Physical-Mathematical Sciences"; break;
    case Degree::PHD: os << "PhD"; break;
    case Degree::DOCTOR_TECHNICAL: os << "Doctor of Technical Sciences"; break;
    }

    return os;
}

std::istream& operator>>(std::istream& is, ResearchTeachingStaff& staff) {
    std::cout << "Enter first name: ";
    is >> staff.firstName;

    std::cout << "Enter middle name: ";
    is >> staff.middleName;

    std::cout << "Enter last name: ";
    is >> staff.lastName;

    // Note: For complex objects, you would need more sophisticated input handling
    // This is a simplified version

    return is;
}

void ResearchTeachingStaff::serialize(std::ofstream& out) const {
    // Use protected accessors instead of direct member access
    const auto& pubs = getPublicationsInternal();
    out << pubs.size() << "\n";
    for (const auto& pub : pubs) {
        out << pub.getAuthors().size() << "\n";
        for (const auto& author : pub.getAuthors()) {
            out << author << "\n";
        }
        out << pub.getPublicationName() << "\n";
        out << pub.getArticleTitle() << "\n";
        out << pub.getYear() << "\n";
    }
    out << getConferencePresentationsInternal() << "\n";
    out << getPatentsCountInternal() << "\n";
    out << static_cast<int>(getAcademicDegreeInternal()) << "\n";

    // Teacher part
    const auto& discs = getDisciplinesInternal();
    out << discs.size() << "\n";
    for (const auto& disc : discs) {
        out << disc << "\n";
    }
    out << getAnnualHoursInternal() << "\n";

    const auto& grps = getGroupsInternal();
    out << grps.size() << "\n";
    for (const auto& group : grps) {
        out << group << "\n";
    }
    out << getYearsOfExperienceInternal() << "\n";

    // Personal info
    out << lastName << "\n";
    out << firstName << "\n";
    out << middleName << "\n";
}

ResearchTeachingStaff ResearchTeachingStaff::deserialize(std::ifstream& in) {
    // Deserialize Scientist part
    size_t pubCount;
    in >> pubCount;
    std::vector<Article> publications;
    for (size_t i = 0; i < pubCount; ++i) {
        size_t authorCount;
        in >> authorCount;
        in.ignore(); // Skip newline
        std::vector<std::string> authors;
        for (size_t j = 0; j < authorCount; ++j) {
            std::string author;
            std::getline(in, author);
            authors.push_back(author);
        }
        std::string pubName, articleTitle;
        int year;
        std::getline(in, pubName);
        std::getline(in, articleTitle);
        in >> year;
        in.ignore(); // Skip newline
        publications.emplace_back(authors, pubName, articleTitle, year);
    }
    int confPres, patents;
    int degreeInt;
    in >> confPres >> patents >> degreeInt;
    in.ignore();
    Degree degree = static_cast<Degree>(degreeInt);

    // Deserialize Teacher part
    size_t discCount;
    in >> discCount;
    in.ignore();
    std::vector<std::string> disciplines;
    for (size_t i = 0; i < discCount; ++i) {
        std::string disc;
        std::getline(in, disc);
        disciplines.push_back(disc);
    }
    int hours;
    in >> hours;
    in.ignore();

    size_t groupCount;
    in >> groupCount;
    in.ignore();
    std::vector<std::string> groups;
    for (size_t i = 0; i < groupCount; ++i) {
        std::string group;
        std::getline(in, group);
        groups.push_back(group);
    }
    int experience;
    in >> experience;
    in.ignore();

    // Deserialize personal info
    std::string lName, fName, mName;
    std::getline(in, lName);
    std::getline(in, fName);
    std::getline(in, mName);

    return ResearchTeachingStaff(
        publications, confPres, patents, degree,
        disciplines, hours, groups, experience,
        lName, fName, mName
    );
}