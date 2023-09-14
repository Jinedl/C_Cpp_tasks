#include <limits.h>

enum { LAST_BIT = 1, BIT = 1, SIZE = sizeof(UTYPE) * CHAR_BIT };

STYPE
bit_reverse(STYPE value)
{
    UTYPE new_value = (UTYPE) value;
    UTYPE reverse_value = 0;
    int n = SIZE;
    for (int i = 0; i < n; i++) {
        reverse_value <<= BIT;
        reverse_value |= new_value & LAST_BIT;
        new_value >>= BIT;
    }
    return (STYPE) reverse_value;
}
