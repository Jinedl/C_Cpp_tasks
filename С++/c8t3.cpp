/*
class Figure
{
    public:
    virtual double get_square() const = 0;
    virtual string to_string() const = 0;
    virtual ~Figure() {}
};

class Rectangle : public Figure
{
    public:
    double a, b, s;
    Rectangle (double a, double b) : a(a), b(b), s(a * b) {}
    static Rectangle*
    make(string str)
    {
        std::size_t offset;
        double h1 = std::stod(&str[0], &offset);
        double h2 = std::stod(&str[offset]);
        return new Rectangle(h1, h2);
    }
    double
    get_square() const
    {
        return s;
    }
    string
    to_string() const
    {
        return "R " + std::to_string(s);
    }
};

class Square : public Figure
{
    public:
    double a, s;
    Square (double a) : a(a), s(a * a) {}
    static Square*
    make(string str)
    {
        std::size_t offset;
        double h = std::stod(&str[0], &offset);
        return new Square(h);
    }
    double
    get_square() const
    {
        return s;
    }
    string
    to_string() const
    {
        return "S " + std::to_string(s);
    }
};


class Circle : public Figure
{
    public:
    double r, s;
    Circle (double r) : r(r), s(r * r * M_PI) {}
    static Circle*
    make(string str)
    {
        std::size_t offset;
        double h = std::stod(&str[0], &offset);
        return new Circle(h);
    }
    double
    get_square() const
    {
        return s;
    }
    string
    to_string() const
    {
        return "C " + std::to_string(s);
    }
};
*/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using std::string;

class Factory
{
    Factory() = default;
public:
    static Factory& factory_instance()
    {
        static Factory INSTANCE;
        return INSTANCE;
    }
    Figure* make(string s)
    {
        std::istringstream st(s);

        char type;
        st >> type;

        string str;
        std::getline(st, str);

        switch (type) {
            case 'R':
                return Rectangle::make(&str[1]);
            case 'S':
                return Square::make(&str[1]);
            case 'C':
                return Circle::make(&str[1]);
        }
        return nullptr;
    }
};

bool
comp(Figure *a, Figure *b)
{
    return a->get_square() < b->get_square();
}

int main()
{
    std::vector<Figure*> v;
    string str;
    while (getline(std::cin, str)) {
        v.push_back(Factory::factory_instance().make(str));
    }
    stable_sort(v.begin(), v.end(), comp);

    for (auto &x : v) {
        std::cout << x->to_string() << std::endl;
        delete x;
    }
}
