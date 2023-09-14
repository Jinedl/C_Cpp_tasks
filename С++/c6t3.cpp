#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <map>

using std::string;
using std::map;
using std::set;

class Date
{
    int year;
    int month;
    int day;
    public:
    Date(const string &str)
    {
        std::size_t offset1, offset2;
        year = std::stod(&str[0], &offset1);
        month = std::stod(&str[offset1 + 1], &offset2);
        day = std::stod(&str[offset1 + offset2 + 2]);
    }
    friend bool operator < (const Date &a, const Date &b)
    {
        if (a.year < b.year) {
            return true;
        } else if (a.year > b.year) {
            return false;
        }
        if (a.month < b.month) {
            return true;
        } else if (a.month > b.month) {
            return false;
        }
        if (a.day < b.day) {
            return true;
        }
        return false;
    }
    friend std::ostream& operator<<(std::ostream &os, const Date& a)
    {
        return os << a.year
            << "/" << std::setw(2) << std::setfill('0') << a.month
                << "/" << std::setw(2) << std::setfill('0') << a.day;
    }
};

int main()
{
    set<Date> s;
    map<string, map<Date, int>> m;
    string surname, date;
    int mark;
    while (std::cin >> surname >> date >> mark) {
        s.insert(Date(date));
        m[surname][Date(date)] = mark;
    }

    std::cout << ". ";
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    for (auto iter1 = m.begin(); iter1 != m.end(); iter1++) {
        std::cout << iter1->first << " ";
        for (auto iter2 = s.begin(); iter2 != s.end(); iter2++) {
            if (iter1->second.find(*iter2) == iter1->second.end()) {
                std::cout << ". ";
            } else {
                std::cout << iter1->second[*iter2] << " ";
            }
        }
        std::cout << std::endl;
    }
}
