#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

double
process(std::vector<double> v)
{
    int unuse = ceil(v.size() * 0.1);
    auto first = v.begin() + unuse, last = v.end() - unuse;

    std::sort(first, last);

    unuse = ceil(std::distance(first, last) * 0.1);
    first += unuse, last -= unuse;

    struct Average
    {
        double sum = 0;
        unsigned count = 0;
        double ave = 0;
        void operator() (double i) {
            sum += i;
            count++;
            ave = sum / count;
        }
    };
    return std::for_each(first, last, Average()).ave;
}



int
main()
{
    std::vector<double> v;
    double h;
    while (std::cin >> h) {
        v.push_back(h);
    }
    std::cout << process(v) << std::endl;
}
