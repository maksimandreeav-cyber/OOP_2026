#include <string>
#include "Database.hpp"
#include "Flat.h"

int main() {
    Database<Flat> a;
    Flat b(5, 'y', (char*)"asd");
    a.push(b);
    a.push(b);
    a.push(b);
    a.push(b);
    char* n = new char[5];
    std::cin >> n;
    a.setFilename(n);
    a.writeToFile();
    a.clear();
    std::cout << a;
    a.readFromFile();
    std::cout << a;
    return 0;
}
