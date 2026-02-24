#include "ArrayFlat.h"
#include "Flat.h"
#include "Utils.h"

namespace {
const int kinitValue = 0;

enum class NumbersAction {
    create = 3,
    outputConsole = 8,
    delet = 4,
    sort = 5,
    search = 6,
    save = 2,
    read = 1,
    reduct = 7,
    exit = 9
};
}  // namespace

void Menu() {
    std::cout << "Выберите действие:\n1. Чтение объектов из файла\n2. Сохранить массив в файл\n3. Создать новый элемент в массив\n"
                 "4. Удаление объктов\n5. Сортировка массива\n6. Поиск элемента\n7. Редактировать элемент"
                 "\n8. Вывести массив на экран \n9. Завершить работу программы\n";
}

void SelectRunAction(int& number, const char* filename) {
    if (!(std::cin >> number)) {
        return;
    }
    switch (number) {
        case (static_cast<int>(NumbersAction::create)):
            ArrayFlat::CreateObject();
            break;
        case (static_cast<int>(NumbersAction::outputConsole)):
            ArrayFlat::OutputArrayConsole();
            break;
        case (static_cast<int>(NumbersAction::exit)):
            break;
        case (static_cast<int>(NumbersAction::delet)):
            ArrayFlat::DeleteObject();
            break;
        case (static_cast<int>(NumbersAction::sort)):
            ArrayFlat::SortArray();
            break;
        case (static_cast<int>(NumbersAction::search)):
            ArrayFlat::SearchObject();
            break;
        case (static_cast<int>(NumbersAction::save)):
            ArrayFlat::SaveArray(filename);
            break;
        case (static_cast<int>(NumbersAction::read)):
            ArrayFlat::ReadFile(filename);
            break;
        case (static_cast<int>(NumbersAction::reduct)): {
            ArrayFlat::ReductionElement();
            break;
        }
        default:
            std::cout << "Такого действия нет!\n";
            break;
    }
}

void App(const char* filename) {
    int numberAction{kinitValue};
    ArrayFlat arrayFlatInstance;
    while (numberAction != static_cast<int>(NumbersAction::exit)) {
        Menu();
        SelectRunAction(numberAction, filename);
    }
}
