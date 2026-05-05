#include "Term.h"

int main() {
    Term a(3, 5);
    Term b(4, 5);
    a = a + b;
    std::cout << a;
    return 0;
}