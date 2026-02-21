#include <cstring>
#include <iostream>
#include <limits>

class Flat {
 private:
    int distanceMetroMinut;
    bool isRepair;
    char* address;
    static int count = 0;

 public:
    Flat();
    Flat(int dist, bool repair, const char* addr);
    Flat(const Flat& other);

    ~Flat();

    Flat& operator=(const Flat& other);

    int getDistanceMetroMinut() const;
    bool getIsRepair() const;
    const char* getAddress() const;
    static int getCount();

    static void setCount(int value);
    void setDistanceMetroMinut(int dist);
    void setIsRepair(bool repair);
    void setAddress(const char* addr);

    friend std::ostream& operator<<(std::ostream& os, const Flat& flat);
    friend std::istream& operator>>(std::istream& is, Flat& flat);
};

void CreateObject(Flat& lastObject);
void OutputLastObject(Flat* lastObject);
void InputObject(Flat* lastObject, Flat*& array, int& lenArray);
void OutputArrayConsole(Flat* array, int lenArray);

void App();
