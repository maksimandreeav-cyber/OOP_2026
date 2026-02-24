#ifndef FLAT_H
#define FLAT_H

#include <cstring>
#include <iostream>

class Flat {
 private:
    int distanceMetroMinut;
    bool isRepair;
    char* address;
    static inline int count = 0;

 public:
    Flat();
    Flat(int dist, bool repair, char* addr);
    Flat(const Flat& other);

    ~Flat();

    Flat& operator=(const Flat& other);

    int getDistanceMetroMinut() const;
    bool getIsRepair() const;
    const char* getAddress() const;
    static int getCount();

    void setDistanceMetroMinut(int dist);
    void setIsRepair(bool repair);
    void setAddress(const char* addr);

    friend std::ostream& operator<<(std::ostream& os, const Flat& flat);
    friend std::istream& operator>>(std::istream& is, Flat& flat);
};

#endif
