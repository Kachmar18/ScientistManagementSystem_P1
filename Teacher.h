#pragma once
#include <string>
#include <vector>
#include <iostream> 
#include <ostream>

class Teacher {
    friend class ResearchTeachingStaff;
private:
    std::vector<std::string> disciplines;
    int annualHours;
    std::vector<std::string> groups;
    int yearsOfExperience;

protected:
    // Add these protected methods for derived classes
    const std::vector<std::string>& getDisciplinesInternal() const { return disciplines; }
    int getAnnualHoursInternal() const { return annualHours; }
    const std::vector<std::string>& getGroupsInternal() const { return groups; }
    int getYearsOfExperienceInternal() const { return yearsOfExperience; }
    
public:
    Teacher(const std::vector<std::string>& disc, int hours,
        const std::vector<std::string>& grps, int experience);

    Teacher(const Teacher& other);

    Teacher(Teacher&& other) noexcept;

    virtual ~Teacher() = default;

    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;

    const std::vector<std::string>& getDisciplines() const;
    int getAnnualHours() const;
    const std::vector<std::string>& getGroups() const;
    int getYearsOfExperience() const;

    void setDisciplines(const std::vector<std::string>& disc);
    void setAnnualHours(int hours);
    void setGroups(const std::vector<std::string>& grps);
    void setYearsOfExperience(int experience);

    void addDiscipline(const std::string& discipline);
    void removeDiscipline(const std::string& discipline);
    void addGroup(const std::string& group);
    void removeGroup(const std::string& group);


    virtual void printInfo(std::ostream& os) const {
        os << "Teaching Info:\n"
            << "  Disciplines: ";
        for (const auto& disc : disciplines) {
            os << disc << ", ";
        }
        os << "\n  Annual Hours: " << annualHours << "\n"
            << "  Years of Experience: " << yearsOfExperience;
    }

    friend std::ostream& operator<<(std::ostream& os, const Teacher& teacher);
};