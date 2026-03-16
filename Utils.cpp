#include "Utils.h"

namespace {
const int kMaxNameLen = 100;
}

void CreateStudent() {
    int age{};
    char* name = new char[kMaxNameLen];
    int numberTerm{};

    std::cout << "Введите ФИО студента: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(name, kMaxNameLen);

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Введите номер курса: ";
    std::cin >> numberTerm;

    Student* newStudent = new Student(age, name, numberTerm);
    Person::GetVector().Push(newStudent);
    delete[] name;
}

void CreateTeacher() {
    int age{};
    char* name = new char[kMaxNameLen];
    bool haveDissertation{false};

    std::cout << "Введите ФИО преподавателя: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(name, kMaxNameLen);

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Есть ли у него диссертация?(у, если да): ";
    char symbol{};
    std::cin >> symbol;
    haveDissertation = symbol == 'y' ? true : false;

    Teacher* newTeacher = new Teacher(age, name, haveDissertation);
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
    std::cout << "Введите индексэлемента, который надо удалить: ";
    int index{};
    std::cin >> index;
    Person::GetVector().Remove(index);
}

void ClearArray() {
    Person::GetVector().Clear();
}
