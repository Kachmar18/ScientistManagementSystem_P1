# Програмний проект C++: Система обліку науково-педагогічних працівників

## Стислий опис

Дана програма створена у мові C++ для обліку та аналізу діяльності науково-педагогічних працівників. Вона реалізує обробку даних, пошук, статистику та серіалізацію у текстовий файл.

## Функціонал
- Додавання нового співробітника
- Обробка списку співробітників
- Пошук за дисципліною
- Серіалізація / десеріалізація у файл
- Редагування записів
- Демонстрація поліморфізму

## Структура коду
- `main.cpp` — точка входу, меню, основна логіка
- `StaffContainer.h/cpp` — контейнер для об'єктів ResearchTeachingStaff
- `Scientist.h`, `Teacher.h`, `Article.h`, `ResearchTeachingStaff.h` — класи структури даних

## Збірка та запуск

```bash
mkdir build && cd build
cmake ..
make
./main.cpp
```

## Формат даних
- Вхід: текстові дані через std::cin, або зчитуваня з файлу у форматі .txt
- Вихід: вивід у консоль та запис у .txt файл

## Додатково
- UML-діаграма додана в [Додатку 1](https://drive.google.com/file/d/1dFEwmGiKhToCMxhO6o8F1pwcubKhzVdt/view?usp=sharing)
- Вихідний код записаний в [Додатки 3-14](https://drive.google.com/file/d/1dFEwmGiKhToCMxhO6o8F1pwcubKhzVdt/view?usp=sharing)

---

Розроблено в рамках курсової роботи [Технічне завдання](https://docs.google.com/document/d/1jyeA8Fzg7uDy3Ude4M6PUQb08Sw1dalJ/edit?usp=sharing&ouid=113111089409960470576&rtpof=true&sd=true)
