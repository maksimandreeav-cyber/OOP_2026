#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Container {
protected:
    T* data;
    int size;
    int max_size;

    void NewPlace() {
        if (size >= max_size) {
            max_size =( max_size == 0 ) ? 1 : max_size * 2;
            T* temp = new T[max_size];
            for (int i = 0; i < size; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
    }

    void DeletePlace() {
        if(size <= max_size / 4) {
            max_size  = max_size / 2;
            T* temp = new T[max_size];
            for (int i = 0; i < size; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
    }

public:
    Container() : data(nullptr), size(0), max_size(0) {}

    Container(const Container& other) : data(nullptr), size(0), max_size(0) {
        if (other.size > 0) {
            data = new T[other.max_size];
            size = other.size;
            max_size = other.max_size;
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    Container(Container&& other) noexcept
        : data(other.data), size(other.size), max_size(other.max_size) {
        other.data = nullptr;
        other.size = 0;
        other.max_size = 0;
    }

    int GetSize() const {
        return size ;
    }

    Container& operator=(const Container& other) {
        if (this != &other) {
            delete[] data;
            if (other.size > 0) {
                data = new T[other.max_size];
                size = other.size;
                max_size = other.max_size;
                for (int i = 0; i < size; ++i) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
                size = 0;
                max_size = 0;
            }
        }
        return *this;
    }

    Container& operator=(Container&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            max_size = other.max_size;
            other.data = nullptr;
            other.size = 0;
            other.max_size = 0;
        }
        return *this;
    }

    ~Container() {
        delete[] data;
    }

    T& operator[](int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }

    bool operator==(const Container& other) const {
        if (size != other.size) { return false; }
        for (int i = 0; i < size; ++i) {
            if (!(data[i] == other.data[i])) { return false; }
        }
        return true;
    }

    bool operator<(const Container& other) const {
        int min_size = std::min(size, other.size);
        for (int i = 0; i < min_size; ++i) {
            if (data[i] < other.data[i]) { return true; }
            if (other.data[i] < data[i]) { return false; }
        }
        return size < other.size;
    }

    void push(const T& value) {
        NewPlace();
        data[size++] = value;
    }

    void pop() {
        if (size > 0) {
            --size;
            DeletePlace();
        }
    }

    void deleteAt(int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int j = i; j < size - 1; ++j) {
            data[j] = data[j + 1];
        }
        --size;
        DeletePlace();
    }

    void clear() {
        size = 0;
        DeletePlace();
    }

    friend std::istream& operator>>(std::istream& is, Container& container) {
        int n;
        std::cout << "Cколько элементов будет введено?" << std::endl;
        is >> n;
        container.clear();
        for (int i = 0; i < n; ++i) {
            T value;
            is >> value;
            container.push(value);
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Container& container) {
        os << "[";
        Iterator it = container.begin();
        if (it != container.end()) {
            os << *it;
            ++it;
            while (it != container.end()) {
                os << ", " << *it;
                ++it;
            }
        }
        os << "]";
        return os;
    }

    class Iterator {
		T* ptr;
	public:
		Iterator(T* p) : ptr(p) {}

		T& operator*() const { return *ptr; }
		Iterator& operator++() { ++ptr; return *this; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
		bool operator==(const Iterator& other) const { return ptr == other.ptr; }
	};

    Iterator begin() const {
        return Iterator(data);
    }
    Iterator end() const {
        return Iterator(data + size);
    }
};
