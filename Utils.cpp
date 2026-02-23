#include "Utils.h"
#include <fstream>

namespace {
const int kBufferSize = 1024;
const int kInitValue = 0;
const int kInitNegativeValue = -1;
const int kSummandPrevios = -1;
const int kBorderSigns = 0;
const int kOnlyElement = 1;
const int kCoincidence = 0;
const int kMinIndex = 0;
const int kSummandForNextIndex = 1;

enum class ParametrValues {
    addressLowerBoundaryLen = 0,
    distLowerBoundaryValue = 0,
    isRepairBoundary = -1,
    isRepairHave = 1,
    isRepairNotHave = 0
};
enum class NumberSearchActions {
    reduct = 1,
    output = 2,
    exits = 3
};

enum class NumberDeleteActions {
    reduct = 1,
    remove = 2,
    exits = 3
};

enum class NumberParametr {
    address = 1,
    isRepair = 2,
    distance = 3
};
}  // namespace

void CreateObject(Flat& lastObject) {
    std::cin >> lastObject;
}

void OutputLastObject(Flat* lastObject) {
    if (lastObject != nullptr) {
        std::cout << *lastObject;
    } else {
        std::cout << "Объект не создан!\n";
    }
}

void InputObject(Flat* lastObject, Flat*& array, int& lenArray) {
    lenArray++;
    Flat* newArray = new Flat[lenArray];

    if (array != nullptr) {
        for (int i = kInitValue; i < lenArray + kSummandPrevios; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
    }

    newArray[lenArray + kSummandPrevios] = *lastObject;

    array = newArray;
}

void OutputArrayConsole(Flat* array, int lenArray) {
    if (lenArray <= kBorderSigns) {
        std::cerr << "Массив пуст!\n";
        return;
    }
    for (int i = kInitValue; i < lenArray; i++) {
        std::cout << array[i] << std::endl;
    }
}

void SaveArray(const char* filename, Flat* array, int lenArray) {
    std::ofstream out;
    out.open(filename);
    if (out.is_open()) {
        for (int i = kInitValue; i < lenArray; i++) {
            out << array[i].getAddress() << '/' << array[i].getDistanceMetroMinut() << '/' << array[i].getIsRepair() << std::endl;
        }
    }
    out.close();
}

void ReadFile(const char* filename, Flat*& array, int& len) {
    std::ifstream in;
    in.open(filename);

    char buffer[kBufferSize];

    char address_buffer[kBufferSize];
    int distance = kInitValue;
    int isRepairFlag = kInitValue;

    int lenArray = kInitValue;
    Flat* newArray = nullptr;

    while (in.getline(buffer, kBufferSize)) {
        char* token = std::strtok(buffer, "/");

        if (token != nullptr) {
            std::strncpy(address_buffer, token, kBufferSize + kSummandPrevios);
            address_buffer[kBufferSize + kSummandPrevios] = '\0';

            token = std::strtok(nullptr, "/");
            if (token != nullptr) {
                distance = std::atoi(token);

                token = std::strtok(nullptr, "/");
                if (token != nullptr) {
                    isRepairFlag = std::atoi(token);

                    lenArray++;
                    Flat* tempArray = new Flat[lenArray];

                    if (newArray != nullptr && lenArray > kOnlyElement) {
                        for (int i = kInitValue; i < lenArray + kSummandPrevios; i++) {
                            tempArray[i] = newArray[i];
                        }
                        delete[] newArray;
                    }

                    Flat& newFlat = tempArray[lenArray + kSummandPrevios];
                    newFlat.setAddress(address_buffer);
                    newFlat.setDistanceMetroMinut(distance);
                    newFlat.setIsRepair(isRepairFlag ? true : false);

                    newArray = tempArray;
                }
            }
        }
    }

    in.close();
    Flat* tempArray = new Flat[len + lenArray];
    for (int i = kInitValue; i < len; i++) {
        tempArray[i] = array[i];
    }
    for (int i = kInitValue; i < lenArray; i++) {
        tempArray[len + i] = newArray[i];
    }
    array = tempArray;
    len += lenArray;
    if (newArray != nullptr) {
        delete[] newArray;
    }
    std::cout << "Успешно прочитано " << lenArray << " объектов из файла" << std::endl;
}

void DeleteObject(Flat*& array, int& lenArray) {
    int numberAction{kInitValue};
    int numberParametr{kInitValue};
    int distLeftParametr{kInitNegativeValue};
    int distRightParametr{kInitNegativeValue};
    int repairParametr{kInitNegativeValue};
    char addrParametr[kBufferSize] = "";
    int count = kInitValue;
    Flat* tempArray{nullptr};
    while (numberAction != static_cast<int>(NumberDeleteActions::exits)) {
        std::cout << "Выберите действие:\n1. Редактировать параметр удаления\n2. Удалить подходящие элементы\n3. Завершить удаление элементов\n";
        std::cin >> numberAction;
        switch (static_cast<NumberDeleteActions>(numberAction)) {
            case NumberDeleteActions::reduct: {
                std::cout << "Какой параметр будем редактировать?\n1. Адресс\n2. Наличие ремонта\n3. Количество минут до метро\n";
                std::cin >> numberParametr;
                switch (static_cast<NumberParametr>(numberParametr)) {
                    case NumberParametr::address: {
                        std::cout << "Введите адрес(оставьте поле пустым, если нужно  убрать параметр): ";
                        std::cin.ignore(kBufferSize, '\n');
                        std::cin.getline(addrParametr, kBufferSize);
                        break;
                    }
                    case NumberParametr::isRepair: {
                        std::cout << "Должен ли быть ремонт(y - да, n - нет, для сброса параметра введите любой другой символ): ";
                        char symbols{};
                        std::cin >> symbols;
                        if (symbols == 'y') {
                            repairParametr = static_cast<int>(ParametrValues::isRepairHave);
                        } else if (symbols == 'n') {
                            repairParametr = static_cast<int>(ParametrValues::isRepairNotHave);
                        } else {
                            repairParametr = static_cast<int>(ParametrValues::isRepairBoundary);
                        }
                        break;
                    }
                    case NumberParametr::distance:
                        std::cout
                            << "Какой промежуток количества минут, в формате 'ОТ ДО'(введите отрицательно значение, если нужно убрать параметр): ";
                        std::cin >> distLeftParametr >> distRightParametr;
                        if (distLeftParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue) or
                            distRightParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                            std::cout << "Неккоретный ввод, значение границ промежутков должны быть не меньше 0\n";
                        }
                        if (distLeftParametr > distRightParametr) {
                            std::cout << "Неккоретный ввод, левая граница промежутка должна быть не больше правой!\n";
                        }
                        break;
                    default:
                        std::cout << "Такого параметра поиска нет!";
                        break;
                }
                break;
            }

            case NumberDeleteActions::remove: {
                for (int i = kInitValue; i < lenArray; i++) {
                    bool isSuitable = true;
                    if (distLeftParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue) and
                        distRightParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                        isSuitable = isSuitable and
                                     (distLeftParametr <= array[i].getDistanceMetroMinut() and array[i].getDistanceMetroMinut() <= distRightParametr);
                    }
                    if (strlen(addrParametr) > static_cast<int>(ParametrValues::addressLowerBoundaryLen)) {
                        isSuitable = isSuitable and (std::strcmp(addrParametr, array[i].getAddress()) == kCoincidence);
                    }
                    if (repairParametr != static_cast<int>(ParametrValues::isRepairBoundary)) {
                        isSuitable = isSuitable and (repairParametr == array[i].getIsRepair());
                    }
                    if (!isSuitable) {
                        count++;
                        Flat* newArray = new Flat[count];
                        for (int j = kInitValue; j < count + kSummandPrevios; j++) {
                            newArray[j] = tempArray[j];
                        }
                        newArray[count + kSummandPrevios] = array[i];
                        tempArray = newArray;
                    }
                }
                if (array != nullptr) {
                    delete[] array;
                }
                array = tempArray;
                lenArray = count;
                std::cout << "Осталось " << count << " объектов\n";
                count = kInitValue;
                break;
            }
            case NumberDeleteActions::exits: {
                break;
            }
            default: {
                std::cout << "Такого дейстия нет\n";
            }
        }
    }
}

void SortArray(Flat*& array, int& lenArray) {
    std::cout << "По какому полю будем сортировать?\n1. Адресс\n2. Наличие ремонта\n3. Минут до метро\n";
    int sortParametr{};
    std::cin >> sortParametr;
    std::cout << "Сортируем по убыванию?(y, если да) ";
    char symbol{};
    std::cin >> symbol;
    bool isDecrease = symbol == 'y' ? true : false;
    for (int i = kInitValue; i < lenArray + kSummandPrevios; i++) {
        for (int j = kInitValue; j < lenArray - i + kSummandPrevios; j++) {
            bool shouldSwap = false;

            switch (static_cast<NumberParametr>(sortParametr)) {
                case NumberParametr::address: {
                    const char* addr1 = array[j].getAddress();
                    const char* addr2 = array[j + kSummandForNextIndex].getAddress();

                    int cmpResult = std::strcmp(addr1, addr2);
                    shouldSwap = isDecrease ? (cmpResult < kCoincidence) : (cmpResult > kCoincidence);
                    break;
                }
                case NumberParametr::isRepair: {
                    bool repair1 = array[j].getIsRepair();
                    bool repair2 = array[j + kSummandForNextIndex].getIsRepair();
                    shouldSwap = isDecrease ? (!repair1 && repair2) : (repair1 && !repair2);
                    break;
                }
                case NumberParametr::distance: {
                    int min1 = array[j].getDistanceMetroMinut();
                    int min2 = array[j + kSummandForNextIndex].getDistanceMetroMinut();
                    shouldSwap = isDecrease ? (min1 < min2) : (min1 > min2);
                    break;
                }
            }
            if (shouldSwap) {
                Flat temp = array[j];
                array[j] = array[j + kSummandForNextIndex];
                array[j + kSummandForNextIndex] = temp;
            }
        }
    }
}

void SearchObject(Flat* array, int lenArray) {
    int numberAction{kInitValue};
    int numberParametr{kInitValue};
    int distLeftParametr{kInitNegativeValue};
    int distRightParametr{kInitNegativeValue};
    int repairParametr{kInitNegativeValue};
    char addrParametr[kBufferSize] = "";
    int countFind = kInitValue;
    while (numberAction != static_cast<int>(NumberSearchActions::exits)) {
        std::cout << "Выберите действие:\n1. Редактировать параметр поиска\n2. Вывести найденные элементы\n3. Завершить поиск элементов\n";
        std::cin >> numberAction;
        switch (static_cast<NumberSearchActions>(numberAction)) {
            case NumberSearchActions::reduct:
                std::cout << "Какой параметр будем редактировать?\n1. Адресс\n2. Наличие ремонта\n3. Количество минут до метро\n";
                std::cin >> numberParametr;
                switch (static_cast<NumberParametr>(numberParametr)) {
                    case NumberParametr::address: {
                        std::cout << "Введите адрес(оставьте поле пустым, если нужно  убрать параметр): ";
                        std::cin.ignore(kBufferSize, '\n');
                        std::cin.getline(addrParametr, kBufferSize);
                        break;
                    }
                    case NumberParametr::isRepair: {
                        std::cout << "Должен ли быть ремонт(y - да, n - нет, для сброса параметра введите любой другой символ): ";
                        char symbols{};
                        std::cin >> symbols;
                        if (symbols == 'y') {
                            repairParametr = static_cast<int>(ParametrValues::isRepairHave);
                        } else if (symbols == 'n') {
                            repairParametr = static_cast<int>(ParametrValues::isRepairNotHave);
                        } else {
                            repairParametr = static_cast<int>(ParametrValues::isRepairBoundary);
                        }
                        break;
                    }
                    case NumberParametr::distance:
                        std::cout
                            << "Какой промежуток количества минут, в формате 'ОТ ДО'(введите отрицательно значение, если нужно убрать параметр): ";
                        std::cin >> distLeftParametr >> distRightParametr;
                        if (distLeftParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue) or
                            distRightParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                            std::cout << "Неккоретный ввод, значение границ промежутков должны быть не меньше 0\n";
                        }
                        if (distLeftParametr > distRightParametr) {
                            std::cout << "Неккоретный ввод, левая граница промежутка должна быть не больше правой!\n";
                        }
                        break;
                    default:
                        std::cout << "Такого параметра поиска нет!";
                        break;
                }
                break;

            case NumberSearchActions::output: {
                for (int i = kInitValue; i < lenArray; i++) {
                    bool isSuitable = true;
                    if (distLeftParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue) and
                        distRightParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                        isSuitable = isSuitable and
                                     (distLeftParametr <= array[i].getDistanceMetroMinut() and array[i].getDistanceMetroMinut() <= distRightParametr);
                    }
                    if (strlen(addrParametr) > static_cast<int>(ParametrValues::addressLowerBoundaryLen)) {
                        isSuitable = isSuitable and (std::strcmp(addrParametr, array[i].getAddress()) == kCoincidence);
                    }
                    if (repairParametr != static_cast<int>(ParametrValues::isRepairBoundary)) {
                        isSuitable = isSuitable and (repairParametr == array[i].getIsRepair());
                    }
                    if (isSuitable) {
                        std::cout << array[i];
                        countFind++;
                    }
                }

                if (countFind == kInitValue) {
                    std::cout << "Элементы не найдены\n";
                }
                countFind = kInitValue;
                break;
            }
            case NumberSearchActions::exits: {
                break;
            }
            default: {
                std::cout << "Такого дейстия нет\n";
            }
        }
    }
}

void ReductionElement(Flat*& array, int lenArray) {
    for (int i = kInitNegativeValue; i < lenArray; i++) {
        std::cout << i << array[i];
    }
    std::cout << "Данные элемента под каким индексом желаете редактировать? ";
    int indexElement{};
    std::cin >> indexElement;
    if (indexElement < kMinIndex or indexElement >= lenArray) {
        std::cout << "Такого элемента нет!\n";
        return;
    }
    std::cout << '\n' << array[indexElement];
    std::cout << "Какое поле желаете редактировать?\n1. Адрес\n2. Наличие ремонта\n3. Количество минут до метро\n";
    int numberParametr{};
    std::cin >> numberParametr;
    switch (static_cast<NumberParametr>(numberParametr)) {
        case NumberParametr::address: {
            char buffer[kBufferSize];
            std::cout << "Введите адрес: ";
            std::cin.getline(buffer, kBufferSize);
            array[indexElement].setAddress(buffer);
            break;
        }
        case NumberParametr::isRepair: {
            bool isRepair{};
            std::cout << "Должен ли быть ремонт(у, если да)? ";
            char symbol{};
            std::cin >> symbol;
            isRepair = (symbol == 'y');
            array[indexElement].setIsRepair(isRepair);
            break;
        }
        case NumberParametr::distance: {
            int dist{};
            std::cout << "Введите количество минут до метро: ";
            std::cin >> dist;
            if (dist < static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                std::cout << "Некорретный ввод, количество минут не меньше 0\n";
                return;
            }
            array[indexElement].setDistanceMetroMinut(dist);
            break;
        }
        default:
            std::cout << "Такого параметра нет!\n";
            break;
    }
}
