#include <stdio.h>

const char access_sample[] = "rwxrwxrwx";

enum { ACCESS_BIT = sizeof(access_sample) - 1, IS_BIT = 01 << (ACCESS_BIT - 1) };

int
main(int argc, char *argv[])
{
    int value, i, j;
    char access_ans[ACCESS_BIT + 1]; // "+ 1" for '\0'
    for (i = 01; i < argc; i++) {
        sscanf(argv[i], "%o", &value);
        for (j = 0; j < ACCESS_BIT; j++) {
            if (value & (IS_BIT >> j)) {
                access_ans[j] = access_sample[j];
            } else {
                access_ans[j] = '-';
            }
        }
        access_ans[j] = access_sample[j];
        printf("%s\n", access_ans);
    }
}
