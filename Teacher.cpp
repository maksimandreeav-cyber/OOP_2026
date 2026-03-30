#include "Persons.h"

Teacher::Teacher() : Person(), salary(0) {
    std::cout << "Teacher constructor\n";
};

Teacher::Teacher(int a, char* n, int s) : Person(a, n), salary(s) {
    std::cout << "Teacher constructor\n";
};

Teacher::Teacher(Teacher& copy) : Person(copy), salary(copy.GetSalary()) {
    std::cout << "Teacher constructor\n";
};

Teacher::~Teacher() {
    std::cout << "Teacher destructor\n";
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        Person::operator=(other);
        salary = other.salary;
    }
    return *this;
}

int Teacher::GetSalary() const {
    return salary;
}

void Teacher::Show() {
    std::cout << "Преподаватель " << name << ", возрастом " << age << " с зарплатой " << salary << " рублей" << std::endl;
}
