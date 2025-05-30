#pragma once
#include "ResearchTeachingStaff.h"
#include <vector>
#include <memory>

class StaffContainer {
private:
    std::vector<std::unique_ptr<ResearchTeachingStaff>> staffMembers;

public:
    class Iterator {
    private:
        std::vector<std::unique_ptr<ResearchTeachingStaff>>::iterator it;

    public:
        Iterator(std::vector<std::unique_ptr<ResearchTeachingStaff>>::iterator iterator);

        Iterator& operator++();
        Iterator operator++(int);
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        ResearchTeachingStaff& operator*() const;
        ResearchTeachingStaff* operator->() const;
    };

    void addStaff(std::unique_ptr<ResearchTeachingStaff> staff);
    void displayAll() const;

    double calculateAverageWorkload() const;
    double calculateAverageExperience() const;
    std::vector<ResearchTeachingStaff*> findStaffByDiscipline(const std::string& discipline) const;

    Iterator begin();
    Iterator end();

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};