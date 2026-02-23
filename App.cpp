#include "Flat.h"
#include "Utils.h"

namespace {
const int initValue = 0;

enum class NumbersAction {
    create = 3,
    outputElement = 4,
    input = 5,
    outputConsole = 9,
    delet = 6,
    sort = 7,
    search = 8,
    save = 2,
    read = 1,
    reduct = 10,
    exit = 11
};
}  // namespace

void Menu() {
    std::cout << "Выберите действие:\n1. Чтение объектов из файла\n2. Сохранить массив в файл\n3. Создать новый элемент\n4. Вывод текущего элемента "
                 "в консоль\n5. Добавить текущий элемент в массив\n6. Удаление объктов\n7. Сортировка массива\n8. Поиск элемента\n9. Вывести массив "
                 "на экран\n10. Редактировать элемент\n11. Завершить работу программы\n";
}

void SelectRunAction(int& number, Flat& lastObject, Flat*& array, int& lenArray, const char* filename) {
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
        case (static_cast<int>(NumbersAction::delet)):
            DeleteObject(array, lenArray);
            break;
        case (static_cast<int>(NumbersAction::sort)):
            SortArray(array, lenArray);
            break;
        case (static_cast<int>(NumbersAction::search)):
            SearchObject(array, lenArray);
            break;
        case (static_cast<int>(NumbersAction::save)):
            SaveArray(filename, array, lenArray);
            break;
        case (static_cast<int>(NumbersAction::read)):
            ReadFile(filename, array, lenArray);
            break;
        case (static_cast<int>(NumbersAction::reduct)): {
            ReductionElement(array, lenArray);
            break;
        }
        default:
            std::cout << "Такого действия нет!\n";
            break;
    }
}

void App(const char* filename) {
    int numberAction{initValue};
    Flat LastObject{};
    Flat* ArrayObject = nullptr;
    int lenArray = initValue;
    while (numberAction != static_cast<int>(NumbersAction::exit)) {
        Menu();
        SelectRunAction(numberAction, LastObject, ArrayObject, lenArray, filename);
    }

    delete[] ArrayObject;
}
