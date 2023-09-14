#include <iostream>
#include <string>
#include <vector>

int
main()
{
    std::vector<std::string> stack;
    std::string s1, s2;
    int in;
    while ((in = getchar()) != EOF && !isspace(in)) {
        switch (in) {
            case '+':
                s1 = *(stack.end() - 1);
                stack.pop_back();
                s2 = *(stack.end() - 1);
                stack.pop_back();
                stack.push_back( '(' +  s2 + '+' + s1 + ')' );
                break;
            case '-':
                s1 = *(stack.end() - 1);
                stack.pop_back();
                s2 = *(stack.end() - 1);
                stack.pop_back();
                stack.push_back( '(' +  s2 + '-' + s1 + ')' );
                break;
            case '*':
                s1 = *(stack.end() - 1);
                stack.pop_back();
                s2 = *(stack.end() - 1);
                stack.pop_back();
                stack.push_back( '(' +  s2 + '*' + s1 + ')' );
                break;
            case '/':
                s1 = *(stack.end() - 1);
                stack.pop_back();
                s2 = *(stack.end() - 1);
                stack.pop_back();
                stack.push_back( '(' +  s2 + '/' + s1 + ')' );
                break;
            default:
                char ch = (char) in;
                s1 = ch;
                stack.push_back(s1);
        }
    }
    std::cout << *(stack.end() - 1) << std::endl;
}
