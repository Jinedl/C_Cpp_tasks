#include <vector>
#include <algorithm>

void
process(const std::vector<int> vc, std::vector<int> &v2)
{
    auto v1 = vc;

    std::sort(v1.begin(), v1.end());
    auto iter0 = std::unique(v1.begin(), v1.end());
    v1.erase(iter0, v1.end());

    iter0 = v1.begin();
    while (iter0 < v1.end() && *iter0 < 0) {
        iter0++;
    }

    auto iter1 = v2.begin();
    auto iter2 = v2.begin();
    int num = 0;
    while (iter1 < v2.end()) {
        if (iter0 < v1.end() && *iter0 == num) {
            iter0++;
        } else {
            std::swap(*iter1, *iter2);
            iter2++;
        }
        num++;
        iter1++;
    }
    v2.erase(iter2, v2.end());
}
