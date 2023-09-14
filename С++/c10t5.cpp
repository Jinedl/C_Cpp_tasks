#include <iostream>
#include <string>

using std::string;
using std::cout;

bool
is_terminal(string str)
{
    int i = 0;
    while (str[i]) {
        if (isupper(str[i])) {
            return false;
        }
        i++;
    }
    return true;
}

bool
is_nonterminal(string str)
{
    return str.length() == 1 && isupper(str[0]);
}

bool
is_shortening(string left, string right)
{
    return (!(left == "S") && right == "_") || left.length() > right.length();
}

bool
is_S_to_empty(string left, string right)
{
    return left == "S" && right == "_";
}

bool
is_right_S(string str)
{
    int i = 0;
    while (str[i]) {
        if (str[i] == 'S') {
            return true;
        }
        i++;
    }
    return false;
}

int
main()
{
    bool empty = true, left_only_terminal = false, left_S = false, context_free = true,
        shortening = false, S_to_empty = false, right_S = false;
    string left, right;
    while (std::cin >> left >> right) {
        empty = false;
        left_S = left_S || left == "S";
        left_only_terminal = left_only_terminal || is_terminal(left);
        context_free = context_free && is_nonterminal(left);
        shortening = shortening || is_shortening(left, right);
        S_to_empty = S_to_empty || is_S_to_empty(left, right);
        right_S = right_S || is_right_S(right);
    }
    shortening = shortening || (S_to_empty && right_S);
    if (empty || left_only_terminal || !left_S) {
        cout << "-1";
    } else if (context_free) {
        cout << "2";
        if (!shortening) {
            cout << "3";
        }
    } else {
        cout << "10";
    }
    cout << std::endl;
}
