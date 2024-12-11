#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <string>
#include <limits>

using namespace std;

// Предварительное объявление структуры, функций поиска и проверки дубликатов.
struct Man;
int FindPos(Man*& obj, int size);
bool Find(string name, Man*& obj, int size);
int language; // Переменная для выбора языка интерфейса.

// Структура, описывающая данные о студенте.
struct Man
{
    string surname; // Фамилия
    string name;    // Имя
    int age;        // Возраст
    string date;    // Дата рождения
    string group;   // Группа

    // Инициализация полей студента
    void init()
    {
        if (language == 1) {
            cout << "Init Surname: ";
            cin >> surname;
            cout << "Init Name: ";
            cin >> name;
            cout << "Init Age: ";
            cin >> age;
            cout << "Init Date of Birth: ";
            cin >> date;
            cout << "Init Group: ";
            cin >> group;
        }
        else {
            cout << "Введите фамилию: ";
            cin >> surname;
            cout << "Введите имя: ";
            cin >> name;
            cout << "Введите возраст: ";
            cin >> age;
            cout << "Введите дату рождения: ";
            cin >> date;
            cout << "Введите группу: ";
            cin >> group;
        }
    }

    // Редактирование данных о студенте
    void Edit()
    {
        if (language == 1) {
            cout << "Enter new Surname: ";
            cin >> surname;
            cout << "Enter new Name: ";
            cin >> name;
            cout << "Enter new Age: ";
            cin >> age;
            cout << "Enter new Date of Birth: ";
            cin >> date;
            cout << "Enter new Group: ";
            cin >> group;
        }
        else {
            cout << "Введите новую фамилию: ";
            cin >> surname;
            cout << "Введите новое имя: ";
            cin >> name;
            cout << "Введите новый возраст: ";
            cin >> age;
            cout << "Введите новую дату рождения: ";
            cin >> date;
            cout << "Введите новую группу: ";
            cin >> group;
        }
    }

    // Вывод информации о студенте
    void show()
    {
        if (language == 1) {
            cout << "Surname: " << surname << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Date of Birth: " << date << endl;
            cout << "Group: " << group << endl;
        }
        else {
            cout << "Фамилия: " << surname << endl;
            cout << "Имя: " << name << endl;
            cout << "Возраст: " << age << endl;
            cout << "Дата рождения: " << date << endl;
            cout << "Группа: " << group << endl;
        }
    }

    // Добавление нового студента в массив
    void add(Man*& man, int& size)
    {
        if (man == nullptr)
        {
            size++;
            man = new Man[size];
            man[0].init();
        }
        else
        {
            size++;
            Man* tmp = man;
            man = new Man[size];
            for (int i = 0; i < size - 1; i++)
            {
                man[i] = tmp[i];
            }
            man[size - 1].init();
            delete[] tmp;
        }
        cout << endl;
        if (language == 1)
            cout << "The student has been added!" << endl;
        else
            cout << "Студент был добавлен!" << endl;
    }

};

// Поиск позиции студента по фамилии. Возвращает индекс или -1, если не найден
int FindPos(Man*& obj, int size)
{
    string str;
    if (language == 1)
        cout << "Enter the student's surname: ";
    else
        cout << "Введите фамилию студента: ";
    cin >> str;

    for (int i = 0; i < size; i++)
    {
        if (obj[i].surname == str) {
            return i;
        }
    }

    if (language == 1)
        cout << "Student not found." << endl;
    else
        cout << "Студент не найден." << endl;
    return -1; // не найден
}

// Проверка, добавлен ли уже студент с таким именем
bool Find(string name, Man*& obj, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (name == obj[i].name)
        {
            if (language == 1)
                cout << "The student with name \"" << name << "\" has already been added" << endl;
            else
                cout << "Студент с именем \"" << name << "\" уже добавлен" << endl;
            return true;
        }
    }
    return false;
}

// Редактирование данных конкретного студента
void Edit(Man*& obj, int size)
{
    if (size == 0) {
        if (language == 1)
            cout << "No students to edit." << endl;
        else
            cout << "Нет студентов для редактирования." << endl;
        return;
    }

    for (int i = 0; i < size; i++)
    {
        obj[i].show();
        cout << endl;
    }

    int pos = FindPos(obj, size);
    if (pos == -1) {
        return; // Студент не найден
    }

    Man tmp;
    tmp.Edit();      // Редактируем временный объект
    obj[pos] = tmp;  // Перезаписываем данные выбранного студента

    if (language == 1) {
        cout << "Edit has been completed." << endl;
    }
    else {
        cout << "Редактирование завершено." << endl;
    }
}

// Удаление студента по фамилии
void DeleteStudent(Man*& obj, int& size)
{
    if (size == 0) {
        if (language == 1)
            cout << "No students to delete." << endl;
        else
            cout << "Нет студентов для удаления." << endl;
        return;
    }

    int pos = FindPos(obj, size);
    if (pos == -1) {
        // Студент не найден
        return;
    }

    int newSize = size - 1;
    Man* newArr = nullptr;

    if (newSize > 0) {
        newArr = new Man[newSize];
        // Копируем всех, кроме найденного
        for (int i = 0, j = 0; i < size; i++) {
            if (i != pos) {
                newArr[j] = obj[i];
                j++;
            }
        }
    }

    delete[] obj;
    obj = newArr;
    size = newSize;

    if (language == 1)
        cout << "The student has been deleted." << endl;
    else
        cout << "Студент был удалён." << endl;
}

int main()
{
    system("color 60");
    srand((unsigned int)time(0));

    int size = 0;      // Текущее число студентов
    Man* mans = nullptr; // Динамический массив студентов

    cout << "Change your language:" << endl;
    cout << "Выберите язык:" << endl;
    cout << "1. English" << endl;
    cout << "2. Русский" << endl;
    cin >> language;
    while (language != 1 && language != 2) {
        cout << "Error. Choose correct answer." << endl;
        cout << "Ошибка. Выберите правильный вариант." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> language;
    }

    // Основной цикл программы
    while (true)
    {
        system("cls");
        cout << "\n--------------------------------\n";
        if (language == 1) {
            cout << "1. Add student\n2. Show all\n3. Find\n4. Edit\n5. Delete student\n6. Exit" << endl;
        }
        else {
            cout << "1. Добавить студента\n2. Показать всех\n3. Найти\n4. Редактировать\n5. Удалить студента\n6. Выход" << endl;
        }
        cout << "--------------------------------\n";
        cout << ((language == 1) ? "Enter choice: " : "Введите номер: ");

        int menu;
        cin >> menu;

        if (cin.fail()) {
            // Если пользователь ввёл не число
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (language == 1)
                cout << "Incorrect choice." << endl;
            else
                cout << "Неправильный выбор." << endl;
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (menu)
        {
        case 1:
        {
            // Добавление студента
            if (mans == nullptr) {
                Man temp;
                temp.add(mans, size);
            }
            else {
                mans[0].add(mans, size);
            }
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
        case 2:
            // Показать всех студентов
        {
            if (mans == nullptr || size == 0)
            {
                if (language == 1) {
                    cout << "You have not added any student" << endl;
                }
                else {
                    cout << "Вы еще не добавили студентов" << endl;
                }
            }
            else
            {
                for (int i = 0; i < size; i++)
                {
                    mans[i].show();
                    cout << endl;
                }
            }
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
        case 3:
            // Найти студента по фамилии
        {
            if (mans == nullptr || size == 0)
            {
                if (language == 1) {
                    cout << "You have not added any student" << endl;
                }
                else {
                    cout << "Вы еще не добавили студентов" << endl;
                }
            }
            else {
                int pos = FindPos(mans, size);
                if (pos != -1) {
                    mans[pos].show();
                }
            }
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
        case 4:
            // Редактирование данных о студенте
        {
            if (mans == nullptr || size == 0)
            {
                if (language == 1) {
                    cout << "You have not added any student" << endl;
                }
                else {
                    cout << "Вы еще не добавили студентов" << endl;
                }
            }
            else {
                Edit(mans, size);
            }
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
        case 5:
            // Удаление студента
        {
            if (mans == nullptr || size == 0)
            {
                if (language == 1) {
                    cout << "You have not added any student" << endl;
                }
                else {
                    cout << "Вы еще не добавили студентов" << endl;
                }
            }
            else {
                DeleteStudent(mans, size);
            }
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }
        case 6:
        {
            // Выход из программы
            if (language == 1)
                cout << "Are you sure want to exit?\nEnter 1 to confirm.\n";
            else
                cout << "Вы точно хотите выйти?\nДля подтверждения нажмите 1. Для отказа - любое другое число.\n";

            int choise_exit;
            cin >> choise_exit;
            if (!cin.fail() && choise_exit == 1) {
                if (mans != nullptr) {
                    delete[] mans;
                    mans = nullptr;
                }
                return 0;
            }
            else {
                // Если пользователь передумал выходить
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
            break;
        }

        default:
            // Обработка неправильного ввода
            if (language == 1)
                cout << "Incorrect choice." << endl;
            else
                cout << "Неправильный выбор." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << ((language == 1) ? "Press Enter to continue..." : "Нажмите Enter для продолжения...");
            cin.get();
            break;
        }
    }
}
