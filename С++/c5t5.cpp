#include <list>
#include <algorithm>
#include <iostream>

void
remove(long long a, std::list<long long> &l)
{
    if ((unsigned long long) a > l.size()) {
        return;
    }
    auto iter = l.begin();
    for (long long i = 1; i < a; i++) {
        iter++;
    }
    l.erase(iter);
}

void
add(long long a, long long b, std::list<long long> &l)
{
    if ((unsigned long long) a > l.size()) {
        l.insert(l.end(), b);
        return;
    }
    auto iter = l.begin();
    for (int i = 1; i < a; i++) {
        iter++;
    }
    l.insert(iter, b);
}

int
main()
{
    std::list<long long> l;
    long long h;
    while (std::cin >> h) {
        if (!h) {
            break;
        }
        l.push_back(h);
    }

    while (std::cin >> h) {
        if (h < 0) {
            remove(-h, l);
        } else {
            long long hh;
            std::cin >> hh;
            add(h, hh, l);
        }
    }

    for (auto iter = l.begin(); iter != l.end(); iter++) {
        std::cout << *iter << std::endl;
    }
}
