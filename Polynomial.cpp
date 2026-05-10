#include "Polynomial.h"
#include <cmath>

Polynomial::Polynomial() : size(0), max_size(5) {
    terms = new Term[max_size];
}
Polynomial::Polynomial(double a) : size(1), max_size(5) {
    terms = new Term[max_size];
    terms[0] = Term(a, 0);
}
Polynomial::Polynomial(double c, int p) : size(1), max_size(5) {
    terms = new Term[max_size];
    terms[0] = Term(c, p);
}
Polynomial::Polynomial(Polynomial& other) : size(other.size), max_size(other.max_size) {
    terms = new Term[max_size];
    for (int i = 0; i < size; i++) {
        terms[i] = other.terms[i];
    }
}

void Polynomial::push(Term& term) {
    if (size == max_size) {
        if (max_size == 0) {
            max_size++;
        } else {
            max_size = max_size * 2;
        }
        Term* temp = new Term[max_size];
        for (int i = 0; i < size; i++) {
            temp[i] = terms[i];
        }
        if (max_size > 1) {
            delete[] terms;
        }
        terms = temp;
    }
    terms[size] = term;
    size++;
    Simplication();
}
void Polynomial::pop(int p) {
    for (int i = 0; i < size; ++i) {
        if (terms[i].GetPower() == p) {
            for (int j = i; j < size - 1; ++j) {
                terms[j] = terms[j + 1];
            }
            size--;
            i--;
        }
    }

    if (size < max_size / 4 && max_size > 5) {
        max_size /= 2;
        Term* temp = new Term[max_size];
        for (int i = 0; i < size; ++i) {
            temp[i] = terms[i];
        }
        delete[] terms;
        terms = temp;
    }
}

void Polynomial::swap(Term& a, Term& b) {
    Term temp = a;
    a = b;
    b = temp;
}
void Polynomial::Simplication() {
    // Сначала сортируем термы по степеням (по убыванию)
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (terms[i].GetPower() < terms[j].GetPower()) {
                swap(terms[i], terms[j]);
            }
        }
    }

    int newSize = 0;
    for (int i = 0; i < size; ++i) {
        double currentCoef = terms[i].GetCoef();
        int currentPower = terms[i].GetPower();

        // Объединяем все последующие термы с той же степенью
        while (i + 1 < size && terms[i + 1].GetPower() == currentPower) {
            currentCoef += terms[i + 1].GetCoef();
            ++i;
        }

        if (currentCoef != 0.0) {
            terms[newSize++] = Term(currentCoef, currentPower);
        }
    }
    size = newSize;
}
double Polynomial::Calculation(double x) {
    double result{0};
    for (int i = 0; i < size; i++) {
        result += terms[i].GetCoef() * pow(x, terms[i].GetPower());
    }
    return result;
}

Term* Polynomial::GetTerms() const {
    return terms;
}

int Polynomial::GetSize() const {
    return size;
}

Polynomial& Polynomial::operator+(Polynomial& a) {
    for (int i = 0; i < a.size; i++) {
        push(a.terms[i]);
    }
    Simplication();
    return *this;
}
Polynomial& Polynomial::operator+=(Polynomial& a) {
    return *this + a;
}
Polynomial& Polynomial::operator-(Polynomial& a) {
    for (int i = 0; i < a.size; i++) {
        a.terms[i].SetCoef((-1) * a.terms[i].GetCoef());
        push(a.terms[i]);
    }
    Simplication();
    return *this;
}
Polynomial& Polynomial::operator-=(Polynomial& a) {
    return *this - a;
}
Polynomial& Polynomial::operator*(Polynomial& a) {
    Polynomial result;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < a.size; ++j) {
            double newCoef = terms[i].GetCoef() * a.terms[j].GetCoef();
            int newPower = terms[i].GetPower() + a.terms[j].GetPower();
            Term z(newCoef, newPower);
            result.push(z);
        }
    }
    result.Simplication();
    *this = result;
    return *this;
}
Polynomial& Polynomial::operator*=(Polynomial& a) {
    return *this * a;
}
Polynomial& Polynomial::operator=(Polynomial& a) {
    if (this == &a) {
        return *this;
    }
    delete[] terms;
    size = a.size;
    max_size = a.max_size;
    terms = new Term[max_size];
    for (int i = 0; i < size; ++i) {
        terms[i] = a.terms[i];
    }
    return *this;
}
bool Polynomial::operator==(Polynomial& a) {
    if (size != a.size) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (terms[i].GetCoef() != a.terms[i].GetCoef() or terms[i].GetPower() != a.terms[i].GetPower()) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.GetSize() == 0) {
        os << "0";
        return os;
    }
    bool firstTerm = true;
    for (int i = 0; i < poly.GetSize(); ++i) {
        const Term& term = poly.GetTerms()[i];
        if (term.GetCoef() != 0.0) {
            if (!firstTerm) {
                os << " + ";
            } else {
                firstTerm = false;
            }
            os << term;
        }
    }
    if (firstTerm) {
        os << "0";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    is >> std::ws;

    char ch;
    bool firstTerm = true;

    while (is.good()) {
        char sign = '+';
        if (is.peek() == '+' || is.peek() == '-') {
            is.get(ch);
            sign = ch;
        } else if (!firstTerm) {
            break;
        }

        Term tempTerm;
        if (is >> tempTerm) {
            if (sign == '-') {
                tempTerm.SetCoef(-tempTerm.GetCoef());
            }
            poly.push(tempTerm);
            firstTerm = false;
        } else {
            break;
        }
        is >> std::ws;
    }

    return is;
}
