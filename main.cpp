#include <iostream>
#include "Math.h"

int main() {
    double a{};
    double b{};
    std::cout << "Введите первое число: ";
    std::cin >> a;
    std::cout << "Введите второе число: ";
    std::cin >> b;
    std::cout << "Результат умножения: " << multiplication(a, b) << std::endl
              << "Результат деления первого на второе: " << division(a, b) << std::endl;
    return 0;
}
