#include <iostream>
#include "Fraction.h"

int main() {
    Fraction x;
    std::cout << "Проверка ввода с помощью строки(формат: 'ЦЧ ЧС/ЗН')\n";
    std::cin >> x;
    std::cout << "x = " << x << std::endl;

    int tempY{};
    std::cout << "Проверка преобразования из int\n";
    std::cin >> tempY;
    Fraction y(tempY);
    std::cout << "y = " << y << std::endl;

    double tempZ{};
    std::cout << "Проверка преобразования из double\n";
    std::cin >> tempZ;
    Fraction z(tempZ);
    std::cout << "z = " << z << std::endl;

    std::cout << "Проверка операций с дробями: \n";
    std::cout << "Введите целое число: ";
    int a{};
    std::cin >> a;
    std::cout << "x += a: ";
    x += a;
    std::cout << x << std::endl;

    std::cout << "Введите дробное число: ";
    double b{};
    std::cin >> b;
    std::cout << "x += b: ";
    x += b;
    std::cout << x << std::endl;
    std::cout << "x -= b: ";
    x -= b;
    std::cout << x << std::endl;
}
