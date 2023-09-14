#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int
main(void)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    pid_t pid;
    int n;
    int flag = 0;
    int status;
    while (1) {
        if ((pid = fork()) < 0) {
            printf("-1\n");
            exit(errno);
        } else if (!pid) {
            if (scanf("%d", &n) == EOF) {
                exit(0);
            } else {
                flag = 1;
            }
        } else {
            wait(&status);
            if (!WEXITSTATUS(status) && flag) printf("%d\n", n);
            if (flag) {
                exit(WEXITSTATUS(status));
            } else {
                exit(0);
            }
        }
    }
}
