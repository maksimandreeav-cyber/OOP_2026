#include "Math.h"

double multiplication(double a, double b) {
    return a * b;
}

double division(double a, double b) {
    if (b == 0) {
        return 0;
    }
    return a / b;
}
