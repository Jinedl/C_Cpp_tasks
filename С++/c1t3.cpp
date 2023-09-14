#include <iostream>
#include <cstdio>

//using std::cin;
using std::cout;
using std::endl;

int
main()
{
    int flag = 0;
    char h;
    while ((h = (char) getchar()) != EOF)  {
        if (0 > (h - '0') || 9 < (h - '0')) {
            if (flag == 2) {
                cout << "0";
            }
            flag = 0;
            cout << h;
        } else if ((h - '0') || flag == 1) {
            flag = 1;
            cout << h;
        } else {
            flag = 2;
        }
    }
    if (flag == 2) {
        cout << "0";
    }
//    cout << endl;
}
