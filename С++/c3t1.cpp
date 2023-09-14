#include <iostream>
#include <string>
#include <cmath>

using std::string;
enum {LEN = 128};

namespace numbers {

    class complex {
        double r, i;
    public:
        complex(double a = 0, double b = 0)
        {
            r = a;
            i = b;
        }
        explicit complex(const char *s)
        {
            string str = string(s);
            complex h(str);
            r = h.r;
            i = h.i;
        }
        explicit complex(const string &str)
        {
            std::size_t offset;
            r = std::stod(&str[1], &offset);
            i = std::stod(&str[offset + 2]);
        }
        double re() const
        {
            return r;
        }
        double im() const
        {
            return i;
        }
        double abs2() const
        {
            return r * r + i * i;
        }
        double abs() const
        {
            return sqrt(this->abs2());
        }
        complex operator += (const complex &a)
        {
            r += a.r;
            i += a.i;
            return *this;
        }
        complex operator -= (const complex &a)
        {
            r -= a.r;
            i -= a.i;
            return *this;
        }
        complex operator *= (const complex &a)
        {
            double r1 = r, i1 = i;
            r = r1 * a.r - i1 * a.i;
            i = r1 * a.i + a.r * i;
            return *this;
        }
        complex operator /= (const complex &a)
        {
            double r1 = r, i1 = i;
            r = (r1 * a.r + i1 * a.i) / a.abs2();
            i = (a.r * i1 - r1 * a.i) / a.abs2();
            return *this;
        }
        complex operator ~ () const
        {
            complex a(r, -i);
            return a;
        }
        complex operator - () const
        {
            complex a(-r, -i);
            return a;
        }
        friend complex operator + (const complex h, const complex a)
        {
            complex b(h.r, h.i);
            return b += a;
        }
        friend complex operator - (const complex h, const complex a)
        {
            complex b(h.r, h.i);
            return b -= a;
        }
        friend complex operator * (const complex h, const complex a)
        {
            complex b(h.r, h.i);
            return b *= a;
        }
        friend complex operator / (const complex h, const complex a)
        {
            complex b(h.r, h.i);
            return b /= a;
        }
        string to_string() const
        {
            char s[LEN];
            snprintf(s, LEN, "(%.10g,%.10g)", r, i);
            string str = string(s);
            return str;
        }
    };
}
