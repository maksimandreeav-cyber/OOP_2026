#include "Utils.h"

namespace {
const int kMaxNameLen = 100;
}

void CreateStudent() {
    int age{};
    char* name = new char[kMaxNameLen];
    int numberTerm{};
    char* department = new char[kMaxNameLen];
    bool literature = false;

    std::cout << "Введите ФИО студента: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(name, kMaxNameLen);

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Введите номер семестра: ";
    std::cin >> numberTerm;

    std::cout << "Введите его факультет: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(department, kMaxNameLen);

    std::cout << "Есть ли у него литература?(у, если да): ";
    char symbol{};
    std::cin >> symbol;
    literature = symbol == 'y' ? true : false;

    Student* newStudent = new Student(age, name, department, literature, numberTerm);
    Person::GetVector().Push(newStudent);
    delete[] name;
}

void CreateTeacher() {
    int age{};
    char* name = new char[kMaxNameLen];
    bool literature{false};
    char* department = new char[kMaxNameLen];

    std::cout << "Введите ФИО преподавателя: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(name, kMaxNameLen);

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Есть ли у него литература?(у, если да): ";
    char symbol{};
    std::cin >> symbol;
    literature = symbol == 'y' ? true : false;

    std::cout << "Введите его факультет: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(department, kMaxNameLen);

    Teacher* newTeacher = new Teacher(age, name, department, literature);
    Person::GetVector().Push(newTeacher);
}

void CreateDepartmentHead() {
    int age{};
    char* name = new char[kMaxNameLen];
    char* department = new char[kMaxNameLen];

    std::cout << "Введите ФИО завкафедры: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(name, kMaxNameLen);

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "На какой кафедре он работает: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(department, kMaxNameLen);

    DepartmentHead* newDepartmentHead = new DepartmentHead(age, name, department);
    Person::GetVector().Push(newDepartmentHead);
}

void OutputArray() {
    Person::GetVector().Print();
}

void RemoveElement() {
    std::cout << "Введите индекс элемента, который надо удалить: ";
    int index{};
    std::cin >> index;
    Person::GetVector().Remove(index);
}

void ClearArray() {
    Person::GetVector().Clear();
}
