#include <iostream>
#include <string>

using std::string;
using std::cout;

bool
is_left(string in, string out)
{
    if (out != "_") {
        int i = 1;
        while (out[i]) {
            if (isupper(out[i])) {
                return false;
            }
            i++;
        }
    }
    return true;
}

bool
is_right(string in, string out)
{
    if (out != "_") {
        int i = out.length() - 2;
        while (out[i] && i >= 0) {
            if (isupper(out[i])) {
                return false;
            }
            i--;
        }
    }
    return true;
}

bool
is_automatic(string in, string out)
{
    if (out != "_" && out != "A") {
        int i = 0, terminal = 0, nonterminal = 0;
        while (out[i]) {
            if (isupper(out[i])) {
                nonterminal++;
            } else {
                terminal++;
            }
            i++;
        }
        return terminal == 1 && nonterminal <= 1;
    }
    return in == "S";
}

bool
is_shortening(string in, string out)
{
    return (!(in == "S") && out == "_") || in.length() > out.length();
}

bool
is_S_to_empty(string in, string out)
{
    return in == "S" && out == "_";
}

bool
is_out_S(string str)
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
    bool left = true, right = true, regular, automatic = true,
        shortening = false, S_to_empty = false, out_S = false;
    string in, out;
    while (std::cin >> in >> out) {
        left = left && is_left(in, out);
        right = right && is_right(in, out);
        automatic = automatic && is_automatic(in, out);
        shortening = shortening || is_shortening(in, out);
        S_to_empty = S_to_empty || is_S_to_empty(in, out);
        out_S = out_S || is_out_S(out);
    }
    shortening = shortening || (S_to_empty && out_S);
    automatic = automatic && !(S_to_empty && out_S);
    regular = left || right;
    if (!regular) {
        cout << "2";
        if (!shortening) {
            cout << "1";
        }
    } else {
        cout << "3";
        if (left) {
            cout << "1";
        } else if (right) {
            cout << "2";
        }
        if (automatic) {
            cout << "1";
        }
    }
    cout << std::endl;
}
