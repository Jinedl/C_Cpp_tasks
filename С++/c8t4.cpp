#include <cstdlib>

namespace Game
{
    template <typename T>
    class Coord
    {
    public:
        typedef T value_type;
        T row, col;
        Coord(T r = 0, T c = 0) : row(r), col(c) {}
    };
    template<typename T>
    T dist(Coord<T> &area, Coord<T> &g1, Coord<T> &g2)
    {
        int xd = abs(g1.col - g2.col);
        int extra  = !(g1.col % 2) - !(g2.col % 2);
        int yd = abs(2 * g1.row - 2 * g2.row + extra);
        extra = yd % 2;
        yd /= 2;
        double result;
        if (xd >= yd * 2 + extra) {
            result = xd;
        } else {
            result = xd * 2 + (yd * 2 + extra - xd);
            result /= 2;
        }
        return T(result);
    }
};
