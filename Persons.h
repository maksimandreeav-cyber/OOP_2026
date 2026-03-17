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

class DepartmentHead : public Person {
 protected:
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

class Teacher : public DepartmentHead {
 protected:
    bool haveLiterature;

 public:
    Teacher();

    Teacher(int a, char* n, char* d, bool l);

    Teacher(Teacher& copy);

    ~Teacher();

    Teacher& operator=(const Teacher& other);

    bool GetHaveLiterature() const;

    void Show() override;
};

class Student : public Teacher {
 private:
    int numberTerm;

 public:
    Student();

    Student(int a, char* n, char* d, bool l, int num);

    Student(Student& copy);

    ~Student();

    Student& operator=(const Student& other);

    int GetNumberTerm() const;

    void Show() override;
};

#endif  // PERSONS_H
