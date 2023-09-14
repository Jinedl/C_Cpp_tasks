#include <iostream>
#include <map>

using std::map;
using std::pair;

enum { MOD = 4294967161 };

int main()
{
    uint32_t r = 0, c = 0;
    uint64_t v = 0;

    map <pair<uint32_t, uint32_t>, uint64_t> mtx, ans;

    while(std::cin >> r >> c >> v, not(v == MOD && r == 0 && c == 0)) {
        mtx[pair<uint32_t, uint32_t> (c, r)] = v % MOD; // transposed
    }

    while(std::cin >> r >> c >> v) {
        auto it = mtx.lower_bound(pair<uint32_t, uint32_t> (r, 0));
        while(it->first.first == r) {
            pair<uint32_t, uint32_t> key(it->first.second, c);
            ans[key] += (it->second * v) % MOD;
            ans[key] %= MOD;
            ++it;
        }
    }

    auto it = ans.begin();
    while(it != ans.end()) {
        if (it->second != 0) {
            std::cout << (it->first).first << " " << (it->first).second << " " << it->second << std::endl;
        }
        ++it;
    }

    return 0;
}
