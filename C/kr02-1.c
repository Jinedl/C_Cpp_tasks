#include <stdio.h>

int
main(void)
{
    unsigned mas[256], n, max = 0;
    int len = 0;
    while (scanf("%u", &n) > 0) {
        mas[len] = n;
        max = mas[len] > max ? mas[len] : max;
        len++;
    }
    if (!max) {
        return 0;
    }
    for (int i = len - 1; i >= 0; i--) {
        if (mas[i] && max % mas[i] == 0) {
            printf("%u\n", mas[i]);
        }
    }
    return 0;
}
