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

    std::cout << "Введите номер семестра: ";
    std::cin >> numberTerm;

    Student* newStudent = new Student(age, name, numberTerm);
    Person::GetVector().Push(newStudent);
    delete[] name;
}

void CreateTeacher() {
    int age{};
    char* name = new char[kMaxNameLen];
    int salary{};

    std::cout << "Введите ФИО преподавателя: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(name, kMaxNameLen);

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Введите зарплату: ";
    std::cin >> salary;

    Teacher* newTeacher = new Teacher(age, name, salary);
    Person::GetVector().Push(newTeacher);
}

void CreateDepartmentHead() {
    int age{};
    char* name = new char[kMaxNameLen];
    char* department = new char[kMaxNameLen];
    int salary{};

    std::cout << "Введите ФИО завкафедры: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(name, kMaxNameLen);

    std::cout << "Введите возраст: ";
    std::cin >> age;

    std::cout << "Введите зарплату: ";
    std::cin >> salary;

    std::cout << "На какой кафедре он работает: ";
    std::cin.ignore(kMaxNameLen, '\n');
    std::cin.getline(department, kMaxNameLen);

    DepartmentHead* newDepartmentHead = new DepartmentHead(age, name, department, salary);
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
