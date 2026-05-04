

template<>
void Container<char*>::DeletePlace() {
    if (size < max_size / 4 && max_size / 2 > kMinSizeContainer) {
        max_size /= 2;
        char** temp = new char*[max_size];
        for (int i = 0; i < size; ++i) {
            if (pdata[i] != nullptr) {
                size_t len = strlen(pdata[i]) + 1;
                temp[i] = new char[len];
                strcpy(temp[i], pdata[i]);
            } else {
                temp[i] = nullptr;
            }
        }
        for (int i = 0; i < size; ++i) {
            delete[] pdata[i];
        }
        delete[] pdata;
        pdata = temp;
    }
}


template<>
void Container<char*>::push(char* s) {
    if (size == max_size) {
        NewPlace();
    }
    if (s != nullptr) {
        size_t len = strlen(s) + 1;
        pdata[size] = new char[len];
        strcpy(pdata[size], s);
    } else {
        pdata[size] = nullptr;
    }
    size++;
}

template<>
int Container<char*>::find(char* s) {
    int result = -1;
    for (int i = 0; i < size; i++) {
        if (strcmp(pdata[i], s) == 0) {
        std::cout << "Элемент найден по индексу: " << i << std::endl;
        result = i;
        break;
        }
    }
    return result;
}


template<>
void Container<char*>::pop(int index) {
    if (index >= 0 && index < size) {
        delete[] pdata[index];
        for (int i = index; i < size - 1; i++) {
            pdata[i] = pdata[i + 1];
        }

        size--;
        DeletePlace();
    }
}

template<>
Container<char*>::Container(const Container& other)
    : max_size(other.max_size), size(other.size), pdata(new char*[max_size]) {
    for (int i = 0; i < size; i++) {
        if (other.pdata[i] != nullptr) {
            size_t len = strlen(other.pdata[i]) + 1;
            pdata[i] = new char[len];
            strcpy(pdata[i], other.pdata[i]);
        } else {
            pdata[i] = nullptr;
        }
    }
}


template<>
Container<char*>::~Container() {
    if (pdata == nullptr) return;

    for (int i = 0; i < size; i++) {
        if (pdata[i] != nullptr) {
            delete[] pdata[i];
            pdata[i] = nullptr; 
        }
    }
    delete[] pdata;
    pdata = nullptr;
}

template<>
Container<char*>& Container<char*>::operator=(Container&& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i) {
            delete[] pdata[i];
        }
        delete[] pdata;

        max_size = other.max_size;
        size = other.size;
        pdata = other.pdata;

        other.max_size = kMinSizeContainer;
        other.size = 0;
        other.pdata = nullptr;
    }
    return *this;
}


