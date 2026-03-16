#ifndef VECTOR_H
#define VECTOR_H

class Person;

class Vector {
 private:
    static inline Person** array = nullptr;
    static inline int size = 0;
    static inline int count = 0;
    static void NewPlace();

 public:
    static void Push(Person* a);

    static void Print();

    static void Remove(int a);

    static void Clear();
};

#endif  // VECTOR_H
