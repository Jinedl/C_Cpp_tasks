#include <algorithm>

template<typename T>
struct Comp
{
    typedef bool (*type) (std::iterator_traits<T>::value_type, std::iterator_traits<T>::value_type);
};

template<typename T, typename F = Comp<T>::type>
void
selection_sort(T first, T last,
    F f = [] (std::iterator_traits<T>::value_type a, std::iterator_traits<T>::value_type b) { return a < b; })
{
    for (auto iter1 = first; iter1 != last; ++iter1) {
        T min = iter1;
        for (auto iter2 = iter1; iter2 != last; ++iter2) {
            if (f(*iter2, *min)) {
                min = iter2;
            }
        }
        std::swap(*iter1, *min);
    }
}
