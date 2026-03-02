#include <iostream>
#include "Fraction.h"

namespace {
    const int kInitNumFr1 = 10;
    const int kInitDenFr1 = 14;
    const int kInitI = 5;
    const double kInitDouble = -1.25;

}

int main() {
    Fraction z;
    std::cout << "Введите дробь: ";
    std::cin >> z;
    std::cout << "1. Ввод дроби с клавиатуры\n";
    std::cout << "z = " << z << std::endl;

    Fraction fr1(kInitNumFr1, kInitDenFr1);
    Fraction fr2;
    Fraction fr3("-1 4/8");

    std::cout << "2. Проверка конструкторов\n";
    std::cout << "fr1 = " << fr1 << std::endl;
    std::cout << "fr2 = " << fr2 << std::endl;
    std::cout << "fr3 = " << fr3 << std::endl;


    Fraction x(z);
    std::cout << "3. Проверка копирующего конструктора\n";
    std::cout << "x = " << x << std::endl;

    std::cout << "4. Арифметические операции (дробь + дробь)" << std::endl;
    Fraction y = x + fr1;
    std::cout << "y = x + fr1 = " << y << std::endl;

    y += fr3;
    std::cout << "y += fr3 -> " << y << std::endl;

    std::cout << "5. Арифметика с целыми числами" << std::endl;
    int i = kInitI;
    y = x + i;
    std::cout << "y = x + i = " << y << std::endl;

    y = i + x;
    std::cout << "y = i + x = " << y << std::endl;

    y += i;
    std::cout << "y += i -> " << y << std::endl;

    std::cout << "6. Арифметика с double" << std::endl;
    double d = kInitDouble;
    Fraction f = d;
    std::cout << "f = " << f << std::endl;

    y = x + d;
    std::cout << "y = x + d = " << y << std::endl;

    y = d + x;
    std::cout << "y = d + x = " << y << std::endl;

    y += d;
    std::cout << "y += d -> " << y << std::endl;

    y += d + i;
    std::cout << "y += d + i -> " << y << std::endl;

    return 0;
}