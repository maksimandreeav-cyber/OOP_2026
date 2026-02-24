#ifndef ARRAYFLAT_H
#define ARRAYFLAT_H

#include <iostream>
#include <limits>
#include "Flat.h"

class ArrayFlat {
 private:
    static inline Flat* array = nullptr;
    static inline int lenArray = 0;

 public:
    ~ArrayFlat();

    static Flat* GetArray() { return array; }
    static int GetLenArray() { return lenArray; }

    static void CreateObject();
    static void OutputArrayConsole();
    static void SaveArray(const char* filename);
    static void ReadFile(const char* filename);
    static void DeleteObject();
    static void SortArray();
    static void SearchObject();
    static void CreateObject(Flat& lastObject);
    static void OutputLastObject(Flat* lastObject);
    static void InputObject(Flat* lastObjecty);
    static void ReductionElement();

    friend std::ostream& operator<<(std::ostream& os, const ArrayFlat& arr);
    friend std::istream& operator>>(std::istream& is, ArrayFlat& arr);
};

#endif  // ARRAYFLAT_H
