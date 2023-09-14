#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

using boost::gregorian::date;

int
main() {

    std::string str;
    date a, b;
    long res = 0;
    short unsigned y, m, d;
    std::size_t offset1, offset2;

    if (std::cin >> str) {

        y = (short unsigned) std::stoi(&str[0], &offset1);
        m = (short unsigned) std::stoi(&str[offset1 + 1], &offset2);
        d = (short unsigned) std::stoi(&str[offset1 + offset2 + 2]);
        a = { y, m, d };
    } else {
        return 0;
    }
    while (std::cin >> str){

        y = (short unsigned) std::stoi(&str[0], &offset1);
        m = (short unsigned) std::stoi(&str[offset1 + 1], &offset2);
        d = (short unsigned) std::stoi(&str[offset1 + offset2 + 2]);
        b = { y, m, d };
        res += abs((a - b).days());
        a = b;
    }
    std::cout << res << std::endl;
}
