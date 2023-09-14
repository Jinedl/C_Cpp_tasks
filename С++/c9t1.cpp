#include <iostream>

class Str
{
    std::string str;
public:
    Str(std::string s) : str(s) {}
    ~Str()
    {
        std::cout << str << std::endl;
    }
};

void
f()
{
    std::string s;
    if (std::cin >> s) {
        Str h(s);
        try {
            f();
        } catch (...) {
            throw std::exception();
        }
    } else {
        throw std::exception();
    }
}

int
main()
{
    try {
        f();
    } catch (...) {
    }
}
