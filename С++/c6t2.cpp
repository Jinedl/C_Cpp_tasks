#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using std::string;
using std::map;

int
main()
{
    struct Student
    {
        int sum = 0;
        int count = 0;
        Student(int a = 0, int b = 0): sum(a), count(b) {}
        ~Student() = default;
    };
    map<string,Student> m;
    char surname[100];
    int mark;
    while (std::cin >> surname >> mark) {
        m[surname].sum += mark;
        m[surname].count++;
    }

    for (auto iter = m.begin(); iter != m.end(); iter++) {
        std::cout << iter->first << " " <<
            ((double)iter->second.sum / (double)iter->second.count) << std::endl;
    }

}
