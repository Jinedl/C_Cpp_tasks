#include <vector>
#include <array>
#include <complex>

template <typename T>
bool
is_zero(const T &a)
{
    if (a == 0) {
        return true;
    }
    return false;
}

template <typename T>
bool
is_zero(const std::complex<T> &a)
{
    if (a.imag() == 0 && a.real() == 0) {
        return true;
    }
    return false;
}

namespace Equations
{
    template <typename T>
    std::pair<bool, std::vector<T>>
    quadratic(const std::array<T, 3> &coeff)
    {
        std::pair<bool, std::vector<T>> ans;
        ans.first = false;
        if (!is_zero(coeff.at(2))) {

            ans.first = true;

            T a = coeff.at(2);
            a *= coeff.at(0);
            a *= 4;
            T b = coeff.at(1);
            b *= coeff.at(1);
            T D = b;
            D -= a;

            T r1 = coeff.at(1);
            r1 *= -1;
            r1 += sqrt(D);
            r1 /= coeff.at(2);
            r1 /= 2;
            ans.second.push_back(r1);

            T r2 = coeff.at(1);
            r2 *= -1;
            r2 -= sqrt(D);
            r2 /= coeff.at(2);
            r2 /= 2;
            ans.second.push_back(r2);

        } else if (!is_zero(coeff.at(1))) {
            ans.first = true;
            ans.second.push_back(-coeff.at(0) / coeff.at(1));
        } else if (!is_zero(coeff.at(0))) {
            ans.first = true;
        }
        return ans;
    }
};
