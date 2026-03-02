#include "Fraction.h"
#include <cmath>
#include <cstring>

namespace {
    const int kNumberDecimalPlaces = 4;
    const int kBase = 10;
    const int kInitKoef = 1;
    const int kBufferSize = 256;
}

int Fraction::gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int Fraction::parseNumber(const char*& str) {
    int result = 0;
    bool isNegative = false;

    if (*str == '-') {
        isNegative = true;
        ++str;
    }

    while (*str >= '0' and *str <= '9') {
        result = result * 10 + (*str - '0');
        ++str;
    }

    return isNegative ? -result : result;
}


void Fraction::Simplification() {
    if (denominator == 0) {
        std::cerr << "Знаменатель не равен 0\n";
        denominator = 1;
        return;
    }
    if (numerator == 0) {
        denominator = 1;
        return;
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    int absNumerator = std::abs(numerator);
    int absDenominator = std::abs(denominator);
    int division = gcd(absNumerator, absDenominator);
    numerator /= division;
    denominator /= division;
}

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    Simplification();
}

Fraction::Fraction(double a) : numerator(a * pow(kBase, kNumberDecimalPlaces)) , denominator(pow(kBase, kNumberDecimalPlaces)) {}

Fraction::Fraction(const char* line) {
    const char* ptr = line;
    int a = parseNumber(ptr);
    if (*ptr == '\0') {
        numerator = a;
        denominator = 1;
        Simplification();
        return;
    }
    if (*ptr == ' ') {
        ++ptr; 
        int b = parseNumber(ptr);

        if (*ptr != '/') {
            std::cerr << "Неверный формат ввода смешаной дроби";
        }
        ++ptr;
        int c = parseNumber(ptr);

        if (a < 0) {
            numerator = a * c - b;
        } else {
            numerator = a * c + b;
        }
        denominator = c;
    }
    else if (*ptr == '/') {
        ++ptr;
        int b = parseNumber(ptr);
        numerator = a;
        denominator = b;
    }
    else {
        numerator = a;
        denominator = 1;
    }

    if (denominator == 0) {
        std::cerr << "знаменатель не может быть равен 0\n";
        denominator = 1;
        return;
    }

    Simplification();
}


Fraction::Fraction(const Fraction& fraction)
    : numerator(fraction.GetNumerator()), denominator(fraction.GetDenominator()) {}


int Fraction::GetNumerator() const {
    return numerator;
}

int Fraction::GetDenominator() const {
    return denominator;
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    Fraction temp = fraction;
    temp.Simplification();

    if (temp.numerator == 0) {
        os << 0;
    } else if (temp.denominator == 1) {
        os << temp.numerator;
    } else if (std::abs(temp.numerator) >= temp.denominator) {
        int whole = temp.numerator / temp.denominator;
        int remainder = std::abs(temp.numerator % temp.denominator);

        if (remainder == 0) {
            os << whole;
        } else {
            os << whole << ' ' << remainder << '/' << temp.denominator;
        }
    } else {
        os << temp.numerator << '/' << temp.denominator;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& fraction) {
    char buffer[256];
    if (!is.getline(buffer, sizeof(buffer))) {
        is.setstate(std::ios::failbit);
        return is;
    }
    fraction = Fraction(buffer);

    return is;
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this == &other) {
        return *this; // Защита от самоприсваивания
    }

    numerator = other.numerator;
    denominator = other.denominator;

    return *this;
}

Fraction& Fraction::operator=(int other) {
    numerator = other;
    denominator = 1;
    Simplification();
    return *this;
}

Fraction& Fraction::operator=(double other) {
    int scale = static_cast<int>(std::pow(kBase, kNumberDecimalPlaces));
    int intPart = static_cast<int>(other * scale);
    *this = Fraction(intPart, scale);
    return *this;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    int newNumerator = numerator * other.GetDenominator() + other.GetNumerator() * denominator;
    int newDenominator = denominator * other.GetDenominator();

    numerator = newNumerator;
    denominator = newDenominator;
    Simplification();
    return *this;
}

Fraction& Fraction::operator+=(int other) {
    numerator += other * denominator;
    Simplification();
    return *this;
}

Fraction& Fraction::operator+=(double other) {
    int scale = static_cast<int>(std::pow(kBase, kNumberDecimalPlaces));
    int intPart = static_cast<int>(other * scale);
    Fraction otherFrac(intPart, scale);
    *this += otherFrac;
    return *this;
}

Fraction Fraction::operator+(const Fraction& other) {
    int newNumerator = numerator * other.denominator + other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

Fraction Fraction::operator+(int other) {
    return Fraction(numerator + other * denominator, denominator);
}

Fraction Fraction::operator+( double right) {
    int scale = static_cast<int>(std::pow(kBase, kNumberDecimalPlaces));
    int intPart = static_cast<int>(right * scale);
    Fraction rightFrac(intPart, scale);
    return *this + rightFrac;
}

Fraction operator+(int left, const Fraction& right) {
    Fraction leftFrac(left);
    return leftFrac + right;
}

Fraction operator+(double left, const Fraction& right) {
    int scale = static_cast<int>(std::pow(kBase, kNumberDecimalPlaces));
    int intPart = static_cast<int>(left * scale);
    Fraction leftFrac(intPart, scale);
    return leftFrac + right;
}