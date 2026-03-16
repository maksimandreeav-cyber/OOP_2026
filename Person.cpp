#include "Persons.h"

Person::Person() : age(0), name(nullptr) {
}

Person::Person(int a, char* n) : age(a), name(nullptr) {
    if (n != nullptr) {
        name = new char[std::strlen(n) + 1];
        strncpy(name, n, strlen(n) + 1);
    }
}

Person::Person(Person& copy) : age(copy.GetAge()) {
    if (name != nullptr) {
        delete[] name;
    }
    name = new char[strlen(copy.name) + 1];
    strncpy(name, copy.GetName(), strlen(copy.name) + 1);
}

Person::~Person() {
    delete[] name;
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        age = other.age;
        if (other.name != nullptr) {
            if (name != nullptr) {
                delete[] name;
            }
            name = new char[strlen(other.name) + 1];
            strncpy(name, other.name, strlen(other.name) + 1);
        } else {
            name = nullptr;
        }
    }
    return *this;
}

int Person::GetAge() const {
    return age;
}

char* Person::GetName() const {
    return name;
}

Vector& Person::GetVector() {
    return persons;
}

void Person::SetVector(Vector& v) {
    persons = v;
}
