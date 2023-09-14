#include <iostream>

using std::cin;
using std::cout;

struct A {
    int a;
    bool flag;

    A(A &h)/*: flag(true)*/ {
        flag = true;
        cin >> a;
        a += h.a;
    }

    A()/*: flag(false)*/ {
        flag = false;
        cin >> a;
    }

    ~A() {
        if (flag) {
            cout << a;
        }
    }

};

int main()
{
    A a, b(a);
}
/*
#include <iostream>
using namespace std;
class A
{
    int n;
    bool is_d;
public:
    A(): is_d(false) {cin >> n;};
    A(A &a): is_d(true){
        cin >> n;
        n += a.n;
    };
    ~A() {if (is_d) cout << n;};
};
*/
