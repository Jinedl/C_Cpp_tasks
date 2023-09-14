#include <string>

using std::string;

class BinaryNumber
{
    string val;
public:

    BinaryNumber(const string &s = "0")
    {
        val = s;
    }

    const BinaryNumber& operator++()
    {
        int pos = (this->val).rfind("0");
        int len = (this->val).length();
        if (pos < 0) {
            val = "1";
            for (int j = 0; j < len; j++) {
                val += "0";
            }
        } else {
            val[pos] = '1';
            pos++;
            while (val[pos]) {
                val[pos] = '0';
                pos++;
            }
        }
        return *this;
    }

    operator string () const
    {
        return this->val;
    }
};
