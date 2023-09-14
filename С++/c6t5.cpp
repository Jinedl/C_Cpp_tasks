#include <iostream>
#include <map>
#include <unordered_map>

enum { BASE = 4294967161 };

using std::string;
using std::map;
using std::unordered_map;

int
main()
{
    unordered_map<unsigned, unordered_map<unsigned, long long unsigned>> m1, m2;
    map<unsigned, map<unsigned, long long unsigned>> m3;
    unsigned r, c;
    long long unsigned v;
    while (std::cin >> r >> c >> v) {
        if (r == 0 && c == 0 && v == BASE) {
            break;
        }
        m1[r][c] = v % BASE;
    }
    while (std::cin >> r >> c >> v) {
        m2[c][r] = v % BASE;
    }

    for (auto iter1r = m1.begin(); iter1r != m1.end(); iter1r++) {
        for (auto iter2c = m2.begin(); iter2c != m2.end(); iter2c++) {
            long long unsigned h = 0;
            for (auto iter1c = iter1r->second.begin(); iter1c != iter1r->second.end(); iter1c++) {
                if (iter2c->second.find(iter1c->first) != iter2c->second.end()) {

                    h += (iter2c->second[iter1c->first] * iter1c->second) % BASE;
                    h %= BASE;
                }
            }
            if (h) {
                m3[iter1r->first][iter2c->first] = h;
            }
        }
    }

    for (auto iter1 = m3.begin(); iter1 != m3.end(); iter1++) {
        for (auto iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
            if (iter2->second) {
                std::cout << iter1->first << " " << iter2->first << " " << iter2->second << std::endl;
            }
        }
    }
}
