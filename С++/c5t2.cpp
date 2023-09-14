#include <vector>
#include <iostream>

void
process(std::vector<long long int> &v, long long int limit)
{
    v.reserve(2 * v.size());
    for (auto iter = v.rbegin(); iter != v.rend(); iter++) {
        if (*iter >= limit) {
            v.push_back(*iter);
        }

    }
}

/*
int
main()
{
    std::vector<long long int> v2 = {1, 4, 3, 2};
    process(v2, 3);
    for (auto i1 = v2.begin(); i1 != v2.end(); ++i1) {
        std::cout << *i1 << std::endl;
    }
}
*/
