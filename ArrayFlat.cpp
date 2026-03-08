#include "ArrayFlat.h"
#include <fstream>
#include "Utils.h"

namespace {
const int kBufferSize = 1024;
const int kInitValue = 0;
const int kInitNegativeValue = -1;
const int kCoincidence = 0;
const int kMinMinut = 0;
const int kMinIndex = 0;

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

ArrayFlat::~ArrayFlat() {
    delete[] array;
    array = nullptr;
    lenArray = 0;
    std::cout << "Память очищена, массив сброшен\n";
}

std::ostream& operator<<(std::ostream& os, const ArrayFlat& arr) {
    int len = arr.GetLenArray();
    if (len <= static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
        os << "Массив пуст!\n";
        return os;
    }

    os << " СОДЕРЖИМОЕ МАССИВА КВАРТИР\n";
    os << "Всего элементов: " << len << "\n\n";

    for (int i = kInitValue; i < len; ++i) {
        const Flat& flat = arr.GetArray()[i];
        os << "Квартира #" << (i + 1) << ":\n";
        os << flat;
        os << 'n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, ArrayFlat& arr) {
    std::cout << "Ввод новой квартиры:\n";

    char address[kBufferSize];
    int distance = kInitValue;
    char repairChoice = '\0';
    bool hasRepair{};

    std::cout << "Введите адрес: ";
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    is.getline(address, kBufferSize);

    std::cout << "Введите количество минут до метро: ";
    while (!(is >> distance) || distance < 0) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка! Введите неотрицательное число: ";
    }

    std::cout << "Есть ли ремонт? (y, если да): ";
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        is >> repairChoice;
        if (repairChoice == 'y') {
            hasRepair = true;
            break;
        } else {
            hasRepair = false;
            break;
        }
    }

    Flat newFlat;
    newFlat.setAddress(address);
    newFlat.setDistanceMetroMinut(distance);
    newFlat.setIsRepair(hasRepair);

    Flat* newArray = new Flat[arr.GetLenArray() + 1];

    for (int i = 0; i < arr.GetLenArray(); ++i) {
        newArray[i] = arr.GetArray()[i];
    }
    newArray[arr.GetLenArray()] = newFlat;
    delete[] arr.GetArray();
    arr.array = newArray;
    arr.lenArray++;

    std::cout << "Квартира успешно добавлена!\n";
    return is;
}

void ArrayFlat::CreateObject() {
    Flat newFlat;

    std::cout << "=== Создание новой квартиры ===\n";

    std::cout << "Введите адрес: ";
    char address_buffer[kBufferSize];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(address_buffer, kBufferSize);
    newFlat.setAddress(address_buffer);

    int distance = kInitValue;
    std::cout << "Введите количество минут до метро: ";
    while (!(std::cin >> distance) || distance < kMinMinut) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка! Введите неотрицательное число: ";
    }
    newFlat.setDistanceMetroMinut(distance);

    char repairChoice = '\0';
    std::cout << "Есть ли ремонт? (y, если да): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> repairChoice;

    bool hasRepair = (repairChoice == 'y' || repairChoice == 'Y');
    newFlat.setIsRepair(hasRepair);

    Flat* newArray = nullptr;
    try {
        newArray = new Flat[lenArray + 1];
    } catch (const std::bad_alloc&) {
        std::cerr << "Ошибка выделения памяти для нового массива\n";
        return;
    }

    for (int i = 0; i < lenArray; ++i) {
        newArray[i] = array[i];
    }

    newArray[lenArray] = newFlat;

    delete[] array;
    array = newArray;
    ++lenArray;

    std::cout << "Квартира успешно добавлена! Всего квартир в массиве: " << lenArray << "\n";
}

void ArrayFlat::OutputArrayConsole() {
    if (lenArray <= kInitValue) {
        std::cerr << "Массив пуст!\n";
        return;
    }
    for (int i = kInitValue; i < lenArray; ++i) {
        std::cout << array[i] << std::endl;
    }
}

void ArrayFlat::SaveArray(const char* filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Ошибка открытия файла для записи: " << filename << "\n";
        return;
    }

    for (int i = kInitValue; i < lenArray; ++i) {
        out << array[i].getAddress() << '/' << array[i].getDistanceMetroMinut() << '/' << (array[i].getIsRepair() ? 1 : 0) << std::endl;
    }
    out.close();
}

void ArrayFlat::ReadFile(const char* filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения: " << filename << "\n";
        return;
    }

    char buffer[kBufferSize];
    int countRead = kInitValue;

    char address_buffer[kBufferSize] = "";
    int distance = kInitValue;
    bool isRepair = false;

    while (in.getline(buffer, kBufferSize)) {
        if (buffer[0] == '\0') {
            continue;
        }

        char* token = std::strtok(buffer, "/");
        if (token == nullptr) {
            continue;
        }

        std::strncpy(address_buffer, token, kBufferSize - 1);
        address_buffer[kBufferSize - 1] = '\0';

        token = std::strtok(nullptr, "/");
        distance = (token != nullptr) ? std::atoi(token) : kInitValue;

        token = std::strtok(nullptr, "/");
        isRepair = (token != nullptr) ? (std::atoi(token) != 0) : false;
        Flat* newArray = new Flat[lenArray + 1];

        for (int i = 0; i < lenArray; ++i) {
            newArray[i] = array[i];
        }

        newArray[lenArray].setAddress(address_buffer);
        newArray[lenArray].setDistanceMetroMinut(distance);
        newArray[lenArray].setIsRepair(isRepair);

        if (array != nullptr) {
            delete[] array;
        }

        array = newArray;
        ++lenArray;
        ++countRead;
    }

    in.close();
    std::cout << "Успешно прочитано " << countRead << " объектов из файла\n";
}

void ArrayFlat::DeleteObject() {
    int numberAction{kInitValue};
    int numberParametr{kInitValue};
    int distLeftParametr{kInitNegativeValue};
    int distRightParametr{kInitNegativeValue};
    int repairParametr{static_cast<int>(ParametrValues::isRepairBoundary)};
    char addrParametr[kBufferSize] = "";

    while (numberAction != static_cast<int>(NumberDeleteActions::exits)) {
        std::cout << "Выберите действие:\n1. Редактировать параметр удаления\n2. Удалить подходящие элементы\n3. Завершить удаление элементов\n";
        std::cin >> numberAction;

        switch (static_cast<NumberDeleteActions>(numberAction)) {
            case NumberDeleteActions::reduct: {
                std::cout << "Какой параметр будем редактировать?\n1. Адрес\n2. Наличие ремонта\n3. Количество минут до метро\n";
                std::cin >> numberParametr;
                switch (static_cast<NumberParametr>(numberParametr)) {
                    case NumberParametr::address: {
                        std::cout << "Введите адрес (оставьте поле пустым, если нужно убрать параметр): ";
                        std::cin.ignore(kBufferSize, '\n');
                        std::cin.getline(addrParametr, kBufferSize);
                        break;
                    }
                    case NumberParametr::isRepair: {
                        std::cout << "Должен ли быть ремонт (y - да, n - нет, для сброса параметра введите любой другой символ): ";
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
                    case NumberParametr::distance: {
                        std::cout
                            << "Какой промежуток количества минут, в формате 'ОТ ДО' (введите отрицательное значение, если нужно убрать параметр): ";
                        std::cin >> distLeftParametr >> distRightParametr;
                        if (distLeftParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue) ||
                            distRightParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                            std::cout << "Некорректный ввод, значение границ промежутков должны быть не меньше 0\n";
                        }
                        if (distLeftParametr > distRightParametr) {
                            std::cout << "Некорректный ввод, левая граница промежутка должна быть не больше правой!\n";
                        }
                        break;
                    }
                    default:
                        std::cout << "Такого параметра поиска нет!\n";
                        break;
                }
                break;
            }
            case NumberDeleteActions::remove: {
                if (lenArray == 0) {
                    std::cout << "Массив пуст, удалять нечего\n";
                    break;
                }
                Flat* tempArray = new Flat[lenArray];
                int newLen = kInitValue;

                for (int i = kInitValue; i < lenArray; ++i) {
                    bool isSuitable = true;
                    if (strlen(addrParametr) > static_cast<int>(ParametrValues::addressLowerBoundaryLen)) {
                        if (std::strcmp(addrParametr, array[i].getAddress()) != kCoincidence) {
                            isSuitable = false;
                        }
                    }

                    if (distLeftParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue) &&
                        distRightParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                        int distance = array[i].getDistanceMetroMinut();
                        if (distance < distLeftParametr || distance > distRightParametr) {
                            isSuitable = false;
                        }
                    }

                    if (repairParametr != static_cast<int>(ParametrValues::isRepairBoundary)) {
                        bool hasRepair = array[i].getIsRepair();
                        if ((repairParametr == static_cast<int>(ParametrValues::isRepairHave) && !hasRepair) ||
                            (repairParametr == static_cast<int>(ParametrValues::isRepairNotHave) && hasRepair)) {
                            isSuitable = false;
                        }
                    }

                    if (!isSuitable) {
                        tempArray[newLen++] = array[i];
                    }
                }

                delete[] array;
                array = tempArray;
                lenArray = newLen;

                std::cout << "Удалено " << (lenArray - newLen) << " элементов\n";
                std::cout << "Осталось " << lenArray << " объектов\n";
                break;
            }
            case NumberDeleteActions::exits:
                break;
            default:
                std::cout << "Такого действия нет\n";
                break;
        }
    }
}

void ArrayFlat::SortArray() {
    if (lenArray <= 1) {
        std::cout << "Массив пуст или содержит один элемент, сортировка не требуется\n";
        return;
    }

    std::cout << "По какому полю будем сортировать?\n1. Адрес\n2. Наличие ремонта\n3. Минут до метро\n";
    int sortParametr{};
    std::cin >> sortParametr;
    std::cout << "Сортируем по убыванию? (y/n): ";
    char symbol{};
    std::cin >> symbol;
    bool isDecrease = (symbol == 'y');

    for (int i = kInitValue; i < lenArray - 1; ++i) {
        for (int j = kInitValue; j < lenArray - i - 1; ++j) {
            bool shouldSwap = false;

            switch (static_cast<NumberParametr>(sortParametr)) {
                case NumberParametr::address: {
                    const char* addr1 = array[j].getAddress();
                    const char* addr2 = array[j + 1].getAddress();

                    int cmpResult = std::strcmp(addr1, addr2);
                    shouldSwap = isDecrease ? (cmpResult < kCoincidence) : (cmpResult > kCoincidence);
                    break;
                }
                case NumberParametr::isRepair: {
                    bool repair1 = array[j].getIsRepair();
                    bool repair2 = array[j + 1].getIsRepair();
                    shouldSwap = isDecrease ? (!repair1 && repair2) : (repair1 && !repair2);
                    break;
                }
                case NumberParametr::distance: {
                    int min1 = array[j].getDistanceMetroMinut();
                    int min2 = array[j + 1].getDistanceMetroMinut();
                    shouldSwap = isDecrease ? (min1 < min2) : (min1 > min2);
                    break;
                }
                default:
                    std::cout << "Неверный параметр сортировки!\n";
                    return;
            }

            if (shouldSwap) {
                Flat temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    std::cout << "Сортировка завершена!\n";
}

void ArrayFlat::SearchObject() {
    int numberAction{kInitValue};
    int numberParametr{kInitValue};
    int distLeftParametr{kInitNegativeValue};
    int distRightParametr{kInitNegativeValue};
    int repairParametr{static_cast<int>(ParametrValues::isRepairBoundary)};
    char addrParametr[kBufferSize] = "";

    while (numberAction != static_cast<int>(NumberSearchActions::exits)) {
        std::cout << "Выберите действие:\n1. Редактировать параметр поиска\n2. Вывести найденные элементы\n3. Завершить поиск элементов\n";
        std::cin >> numberAction;

        switch (static_cast<NumberSearchActions>(numberAction)) {
            case NumberSearchActions::reduct: {
                std::cout << "Какой параметр будем редактировать?\n1. Адрес\n2. Наличие ремонта\n3. Количество минут до метро\n";
                std::cin >> numberParametr;
                switch (static_cast<NumberParametr>(numberParametr)) {
                    case NumberParametr::address: {
                        std::cout << "Введите адрес (оставьте поле пустым, если нужно убрать параметр): ";
                        std::cin.ignore(kBufferSize, '\n');
                        std::cin.getline(addrParametr, kBufferSize);
                        break;
                    }
                    case NumberParametr::isRepair: {
                        std::cout << "Должен ли быть ремонт (y - да, n - нет, для сброса параметра введите любой другой символ): ";
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
                    case NumberParametr::distance: {
                        std::cout
                            << "Какой промежуток количества минут, в формате 'ОТ ДО' (введите отрицательное значение, если нужно убрать параметр): ";
                        std::cin >> distLeftParametr >> distRightParametr;
                        if (distLeftParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue) ||
                            distRightParametr < static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                            std::cout << "Некорректный ввод, значение границ промежутков должны быть не меньше 0\n";
                        }
                        if (distLeftParametr > distRightParametr) {
                            std::cout << "Некорректный ввод, левая граница промежутка должна быть не больше правой!\n";
                        }
                        break;
                    }
                    default:
                        std::cout << "Такого параметра поиска нет!\n";
                        break;
                }
                break;
            }
            case NumberSearchActions::output: {
                int countFind = kInitValue;
                for (int i = kInitValue; i < lenArray; ++i) {
                    bool isSuitable = true;

                    if (strlen(addrParametr) > static_cast<int>(ParametrValues::addressLowerBoundaryLen)) {
                        if (std::strcmp(addrParametr, array[i].getAddress()) != kCoincidence) {
                            isSuitable = false;
                        }
                    }

                    if (distLeftParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue) &&
                        distRightParametr >= static_cast<int>(ParametrValues::distLowerBoundaryValue)) {
                        int distance = array[i].getDistanceMetroMinut();
                        if (distance < distLeftParametr || distance > distRightParametr) {
                            isSuitable = false;
                        }
                    }

                    if (repairParametr != static_cast<int>(ParametrValues::isRepairBoundary)) {
                        bool hasRepair = array[i].getIsRepair();
                        if ((repairParametr == static_cast<int>(ParametrValues::isRepairHave) && !hasRepair) ||
                            (repairParametr == static_cast<int>(ParametrValues::isRepairNotHave) && hasRepair)) {
                            isSuitable = false;
                        }
                    }

                    if (isSuitable) {
                        std::cout << array[i];
                        countFind++;
                    }
                }

                if (countFind == kInitValue) {
                    std::cout << "Элементы не найдены\n";
                } else {
                    std::cout << "Найдено элементов: " << countFind << "\n";
                }
                break;
            }
            case NumberSearchActions::exits:
                break;
            default:
                std::cout << "Такого действия нет\n";
                break;
        }
    }
}

void ArrayFlat::ReductionElement() {
    for (int i = kInitValue; i < lenArray; i++) {
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
            std::cin.clear();
            std::cin.ignore(kBufferSize, '\n');
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
