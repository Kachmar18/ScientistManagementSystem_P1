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

    // Зчитування даних
    std::cout << "Enter full name (Last First Middle): ";
    std::getline(std::cin, input);

    // Наукові дані
    std::vector<Article> pubs;
    int presentations, patents;
    AcademicDegree deg;

    std::cout << "Enter number of conference presentations: ";
    std::cin >> presentations;

    std::cout << "Enter number of patents: ";
    std::cin >> patents;

    std::cout << "Enter academic degree (0-4): ";
    int degree;
    std::cin >> degree;
    deg = static_cast<AcademicDegree>(degree);

    std::cin.ignore(); // Очистка буфера

    // Педагогічні дані
    std::vector<std::string> disciplines, groups;
    unsigned int hours, exp;

    std::cout << "Enter disciplines (comma separated): ";
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, ',')) {
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);
        if (!item.empty()) disciplines.push_back(item);
    }

    std::cout << "Enter yearly hours: ";
    std::cin >> hours;

    std::cout << "Enter groups (comma separated): ";
    std::cin.ignore();
    std::getline(std::cin, input);
    ss.clear();
    ss.str(input);
    while (std::getline(ss, item, ',')) {
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);
        if (!item.empty()) groups.push_back(item);
    }

    std::cout << "Enter work experience (years): ";
    std::cin >> exp;
    std::cin.ignore();


    staff(input, pubs, presentations, patents, deg, disciplines, hours, groups, exp);

    container.addStaff(std::make_unique<ResearchTeachingStaff>(std::move(staff)));
    std::cout << "Staff member added successfully!\n";
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

    // Вибір працівника з перевіркою
    int employeeNum;
    std::cout << "Enter employee number to edit: ";
    if (!(std::cin >> employeeNum) || employeeNum < 0 || employeeNum >= index) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Invalid selection.\n";
        return;
    }
    std::cin.ignore();


    int count = 0;
    for (auto it = container.begin(); it != container.end(); ++it) {
        count++;
    }

    if (employeeNum < 0 || employeeNum >= count) {
        std::cout << "Invalid employee number.\n";
        return;
    }

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


void demonstratePolymorphism(Scientist* sci) {
    sci->displayInfo();  // Late binding demonstration
}

void demonstratePolymorphism(StaffContainer& container) {
    if (container.begin() == container.end()) {
        std::cout << "Staff list is empty. Please add staff members first.\n";
        return;
    }

    std::cout << "\n=== POLYMORPHISM DEMONSTRATION ===\n";

    auto& firstStaff = *container.begin();

    // 1. Виклик віртуального методу безпосередньо
    std::cout << "\n1. Direct virtual method call:\n";
    firstStaff.displayInfo();

    // 2. Пізнє зв'язування через вказівники на базові класи
    std::cout << "\n2. Late binding through base class pointers:\n";


    Scientist* sciPtr = &firstStaff;
    Teacher* teachPtr = &firstStaff;

    std::cout << "Call through Scientist* pointer:\n";
    sciPtr->displayInfo();

    std::cout << "\nCall through Teacher* pointer:\n";
    teachPtr->displayInfo();

    // 3. Демонстрація через функцію, що приймає базовий клас
    std::cout << "\n3. Demonstration through function accepting Scientist*:\n";
    demonstratePolymorphism(sciPtr);
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
            case 6: readFromFile(container); break;
            case 7: writeToFile(container); break;
            case 8: editEmployee(container); break;
            case 9: demonstratePolymorphism(container); break;
            case 0: std::cout << "Exiting program...\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}