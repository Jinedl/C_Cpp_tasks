#include <iostream>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;

int
main()
{
    int m;
    char h, prev;
    if ((m = getchar()) == EOF) {
        return 0;
    }
    prev = (char) m;
    int count = 1;
    while ((m = getchar()) != EOF)  {
        h = (char) m;
        if (h == prev) {
            count++;
        } else {
            if (count > 4 || prev == '#') {
                cout << "#" << prev << std::hex << count << "#";
            } else {
                for (int i = 0; i < count; i++) {
                    cout << prev;
                }
            }
            count = 1;
        }
        prev = h;
    }
    if (count > 4 || prev == '#') {
        cout << "#" << prev << std::hex << count << "#";
    } else {
        for (int i = 0; i < count; i++) {
            cout << prev;
        }
    }
    return 0;
}
