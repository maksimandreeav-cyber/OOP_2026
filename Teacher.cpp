#include "Persons.h"

Teacher::Teacher() : Person(), haveDissertation(false){};

Teacher::Teacher(int a, char* n, bool d) : Person(a, n), haveDissertation(d){};

Teacher::Teacher(Teacher& copy) : Person(copy), haveDissertation(copy.GetHaveDissartation()){};

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        Person::operator=(other);
        haveDissertation = other.haveDissertation;
    }
    return *this;
}

bool Teacher::GetHaveDissartation() const {
    return haveDissertation;
}

void Teacher::Show() {
    std::cout << "Преподаватель " << name << ", возрастом " << age << " лет, собственная диссертация "
              << (haveDissertation == true ? "имеется" : "отсутствует") << std::endl;
}
