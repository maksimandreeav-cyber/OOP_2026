#include "Term.h"
Term::Term() : coef(0), power(0) {}
Term::Term(double c) : coef(c), power(0) {}
Term::Term(double c, int p) : coef(c), power(p) {}

Term Term::operator+(Term other) {
    coef += other.coef;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
    if(power == 0) {
        os << term.coef;
        return os;
    }
    else if (power == 1) {
        os << term.coef << 'x';
        return os
    }
    else if (coef == 0) {
        os << 0;
        return os;;
    }
    else if (coef == 1) {
        os << 'x^' << term.power;
        return os;
    }
    os << term.coef << "x^" << term.power << ' ';
    return os;
}

std::istream& operator>>(std::istream& is, Term& term) {
    is >> std::ws;
    if (!(is >> term.coefficient)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> std::ws;
    char x;
    if (!(is >> x) || x != 'x') {
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> std::ws;

    char caret;
    if (!(is >> caret) || caret != '^') {
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> std::ws;
    if (!(is >> term.degree)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    return is;
}
