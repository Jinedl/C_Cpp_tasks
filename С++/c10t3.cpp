/*
    S = aXPQ | aXP | aXQ | aX
    P = YXP | YX
    Q = UVQ | UV
    aY = aa
    aU = a0
    0U = 00
    0X = 0b
    bX = bb
    bV = b1
    1V = 11
    XY = YX
    UY = YU
    VY = YV
    XU = UX
    VU = UV
    VX = XV
 *
 * L(G*) = { (a^n)(0^m)(b^n)(1^m) | m, n > 0 }
 */

#include <iostream>
#include <cstdio>

int
is0(int a)
{
    return a == '0';
}

int
is1(int a)
{
    return a == '1';
}

int
isa(int a)
{
    return a == 'a';
}

int
isb(int a)
{
    return a == 'b';
}

int
is01ab(int a)
{
    return is0(a) || is1(a) || isa(a) || isb(a);
}

int
main()
{
    int in, n, m;
    int condition = 0;

    while ((in = getchar()) != EOF) {

        switch (condition) {
            case 0:
                n = 0, m = 0;
                if (isspace(in)) {
                    continue;
                }
                if (!isspace(in) && !isa(in)) {
                    condition = 5;
                    continue;
                }
                condition = 1;
            case 1:
                if (!isspace(in)) {
                    if (!is01ab(in) || isb(in) || is1(in)) {
                        condition = 5;
                    } else if (isa(in)) {
                        n++;
                    } else if (is0(in)) {
                        m++;
                        condition = 2;
                    }
                } else {
                    std::cout << "0" << std::endl;
                    condition = 0;
                }
                continue;
            case 2:
                if (!isspace(in)) {
                    if (!is01ab(in) || isa(in) || is1(in)) {
                        condition = 5;
                    } else if (is0(in)) {
                        m++;
                    } else if (isb(in)) {
                        n--;
                        condition = 3;
                    }
                } else {
                    std::cout << "0" << std::endl;
                    condition = 0;
                }
                continue;
            case 3:
                if (!isspace(in)) {
                    if (!is01ab(in) || isa(in) || is0(in)) {
                        condition = 5;
                    } else if (isb(in)) {
                        n--;
                        if (n < 0) {
                            condition = 5;
                        }
                    } else if (is1(in)) {
                        m--;
                        if (n) {
                            condition = 5;
                        } else {
                            condition = 4;
                        }
                    }
                } else {
                    std::cout << "0" << std::endl;
                    condition = 0;
                }
                continue;
            case 4:
                if (!isspace(in)) {
                    if (!is1(in)) {
                        condition = 5;
                    } else {
                        m--;
                        if (m < 0) {
                            condition = 5;
                        }
                    }
                } else {
                    if (!n && !m) {
                        std::cout << "1" << std::endl;
                    } else {
                        std::cout << "0" << std::endl;
                    }
                    condition = 0;
                }
                continue;
            case 5:
                if (!isspace(in)) {
                    continue;
                }
                std::cout << "0" << std::endl;
                condition = 0;
        }
    }

    switch (condition) {
        case 4:
            if (!n && !m) {
                std::cout << "1" << std::endl;
            } else {
                std::cout << "0" << std::endl;
            }
            break;
        case 1:
        case 2:
        case 3:
        case 5:
            std::cout << "0" << std::endl;
    }
}
