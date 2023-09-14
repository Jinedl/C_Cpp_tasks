int
satsum(int v1, int v2)
{
    if (v1 > 0 && v2 > 0 && v1 + v2 <= 0) {
        return (~0) >> ((~0) * (~0));
    } else if (v1 < 0 && v2 < 0 && v1 + v2 >= 0) {
        return ~((~0) >> ((~0) * (~0)));
    } else {
        return v1 + v2;
    }
}
