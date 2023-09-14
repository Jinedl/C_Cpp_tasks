class C {
public:
    C() {}
    C(int a, int b) {}
    C(double a) {}
    C& operator++() { return *this; };
    int operator*(C *b) { return 0; };
    friend const C& func1(const C *a, double b) { return *a; };
    friend int operator~(const C& a) { return 0; }
    friend int operator+(int a, const C &b) { return 0; };
};
