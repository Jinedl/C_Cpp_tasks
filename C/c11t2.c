#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int
main(void)
{
    int fd[2];
    if (pipe(fd) < 0) {;
        exit(1);
    }
    pid_t pid1 = fork();
    if (pid1 < 0) {
        exit(1);
    } else if (!pid1) {
        close(fd[1]);
        pid_t pid2 = fork();
        if (pid2 < 0) {
            _exit(1);
        } else if (!pid2) {
            int val;
            long long int sum = 0;
            while (read(fd[0], &val, sizeof(val)) > 0) {
                sum += val;
            }
            close(fd[0]);
            printf("%lld\n", sum);
            fflush(stdout);
            _exit(0);
        } else {
            int status2;
            close(fd[0]);
            waitpid(pid2, &status2, 0);
            _exit(!(WIFEXITED(status2) && !WIFSIGNALED(status2)));
        }
    }
    close(fd[0]);
    int val;
    while (scanf("%d", &val) > 0) {
        if (write(fd[1], &val, sizeof(val)) < 0) {
            exit(1);
        }
    }
    close(fd[1]);
    int status1;
    waitpid(pid1, &status1, 0);
    exit(!(WIFEXITED(status1) && !WIFSIGNALED(status1)));
}
