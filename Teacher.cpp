#include "Teacher.h"
#include <algorithm>

Teacher::Teacher(const std::vector<std::string>& disc, int hours,
    const std::vector<std::string>& grps, int experience)
    : disciplines(disc), annualHours(hours),
    groups(grps), yearsOfExperience(experience) {}

Teacher::Teacher(const Teacher& other)
    : disciplines(other.disciplines), annualHours(other.annualHours),
    groups(other.groups), yearsOfExperience(other.yearsOfExperience) {}

Teacher::Teacher(Teacher&& other) noexcept
    : disciplines(std::move(other.disciplines)),
    annualHours(other.annualHours),
    groups(std::move(other.groups)),
    yearsOfExperience(other.yearsOfExperience) {}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        disciplines = other.disciplines;
        annualHours = other.annualHours;
        groups = other.groups;
        yearsOfExperience = other.yearsOfExperience;
    }
    return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept {
    if (this != &other) {
        disciplines = std::move(other.disciplines);
        annualHours = other.annualHours;
        groups = std::move(other.groups);
        yearsOfExperience = other.yearsOfExperience;
    }
    return *this;
}

const std::vector<std::string>& Teacher::getDisciplines() const {
    return disciplines;
}

int Teacher::getAnnualHours() const {
    return annualHours;
}

const std::vector<std::string>& Teacher::getGroups() const {
    return groups;
}

int Teacher::getYearsOfExperience() const {
    return yearsOfExperience;
}

void Teacher::setDisciplines(const std::vector<std::string>& disc) {
    disciplines = disc;
}

void Teacher::setAnnualHours(int hours) {
    annualHours = hours;
}

void Teacher::setGroups(const std::vector<std::string>& grps) {
    groups = grps;
}

void Teacher::setYearsOfExperience(int experience) {
    yearsOfExperience = experience;
}

void Teacher::addDiscipline(const std::string& discipline) {
    disciplines.push_back(discipline);
}

void Teacher::removeDiscipline(const std::string& discipline) {
    disciplines.erase(std::remove(disciplines.begin(), disciplines.end(), discipline),
        disciplines.end());
}

void Teacher::addGroup(const std::string& group) {
    groups.push_back(group);
}

void Teacher::removeGroup(const std::string& group) {
    groups.erase(std::remove(groups.begin(), groups.end(), group),
        groups.end());
}

std::ostream& operator<<(std::ostream& os, const Teacher& teacher) {
    teacher.printInfo(os);
    return os;
}