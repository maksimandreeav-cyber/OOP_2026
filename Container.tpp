#include "Container.h"

template<>
void Container<char*>::NewPlace() {
    max_size = max_size * 2;
    char** temp = new char*[max_size];
    for (int i = 0; i < size; i++) {
        if (pdata[i] != nullptr) {
            size_t len = strlen(pdata[i]) + 1;
            temp[i] = new char[len];
            strcpy(temp[i], pdata[i]);
        } else {
            temp[i] = nullptr;
        }
    }
    for (int i = 0; i < size; ++i) {
        delete[] pdata[i];
    }
    delete[] pdata;
    pdata = temp;
}

template<>
void Container<char*>::DeletePlace() {
    if (size < max_size / 4 && max_size / 2 > kMinSizeContainer) {
        max_size /= 2;
        char** temp = new char*[max_size];
        for (int i = 0; i < size; ++i) {
            if (pdata[i] != nullptr) {
                size_t len = strlen(pdata[i]) + 1;
                temp[i] = new char[len];
                strcpy(temp[i], pdata[i]);
            } else {
                temp[i] = nullptr;
            }
        }
        for (int i = 0; i < size; ++i) {
            delete[] pdata[i];
        }
        delete[] pdata;
        pdata = temp;
    }
}

template<>
Container<char*>::Container(const Container& other)
    : max_size(other.max_size), size(other.size), pdata(new char*[max_size]) {
    for (int i = 0; i < size; i++) {
        if (other.pdata[i] != nullptr) {
            size_t len = strlen(other.pdata[i]) + 1;
            pdata[i] = new char[len];
            strcpy(pdata[i], other.pdata[i]);
        } else {
            pdata[i] = nullptr;
        }
    }
}

template<>
Container<char*>::~Container() {
    for (int i = 0; i < size; i++) {
        delete[] pdata[i];
    }
    delete[] pdata;
}

template<>
Container<char*>& Container<char*>::operator=(Container&& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete[] pdata[i];
        }
        delete[] pdata;

        max_size = other.max_size;
        size = other.size;
        pdata = other.pdata;

        other.max_size = kMinSizeContainer;
        other.size = 0;
        other.pdata = nullptr;
    }
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Container<T>& container) {
    int size = container.GetSize();
    if (size == 0) {
        os << "(пусто)" << std::endl;
        return os;
    }

    for (int i = 0; i < size; i++) {
        os << container.GetPData()[i];
        if (i < size - 1) {
            os << ' ';
        }
    }
    os << std::endl;
    return os;
}

