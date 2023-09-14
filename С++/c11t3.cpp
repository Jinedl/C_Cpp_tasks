#include <iostream>
#include <string>
#include <map>

using std::map;
using std::pair;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int
main()
{
    map<string, pair<map<char, string>, bool>> automat;
    string CUR, NEW;
    char CHAR;
    while (true) {
        cin >> CUR;
        if (CUR != "END") {
            cin >> CHAR >> NEW;
            automat[CUR].first[CHAR] = NEW;
            automat[CUR].second = false;
        } else {
            break;
        }
    }
    while (true) {
        cin >> CUR;
        if (CUR != "END") {
            automat[CUR].second = true;
        } else {
            break;
        }
    }
    cin >> CUR;
    bool ok;
    int in, i = 0;
    while ((in = getchar()) != EOF && isspace(in)) {}
    do {
        CHAR = (char) in;
        if (automat[CUR].first.find(CHAR) != automat[CUR].first.end()) {
            CUR = automat[CUR].first[CHAR];
            ok = automat[CUR].second;
            i++;
        } else {
            ok = false;
            break;
        }
    } while ((in = getchar()) != EOF && !isspace(in));
    cout << (int) ok << endl << i << endl << CUR << endl;
}
