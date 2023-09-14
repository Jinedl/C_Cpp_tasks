#include <vector>
#include <functional>

template<typename T, typename F>
void
myapply(const T &begin, const T &end, F f)
{
    for (auto iter = begin; iter != end; ++iter) {
        f(*iter);
    }
}

template<typename T, typename Ok>
std::vector<std::reference_wrapper<typename std::iterator_traits<T>::value_type>>
myfilter2(const T &begin, const T &end, Ok ok)
{
    std::vector<std::reference_wrapper<typename std::iterator_traits<T>::value_type>> v;
    for (auto iter = begin; iter != end; ++iter) {
        if (ok(*iter)) {
            v.push_back(std::ref(*iter));
        }
    }
    return v;
}
