#include <vector>
#include <iostream>

void
process(const std::vector<uint64_t> &v1,
    std::vector<uint64_t> &v2, const unsigned int &step)
{

    auto iter1 = v1.begin();
    auto iter2 = v2.rbegin();
    while (iter1 < v1.end() && iter2 < v2.rend()) {
        *iter2 += *iter1;
        iter2 += 1;
        iter1 += step;
    }
}
