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
    // In ResearchTeachingStaff.h
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

    // Copy constructor
    ResearchTeachingStaff(const ResearchTeachingStaff& other);

    // Move constructor
    ResearchTeachingStaff(ResearchTeachingStaff&& other) noexcept;

    // Destructor
    ~ResearchTeachingStaff();

    // Assignment operators
    ResearchTeachingStaff& operator=(const ResearchTeachingStaff& other);
    ResearchTeachingStaff& operator=(ResearchTeachingStaff&& other) noexcept;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const ResearchTeachingStaff& rts);
    friend std::istream& operator>>(std::istream& is, ResearchTeachingStaff& rts);

    // Getters
    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getMiddleName() const;

    // Setters
    void setLastName(const std::string& last);
    void setFirstName(const std::string& first);
    void setMiddleName(const std::string& middle);

    // Combined information methods
    std::string getFullName() const;




    // Override virtual method
    void displayInfo() const override;




    // Add these method declarations
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);



    friend std::ostream& operator<<(std::ostream& os, const ResearchTeachingStaff& rts);
    friend std::istream& operator>>(std::istream& is, ResearchTeachingStaff& rts);

};