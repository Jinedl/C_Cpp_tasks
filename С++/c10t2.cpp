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
is01(int a)
{
    return is0(a) || is1(a);
}

int
main()
{
    int in, zeros, ones, zeros_repeat, ones_repeat;
    int condition = 0;

    while ((in = getchar()) != EOF) {

        switch (condition) {
            case 0:
                zeros = 0, ones = 0, zeros_repeat = 0, ones_repeat = 0;
                if (isspace(in)) {
                    continue;
                }
                condition = 1;
            case 1:
                if ((!isspace(in) && !is01(in)) || (!zeros && is1(in))) {
                    condition = 3;
                    continue;
                }
                if (isspace(in)) {
                    if (ones) {
                        std::cout << "1" << std::endl;
                    } else {
                        std::cout << "0" << std::endl;
                    }
                    condition = 0;
                    continue;
                }
                if (!(ones && is0(in))) {
                    zeros += is0(in);
                    ones += is1(in);
                    continue;
                }
                condition = 2;
            case 2:
                if (!isspace(in) && !is01(in)) {
                    condition = 3;
                    continue;
                }
                if (isspace(in)) {
                    if (!zeros_repeat && !ones_repeat) {
                        std::cout << "1" << std::endl;
                    } else {
                        std::cout << "0" << std::endl;
                    }
                    condition = 0;
                    continue;
                }
                if (zeros_repeat < zeros && is1(in)) {
                    condition = 3;
                    continue;
                }
                zeros_repeat += is0(in);
                ones_repeat += is1(in);
                if (zeros < zeros_repeat || ones < ones_repeat) {
                    condition = 3;
                } else if (zeros == zeros_repeat && ones == ones_repeat) {
                    zeros_repeat = 0, ones_repeat = 0;
                }
                continue;
            case 3:
                if (!isspace(in)) {
                    continue;
                }
                std::cout << "0" << std::endl;
                condition = 0;
        }
    }

    switch (condition) {
        case 1:
            std::cout << "1" << std::endl;
            break;
        case 2:
            if (!zeros_repeat && !ones_repeat) {
                std::cout << "1" << std::endl;
            } else {
                std::cout << "0" << std::endl;
            }
            break;
        case 3:
            std::cout << "0" << std::endl;
    }
}
