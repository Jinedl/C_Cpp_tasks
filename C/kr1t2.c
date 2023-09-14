#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int
main(int argc, char *argv[])
{

    int flag = 0;
    long long nll;
    int ni, len;
    int ans = 0;
    
    for (int i = 1; i < argc; i++) {
        nll = atoll(argv[i]);
        len = strlen(argv[i]);

        if ((nll <= INT_MAX && nll >= INT_MIN) &&
            len >= 2 && (argv[i][0] == '+' || argv[i][0] == '-' || (argv[i][0] - '0' >= 0 && 
            argv[i][0] - '0' <= 9)) &&
                (argv[i][len - 1] == '+' || argv[i][len - 1] == '-') &&
                    (argv[i][len - 2] == 'k' || (argv[i][len - 2] - '0' >= 0 &&
                        argv[i][len - 2] - '0' <= 9))) {
            for (int j = 1; j < len - 2; j++) {
                if (!(argv[i][j] - '0' >= 0 && argv[i][j] - '0' <= 9)) {
                    flag = 1;
                    break;
                }
            }
        } else {
            continue;
        }
        if (flag) {
            continue;
        }
        ni = nll;
        if (argv[i][len - 2] == 'k') ni *= 1000;
        if (argv[i][len - 1] == '-') ni *= -1;

        ans += ni;
    }
    printf("%d\n", ans);
}
