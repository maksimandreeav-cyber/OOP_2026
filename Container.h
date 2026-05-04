#ifndef CONTAINER_H
#define CONTAINER_H

#include <cstring>
#include <iostream>

namespace {
const int kMinSizeContainer = 4;
}

template<typename T>
class Container {
 protected:
    int max_size;
    int size;
    T* pdata;

    void NewPlace() {
      max_size = max_size * 2;
      T* temp = new T[max_size];
      for (int i = 0; i < size; i++) {
         temp[i] = pdata[i];
      }
      delete[] pdata;
      pdata = temp;
   }

   void DeletePlace() {
      if (size < max_size / 4 && max_size / 2 > kMinSizeContainer) {
         max_size /= 2;
         T* temp = new T[max_size];
         for (int i = 0; i < size; ++i) {
            temp[i] = pdata[i];
         }
         delete[] pdata;
         pdata = temp;
      }
   }

 public:
   

   Container() : max_size(kMinSizeContainer), size(0), pdata(nullptr) {}

   Container(T s) : max_size(kMinSizeContainer), size(1), pdata(new T[kMinSizeContainer]) {
      pdata[0] = s;
   }

   Container(const Container& other)
      : max_size(other.max_size), size(other.size), pdata(new T[max_size]) {
      for (int i = 0; i < size; i++) {
         pdata[i] = other.pdata[i];
      }
   }

   Container(Container&& other) noexcept
      : max_size(other.max_size), size(other.size), pdata(other.pdata) {
      other.max_size = kMinSizeContainer;
      other.size = 0;
      other.pdata = nullptr;
   }

   ~Container() {
      delete[] pdata;
   }


   Container<T>& operator=(Container&& other) {
      if (this != &other) {
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

   T& operator[](int a) {
      if (a >= 0 && a < size) {
         return pdata[a];
      } else {
         throw std::out_of_range("Такого элемента нет ");
      }
   }

   int GetMaxSize() const {
      return max_size;
   }

   int GetSize() const {
      return size;
   }

   T* GetPData() const {
      return pdata;
   }

   void push(T element) {
      if (size == max_size) {
         NewPlace();
      }
      pdata[size] = element;
      size++;
   }

   void pop(int index) {
      if (index >= 0 && index < size) {
         for (int i = index; i < size - 1; i++) {
            pdata[i] = pdata[i + 1];
         }

         size--;
         DeletePlace();
      }
   }

   int find(T element) {
      int result = -1;
      for (int i = 0; i < size; i++) {
         if (pdata[i] == element) {
            std::cout << "Элемент найден по индексу: " << i << std::endl;
            result = i;
            break;
         }
      }
      return result;
   }

   friend std::ostream& operator<<(std::ostream& os, const Container<T>& container) {
         int size = container.GetSize();
         if (size == 0) {
            os << "(пусто)" << std::endl;
            return os;
         }

         for (int i = 0; i < size; i++) {
            os << container.GetPData()[i];
            if (i < size - 1) {
                  os << ' ';
            }
         }
         os << std::endl;
         return os;
   }

};

template<>
void Container<char*>::DeletePlace();

template<>
void Container<char*>::push(char* s);

template<>
int Container<char*>::find(char* s);

template<>
void Container<char*>::pop(int index);

template<>
Container<char*>::Container(const Container& other);

template<>
Container<char*>::~Container();

template<>
Container<char*>& Container<char*>::operator=(Container&& other);

#include "Container.tpp"
#endif  // CONTAINER_H
