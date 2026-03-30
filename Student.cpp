#include "Persons.h"

Student::Student() : Person(), numberTerm(0) {
    std::cout << "Student constructor\n";
}

Student::Student(int a, char* n, int num) : Person(a, n), numberTerm(num) {
    std::cout << "Student constructor\n";
}

Student::Student(Student& copy) : Person(copy), numberTerm(copy.GetNumberTerm()) {
    std::cout << "Student constructor\n";
}

Student::~Student() {
    std::cout << "Student destructor\n";
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Person::operator=(other);
        numberTerm = other.GetNumberTerm();
    }
    return *this;
}

int Student::GetNumberTerm() const {
    return numberTerm;
}

void Student::Show() {
    std::cout << "Cтудент " << name << ", возрастом " << age << " лет, учится на " << numberTerm << " семестре " << std::endl;
}
