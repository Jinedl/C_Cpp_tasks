template<typename T>
typename T::value_type process(const T &a)
{
    typename T::value_type ans = typename T::value_type();
    int count = a.size() >= 5 ? 3 : (a.size() + 1) / 2;
    auto iter = a.end();
    for (int i = 0; i < count; i++) {
        iter--;
        ans += *iter;
        iter--;
    }
    return ans;
}
