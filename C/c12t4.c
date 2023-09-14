#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

volatile sig_atomic_t flag = 0;
void handler(int s)
{
    flag = 1;
}

void
work(int number, int max, int out)
{
    sigset_t s;
    sigemptyset(&s);
    while (1) {
        while (!flag) {
            sigsuspend(&s);
        }
        flag = 0;
        pid_t pid;
        int v;
        if (scanf("%d%d", &pid, &v) < 0) {
            break;
        }
        if (v >= max) {
            break;
        }
        dprintf(out, "%d %d\n", number, v);
        v++;
        printf("%d %d\n", getpid(), v);
        fflush(stdout);
        kill(pid, SIGUSR1);
        if (v >= max) {
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

    int pfd[2];
    if (pipe(pfd) < 0) {
        exit(1);
    }

    int out = dup(1);

    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s, NULL);

    sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);

    pid_t pid1 = fork();
    if (!pid1) {
        dup2(pfd[0], 0);
        dup2(pfd[1], 1);
        close(pfd[0]);
        close(pfd[1]);
        work(1, max, out);
        _exit(0);
    }

    pid_t pid2 = fork();
    if (!pid2) {
        dup2(pfd[0], 0);
        dup2(pfd[1], 1);
        close(pfd[0]);
        close(pfd[1]);
        int v = 1;
        printf("%d %d\n", getpid(), v);
        fflush(stdout);
        kill(pid1, SIGUSR1);
        if (v >= max) {
            _exit(0);
        }
        work(2, max, out);
        _exit(0);
    }

    close(pfd[0]);
    close(pfd[1]);

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
