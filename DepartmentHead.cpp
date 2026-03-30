#include "Persons.h"

DepartmentHead::DepartmentHead() : Teacher(), department(nullptr) {
    std::cout << "Department constructor\n";
}

DepartmentHead::DepartmentHead(int a, char* n, char* d, int s) : Teacher(a, n, s), department(d) {
    std::cout << "Department constructor\n";
}

DepartmentHead::DepartmentHead(DepartmentHead& copy) : Teacher(copy), department(copy.GetDepartment()) {
    std::cout << "Department constructor\n";
}

DepartmentHead::~DepartmentHead() {
    delete[] department;
    std::cout << "Department destructor\n";
}

DepartmentHead& DepartmentHead::operator=(const DepartmentHead& other) {
    if (&other != this) {
        Teacher::operator=(other);
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
    std::cout << name << " - заведующий кафедры " << department << ", возрастом " << age << " с зарплатой " << salary << std::endl;
}
