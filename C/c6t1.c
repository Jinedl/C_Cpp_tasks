#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

enum { MS = 1000000 };

int main(int argc, char *argv[])
{
    char *eptr;
    errno = 0;
    struct timeval tv;

    eptr = NULL;
    tv.tv_sec = strtol(argv[1], &eptr, 10);
    if (errno || *eptr || eptr == argv[1]) {
        exit(errno);
    }
    eptr = NULL;
    tv.tv_usec = strtol(argv[2], &eptr, 10);
    if (errno || *eptr || eptr == argv[2]) {
        exit(errno);
    }

    double U;

    eptr = NULL;
    double lambda = strtod(argv[3], &eptr);
    if (errno || *eptr || eptr == argv[3]) {
        exit(errno);
    }

    eptr = NULL;
    long K = strtol(argv[4], &eptr, 10);
    if (errno || *eptr || eptr == argv[4]) {
        exit(errno);
    }

    eptr = NULL;
    unsigned long S = (unsigned long) strtol(argv[5], &eptr, 10);
    if (errno || *eptr || eptr == argv[5]) {
        exit(errno);
    }

    srand(S);

    for (int i = 0; i < K; i++) {
        U = (double) rand() / RAND_MAX;
        tv.tv_usec += (long) (-log(U) / lambda);
        tv.tv_sec += tv.tv_usec / MS;
        tv.tv_usec %= MS;
        printf("%ld %ld\n", tv.tv_sec, tv.tv_usec);
    }
}
