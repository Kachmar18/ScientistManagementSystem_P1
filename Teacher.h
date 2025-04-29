#pragma once
#include <string>
#include <vector>

class Teacher {
private:
    std::vector<std::string> disciplines;
    unsigned int yearlyHours;
    std::vector<std::string> groups;
    unsigned int workExperience; // in years

public:
    // Default constructor
    Teacher();

    // Parameterized constructor
    Teacher(const std::vector<std::string>& disc, unsigned int hours,
        const std::vector<std::string>& grps, unsigned int exp);

    // Copy constructor
    Teacher(const Teacher& other);

    // Move constructor
    Teacher(Teacher&& other) noexcept;

    // Destructor
    ~Teacher();








    // Assignment operators
    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;

    // Function call operator for setting fields
    Teacher& operator()(const std::vector<std::string>& disc, unsigned int hours,
        const std::vector<std::string>& grps, unsigned int exp);

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Teacher& teacher);
    friend std::istream& operator>>(std::istream& is, Teacher& teacher);










    // Getters
    const std::vector<std::string>& getDisciplines() const;
    unsigned int getYearlyHours() const;
    const std::vector<std::string>& getGroups() const;
    unsigned int getWorkExperience() const;

    // Setters
    void setDisciplines(const std::vector<std::string>& disc);
    void setYearlyHours(unsigned int hours);
    void setGroups(const std::vector<std::string>& grps);
    void setWorkExperience(unsigned int exp);

    // Additional methods
    void addDiscipline(const std::string& discipline);
    void removeDiscipline(const std::string& discipline);
    void addGroup(const std::string& group);
    void removeGroup(const std::string& group);





    // In Teacher.h, ensure these declarations exist in the class body
    friend std::ostream& operator<<(std::ostream& os, const Teacher& teacher);
    friend std::istream& operator>>(std::istream& is, Teacher& teacher);


    // Add virtual method declaration
    virtual void displayInfo() const;
};