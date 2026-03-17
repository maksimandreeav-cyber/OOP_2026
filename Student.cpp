#include "Persons.h"

Student::Student() : numberTerm(0) {
    std::cout << "Student constructor\n";
}

Student::Student(int a, char* n, char* d, bool l, int num) : Teacher(a, n, d, l), numberTerm(num) {
    std::cout << "Student constructor\n";
}

Student::Student(Student& copy) : Teacher(copy), numberTerm(copy.GetNumberTerm()) {
    std::cout << "Student constructor\n";
}

Student::~Student() {
    std::cout << "Student destructor\n";
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Teacher::operator=(other);
        numberTerm = other.GetNumberTerm();
    }
    return *this;
}

int Student::GetNumberTerm() const {
    return numberTerm;
}

void Student::Show() {
    std::cout << "Cтудент " << name << ", возрастом " << age << " лет, учится на " << numberTerm << " семестре на факультете " << department
              << (haveLiterature = true ? ". Имеет свою литературу" : ". Не имеет свою литературу") << std::endl;
}
