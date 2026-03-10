#ifndef FRACTION_H
#define FRACTION_H

#include <cstdlib>
#include <iostream>

class Fraction {
 private:
    int numerator;
    int denominator;

    int gcd(int a, int b);
    void Simplification();
    int parseNumber(const char*& str);

 public:
    Fraction();
    Fraction(int num, int den = 1);
    Fraction(const char* line);
    Fraction(const Fraction& fraction);
    Fraction(double a);

    int GetNumerator() const;
    int GetDenominator() const;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& is, Fraction& fraction);

    Fraction& operator=(const Fraction& other);
    Fraction& operator=(int other);
    Fraction& operator=(double other);

    Fraction& operator+=(const Fraction& other);
    Fraction& operator+=(int other);
    Fraction& operator+=(double other);

    Fraction operator+(const Fraction& other);
    Fraction operator+(int other);
    Fraction operator+(double other);

    Fraction& operator-=(const Fraction& other);
    Fraction& operator-=(int other);
    Fraction& operator-=(double other);

    Fraction operator-(const Fraction& other);
    Fraction operator-(int other);
    Fraction operator-(double other);

    //friend Fraction operator+(double left, const Fraction& right);
    //friend Fraction operator+(int left, const Fraction& right);
};

#endif
