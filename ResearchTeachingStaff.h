#pragma once
#include "Scientist.h"
#include "Teacher.h"
#include <string>
#include <iostream>
#include <fstream>

class ResearchTeachingStaff : public Scientist, public Teacher {
private:
    std::string lastName;
    std::string firstName;
    std::string middleName;

public:
    ResearchTeachingStaff(const std::vector<Article>& pubs, int confPres, int patents, Degree degree,
        const std::vector<std::string>& disc, int hours,
        const std::vector<std::string>& grps, int experience,
        const std::string& lName, const std::string& fName,
        const std::string& mName);

    ResearchTeachingStaff(const ResearchTeachingStaff& other);

    ResearchTeachingStaff(ResearchTeachingStaff&& other) noexcept;

    ResearchTeachingStaff() : Scientist({}, 0, 0, Degree::NONE),
        Teacher({}, 0, {}, 0),
        lastName(""), firstName(""), middleName("") {}

    ~ResearchTeachingStaff();

    ResearchTeachingStaff& operator=(const ResearchTeachingStaff& other);
    ResearchTeachingStaff& operator=(ResearchTeachingStaff&& other) noexcept;

    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getMiddleName() const;

    void setLastName(const std::string& lName);
    void setFirstName(const std::string& fName);
    void setMiddleName(const std::string& mName);

    // I/O operators
    friend std::ostream& operator<<(std::ostream& os, const ResearchTeachingStaff& staff);
    friend std::istream& operator>>(std::istream& is, ResearchTeachingStaff& staff);

    void printInfo(std::ostream& os) const override {
        os << "Name: " << firstName << " " << middleName << " " << lastName << "\n";
        Teacher::printInfo(os);
        os << "\n";
        Scientist::printInfo(os);
    }

    friend std::ostream& operator<<(std::ostream& os, const ResearchTeachingStaff& staff);

    void serialize(std::ofstream& out) const;
    static ResearchTeachingStaff deserialize(std::ifstream& in);

};