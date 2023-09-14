#include <iostream>

class Result
{
public:
    int val;
    Result(int h = 0) : val(h) {}
};

void
ackermann(int m, int n)
{
    if (!m && n >= 0) {
        throw Result(n + 1);
    } else if (!n && m > 0) {
        try {
            ackermann(m - 1, 1);
        } catch (Result &res) {
            throw res;
        }
    } else if (m > 0 && n > 0) {
        try {
            ackermann(m, n - 1);
        } catch (Result &res) {
            try {
                ackermann(m - 1, res.val);
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
    int m, n;
    std::cin >> m >> n;
    try {
        ackermann(m, n);
    } catch (Result &res) {
        std::cout << res.val << std::endl;;
    }
}
