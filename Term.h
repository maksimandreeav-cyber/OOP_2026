#include <iostream>
class Term {
    protected:
    double coef;
    int power;

    public:
    Term();
    Term(double c);
    Term(double c, int p);

    Term operator+(Term other);
    
    friend std::ostream& operator<<(std::ostream& os, const Term& term);
    friend std::istream& operator>>(std::istream& is, Term& term);
};