#define NOMINMAX
#include <iostream>
#include <fstream>
#include <limits>
#include <windows.h>
#include "ResearchStaffContainer.h"

void displayMenu() {
    std::cout << "\n================= МЕНЮ =================\n";
    std::cout << "1. Додати науково-педагогічного працівника\n";
    std::cout << "2. Показати інформацію про всіх працівників\n";
    std::cout << "3. Пошук працівників за дисципліною\n";
    std::cout << "4. Вивести середнє навантаження\n";
    std::cout << "5. Вивести середній стаж роботи\n";
    std::cout << "6. Зчитати працівників з файлу\n";
    std::cout << "7. Записати працівників у файл\n";
    std::cout << "8. Редагувати працівника\n";  // Нова опція
    std::cout << "9. Завершити програму\n";
    std::cout << "========================================\n";
    std::cout << "Виберіть опцію: ";
}

void addStaffMember(ResearchStaffContainer& container) {
    try {
        std::cout << "\n=== Додавання нового працівника ===\n";

        // Використовуємо конструктор з параметрами
        std::vector<Article> publications;
        int confPres, patents;
        Degree degree = Degree::NONE;
        std::vector<std::string> disciplines;
        int hours;
        std::vector<std::string> groups;
        int experience;
        std::string lastName, firstName, middleName;

        // Введення даних через існуючі методи
        std::cout << "Прізвище: "; std::cin >> lastName;
        std::cout << "Ім'я: "; std::cin >> firstName;
        std::cout << "По батькові: "; std::cin >> middleName;

        // Використовуємо методи addDiscipline та addGroup
        std::cout << "Кількість дисциплін: ";
        int discCount; std::cin >> discCount;
        for (int i = 0; i < discCount; ++i) {
            std::string disc;
            std::cout << "Дисципліна " << i + 1 << ": ";
            std::cin >> disc;
            disciplines.push_back(disc);
        }

        std::cout << "Навантаження: "; std::cin >> hours;

        std::cout << "Кількість груп: ";
        int groupCount; std::cin >> groupCount;
        for (int i = 0; i < groupCount; ++i) {
            std::string group;
            std::cout << "Група " << i + 1 << ": ";
            std::cin >> group;
            groups.push_back(group);
        }

        std::cout << "Стаж: "; std::cin >> experience;

        // Використовуємо методи для науковця
        std::cout << "Кількість публікацій: ";
        int pubCount; std::cin >> pubCount;
        for (int i = 0; i < pubCount; ++i) {
            std::vector<std::string> authors;
            std::string pubName, articleTitle;
            int year;

            std::cout << "Кількість авторів: ";
            int authCount; std::cin >> authCount;
            for (int j = 0; j < authCount; ++j) {
                std::string author;
                std::cout << "Автор " << j + 1 << ": ";
                std::cin >> author;
                authors.push_back(author);
            }

            std::cout << "Назва видання: "; std::cin >> pubName;
            std::cout << "Назва статті: "; std::cin >> articleTitle;
            std::cout << "Рік: "; std::cin >> year;

            publications.emplace_back(authors, pubName, articleTitle, year);
        }

        std::cout << "Виступи на конференціях: "; std::cin >> confPres;
        std::cout << "Патенти: "; std::cin >> patents;

        std::cout << "Ступінь (0-4): ";
        int deg; std::cin >> deg;
        degree = static_cast<Degree>(deg);

        // Використовуємо існуючий конструктор ResearchTeachingStaff
        ResearchTeachingStaff newStaff(
            publications, confPres, patents, degree,
            disciplines, hours, groups, experience,
            lastName, firstName, middleName
        );

        container.addStaff(newStaff);
        std::cout << "Працівника додано!\n";

    }
    catch (...) {
        std::cout << "Помилка при додаванні!\n";
    }
}

void showAllStaff(ResearchStaffContainer& container) {
    std::cout << "\n=== Список працівників ===\n";
    // Використовуємо ітератор контейнера
    for (auto it = container.begin(); it != container.end(); ++it) {
        // Використовуємо перевантажений оператор <<
        std::cout << *it << "\n---\n";
    }
}

void searchByDiscipline(ResearchStaffContainer& container) {
    std::string discipline;
    std::cout << "Введіть дисципліну: ";
    std::cin >> discipline;

    // Використовуємо готовий метод контейнера
    auto result = container.getStaffTeachingDiscipline(discipline);

    if (result.empty()) {
        std::cout << "Не знайдено!\n";
        return;
    }

    std::cout << "Знайдено " << result.size() << " працівників:\n";
    for (const auto& staff : result) {
        std::cout << staff.getLastName() << " "
            << staff.getFirstName() << "\n";
    }
}

void showAverageWorkload(ResearchStaffContainer& container) {
    // Використовуємо готовий метод
    std::cout << "Середнє навантаження: "
        << container.getAverageWorkload() << " годин\n";
}

void showAverageExperience(ResearchStaffContainer& container) {
    // Використовуємо готовий метод
    std::cout << "Середній стаж: "
        << container.getAverageExperience() << " років\n";
}

void loadFromFile(ResearchStaffContainer& container) {
    std::string filename;
    std::cout << "Ім'я файлу: ";
    std::cin >> filename;

    try {
        // Використовуємо готовий метод
        container.loadFromFile(filename);
        std::cout << "Дані завантажено!\n";
    }
    catch (...) {
        std::cout << "Помилка завантаження!\n";
    }
}

void saveToFile(ResearchStaffContainer& container) {
    std::string filename;
    std::cout << "Ім'я файлу: ";
    std::cin >> filename;

    try {
        // Використовуємо готовий метод
        container.saveToFile(filename);
        std::cout << "Дані збережено!\n";
    }
    catch (...) {
        std::cout << "Помилка збереження!\n";
    }
}

void editStaffMember(ResearchStaffContainer& container) {
    if (container.size() == 0) {
        std::cout << "\nНемає працівників для редагування!\n";
        return;
    }

    // Показуємо список працівників для вибору
    std::cout << "\n=== Список працівників ===\n";
    int index = 0;
    for (auto it = container.begin(); it != container.end(); ++it, ++index) {
        std::cout << index << ": " << it->getLastName() << " "
            << it->getFirstName() << "\n";
    }

    // Вибір працівника
    std::cout << "\nВведіть номер працівника для редагування: ";
    size_t staffIndex;
    std::cin >> staffIndex;

    if (staffIndex >= container.size()) {
        std::cout << "Невірний номер!\n";
        return;
    }

    // Отримуємо працівника за індексом
    auto it = container.begin();
    std::advance(it, staffIndex);
    ResearchTeachingStaff& staff = *it;

    // Меню редагування
    int choice;
    do {
        std::cout << "\n=== Редагування працівника ===\n";
        std::cout << "1. Змінити особисті дані\n";
        std::cout << "2. Змінити педагогічні дані\n";
        std::cout << "3. Змінити наукові дані\n";
        std::cout << "4. Переглянути поточні дані\n";
        std::cout << "5. Завершити редагування\n";
        std::cout << "Виберіть опцію: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            // Редагування особистих даних
            std::string lastName, firstName, middleName;
            std::cout << "Нове прізвище: ";
            std::cin >> lastName;
            std::cout << "Нове ім'я: ";
            std::cin >> firstName;
            std::cout << "Нове по батькові: ";
            std::cin >> middleName;

            staff.setLastName(lastName);
            staff.setFirstName(firstName);
            staff.setMiddleName(middleName);
            break;
        }
        case 2: {
            // Редагування педагогічних даних
            std::vector<std::string> disciplines;
            int hours, experience;
            std::vector<std::string> groups;

            std::cout << "Нова кількість дисциплін: ";
            int discCount;
            std::cin >> discCount;
            for (int i = 0; i < discCount; ++i) {
                std::string disc;
                std::cout << "Дисципліна " << i + 1 << ": ";
                std::cin >> disc;
                disciplines.push_back(disc);
            }

            std::cout << "Нове навантаження: ";
            std::cin >> hours;

            std::cout << "Нова кількість груп: ";
            int groupCount;
            std::cin >> groupCount;
            for (int i = 0; i < groupCount; ++i) {
                std::string group;
                std::cout << "Група " << i + 1 << ": ";
                std::cin >> group;
                groups.push_back(group);
            }

            std::cout << "Новий стаж: ";
            std::cin >> experience;

            staff.setDisciplines(disciplines);
            staff.setAnnualHours(hours);
            staff.setGroups(groups);
            staff.setYearsOfExperience(experience);
            break;
        }
        case 3: {
            // Редагування наукових даних
            std::vector<Article> publications;
            int confPres, patents;
            Degree degree;

            std::cout << "Нова кількість публікацій: ";
            int pubCount;
            std::cin >> pubCount;
            for (int i = 0; i < pubCount; ++i) {
                std::vector<std::string> authors;
                std::string pubName, articleTitle;
                int year;

                std::cout << "Кількість авторів: ";
                int authCount;
                std::cin >> authCount;
                for (int j = 0; j < authCount; ++j) {
                    std::string author;
                    std::cout << "Автор " << j + 1 << ": ";
                    std::cin >> author;
                    authors.push_back(author);
                }

                std::cout << "Назва видання: "; std::cin >> pubName;
                std::cout << "Назва статті: "; std::cin >> articleTitle;
                std::cout << "Рік: "; std::cin >> year;

                publications.emplace_back(authors, pubName, articleTitle, year);
            }

            std::cout << "Нова кількість виступів: ";
            std::cin >> confPres;
            std::cout << "Нова кількість патентів: ";
            std::cin >> patents;

            std::cout << "Новий ступінь (0-4): ";
            int deg; std::cin >> deg;
            degree = static_cast<Degree>(deg);

            staff.setPublications(publications);
            staff.setConferencePresentations(confPres);
            staff.setPatentsCount(patents);
            staff.setAcademicDegree(degree);
            break;
        }
        case 4:
            std::cout << "\nПоточні дані працівника:\n";
            std::cout << staff << "\n";
            break;
        case 5:
            std::cout << "Редагування завершено.\n";
            break;
        default:
            std::cout << "Невірний вибір!\n";
        }
    } while (choice != 5);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    ResearchStaffContainer container;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: addStaffMember(container); break;
        case 2: showAllStaff(container); break;
        case 3: searchByDiscipline(container); break;
        case 4: showAverageWorkload(container); break;
        case 5: showAverageExperience(container); break;
        case 6: loadFromFile(container); break;
        case 7: saveToFile(container); break;
        case 8: editStaffMember(container); break;
        case 9: std::cout << "Вихід...\n"; break;
        default: std::cout << "Невірний вибір!\n";
        }
    } while (choice != 9);

    return 0;
}