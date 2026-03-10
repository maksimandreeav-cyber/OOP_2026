#include "Fraction.h"
#include <cmath>
#include <cstring>

namespace {
const int kNumberDecimalPlaces = 4;
const int kBase = 10;
const int kBufferSize = 256;
const double kSummandRound = 0.5;
}  // namespace

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
        result = result * kBase + (*str - '0');
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

Fraction::Fraction() : numerator(0), denominator(1) {
}

Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    Simplification();
}

Fraction::Fraction(double a) {
    int scale = static_cast<int>(std::pow(kBase, kNumberDecimalPlaces) + kSummandRound);
    double scaledValue = a * scale;
    int intPart{};
    if (scaledValue >= 0) {
        intPart = static_cast<int>(scaledValue + kSummandRound);
    } else {
        intPart = static_cast<int>(scaledValue - kSummandRound);
    }
    numerator = intPart;
    denominator = scale;
    Simplification();
}

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
            std::cerr << "Неверный формат ввода смешаной дроби\n";
            std::exit(1);
        }
        ++ptr;
        int c = parseNumber(ptr);

        if (a < 0) {
            numerator = a * c - b;
        } else {
            numerator = a * c + b;
        }
        denominator = c;
    } else if (*ptr == '/') {
        ++ptr;
        int b = parseNumber(ptr);
        numerator = a;
        denominator = b;
    } else {
        numerator = a;
        denominator = 1;
    }

    if (denominator == 0) {
        std::cerr << "знаменатель не может быть равен 0, принят за 1\n";
        denominator = 1;
        return;
    }

    Simplification();
}

Fraction::Fraction(const Fraction& fraction) : numerator(fraction.GetNumerator()), denominator(fraction.GetDenominator()) {
}

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
    char buffer[kBufferSize];
    if (!is.getline(buffer, sizeof(buffer))) {
        return is;
    }
    fraction = Fraction(buffer);

    return is;
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this == &other) {
        return *this;
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
    Fraction result = *this;
    result += other;
    return result;
}

Fraction Fraction::operator+(int other) {
    Fraction result = *this;
    result += other;
    return result;
}

Fraction Fraction::operator+(double other) {
    Fraction result = *this;
    result += other;
    return result;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    int newNumerator = numerator * other.GetDenominator() - other.GetNumerator() * denominator;
    int newDenominator = denominator * other.GetDenominator();

    numerator = newNumerator;
    denominator = newDenominator;
    Simplification();
    return *this;
}

Fraction& Fraction::operator-=(int other) {
    numerator -= other * denominator;
    Simplification();
    return *this;
}

Fraction& Fraction::operator-=(double other) {
    int scale = static_cast<int>(std::pow(kBase, kNumberDecimalPlaces));
    int intPart = static_cast<int>(other * scale);
    Fraction otherFrac(intPart, scale);
    *this -= otherFrac;
    return *this;
}

Fraction Fraction::operator-(const Fraction& other) {
    Fraction result = *this;
    result -= other;
    return result;
}

Fraction Fraction::operator-(int other) {
    Fraction result = *this;
    result -= other;
    return result;
}

Fraction Fraction::operator-(double other) {
    Fraction result = *this;
    result -= other;
    return result;
}

Fraction operator+(int left, const Fraction& right) {
    Fraction leftFrac(left);
    Fraction temp = leftFrac + right;
    return temp;
}

Fraction operator+(double left, const Fraction& right) {
    int scale = static_cast<int>(std::pow(kBase, kNumberDecimalPlaces));
    int intPart = static_cast<int>(left * scale);
    Fraction leftFrac(intPart, scale);
    Fraction temp = leftFrac + right;
    return temp;
}
