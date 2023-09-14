#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
    long long int neg = 0, pos = 0;
    for (long long int j = 1; j < argc; j++) {
        char *eptr = NULL;
        errno = 0;
        long lval = strtol(argv[j], &eptr, 10);
        if (errno || *eptr || eptr == argv[j] || (int) lval != lval) {
            exit(errno);
        }
        if (lval > 0) {
            pos += lval;
        } else {
            neg += lval;
        }
    }
    printf("%lld\n%lld\n", pos, neg);
}
