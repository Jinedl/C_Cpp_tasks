/*
class Figure
{
    public:
    virtual double get_square() const = 0;
    virtual ~Figure() {}
};
*/

#include <string>
#include <cmath>

using std::string;

class Rectangle : public Figure
{
    public:
    double a, b, s;
    Rectangle (double a, double b) : a(a), b(b), s(a * b) {}
    static Rectangle* make(string str)
    {
        std::size_t offset;
        double h1 = std::stod(&str[0], &offset);
        double h2 = std::stod(&str[offset]);
        return new Rectangle(h1, h2);
    }
    double get_square() const
    {
        return s;
    }
};

class Square : public Figure
{
    public:
    double a, s;
    Square (double a) : a(a), s(a * a) {}
    static Square* make(string str)
    {
        std::size_t offset;
        double h = std::stod(&str[0], &offset);
        return new Square(h);
    }
    double get_square() const
    {
        return s;
    }
};


class Circle : public Figure
{
    public:
    double r, s;
    Circle (double r) : r(r), s(r * r * M_PI) {}
    static Circle* make(string str)
    {
        std::size_t offset;
        double h = std::stod(&str[0], &offset);
        return new Circle(h);
    }
    double get_square() const
    {
        return s;
    }
};
