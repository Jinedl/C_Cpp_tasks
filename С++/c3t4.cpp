#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <functional>
#include <math.h>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

using std::string;
using std::vector;

int
main(int argc, char *argv[])
{
    using namespace numbers;
    complex c(argv[1]);
    double r = strtod(argv[2], nullptr);
    int n = (int) strtol(argv[3], nullptr, 10);
    vector<string> args;
    for (int i = 4; i < argc; i++) {
        args.emplace_back(string(argv[i]));
    }

    complex ans(0, 0);
    double dx = 2 * M_PI / double(n);
    double t = dx / 2;

    complex i(0, 1);
    for (int j = 0; j < n; j++) {
        complex ei(cos(t), sin(t));
        complex h = r * ei;
        complex val = eval(args, h + c);
        ans += val * h * i * dx;
        t += dx;
    }
    std::cout << ans.to_string() << std::endl;
}
