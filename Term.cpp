#include "Term.h"
Term::Term() : coef(0), power(0) {
}
Term::Term(double c) : coef(c), power(0) {
}
Term::Term(double c, int p) : coef(c), power(p) {
}

Term Term::operator+(Term other) {
    if (power == other.GetPower()) {
        coef += other.coef;
    }
    return *this;
}

double Term::GetCoef() const {
    return coef;
}

int Term::GetPower() const {
    return power;
}

void Term::SetCoef(double c) {
    coef = c;
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
    double coef = term.coef;
    int power = term.power;
    if (power == 0) {
        os << coef;
        return os;
    }
    if (power == 1) {
        if (coef == 1.0) {
            os << "x";
        } else if (coef == -1.0) {
            os << "(-x)";
        } else {
            os << (coef < 0 ? '(' : ' ') << coef << "x" << (coef < 0 ? ')' : ' ');
        }
        return os;
    }
    if (coef == 1.0) {
        os << "x^" << power;
    } else if (coef == -1.0) {
        os << "(-x^" << power << ')';
    } else {
        os << (coef < 0 ? '(' : ' ') << coef << "x^" << power << (coef < 0 ? ')' : ' ');
    }

    return os;
}

std::istream& operator>>(std::istream& is, Term& term) {
    is >> std::ws;

    if (!(is >> term.coef)) {
        if (is.peek() == 'x') {
            is.get();
            term.coef = 1.0;
        } else {
            is.setstate(std::ios::failbit);
            return is;
        }
    }

    is >> std::ws;

    if (is.peek() != 'x') {
        term.power = 0;
        return is;
    }

    char x{};
    is.get(x);
    is >> std::ws;
    if (is.peek() != '^') {
        term.power = 1;
        return is;
    }

    char caret{};
    is.get(caret);

    is >> std::ws;

    if (!(is >> term.power)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    return is;
}
