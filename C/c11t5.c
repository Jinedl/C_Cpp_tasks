#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void
work(int number, int max, int out)
{
    while (1) {
        int cnt;
        if (scanf("%d", &cnt) != EOF) {
            if (cnt >= max) break;
            dprintf(out, "%d %d\n", number, cnt);
            if (cnt >= max - 1) break;
            printf("%d ", cnt + 1);
            fflush(stdout);
            if (cnt >= max - 2) break;
        } else {
            break;
        }
    }
}

int
main(int argc, char *argv[])
{
    errno = 0;
    char *eptr = NULL;
    long max_l = strtol(argv[1], &eptr, 10);
    if (errno || eptr == argv[1] || *eptr || max_l != (int) max_l) {
        exit(1);
    }
    int max = max_l;

    int pfd1[2];
    int pfd2[2];
    if (pipe(pfd1) < 0 || pipe(pfd2) < 0) {
        exit(1);
    }

    int out = dup(1);

    pid_t pid1 = fork();
    if (!pid1) {
        dup2(pfd1[0], 0);
        dup2(pfd2[1], 1);
        close(pfd1[0]);
        close(pfd1[1]);
        close(pfd2[0]);
        close(pfd2[1]);
        work(1, max, out);
        _exit(0);
    }

    pid_t pid2 = fork();
    if (!pid2) {
        dup2(pfd2[0], 0);
        dup2(pfd1[1], 1);
        close(pfd1[0]);
        close(pfd1[1]);
        close(pfd2[0]);
        close(pfd2[1]);
        work(2, max, out);
        _exit(0);
    }

    int cnt = 1;
    dprintf(pfd1[1], "%d ", cnt);

    close(pfd1[0]);
    close(pfd1[1]);
    close(pfd2[0]);
    close(pfd2[1]);

    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    if (!(WIFEXITED(status1) && !WIFSIGNALED(status1)) ||
        !(WIFEXITED(status2) && !WIFSIGNALED(status2))) {
        exit(1);
    }

    printf("Done\n");

    exit(0);
}
