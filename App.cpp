#include "Utils.h"

namespace {
enum class Actions {
    createStudent = 1,
    createTeacher = 2,
    createDepartmentHead = 3,
    outputArray = 4,
    removeElement = 5,
    clearArray = 6,
    exits = 7
};
}  // namespace

void Menu() {
    std::cout << "Выберите действие:\n1. Создание записи о студенте\n2. Создание записи о преподавателе\n3. Создание записи о завкафедры\n4. Вывести "
                 "массив записей\n5. Удалить элемент по индексу\n6. Очистить список\n7. Завершить работу программы"
              << std::endl;
}

void RunAction(int numberAction) {
    switch (static_cast<Actions>(numberAction)) {
        case Actions::createStudent:
            CreateStudent();
            break;
        case Actions::createTeacher:
            CreateTeacher();
            break;
        case Actions::createDepartmentHead:
            CreateDepartmentHead();
            break;
        case Actions::outputArray:
            OutputArray();
            break;
        case Actions::removeElement:
            RemoveElement();
            break;
        case Actions::clearArray:
            ClearArray();
            break;
        case Actions::exits:
            ClearArray();
            break;
        default:
            std::cout << "Такого действия нет!" << std::endl;
    }
}

void App() {
    int numberAction{0};
    while (numberAction != static_cast<int>(Actions::exits)) {
        Menu();
        std::cin >> numberAction;
        RunAction(numberAction);
    }
}
