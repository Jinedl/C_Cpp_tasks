#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

enum { SONS = 3, LEN = 8 };

int
main(void)
{
    errno = 0;
    char *eptr;
    pid_t pid;
    char str[LEN + 1];
    long lin;
    int i, in;
    for (i = 0; i < SONS; i++) {
        if ((pid = fork()) < 0) {
            exit(errno);
        } else if (!pid) {
            read(0, str, sizeof(str) - 1);
            str[LEN] = '\0';
            eptr = NULL;
            lin = strtol(str, &eptr, 10);
            if (errno || (int) lin != lin) {
                exit(1);
            }
            in = (int) lin;

            printf("%d %d\n", i + 1, in * in);
            exit(0);
        }
    }
    for (i = 0; i < SONS; i++) {
        wait(NULL);
    }
}
