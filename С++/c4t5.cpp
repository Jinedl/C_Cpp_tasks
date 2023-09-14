#include <iostream>

struct suffix {
    int num;
    char *str;
};

using std::cout;

int main()
{
    str str, space;
    char c;
    int h;
    if ((h = getchar()) == EOF) {
        return 0;
    }
    while ((h = getchar()) != EOF)  {
        c = (char) h;
        if (c ==  ' ') {
            space += c;
        } else {
            str += space + c;
            space = "";
        }
    }
    int len = str.length();
    if (len == 0) {
        return 0;
    }
    suffix mas[len];
    for (int i = 0; i < len; i++) {
        mas[i].num = i;
        mas[i].str = &str[i];
    }
    
    //sort
    
    for (int i = 0; i < len; i++) {
        std::cout << mas[i].num;
    }
    return 0;
}
