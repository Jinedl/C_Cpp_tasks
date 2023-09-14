#include <iostream>

class S
{
    int val;
    bool ok;
public:
    S()
    {
        ok = (bool) (std::cin >> val);
    }
    S(S &a)
    {
        ok = (bool) (std::cin >> val);
        if (ok) {
            val += a.val;
            a.ok = false;
        }
    }
    ~S()
    {
        if (ok) {
            std::cout << val << std::endl;
        }
    }
    operator bool() const
    {
        return ok;
    }
};

S
move(S &a)
{
    return S(a);
}

/*
using namespace std;
void func(S v)
{
    if (v) {
        func(move(v));
    }
}

int
main()
{
    func(S());
}
*/
