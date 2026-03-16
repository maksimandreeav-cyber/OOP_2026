#include "Persons.h"

DepartmentHead::DepartmentHead() : Person(), department(nullptr) {
}

DepartmentHead::DepartmentHead(int a, char* n, char* d) : Person(a, n), department(d) {
}

DepartmentHead::DepartmentHead(DepartmentHead& copy) : Person(copy), department(copy.GetDepartment()) {
}

DepartmentHead::~DepartmentHead() {
    delete[] department;
}

DepartmentHead& DepartmentHead::operator=(const DepartmentHead& other) {
    if (&other != this) {
        Person::operator=(other);
        if (other.department != nullptr) {
            if (department != nullptr) {
                delete[] department;
            }
            department = new char[strlen(other.department) + 1];
            strncpy(department, other.department, strlen(other.department) + 1);
        }
    }
    return *this;
}

char* DepartmentHead::GetDepartment() const {
    return department;
}

void DepartmentHead::Show() {
    std::cout << name << " - заведующий кафедры " << department << ", возрастом " << age << std::endl;
}
