#include <iostream>
#include "Term.h"
class Polynomial {
 private:
    Term* terms;
    int size;
    int max_size;
    void swap(Term& a, Term& b);

 public:
    Polynomial();
    Polynomial(double a);
    Polynomial(double c, int p);
    Polynomial(Polynomial& other);

    void push(Term& term);
    void pop(int p);
    void Simplication();
    double Calculation(double x);

    Term* GetTerms() const;
    int GetSize() const;

    Polynomial& operator+(Polynomial& a);
    Polynomial& operator+=(Polynomial& a);
    Polynomial& operator-(Polynomial& a);
    Polynomial& operator-=(Polynomial& a);
    Polynomial& operator*(Polynomial& a);
    Polynomial& operator*=(Polynomial& a);
    Polynomial& operator=(const Polynomial& a);
    bool operator==(Polynomial& a);
    friend std::istream& operator>>(std::istream& is, Polynomial& a);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& a);
};
