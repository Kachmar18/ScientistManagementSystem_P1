#pragma once
#include <string>
#include <vector>

class Teacher {
private:
    std::vector<std::string> disciplines;
    unsigned int yearlyHours;
    std::vector<std::string> groups;
    unsigned int workExperience;

public:
    Teacher();
    Teacher(const std::vector<std::string>& disc, unsigned int hours,
        const std::vector<std::string>& grps, unsigned int exp);

    Teacher(const Teacher& other);
    Teacher(Teacher&& other) noexcept;

    ~Teacher();


    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;


    Teacher& operator()(const std::vector<std::string>& disc, unsigned int hours,
        const std::vector<std::string>& grps, unsigned int exp);



    const std::vector<std::string>& getDisciplines() const;
    unsigned int getYearlyHours() const;
    const std::vector<std::string>& getGroups() const;
    unsigned int getWorkExperience() const;


    void setDisciplines(const std::vector<std::string>& disc);
    void setYearlyHours(unsigned int hours);
    void setGroups(const std::vector<std::string>& grps);
    void setWorkExperience(unsigned int exp);

    void addDiscipline(const std::string& discipline);
    void removeDiscipline(const std::string& discipline);
    void addGroup(const std::string& group);
    void removeGroup(const std::string& group);


    friend std::ostream& operator<<(std::ostream& os, const Teacher& teacher);
    friend std::istream& operator>>(std::istream& is, Teacher& teacher);

    virtual void displayInfo() const;
};