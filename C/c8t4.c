#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

enum { MAX_ARGS_BYTES = 64 };

int
main(int argc, char *argv[])
{
    char *eptr;
    errno = 0;
    long arg_l;
    int arg_i;
    double arg_d;
    typedef struct args {
        char mem[MAX_ARGS_BYTES];
    } args;
    args x;
    void *handle, *func;
    if (!(handle = dlopen(argv[1], RTLD_LAZY))) exit(1);
    if (!(func = dlsym(handle, argv[2]))) exit(1);

    int i = 1, j = 0;
    char c;
    while ((c = argv[3][i])) {
        if (c == 'v') {
            i++;
        } else if (c == 'i') {

            eptr = NULL;
            arg_l = strtol(argv[3 + i], &eptr, 10);
            arg_i = (int) arg_l;

            memcpy(x.mem + j, &arg_i, sizeof(int));
            j += sizeof(int);
            i++;
        } else if (c == 'd') {

            eptr = NULL;
            arg_d = strtod(argv[3 + i], &eptr);

            memcpy(x.mem + j, &arg_d, sizeof(double));
            j += sizeof(double);
            i++;
        } else if (c == 's') {
            memcpy(x.mem + j, &argv[3 + i], sizeof(char*));
            j += sizeof(char*);
            i++;
        }
    }

    c = argv[3][0];
    if (c == 'v') {
        ((void (*)(args)) func)(x);
    } else if (c == 'i') {
        int res_i = ((int (*)(args)) func)(x);
        printf("%d\n", res_i);
    } else if (c == 'd') {
        double res_d = ((double (*)(args)) func)(x);
        printf("%.10g\n", res_d);
    } else if (c == 's') {
        char *res_s = ((char* (*)(args)) func)(x);
        printf("%s\n", res_s);
    }
    dlclose(handle);
}
