#pragma once
#include "ResearchTeachingStaff.h"
#include <vector>
#include <algorithm>
#include <iterator>

class ResearchStaffContainer {
private:
    std::vector<ResearchTeachingStaff> staffMembers;

public:
    // Iterator class
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ResearchTeachingStaff;
        using difference_type = std::ptrdiff_t;
        using pointer = ResearchTeachingStaff*;
        using reference = ResearchTeachingStaff&;

    private:
        std::vector<ResearchTeachingStaff>::iterator it;
    public:
        Iterator(std::vector<ResearchTeachingStaff>::iterator iterator) : it(iterator) {}

        Iterator& operator++() {
            ++it;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return it == other.it;
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }

        reference operator*() {
            return *it;
        }

        pointer operator->() {
            return &(*it);
        }
    };

    // Const Iterator class
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const ResearchTeachingStaff;
        using difference_type = std::ptrdiff_t;
        using pointer = const ResearchTeachingStaff*;
        using reference = const ResearchTeachingStaff&;

    private:
        std::vector<ResearchTeachingStaff>::const_iterator it;
    public:
        ConstIterator(std::vector<ResearchTeachingStaff>::const_iterator iterator) : it(iterator) {}

        ConstIterator& operator++() {
            ++it;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const ConstIterator& other) const {
            return it == other.it;
        }

        bool operator!=(const ConstIterator& other) const {
            return it != other.it;
        }

        reference operator*() const {
            return *it;
        }

        pointer operator->() const {
            return &(*it);
        }
    };


    void addStaff(const ResearchTeachingStaff& staff) {
        staffMembers.push_back(staff);
    }

    void removeStaff(size_t index) {
        if (index < staffMembers.size()) {
            staffMembers.erase(staffMembers.begin() + index);
        }
    }

    // Iterator access
    Iterator begin() { return Iterator(staffMembers.begin()); }
    Iterator end() { return Iterator(staffMembers.end()); }
    ConstIterator begin() const { return ConstIterator(staffMembers.begin()); }
    ConstIterator end() const { return ConstIterator(staffMembers.end()); }

    // Statistics methods
    double getAverageWorkload() const {
        if (staffMembers.empty()) return 0.0;
        double total = 0.0;
        for (const auto& staff : staffMembers) {
            total += staff.getAnnualHours();
        }
        return total / staffMembers.size();
    }

    double getAverageExperience() const {
        if (staffMembers.empty()) return 0.0;
        double total = 0.0;
        for (const auto& staff : staffMembers) {
            total += staff.getYearsOfExperience();
        }
        return total / staffMembers.size();
    }

    std::vector<ResearchTeachingStaff> getStaffTeachingDiscipline(const std::string& discipline) const {
        std::vector<ResearchTeachingStaff> result;
        for (const auto& staff : staffMembers) {
            const auto& disciplines = staff.getDisciplines();
            if (std::find(disciplines.begin(), disciplines.end(), discipline) != disciplines.end()) {
                result.push_back(staff);
            }
        }
        return result;
    }

    void printAllStaff() const {
        for (const auto& staff : staffMembers) {
            std::cout << staff << "\n---\n";
        }
    }


    void saveToFile(const std::string& filename) const {
        std::ofstream out(filename);
        if (!out) {
            throw std::runtime_error("Cannot open file for writing");
        }

        out << staffMembers.size() << "\n";
        for (const auto& staff : staffMembers) {
            staff.serialize(out);
        }
    }

    // Load from file
    void loadFromFile(const std::string& filename) {
        std::ifstream in(filename);
        if (!in) {
            throw std::runtime_error("Cannot open file for reading");
        }

        staffMembers.clear();
        size_t count;
        in >> count;
        in.ignore(); // Skip newline

        for (size_t i = 0; i < count; ++i) {
            staffMembers.push_back(ResearchTeachingStaff::deserialize(in));
        }
    }

    size_t size() const {
        return staffMembers.size();
    }
};

