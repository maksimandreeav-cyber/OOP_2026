#include <fstream>
#include "Container.hpp"
#include <cstring>

template<typename T>
class Database : public Container<T> {
protected:
    char* filename;
    bool decreasing;
    bool increasing;

    template<typename Compare>
    void quickSort(T* arr, int low, int high, Compare comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSort(arr, low, pi - 1, comp);
            quickSort(arr, pi + 1, high, comp);
        }
    }

    template<typename Compare>
    int partition(T* arr, int low, int high, Compare comp) {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (comp(arr[j], pivot)) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

public:
    Database(const char* fname = nullptr) : filename(nullptr), decreasing(false), increasing(false) {
        if (fname) {
            filename = new char[strlen(fname) + 1];
            strcpy(filename, fname);
        }
    }

    ~Database() {
        delete[] filename;
    }

    Database(const Database& other) : Container<T>(other), decreasing(other.decreasing), increasing(other.increasing) {
        if (other.filename) {
            filename = new char[strlen(other.filename) + 1];
            strcpy(filename, other.filename);
        } else {
            filename = nullptr;
        }
    }

    void setFilename(char* name) {
        if(filename != nullptr) {
            delete[] filename;
        }
        filename = name;
    }

    Database& operator=(const Database& other) {
        if (this != &other) {
            Container<T>::operator=(other);
            decreasing = other.decreasing;
            increasing = other.increasing;

            delete[] filename;
            if (other.filename) {
                filename = new char[strlen(other.filename) + 1];
                strcpy(filename, other.filename);
            } else {
                filename = nullptr;
            }
        }
        return *this;
    }

    void readFromFile() {
        if (!filename) {
            std::cout << "Filename not set!\n";
            return;
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Cannot open file: " << filename << "\n";
            return;
        }

        this->clear();
        T value;
        while (file >> value) {
            this->push(value);
        }
        file.close();
    }

    void writeToFile() {
        if (!filename) {
            std::cout << "Filename not set!\n";
            return;
        }

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Cannot open file for writing: " << filename << "\n";
            return;
        }

        for (int i = 0; i < this->size; ++i) {
            file << this->data[i] << " ";
        }
        file.close();
    }

    template<typename Compare = std::less<T>>
    void sortQsort(Compare comp = Compare()) {
        if (this->size > 1) {
            quickSort(this->data, 0, this->size - 1, comp);
        }
    }

    int find(const T& value) {
        auto it = std::find(this->data, this->data + this->size, value);
        if (it != this->data + this->size) {
            return static_cast<int>(it - this->data);
        }
        return -1;
    }

    void push(const T& value) {
        Container<T>::push(value);
    }

    void pop() {
        if (this->size > 0) {
            Container<T>::pop();
        }
    }

    void clear() {
        Container<T>::clear();
    }

    void Display() const {
        std::cout << *this << "\n";
    }

    void inputFromConsole() {
        std::cout << "Enter elements (type 'end' to finish):\n";
        T value;
        while (std::cin >> value) {
            this->push(value);
        }
        std::cin.clear();
        std::cin.ignore(64, '\n');
    }
};
