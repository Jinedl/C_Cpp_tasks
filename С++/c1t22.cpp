#include <iostream>

using std::cin;
using std::cout;

struct A {
    int a;
    bool flag;

    A(A &h) {
        flag = true;
        cin >> a;
        a += h.a;
    }

    A() {
        flag = false;
        cin >> a;
    }

    ~A() {
        if (flag) {
            cout << a;
        }
    }

};
