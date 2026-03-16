#include "Persons.h"

Student::Student() : numberTerm(0) {
}

Student::Student(int a, char* n, int num) : Person(a, n), numberTerm(num) {
}

Student::Student(Student& copy) : Person(copy), numberTerm(copy.GetNumberTerm()) {
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
    std::cout << "Cтудент " << name << ", возрастом " << age << " лет, учится на " << numberTerm << " семестре\n";
}
