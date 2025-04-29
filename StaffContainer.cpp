#include "StaffContainer.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>

// Iterator implementation
StaffContainer::Iterator::Iterator(std::vector<std::unique_ptr<ResearchTeachingStaff>>::iterator iterator)
    : it(iterator) {}

StaffContainer::Iterator& StaffContainer::Iterator::operator++() {
    ++it;
    return *this;
}

StaffContainer::Iterator StaffContainer::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool StaffContainer::Iterator::operator!=(const Iterator& other) const {
    return it != other.it;
}

bool StaffContainer::Iterator::operator==(const Iterator& other) const {
    return it == other.it;
}



ResearchTeachingStaff& StaffContainer::Iterator::operator*() const {
    return **it;
}

ResearchTeachingStaff* StaffContainer::Iterator::operator->() const {
    return it->get();
}

// Container implementation
void StaffContainer::addStaff(std::unique_ptr<ResearchTeachingStaff> staff) {
    staffMembers.push_back(std::move(staff));
}

void StaffContainer::displayAll() const {
    for (const auto& staff : staffMembers) {
        staff->displayInfo();  // Polymorphic call
        std::cout << "------------------------\n";
    }
}

double StaffContainer::calculateAverageWorkload() const {
    if (staffMembers.empty()) return 0.0;

    double total = std::accumulate(staffMembers.begin(), staffMembers.end(), 0.0,
        [](double sum, const std::unique_ptr<ResearchTeachingStaff>& staff) {
            return sum + staff->getYearlyHours();
        });

    return total / staffMembers.size();
}

double StaffContainer::calculateAverageExperience() const {
    if (staffMembers.empty()) return 0.0;

    double total = std::accumulate(staffMembers.begin(), staffMembers.end(), 0.0,
        [](double sum, const std::unique_ptr<ResearchTeachingStaff>& staff) {
            return sum + staff->getWorkExperience();
        });

    return total / staffMembers.size();
}

std::vector<ResearchTeachingStaff*> StaffContainer::findStaffByDiscipline(const std::string& discipline) const {
    std::vector<ResearchTeachingStaff*> result;

    for (const auto& staff : staffMembers) {
        const auto& disciplines = staff->getDisciplines();
        if (std::find(disciplines.begin(), disciplines.end(), discipline) != disciplines.end()) {
            result.push_back(staff.get());
        }
    }

    return result;
}

StaffContainer::Iterator StaffContainer::begin() {
    return Iterator(staffMembers.begin());
}

StaffContainer::Iterator StaffContainer::end() {
    return Iterator(staffMembers.end());
}



void StaffContainer::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Cannot open file for writing");
    }

    outFile << staffMembers.size() << "\n";
    for (const auto& staff : staffMembers) {
        staff->serialize(outFile);
    }
}

void StaffContainer::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Cannot open file for reading");
    }

    staffMembers.clear();
    int count;
    inFile >> count;
    inFile.ignore();

    for (int i = 0; i < count; ++i) {
        auto staff = std::make_unique<ResearchTeachingStaff>();
        staff->deserialize(inFile);
        staffMembers.push_back(std::move(staff));
    }
}