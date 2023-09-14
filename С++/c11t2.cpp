#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Sym {
    bool unreachable = true;
    std::vector<std::string> sons;
};

void
reach_sons(char sym, std::map<char, Sym> &m)
{
    if (m[sym].unreachable) {
        m[sym].unreachable = false;
        for (auto iter = m[sym].sons.begin(); iter != m[sym].sons.end(); ++iter) {
            int i = 0;
            while ((*iter)[i]) {
                reach_sons((*iter)[i], m);
                i++;
            }
        }
    }
}

int
main()
{
    std::map<char, Sym> m;
    char sym;
    std::string sons;

    while (std::cin >> sym >> sons) {
        m[sym].sons.push_back(sons);
    }

    reach_sons('S', m);

    for (auto iter1 = m.begin(); iter1 != m.end(); ++iter1) {
        if (!iter1->second.unreachable) {
            for (auto iter2 = iter1->second.sons.begin(); iter2 != iter1->second.sons.end(); ++iter2) {
                std::cout << iter1->first << " " << *iter2 << std::endl;
            }
        }
    }

}
