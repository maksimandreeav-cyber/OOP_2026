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

    double GetCoef() const;
    int GetPower() const;

    void SetCoef(double c);

    friend std::ostream& operator<<(std::ostream& os, const Term& term);
    friend std::istream& operator>>(std::istream& is, Term& term);
};
