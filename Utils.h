#include <cstring>
#include <iostream>
#include <limits>
#include "Flat.h"

void CreateObject(Flat& lastObject);
void OutputLastObject(Flat* lastObject);
void InputObject(Flat* lastObject, Flat*& array, int& lenArray);
void OutputArrayConsole(Flat* array, int lenArray);
void SaveArray(const char* filename, Flat* array, int lenArray);
void ReadFile(const char* filename, Flat*& array, int& lenArray);
void DeleteObject(Flat*& array, int& lenArray);
void SortArray(Flat*& array, int& lenArray);
void SearchObject(Flat* array, int lenArray);
void ReductionElement(Flat*& array, int lenArray);

void App(const char* filename);