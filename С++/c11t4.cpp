#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

const string operations = " */+-&^|";

bool
is_op(char a)
{
    return operations.find(a) != (long unsigned int) (-1);
}

int
f(int a)
{
    return (a == 1 || a == 3) + a;
}

bool
cmp_op(char a, char b)
{
    int a_op = f(operations.find(a));
    int b_op = f(operations.find(b));
    return a_op > b_op;
}

int
simplify(string &expression, int start)
{
    int i = start;
    int first = i++;
    char op = ' ';
    while (expression[i] != ')') {
        if (expression[i] == '(') {
            i = simplify(expression, i);
        } else {
            if (is_op(expression[i])) {
                op = cmp_op(op, expression[i]) ? op : expression[i];
            }
            i++;
        }
    }
    int second = i;
    bool ok = true;
    if (first && is_op(expression[first - 1])) {
        ok = ok && cmp_op(expression[first - 1], op);
    }
    if ((long unsigned int) second != expression.length() - 1 && is_op(expression[second + 1])) {
        ok = ok &&
            (cmp_op(expression[second + 1], op) ||
                (!cmp_op(expression[second + 1], op) && !cmp_op(op, expression[second + 1])));
    }
    if (ok) {
        expression.erase(second, 1);
        expression.erase(first, 1);
        i -= 2;
        return start;
    }
    return i + 1;
}



int
main()
{
    string expression;
    cin >> expression;
    int i = 0;
    while (expression[i]) {
        if (expression[i] == '(') {
            i = simplify(expression, i);
        } else {
            i++;
        }
    }
    cout << expression << endl;
}
