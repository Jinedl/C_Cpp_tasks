#include <iostream>

struct Sum {
    int a;
    int b;

    Sum(int p1, int p2) {
        a = p1;
        b = p2;
    }

    Sum(Sum p1, int p2) {
        a = p1.get();
        b = p2;
    }

    int get() const { return a + b; }

};
