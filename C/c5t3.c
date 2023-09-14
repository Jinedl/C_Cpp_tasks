#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

enum { BYTE = 8 };

int32_t
dec_to_sm(uint32_t value, uint32_t digit)
{
    if (digit == 1) return 0;
    uint32_t sign = value & (1u << (digit - 1u));
    return ((value << (sizeof(value) * BYTE - digit + 1u)) >>
        (sizeof(value) * BYTE - digit + 1u)) * (sign ? -1 : 1);
}

int
main(void)
{
    uint32_t n, s, w, i;
    int32_t sm;
    scanf("%"PRIu32"%"PRIu32"%"PRIu32, &n, &s, &w);
    uint32_t limit = (n == 32 ? ~(0u) - s + 1u : (1u << n) - s);
    i = 0;
    for (i = 0; i < limit; i += s) {
        sm = dec_to_sm(i, n);
        printf("|%*"PRIo32"|%*"PRIu32"|%*"PRId32"|\n",
            (int)w, i, (int)w, i, (int)w, sm);
    }
    sm = dec_to_sm(i, n);
    printf("|%*"PRIo32"|%*"PRIu32"|%*"PRId32"|\n",
        (int)w, i, (int)w, i, (int)w, sm);
    return 0;
}
