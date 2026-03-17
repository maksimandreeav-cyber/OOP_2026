#include "Vector.h"
#include "Persons.h"

void Vector::NewPlace() {
    if (size == 0) {
        size++;
        Person** temp = new Person*[size];
        array = temp;
    } else {
        size *= 2;
        Person** temp = new Person*[size];
        for (int i = 0; i < count; i++) {
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
    }
}

void Vector::Push(Person* a) {
    if (count == size) {
        NewPlace();
    }
    array[count] = a;
    count++;
}

void Vector::Print() {
    for (int i = 0; i < count; i++) {
        std::cout << '[' << i << ']';
        array[i]->Show();
    }
}

void Vector::Remove(int a) {
    count--;
    for (int i = a; i < count; i++) {
        array[i] = array[i + 1];
    }
}

void Vector::Clear() {
    if (array != nullptr) {
        for (int i = 0; i < count; i++) {
            if (array[i] != nullptr) {
                delete array[i];
            }
        }
        delete[] array;
        array = nullptr;
    }
    count = 0;
}
