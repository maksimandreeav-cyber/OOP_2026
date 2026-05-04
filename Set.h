#ifndef SET_H
#define SET_H

#include "Container.h"

template<typename T>
class Set : public Container<T> {
 private:
    using Container<T>::size;
    using Container<T>::pdata;

   int Compare(const T& a, const T& b) const {
      if (a < b) {
         return -1;
      }
      if (a > b) {
         return 1;
      }
      return 0;
   }

   void Sort() {
      for (int i = 0; i < size - 1; i++) {
         bool swapped = false;

         for (int j = 0; j < size - i - 1; j++) {
               if (Compare(pdata[j], pdata[j + 1]) > 0) {
                  std::swap(pdata[j], pdata[j + 1]);
                  swapped = true;
               }
         }
         if (!swapped) {
               break;
         }
      }
   }

 public:
    using Container<T>::Container;

   void push(const T& element) {
      if (is_element(element)) return;

      T* temp = new T[size + 1];

      for (int i = 0; i < size; i++) {
         temp[i] = pdata[i];  
      }

      if constexpr (std::is_same_v<T, char*>) {
         const char* literal = static_cast<const char*>(element);
         size_t len = strlen(literal) + 1;
         temp[size] = new char[len];
         strcpy(temp[size], literal);
      } else {
         temp[size] = element;
      }

      delete[] pdata;
      pdata = temp;
      size++;
      Sort();
   }


   void pop(const T& element) {
      int index = q_find(element);
      if (index == -1) {
         return;
      }

      if constexpr (std::is_same_v<T, char*>) {
         delete[] pdata[index];
      }

      for (int j = index; j < size - 1; ++j) {
         pdata[j] = pdata[j + 1];
      }
      size--;
   }

   bool is_element(const T& element) const {
      bool presence = false;
      for (int i = 0; i < size; i++) {
         presence = Compare(element, pdata[i]) == 0 ? true : false;
         if (presence) {
               break;
         } 
      }
      return presence;
   }

   int q_find(const T& element) const {
      int left = 0;
      int right = size;

      while (left < right) {
         size_t mid = left + (right - left) / 2;
         int comparison = Compare(pdata[mid], element);

         if (comparison == 0) {
               return mid;
         } else if (comparison < 0) {
               left = mid + 1;
         } else {
               right = mid;
         }
      }
      return -1;
   }

   Set<T> operator+(Set<T>& other) {
      Set<T> result = *this;
      for (int i = 0; i < other.GetSize(); i++) {
         if (result.q_find(other[i]) == -1) {
               result.push(other[i]);
         }
      }
      return result;
   }

   Set<T> operator-(Set& other) {
      Set<T> result;
      for (int i = 0; i < size; i++) {
         if (other.q_find(pdata[i]) == -1) {
               result.push(pdata[i]);
         }
      }
      return result;
   }

   Set<T> operator*(Set& other) {
      Set<T> result;
      for (int i = 0; i < size; i++) {
         if (other.q_find(pdata[i]) != -1) {
               result.push(pdata[i]);
         }
      }
      return result;
   }

   Set<T>& operator-=(Set<T>& other) {
      *this = *this - other;
      return *this;
   }

   Set<T>& operator+=(Set& other) {
      *this = *this + other;
      return *this;
   }

   Set<T>& operator*=(Set& other) {
      *this = *this * other;
      return *this;
   }

   bool operator==(const Set& other) {
      if (size != other.GetSize()) {
         return false;
      }
      for (int i = 0; i < size; i++) {
         if (Compare(pdata[i], other.pdata[i]) != 0) {
               return false;
         }
      }
      return true;
   }
   
};

template<>
int Set<char*>::Compare(char* const& a, char* const& b) const {
    return strcmp(a, b);
}


#endif  // SET_H
