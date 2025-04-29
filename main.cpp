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
        << "6. Read employees from the file\n"
        << "7. Write employees to the file\n"
        << "8. Edit an employee\n"  // Новий пункт меню
        << "9. Demonstration of polymorphism\n"
        << "10. End the programme\n"
        << "========================================\n"
        << "Enter your choice: ";
}

void addStaffMember(StaffContainer& container) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    ResearchTeachingStaff staff;
    std::string input;

    // Personal info
    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    staff.setLastName(input);

    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    staff.setFirstName(input);

    std::cout << "Enter middle name: ";
    std::getline(std::cin, input);
    staff.setMiddleName(input);

    // Scientific info
    std::cout << "Enter scientific information (use operator>>):\n";
    std::cin >> static_cast<Scientist&>(staff);

    // Teaching info
    std::cout << "Enter teaching information (use operator>>):\n";
    std::cin >> static_cast<Teacher&>(staff);

    container.addStaff(std::make_unique<ResearchTeachingStaff>(std::move(staff)));
    std::cout << "Staff member added successfully!\n";
}

void editEmployee(StaffContainer& container) {
    if (container.begin() == container.end()) {
        std::cout << "No employees to edit. Please add employees first.\n";
        return;
    }

    // Показати список працівників для вибору
    std::cout << "\n=== LIST OF EMPLOYEES ===\n";
    int index = 0;
    for (auto it = container.begin(); it != container.end(); ++it, ++index) {
        std::cout << index << ". " << it->getLastName() << " "
            << it->getFirstName() << " " << it->getMiddleName() << "\n";
    }

    std::cout << "Enter employee number to edit: ";
    int employeeNum;
    std::cin >> employeeNum;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Визначаємо кількість працівників
    int count = 0;
    for (auto it = container.begin(); it != container.end(); ++it) {
        count++;
    }

    if (employeeNum < 0 || employeeNum >= count) {
        std::cout << "Invalid employee number.\n";
        return;
    }

    // Знаходимо працівника за індексом
    auto it = container.begin();
    for (int i = 0; i < employeeNum; ++i) {
        ++it;
    }
    ResearchTeachingStaff& staff = *it;

    // Меню редагування
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
        std::string lastName, firstName, middleName;
        std::cout << "Enter new last name: ";
        std::getline(std::cin, lastName);
        std::cout << "Enter new first name: ";
        std::getline(std::cin, firstName);
        std::cout << "Enter new middle name: ";
        std::getline(std::cin, middleName);

        staff.setLastName(lastName);
        staff.setFirstName(firstName);
        staff.setMiddleName(middleName);
        break;
    }
    case 2: {
        std::cout << "Enter new scientific information:\n";
        std::cin >> static_cast<Scientist&>(staff);
        break;
    }
    case 3: {
        std::cout << "Enter new teaching information:\n";
        std::cin >> static_cast<Teacher&>(staff);
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

// Add this overload before the main function
void demonstratePolymorphism(Scientist* sci) {
    sci->displayInfo();  // Late binding demonstration
}

void demonstratePolymorphism(StaffContainer& container) {
    if (container.begin() == container.end()) {
        std::cout << "Staff list is empty. Please add staff members first.\n";
        return;
    }

    std::cout << "\n=== POLYMORPHISM DEMONSTRATION ===\n";

    // 1. Virtual methods
    std::cout << "\n1. Virtual methods (displayInfo()):\n";
    std::cout << "Call through derived class object:\n";
    (*container.begin()).displayInfo();

    // 2. Late binding through base class pointers
    std::cout << "\n2. Late binding through base class pointers:\n";

    // Create vector of base class pointers
    std::vector<Scientist*> scientists;
    std::vector<Teacher*> teachers;

    for (auto it = container.begin(); it != container.end(); ++it) {
        scientists.push_back(&(*it));  // As Scientist*
        teachers.push_back(&(*it));    // As Teacher*
    }

    std::cout << "Call through Scientist* pointer:\n";
    scientists[0]->displayInfo();

    std::cout << "\nCall through Teacher* pointer:\n";
    teachers[0]->displayInfo();

    // 3. Demonstration through function
    std::cout << "\n3. Demonstration through function accepting Scientist*:\n";
    demonstratePolymorphism(scientists[0]);
}


int main() {
    StaffContainer container;
    int choice = 0;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: addStaffMember(container); break;
        case 2:
            std::cout << "\n=== ALL STAFF MEMBERS ===\n";
            for (auto it = container.begin(); it != container.end(); ++it) {
                std::cout << *it << "\n---\n";
            }
            break;
        case 3: searchByDiscipline(container); break;
        case 4:
            std::cout << "Average workload: "
                << container.calculateAverageWorkload() << " hours\n";
            break;
        case 5:
            std::cout << "Average length of service: "
                << container.calculateAverageExperience() << " years\n";
            break;
        case 6: readFromFile(container); break;
        case 7: writeToFile(container); break;
        case 8: editEmployee(container); break;  // Новий пункт меню
        case 9: demonstratePolymorphism(container); break;
        case 10: std::cout << "Exiting program...\n"; break;
        default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}