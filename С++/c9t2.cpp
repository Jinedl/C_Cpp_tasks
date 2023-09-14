#include <iostream>

class Result
{
public:
    long long val;
    Result(long long h = 0) : val(h) {}
};

void
f(long long a, long long b, long long k)
{ //Ackermann function of 3 arguments
    if (!k && a > 0 && b >= 1) {
        throw Result(a + b);
    } else if (b == 1 && k > 0 && a > 0) {
        throw Result(a);
    } else if (k > 0 && b > 1 && a > 0) {
        try {
            f(a, b - 1, k);
        } catch (Result &res) {
            try {
                f(a, res.val, k - 1);
            } catch (Result &res) {
                throw res;
            }
        }
    }
    throw Result();
}


int
main()
{
    long long a, b, k;
    while (std::cin >> a >> b >> k) {
        try {
            f(a, b, k);
        } catch (Result &res) {
            std::cout << res.val << std::endl;
        }
    }
}
