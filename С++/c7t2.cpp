template<typename T, typename Ok>
T myfilter(const T &a, Ok ok)
{
    T ans{};
    for (auto iter = a.begin(); iter != a.end(); iter++) {
        if (ok(*iter)) {
            ans.insert(ans.end(), *iter);
        }
    }
    return ans;
}
