#include <iostream>

/*

S -> aSd | bWc
W -> bWc | _

*/

void
W(unsigned k)
{
    if (k == 0) {
    }
    else {
        std::cout << 'b';
        W(k - 1);
        std::cout << 'c';
    }
}

void
S(unsigned k, unsigned bc)
{
    if (bc == 0) {
        W(k);
    }
    else {
        std::cout << 'a';
        S(k - 1, bc - 1);
        std::cout << 'd';
    }
}

int
main()
{
    unsigned k;
    std::cin >> k;
    if (k >= 4 && !(k & 1)) {
        for (unsigned bc = (k >> 1) - 1; bc >= 1; bc--) {
            S(k >> 1, bc);
            std::cout << std::endl;
        }
    }
}
