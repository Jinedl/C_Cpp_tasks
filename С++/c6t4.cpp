#include <iostream>
#include <map>

enum { BASE = 4294967161 };

using std::string;
using std::map;

int main()
{
    map<unsigned, map<unsigned, long long unsigned>> m;
    unsigned r, c;
    long long unsigned v;
    while (std::cin >> r >> c >> v) {
        if (r == 0 && c == 0 && v == BASE) {
            break;
        }
        m[r][c] = v % BASE;
    }
    while (std::cin >> r >> c >> v) {
        if (m.find(r) == m.end()) {
            m[r][c] = v % BASE;
        } else if (m[r].find(c) == m[r].end()) {
            m[r][c] = v % BASE;
        } else {
            m[r][c] += v;
            m[r][c] %= BASE;
        }
    }

    for (auto iter1 = m.begin(); iter1 != m.end(); iter1++) {
        for (auto iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
            if (iter2->second) {
                std::cout << iter1->first << " " << iter2->first << " " << iter2->second << std::endl;
            }
        }
    }
}
