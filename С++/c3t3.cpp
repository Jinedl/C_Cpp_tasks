#include <vector>
#include <map>
#include <string>

namespace numbers {
    complex eval(const std::vector<std::string> &args, const complex &z)
    {
        std::vector<complex> stack;
        std::map<std::string, void (*) (std::vector<complex> &a)> func
        {
            {"+", [] (std::vector<complex> &a) { *(a.end() - 2) += *(a.end() - 1); a.pop_back(); }},
            {"-", [] (std::vector<complex> &a) { *(a.end() - 2) -= *(a.end() - 1); a.pop_back(); }},
            {"*", [] (std::vector<complex> &a) { *(a.end() - 2) *= *(a.end() - 1); a.pop_back(); }},
            {"/", [] (std::vector<complex> &a) { *(a.end() - 2) /= *(a.end() - 1); a.pop_back(); }},
            {"!", [] (std::vector<complex> &a) { a.push_back(*(a.end() - 1)); }},
            {";", [] (std::vector<complex> &a) { a.pop_back(); }},
            {"~", [] (std::vector<complex> &a) { *(a.end() - 1) = ~(*(a.end() - 1)); }},
            {"#", [] (std::vector<complex> &a) { *(a.end() - 1) = -(*(a.end() - 1)); }},
        };
        for (auto iter = args.begin(); iter < args.end(); iter++) {
            if (iter->find("(") == 0) {
                stack.push_back(complex(*iter));
            } else if ("a" <= *iter && *iter <= "z") {
                stack.push_back(z);
            } else {
                func[*iter](stack);
            }
        }
        return *(stack.end() - 1);
    }
};
