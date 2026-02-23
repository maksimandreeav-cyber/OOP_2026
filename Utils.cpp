#include "Utils.h"

namespace {
const int kInitValue = 0;
const int kSummandForNextIndex = 1;
const int kMinStrLen = 0;
const int kBufferSize = 1024;
}  // namespace

Flat::Flat() : distanceMetroMinut(kInitValue), isRepair(false), address(nullptr) {
    setAddress("");
}

Flat::Flat(int dist, bool repair, const char* addr) : distanceMetroMinut(dist), isRepair(repair), address(nullptr) {
    setAddress(addr);
}

Flat::Flat(const Flat& other) : distanceMetroMinut(other.distanceMetroMinut), isRepair(other.isRepair), address(nullptr) {
    if (other.address != nullptr) {
        size_t len = std::strlen(other.address);
        address = new char[len + kSummandForNextIndex];
        strncpy(address, other.address, len + kSummandForNextIndex);
    }
}

Flat::~Flat() {
    delete[] address;
}

Flat& Flat::operator=(const Flat& other) {
    if (this == &other) {
        return *this;
    }

    delete[] address;

    distanceMetroMinut = other.distanceMetroMinut;
    isRepair = other.isRepair;

    if (other.address != nullptr) {
        address = new char[std::strlen(other.address) + kSummandForNextIndex];
        size_t len = std::strlen(other.address);
        address = new char[len + kSummandForNextIndex];
        strncpy(address, other.address, len + kSummandForNextIndex);
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

void Flat::setDistanceMetroMinut(int dist) {
    distanceMetroMinut = dist;
}
void Flat::setIsRepair(bool repair) {
    isRepair = repair;
}
void Flat::setAddress(const char* addr) {
    delete[] address;

    if (addr != nullptr && std::strlen(addr) > kMinStrLen) {
        size_t len = std::strlen(addr);
        address = new char[len + kSummandForNextIndex];
        strncpy(address, addr, len + kSummandForNextIndex);
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

    is.ignore(kBufferSize, '\n');
    std::cout << "Введите адрес: ";
    char address_buffer[kBufferSize];
    if (is.getline(address_buffer, kBufferSize)) {
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
    lenArray++;
    Flat* newArray = new Flat[lenArray];

    if (array != nullptr) {
        for (int i = kInitValue; i < lenArray - kSummandForNextIndex; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
    }

    newArray[lenArray - kSummandForNextIndex] = *lastObject;

    array = newArray;
}

void OutputArrayConsole(Flat* array, int lenArray) {
    if (lenArray <= kMinStrLen) {
        std::cerr << "Массив пуст!\n";
        return;
    }
    for (int i = kInitValue; i < lenArray; i++) {
        std::cout << array[i] << std::endl;
    }
}
