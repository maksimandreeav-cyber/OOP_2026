#ifndef PERSONS_H
#define PERSONS_H
#include <cstring>
#include <iostream>
#include "Vector.h"

class Vector;

class Person {
 protected:
    static inline Vector persons = Vector();
    int age;
    char* name;

 public:
    Person();

    Person(int a, char* n);

    Person(Person& copy);

    virtual ~Person();

    Person& operator=(const Person& other);

    int GetAge() const;
    char* GetName() const;
    static Vector& GetVector();

    void SetVector(Vector& v);

    virtual void Show() = 0;
};

class Student : public Person {
 private:
    int numberTerm;

 public:
    Student();

    Student(int a, char* n, int num);

    Student(Student& copy);

    ~Student() = default;

    Student& operator=(const Student& other);

    int GetNumberTerm() const;

    void Show() override;
};

class Teacher : public Person {
 private:
    bool haveDissertation;

 public:
    Teacher();

    Teacher(int a, char* n, bool d);

    Teacher(Teacher& copy);

    ~Teacher() = default;

    Teacher& operator=(const Teacher& other);

    bool GetHaveDissartation() const;

    void Show() override;
};

class DepartmentHead : public Person {
 private:
    char* department;

 public:
    DepartmentHead();

    DepartmentHead(int a, char* n, char* d);

    DepartmentHead(DepartmentHead& copy);

    ~DepartmentHead();

    DepartmentHead& operator=(const DepartmentHead& other);

    char* GetDepartment() const;

    void Show() override;
};
#endif  // PERSONS_H
