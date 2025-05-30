#include "Teacher.h"
#include <algorithm>
#include <sstream>
#include <iostream>

Teacher::Teacher()
    : yearlyHours(0), workExperience(0) {}

Teacher::Teacher(const std::vector<std::string>& disc, unsigned int hours,
    const std::vector<std::string>& grps, unsigned int exp)
    : disciplines(disc), yearlyHours(hours), groups(grps), workExperience(exp) {}

Teacher::Teacher(const Teacher& other)
    : disciplines(other.disciplines), yearlyHours(other.yearlyHours),
    groups(other.groups), workExperience(other.workExperience) {}

Teacher::Teacher(Teacher&& other) noexcept
    : disciplines(std::move(other.disciplines)), yearlyHours(other.yearlyHours),
    groups(std::move(other.groups)), workExperience(other.workExperience) {}

Teacher::~Teacher() {}



Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        disciplines = other.disciplines;
        yearlyHours = other.yearlyHours;
        groups = other.groups;
        workExperience = other.workExperience;
    }
    return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept {
    if (this != &other) {
        disciplines = std::move(other.disciplines);
        yearlyHours = other.yearlyHours;
        groups = std::move(other.groups);
        workExperience = other.workExperience;
    }
    return *this;
}

Teacher& Teacher::operator()(const std::vector<std::string>& disc, unsigned int hours,
    const std::vector<std::string>& grps, unsigned int exp) {
    disciplines = disc;
    yearlyHours = hours;
    groups = grps;
    workExperience = exp;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Teacher& teacher) {
    os << "Disciplines: ";
    for (const auto& disc : teacher.getDisciplines()) {
        os << disc << ", ";
    }
    os << "\nYearly hours: " << teacher.getYearlyHours();
    os << "\nGroups: ";
    for (const auto& group : teacher.getGroups()) {
        os << group << ", ";
    }
    os << "\nWork experience: " << teacher.getWorkExperience() << " years";
    return os;
}

std::istream& operator>>(std::istream& is, Teacher& teacher) {
    std::string line;

    // Read disciplines
    std::cout << "Enter disciplines (comma separated): ";
    std::getline(is, line);
    std::vector<std::string> disciplines;
    std::stringstream ss(line);
    std::string discipline;
    while (std::getline(ss, discipline, ',')) {
        discipline.erase(0, discipline.find_first_not_of(" \t"));
        discipline.erase(discipline.find_last_not_of(" \t") + 1);
        if (!discipline.empty()) disciplines.push_back(discipline);
    }
    teacher.setDisciplines(disciplines);

    std::cout << "Enter yearly hours: ";
    unsigned int hours;
    is >> hours;
    teacher.setYearlyHours(hours);
    is.ignore(); // ignore newline

    std::cout << "Enter groups (comma separated): ";
    std::getline(is, line);
    std::vector<std::string> groups;
    ss.clear();
    ss.str(line);
    std::string group;
    while (std::getline(ss, group, ',')) {
        group.erase(0, group.find_first_not_of(" \t"));
        group.erase(group.find_last_not_of(" \t") + 1);
        if (!group.empty()) groups.push_back(group);
    }
    teacher.setGroups(groups);

    std::cout << "Enter work experience (years): ";
    unsigned int exp;
    is >> exp;
    teacher.setWorkExperience(exp);
    is.ignore();

    return is;
}




const std::vector<std::string>& Teacher::getDisciplines() const { return disciplines; }
unsigned int Teacher::getYearlyHours() const { return yearlyHours; }
const std::vector<std::string>& Teacher::getGroups() const { return groups; }
unsigned int Teacher::getWorkExperience() const { return workExperience; }

void Teacher::setDisciplines(const std::vector<std::string>& disc) { disciplines = disc; }
void Teacher::setYearlyHours(unsigned int hours) { yearlyHours = hours; }
void Teacher::setGroups(const std::vector<std::string>& grps) { groups = grps; }
void Teacher::setWorkExperience(unsigned int exp) { workExperience = exp; }




void Teacher::addDiscipline(const std::string& discipline) {
    if (std::find(disciplines.begin(), disciplines.end(), discipline) == disciplines.end()) {
        disciplines.push_back(discipline);
    }
}

void Teacher::removeDiscipline(const std::string& discipline) {
    auto it = std::find(disciplines.begin(), disciplines.end(), discipline);
    if (it != disciplines.end()) {
        disciplines.erase(it);
    }
}

void Teacher::addGroup(const std::string& group) {
    if (std::find(groups.begin(), groups.end(), group) == groups.end()) {
        groups.push_back(group);
    }
}

void Teacher::removeGroup(const std::string& group) {
    auto it = std::find(groups.begin(), groups.end(), group);
    if (it != groups.end()) {
        groups.erase(it);
    }
}



void Teacher::displayInfo() const {
    std::cout << "--- Teaching Information ---\n";
    std::cout << "Disciplines: ";
    for (const auto& d : getDisciplines()) {
        std::cout << d << ", ";
    }
    std::cout << "\nYearly hours: " << getYearlyHours() << "\n";
    std::cout << "Groups: ";
    for (const auto& g : getGroups()) {
        std::cout << g << ", ";
    }
    std::cout << "\nExperience: " << getWorkExperience() << " years\n";
}