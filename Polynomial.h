class Polynomial {
    private:
    Term* terms;
    int size;
    int max_size;
    bool order;

    public:
    Polynomial();
    Polynomial(double a);
    Polynomial(double c, int p);
    Polynomial(Term& other);

    push(Term& term);
    pop(int p);
    Simplication();
    Calculation(double x);
};