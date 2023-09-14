#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int
main(void)
{
    setbuf(stdout, NULL);
    errno = 0;
    pid_t pid;
    int i, n;
    scanf("%d", &n);
    for (i = 1; i <= n - 1; i++) {
        printf("%d ", i);
        if ((pid = fork()) < 0) {
            exit(errno);
        } else if (!pid) {
            continue;
        } else {
            wait(NULL);
            exit(0);
        }
    }
    printf("%d\n", i);
    _exit(0);
}
