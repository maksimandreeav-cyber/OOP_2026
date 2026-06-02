#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <numeric>
#include "MyStack.h"

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void Multipliers(int n, MyStack<int>& stack) {
    int divisor = 2;
    while (n > 1) {
        while (n % divisor == 0) {
            stack.push(divisor);
            n /= divisor;
        }
        divisor++;
        if (divisor * divisor > n && n > 1) {
            stack.push(n);
            break;
        }
    }
}

struct DescendingOrder {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

int main() {
    const int N = 3960;
    MyStack<int> stack;

    Multipliers(N, stack);

    std::cout << std::endl << "========== ЗАДАНИЕ 2: Разложение на множители ==========" << std::endl;
    std::cout << N << " = ";
    MyStack<int> tempStack1 = stack; 
    bool first = true;
    int factor;
    while (tempStack1.pop(factor)) {
        if (!first) std::cout << " * ";
        std::cout << factor;
        first = false;
    }
    std::cout << std::endl;

    std::vector<int> factors;
    MyStack<int> tempStack2 = stack;
    while (tempStack2.pop(factor)) {
        factors.push_back(factor);
    }

    std::cout << N << " = ";
    first = true;
    for (auto it = factors.rbegin(); it != factors.rend(); ++it) {
        if (!first) std::cout << " * ";
        std::cout << *it;
        first = false;
    }
    std::cout << std::endl;

    std::vector<int> vec;
    for (auto it = factors.rbegin(); it != factors.rend(); ++it) {
        vec.push_back(*it);
    }

    std::cout << std::endl << "========== ЗЗАДАНИЕ 3.1: Работа с vector ==========" << std::endl;
    std::cout << "Вектор до сортировки по убыванию: ";
    std::for_each(vec.begin(), vec.end(), [](int n) { std::cout << n << " "; });
    std::sort(vec.begin(), vec.end(), DescendingOrder());
    std::cout << std::endl << "Вектор после сортировки по убыванию: ";
    std::for_each(vec.begin(), vec.end(), [](int n) { std::cout << n << " "; });
    std::cout << std::endl;

    int count_2 = std::count(vec.begin(), vec.end(), 2);
    std::cout << "Количество двоек: " << count_2 << std::endl;

    std::vector<int> squares;
    std::transform(vec.begin(), vec.end(), std::back_inserter(squares),
                   [](int n) { return n * n; });

    std::cout << "Квадраты элементов: ";
    std::for_each(squares.begin(), squares.end(), [](int n) { std::cout << n << " "; });
    std::cout << std::endl;

    std::list<int> lst;
    for (auto it = factors.rbegin(); it != factors.rend(); ++it) {
        lst.push_back(*it);
    }

    std::cout << std::endl << "========== ЗАДАНИЕ 3.2: Работа с list ==========" << std::endl;
    lst.remove_if([](int n) { return n == 2; });
    std::cout << "Список после удаления двоек: ";
    std::for_each(lst.begin(), lst.end(), [](int n) { std::cout << n << " "; });
    std::cout << std::endl;

    auto found = std::find(lst.begin(), lst.end(), 3);
    if (found != lst.end()) {
        std::cout << "Найден элемент: " << *found << std::endl;
    } else {
        std::cout << "Элемент не найден" << std::endl;
    }

    int count_greater_than_3 = std::count_if(lst.begin(), lst.end(), [](int n) { return n > 3; });
    std::cout << "Количество элементов > 3: " << count_greater_than_3 << std::endl;

    std::map<int, int> factorCount;
    MyStack<int> tempStack3 = stack;
    while (tempStack3.pop(factor)) {
        factorCount[factor]++;
    }

    std::cout << std::endl << "========== ЗАДАНИЕ 3.3: Работа с map ==========" << std::endl;
    std::cout << "Содержимое map:" << std::endl;
    for (const auto& pair : factorCount) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }

    int searchKey = 3;
    auto mapFound = factorCount.find(searchKey);
    if (mapFound != factorCount.end()) {
        std::cout << "Поиск ключа " << searchKey << " найден, количество: " << mapFound->second << std::endl;
    } else {
        std::cout << "Ключ " << searchKey << " не найден" << std::endl;
    }

    std::cout << std::endl << "========== ЗАДАНИЕ 3.4: Работа с несколькими контейнерами ==========" << std::endl;
    int count_more_than_1 = std::count_if(factorCount.begin(), factorCount.end(),
                                         [](const std::pair<int, int>& p) { return p.second > 1; });
    std::cout << "Количество множителей, встречающихся больше 1 раза: " << count_more_than_1 << std::endl;

    std::vector<int> originalVec;
    for (auto it = factors.rbegin(); it != factors.rend(); ++it) {
        originalVec.push_back(*it);
    }

    std::vector<int> squareVec;
    std::transform(originalVec.begin(), originalVec.end(), std::back_inserter(squareVec), [](int n) { return n * n; });

    int innerProd = std::inner_product(originalVec.begin(), originalVec.end(),
                                      squareVec.begin(), 0);
    std::cout << "Скалярное произведение: " << innerProd << std::endl;

    std::vector<int> sumVec;
    std::transform(originalVec.begin(), originalVec.end(), squareVec.begin(),
                   std::back_inserter(sumVec), [](int a, int b) { return a + b; });
    std::cout << "Вектор сумм: ";
    std::for_each(sumVec.begin(), sumVec.end(), [](int n) { std::cout << n << " "; });
    std::cout << std::endl;

    return 0;
}
