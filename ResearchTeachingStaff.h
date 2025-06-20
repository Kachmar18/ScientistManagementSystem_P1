#pragma once
#include "Scientist.h"
#include "Teacher.h"
#include <string>

class ResearchTeachingStaff : public Scientist, public Teacher {
private:
    std::string lastName;
    std::string firstName;
    std::string middleName;

public:
    ResearchTeachingStaff(
        const std::string& last = "",
        const std::string& first = "",
        const std::string& middle = "",
        const std::vector<Article>& pubs = {},
        int presentations = 0,
        int patents = 0,
        AcademicDegree deg = AcademicDegree::NONE,
        const std::vector<std::string>& disc = {},
        unsigned int hours = 0,
        const std::vector<std::string>& grps = {},
        unsigned int exp = 0
    );

    ResearchTeachingStaff& operator()(
        const std::string& fullName,  // "������� ��'� ��-�������"
        const std::vector<Article>& pubs,
        int presentations,
        int patents,
        AcademicDegree deg,
        const std::vector<std::string>& disc,
        unsigned int hours,
        const std::vector<std::string>& grps,
        unsigned int exp
        );

    ResearchTeachingStaff(const ResearchTeachingStaff& other);
    ResearchTeachingStaff(ResearchTeachingStaff&& other) noexcept;

    ~ResearchTeachingStaff();

    ResearchTeachingStaff& operator=(const ResearchTeachingStaff& other);
    ResearchTeachingStaff& operator=(ResearchTeachingStaff&& other) noexcept;

    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getMiddleName() const;

    void setLastName(const std::string& last);
    void setFirstName(const std::string& first);
    void setMiddleName(const std::string& middle);

    std::string getFullName() const {
        return lastName + " " + firstName + " " + middleName;
    }

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);


    friend std::ostream& operator<<(std::ostream& os, const ResearchTeachingStaff& rts);
    friend std::istream& operator>>(std::istream& is, ResearchTeachingStaff& rts);

    void displayInfo() const override;

};