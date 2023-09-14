#include <vector>
#include <algorithm>
#include <iostream>

enum { SIZE = 32 };

int
bit(unsigned a)
{
    int ans = 0;
    for (int i = 0; i < SIZE; i++) {
        ans += a & 1;
        a >>= 1;
    }
    return ans;
}

bool
comp(unsigned a, unsigned b)
{
    return bit(a) < bit(b);
}

int
main()
{
    std::vector<unsigned> v;
    unsigned h;
    while (std::cin >> h) {
        v.push_back(h);
    }
    std::stable_sort(v.begin(), v.end(), comp);
    for (auto iter = v.begin(); iter < v.end(); iter++) {
        std::cout << *iter << std::endl;
    }
}
