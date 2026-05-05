Polynomial::Polynomial() : terms(nullptr), size(0), max_size(5), order(true) {}
Polynomial::Polynomial(double a) : size(1), max_size(5), order(true) {
    terms = new Term[1];
    terms[0] = Term(a, 0);
}
Polynomial::Polynomial(double c, int p) : size(1), max_size(5), order(true) {
    terms = new Term[1];
    terms[0] = Term(c, p);
}
Polynomial::Polynomial(Term& other) : size(other.size), max_size(other.max_size), order(other.order) {
    for(int i = 0; i < size; i++) {
        terms[i] = other.terms[i];
    }
}

Polynomial::push(Term& term);
Polynomial::pop(int p);
Polynomial::Simplication();
Polynomial::Calculation(double x);