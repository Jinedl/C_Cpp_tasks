#include <vector>
#include <algorithm>

template<typename A, typename B>
B
myremove(const A &begin1, const A &end1, const B &begin2, const B &end2)
{
    std::vector<typename std::iterator_traits<A>::value_type> v1;
    for (auto iter = begin1; iter != end1; ++iter) {
        v1.push_back(*iter);
    }

    std::sort(v1.begin(), v1.end());
    auto iter0 = std::unique(v1.begin(), v1.end());
    v1.erase(iter0, v1.end());

    iter0 = v1.begin();
    while (iter0 < v1.end() && *iter0 < 0) {
        iter0++;
    }

    auto iter1 = begin2;
    auto iter2 = begin2;
    int num = 0;
    while (iter1 != end2) {
        if (iter0 != v1.end() && *iter0 == num) {
            ++iter0;
        } else {
            std::swap(*iter1, *iter2);
            ++iter2;
        }
        ++num;
        ++iter1;
    }
    return iter2;
}
