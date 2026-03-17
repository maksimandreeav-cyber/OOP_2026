#include "Persons.h"

Teacher::Teacher() : DepartmentHead(), haveLiterature(false) {
    std::cout << "Teacher constructor\n";
};

Teacher::Teacher(int a, char* n, char* d, bool l) : DepartmentHead(a, n, d), haveLiterature(l) {
    std::cout << "Teacher constructor\n";
};

Teacher::Teacher(Teacher& copy) : DepartmentHead(copy), haveLiterature(copy.GetHaveLiterature()) {
    std::cout << "Teacher constructor\n";
};

Teacher::~Teacher() {
    std::cout << "Teacher destructor\n";
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        DepartmentHead::operator=(other);
        haveLiterature = other.haveLiterature;
    }
    return *this;
}

bool Teacher::GetHaveLiterature() const {
    return haveLiterature;
}

void Teacher::Show() {
    std::cout << "Преподаватель на кафедре " << department << ", " << name << ", возрастом " << age << " лет, собственная литература "
              << (haveLiterature == true ? "имеется" : "отсутствует") << std::endl;
}
