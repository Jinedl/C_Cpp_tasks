#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
int
main(void)
{
    errno = 0;
    pid_t pid1, pid2;
    if ((pid1 = fork()) < 0) {
        exit(errno);
    } else if (!pid1) {
        if ((pid2 = fork()) < 0) {
            exit(errno);
        } else if (!pid2) {
            printf("3 ");
        } else {
            wait(NULL);
            printf("2 ");
        }
    } else {
        wait(NULL);
        printf("1\n");
    }
}
