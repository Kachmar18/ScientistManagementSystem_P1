#include <iostream>
#include <memory>
#include <limits>
#include <sstream>
#include <vector>
#include "StaffContainer.h"

void displayMenu() {
    std::cout << "\n================= MENU =================\n"
        << "1. Add an academic staff member\n"
        << "2. Show information about all employees\n"
        << "3. Search for employees by discipline\n"
        << "4. Display the average workload\n"
        << "5. Display the average length of service\n"
        << "6. Edit an employee\n"  // Новий пункт меню
        << "7. Demonstration of polymorphism\n"
        << "8. Read employees from the file\n"
        << "9. Write employees to the file\n"
        << "10. End the programme\n"
        << "========================================\n"
        << "Enter your choice: ";
}

void addStaffMember(StaffContainer& container) {
    while (true) {
        try {
            ResearchTeachingStaff staff;
            std::cin >> staff;  // тут усі set* викличуть перевірки
            container.addStaff(std::make_unique<ResearchTeachingStaff>(std::move(staff)));
            std::cout << "Staff member added successfully!\n";
            break;  // вийти з циклу, якщо все пройшло успішно
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Input error: " << e.what() << " Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}


void editEmployee(StaffContainer& container) {
    if (container.begin() == container.end()) {
        std::cout << "No employees to edit.\n";
        return;
    }

    int index = 0;
    std::cout << "\n=== Employee List ===\n";
    for (const auto& staff : container) {
        std::cout << index++ << ". " << staff.getFullName() << "\n";
    }

    int employeeNum;
    std::cout << "Enter employee number to edit: ";
    if (!(std::cin >> employeeNum) || employeeNum < 0 || employeeNum >= index) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Invalid selection.\n";
        return;
    }
    std::cin.ignore();

    auto it = container.begin();
    for (int i = 0; i < employeeNum; ++i) {
        ++it;
    }
    ResearchTeachingStaff& staff = *it;

    std::cout << "\n=== EDITING EMPLOYEE ===\n"
        << "1. Edit personal information\n"
        << "2. Edit scientific information\n"
        << "3. Edit teaching information\n"
        << "4. Cancel\n"
        << "Enter your choice: ";

    int editChoice;
    std::cin >> editChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (editChoice) {
    case 1: {
        std::cout << "Enter new personal information:\n";
        // Прямо вводимо частину персональної інформації
        std::string last, first, middle;
        std::cout << "Last name: ";
        std::getline(std::cin, last);
        std::cout << "First name: ";
        std::getline(std::cin, first);
        std::cout << "Middle name: ";
        std::getline(std::cin, middle);
        staff.setLastName(last);
        staff.setFirstName(first);
        staff.setMiddleName(middle);
        break;
    }
    case 2: {
        std::cout << "Enter new scientific information:\n";
        std::cin >> static_cast<Scientist&>(staff);  // використовуємо вже готовий operator>>
        break;
    }
    case 3: {
        std::cout << "Enter new teaching information:\n";
        std::cin >> static_cast<Teacher&>(staff);  // використовуємо готовий operator>>
        break;
    }
    case 4:
        std::cout << "Editing canceled.\n";
        return;
    default:
        std::cout << "Invalid choice.\n";
        return;
    }

    std::cout << "Employee information updated successfully!\n";
}



void searchByDiscipline(const StaffContainer& container) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string discipline;
    std::cout << "Enter discipline to search: ";
    std::getline(std::cin, discipline);

    auto result = container.findStaffByDiscipline(discipline);
    if (result.empty()) {
        std::cout << "No staff members found teaching " << discipline << "\n";
    }
    else {
        std::cout << "\n=== STAFF TEACHING " << discipline << " ===\n";
        for (auto teacher : result) {
            std::cout << *teacher << "\n---\n";
        }
    }
}

void readFromFile(StaffContainer& container) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string filename;
    std::cout << "Enter filename to read from: ";
    std::getline(std::cin, filename);

    try {
        container.loadFromFile(filename);
        std::cout << "Data loaded successfully from " << filename << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}


void writeToFile(const StaffContainer& container) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string filename;
    std::cout << "Enter filename to write to: ";
    std::getline(std::cin, filename);

    try {
        container.saveToFile(filename);
        std::cout << "Data saved successfully to " << filename << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}




void demonstratePolymorphism(StaffContainer& container) {
    if (container.begin() == container.end()) {
        std::cout << "Staff list is empty. Please add staff members first.\n";
        return;
    }

    std::cout << "\n=== Demonstrating late binding with a single pointer ===\n";

    Scientist* ptr = nullptr;

    Scientist baseScientist;
    ptr = &baseScientist;

    std::cout << "Pointing Scientist* to a Scientist object:\n";
    ptr->displayInfo();

    std::cout << "\n";

    // Тепер вказуємо на об’єкт похідного класу ResearchTeachingStaff
    ptr = &(*container.begin());

    std::cout << "Now pointing Scientist* to a ResearchTeachingStaff object:\n";
    ptr->displayInfo();

    std::cout << "\n";
}




int main() {
    StaffContainer container;
    int choice = -1;

    while (choice != 0) {
        displayMenu();
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }
        std::cin.ignore();

        switch (choice) {
            case 1: addStaffMember(container); break;
            case 2: 
                std::cout << "\n=== All Staff ===" << std::endl;
                for (const auto& staff : container) {
                    std::cout << staff << "\n---\n";
                }

                break;
            case 3: searchByDiscipline(container); break;
            case 4:
                std::cout << "Average workload: " 
                          << container.calculateAverageWorkload() << " hours\n";
                break;
            case 5:
                std::cout << "Average experience: "
                          << container.calculateAverageExperience() << " years\n";
                break;
            case 6: editEmployee(container); break;
            case 7: demonstratePolymorphism(container); break;
            case 8: readFromFile(container); break;
            case 9: writeToFile(container); break;
            case 0: std::cout << "Exiting program...\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}