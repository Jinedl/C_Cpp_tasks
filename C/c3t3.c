#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

const double TO_PERCENT = 100, FOR_FOUR_DIGITS_ROUND = 10000;

int
main(int argc, char *argv[]) {
    errno = 0;
    char *eptr = NULL;
    double percent;
    double cash = strtod(argv[1], &eptr);
    if (errno || *eptr || eptr == argv[1]) {
        exit(errno);
    }
    for (int i = 2; i < argc; i++) {
        percent = strtod(argv[i], &eptr);
        if (errno || *eptr || eptr == argv[i]) {
            exit(errno);
        }
        percent = FOR_FOUR_DIGITS_ROUND +  percent * (FOR_FOUR_DIGITS_ROUND / TO_PERCENT);/* <=>
        <=> percent = (1 + percent / TO_PERCENT) * FOR_FOUR_DIGITS_ROUND */
        cash *= percent;
        cash = round(cash) / FOR_FOUR_DIGITS_ROUND;
    }
    printf("%.4f\n", cash);
}
