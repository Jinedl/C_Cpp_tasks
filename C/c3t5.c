#include <stdio.h>
#include <limits.h>
#include <string.h>

enum { DIGITS_COUNT = 10 };

void
digits_count(char *name)
{
    unsigned long long digits[DIGITS_COUNT];
    memset(digits, 0, DIGITS_COUNT * sizeof(*digits));
    int number;
    FILE *f = fopen(name, "r");
    while (f && !feof(f)) {
        number = getc_unlocked(f) - '0';
        if (0 <= number && number <= 9) digits[number]++;
    }
    if (f) fclose(f);
    for (int i = 0; i < DIGITS_COUNT; i++) {
        printf("%d %llu\n", i, digits[i]);
    }
}

int
main(void)
{
    char name[PATH_MAX];
    int j = 0;
    int ch = 0;
    while((ch = getchar_unlocked()) >= 0 && ch != '\n' && ch != '\r' && ch != '\0' && ch != EOF && PATH_MAX - j - 1){
        name[j++] = (char) ch;
    }
    name[j] = '\0';
    digits_count(name);
}
