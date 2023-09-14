#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;

int
min(int a, int b)
{
    return a < b ? a : b;
}

int
main()
{
    int m, n, r1, c1, r2, c2;
    cin >> m >> n;
    while (cin >> r1 >> c1 >> r2 >> c2) {
        int r = abs(r1 - r2);
        int c = abs(c1 - c2);
        cout << min(r, abs(m - r)) + min(c, abs(n - c)) << std::endl;
    }
}
