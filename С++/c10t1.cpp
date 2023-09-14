#include <iostream>
#include <string>

struct Exc{
    Exc () {}
};

using std::string;

void
ok(string str)
{
    int len = str.length();
    int i = 0;
    while (i < len) {
        if (str[i] - '0' == 3 || str[i] - '0' == 4) {
            i++;
        } else if (str[i] - '0' == 1 || str[i] - '0' == 2) {
            break;
        } else {
            throw Exc();
        }
    }
    while (i < len) {
        if (str[i] - '0' == 1 || str[i] - '0' == 2) {
            i++;
        } else {
            throw Exc();
        }
    }
}

int
main()
{
    string in;
    while (std::cin >> in) {
        try {
            ok(in);
        } catch (Exc) {
            std::cout << "0" << std::endl;
            continue;
        }
        std::cout << "1" << std::endl;
    }
}
