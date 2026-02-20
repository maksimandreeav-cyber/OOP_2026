#include "Utils.h"

namespace {
const int initValue = 0;

enum class NumbersAction {
    create = 1,
    outputElement = 2,
    input = 3,
    outputConsole = 4,
    exit = 5
};
}  // namespace

void Menu() {
    std::cout << "Выберите действие:\n1. Создание объекта\n2. Вывести последний объект\n3. Добавить текущий объект в массив\n4. Вывод массива в "
                 "консоль\n5. Завершение работы программы\n";
}

void SelectRunAction(int& number, Flat& lastObject, Flat*& array, int& lenArray) {
    if (!(std::cin >> number)) {
        return;
    }
    switch (number) {
        case (static_cast<int>(NumbersAction::create)):
            CreateObject(lastObject);
            break;
        case (static_cast<int>(NumbersAction::outputElement)):
            OutputLastObject(&lastObject);
            break;
        case (static_cast<int>(NumbersAction::input)):
            InputObject(&lastObject, array, lenArray);
            break;
        case (static_cast<int>(NumbersAction::outputConsole)):
            OutputArrayConsole(array, lenArray);
            break;
        case (static_cast<int>(NumbersAction::exit)):
            break;
        default:
            std::cout << "Такого действия нет";
            break;
    }
}

void App() {
    int numberAction{initValue};
    Flat LastObject{};
    Flat* ArrayObject = nullptr;
    int lenArray = initValue;
    while (numberAction != static_cast<int>(NumbersAction::exit)) {
        Menu();
        SelectRunAction(numberAction, LastObject, ArrayObject, lenArray);
    }

    delete[] ArrayObject;
}
