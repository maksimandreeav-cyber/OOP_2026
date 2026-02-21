#include "Utils.h"

#include <atomic>

std::atomic<int> Flat::count{0};

Flat::Flat() : distanceMetroMinut(0), isRepair(false), address(nullptr) {
    setAddress("");
    setCount(1);
}

Flat::Flat(int dist, bool repair, const char* addr) : distanceMetroMinut(dist), isRepair(repair), address(nullptr) {
    setAddress(addr);
    setCount(1);
}

Flat::Flat(const Flat& other) : distanceMetroMinut(other.distanceMetroMinut), isRepair(other.isRepair), address(nullptr) {
    if (other.address != nullptr) {
        size_t len = std::strlen(other.address);
        address = new char[len + 1];
        strncpy(address, other.address, len + 1);
    }
    setCount(1);
}

Flat::~Flat() {
    delete[] address;
    setCount(-1);
}

Flat& Flat::operator=(const Flat& other) {
    if (this == &other) {
        return *this;
    }

    delete[] address;

    distanceMetroMinut = other.distanceMetroMinut;
    isRepair = other.isRepair;

    if (other.address != nullptr) {
        address = new char[std::strlen(other.address) + 1];
        size_t len = std::strlen(other.address);
        address = new char[len + 1];
        strncpy(address, other.address, len + 1);
    } else {
        address = nullptr;
    }

    return *this;
}

int Flat::getDistanceMetroMinut() const {
    return distanceMetroMinut;
}
bool Flat::getIsRepair() const {
    return isRepair;
}
const char* Flat::getAddress() const {
    return address ? address : "";
}
int Flat::getCount() {
    return count;
}

void Flat::setCount(int value) {
    count += value;
}
void Flat::setDistanceMetroMinut(int dist) {
    distanceMetroMinut = dist;
}
void Flat::setIsRepair(bool repair) {
    isRepair = repair;
}
void Flat::setAddress(const char* addr) {
    delete[] address;

    if (addr != nullptr && std::strlen(addr) > 0) {
        size_t len = std::strlen(addr);
        address = new char[len + 1];
        strncpy(address, addr, len + 1);
    } else {
        address = nullptr;
    }
}

std::ostream& operator<<(std::ostream& os, const Flat& flat) {
    os << "Flat\n";
    os << "  Адрес: " << flat.getAddress() << "\n";
    os << "  Метро в " << flat.distanceMetroMinut << " минутах(-е)\n";
    os << "  Наличие ремонта: " << (flat.isRepair ? "да\n" : "нет\n") << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Flat& flat) {
    std::cout << "Сколько минут до метро? ";
    int dist{};
    is >> dist;

    if (!is) {
        return is;
    }

    std::cout << "Ремонт имеется?(y, если да) ";
    bool repair{};
    char symbol{};
    is >> symbol;
    repair = symbol == 'y' || symbol == 'Y';

    if (!is) {
        return is;
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите адрес: ";
    const int BUFFER_SIZE = 1024;
    char address_buffer[BUFFER_SIZE];
    if (is.getline(address_buffer, BUFFER_SIZE)) {
        flat.setDistanceMetroMinut(dist);
        flat.setIsRepair(repair);
        flat.setAddress(address_buffer);
    } else {
        flat.setDistanceMetroMinut(dist);
        flat.setIsRepair(repair);
        flat.setAddress("");
    }

    return is;
}

void CreateObject(Flat& lastObject) {
    std::cin >> lastObject;
}

void OutputLastObject(Flat* lastObject) {
    if (lastObject != nullptr) {
        std::cout << *lastObject;
    } else {
        std::cout << "Объект не создан!\n";
    }
}

void InputObject(Flat* lastObject, Flat*& array, int& lenArray) {
    lenArray += 1;
    Flat* newArray = new Flat[lenArray];

    if (array != nullptr) {
        for (int i = 0; i < lenArray - 1; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
    }

    newArray[lenArray - 1] = *lastObject;

    array = newArray;
}

void OutputArrayConsole(Flat* array, int lenArray) {
    if (lenArray <= 0) {
        std::cerr << "Массив пуст!\n";
        return;
    }
    for (int i = 0; i < lenArray; i++) {
        std::cout << array[i] << std::endl;
    }
}
