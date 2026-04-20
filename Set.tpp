#include "Set.h"

template<>
int Set<char*>::Compare(const char*& a, const char*& b) const {
    return strcmp(a, b);
}

template<>
void Set<char*>::push(const char*& element) {
    if (is_element(element)) {
        return;
    }
    char** temp = new char*[size + 1];
    for (int i = 0; i < size; i++) {
        if (pdata[i] != nullptr) {
            size_t len = strlen(pdata[i]) + 1;
            temp[i] = new char[len];
            strcpy(temp[i], pdata[i]);
        } else {
            temp[i] = nullptr;
        }
    }

    size_t len = strlen(element) + 1;
    temp[size] = new char[len];
    strcpy(temp[size], element);

    for (int i = 0; i < size; ++i) {
        delete[] pdata[i];
    }
    delete[] pdata;

    pdata = temp;
    size++;
    Sort();
}

friend std::ostream& operator<<(std::ostream& os, const Set<T>& set) {
      int size = set.GetSize();
      if (size == 0) {
         os << "(пусто)" << std::endl;
         return os;
      }

      for (int i = 0; i < size; i++) {
         os << set.GetPData()[i];
         if (i < size - 1) {
               os << ' ';
         }
      }
      os << std::endl;
      return os;
   }