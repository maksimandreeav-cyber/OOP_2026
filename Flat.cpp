#include "Flat.h"
#include <limits>

namespace {
const int BUFFER_SIZE = 1024;
const int kInitValue = 0;
const int kSummandForNextIndex = 1;
const int kMinSrtLen = 0;
const int kMinMinut = 0;
}  // namespace

Flat::Flat() : distanceMetroMinut(kInitValue), isRepair(false), address(nullptr) {
    setAddress("");
}

Flat::Flat(int dist, bool repair, char* addr) : distanceMetroMinut(dist), isRepair(repair), address(nullptr) {
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

    if (addr != nullptr && std::strlen(addr) > kMinSrtLen) {
        size_t len = std::strlen(addr);
        address = new char[len + kSummandForNextIndex];
        strncpy(address, addr, len + kSummandForNextIndex);
    } else {
        address = nullptr;
    }
}

std::ostream& operator<<(std::ostream& os, const Flat& flat) {
    os << "Flat\n";
    os << "  Адрес: '" << flat.getAddress() << "'\n";
    os << "  Метро в " << flat.distanceMetroMinut << " минутах(-е)\n";
    os << "  Наличие ремонта: " << (flat.isRepair ? "да\n" : "нет\n") << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Flat& flat) {
    std::cout << "Сколько минут до метро? ";
    int dist{};
    is >> dist;
    if (dist < kMinMinut) {
        std::cout << "Неккоретные данные!\n";
        dist = kMinMinut;
    }

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
