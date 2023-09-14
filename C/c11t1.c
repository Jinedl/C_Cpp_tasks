#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <string.h>

int
main(void)
{
    int fd[2];
    pipe(fd);
    pid_t pid1 = fork();
    if (pid1 < 0) {
        _exit(1);
    }
    if (!pid1) {
        pid_t pid2 = fork();
        if (pid2 < 0) {
            _exit(1);
        }
        if (!pid2) {
            pid_t pid3 = fork();
            if (pid3 < 0) {
                _exit(1);
            }
            if (!pid3) {
                close(fd[0]);
                time_t curtime = time(NULL);
                write(fd[1], &curtime, sizeof(curtime));
                close(fd[1]);
                _exit(0);
            }
            int status;
            waitpid(pid2, &status, 0);
            if (WIFEXITED(status) && WIFSIGNALED(status)) {
                _exit(1);
            }

            time_t curtime;
            read(fd[0], &curtime, sizeof(curtime));
            struct tm *tm = localtime(&curtime);
            printf("D:%d\n", tm->tm_mday);
            fflush(stdout);
            write(fd[1], &curtime, sizeof(curtime));
            close(fd[1]);
            close(fd[0]);
            _exit(0);
        }
        int status;
        waitpid(pid2, &status, 0);
        if (WIFEXITED(status) && WIFSIGNALED(status)) {
            _exit(1);
        }
        time_t curtime;
        read(fd[0], &curtime, sizeof(curtime));
        struct tm *tm = localtime(&curtime);
        printf("M:%d\n", tm->tm_mon + 1);
        fflush(stdout);
        write(fd[1], &curtime, sizeof(curtime));
        close(fd[1]);
        close(fd[0]);
        _exit(0);
    }

    close(fd[1]);
    int status;
    waitpid(pid1, &status, 0);
    if (WIFEXITED(status) && WIFSIGNALED(status)) {
        _exit(1);
    }
    time_t curtime;
    read(fd[0], &curtime, sizeof(curtime));
    struct tm *tm = localtime(&curtime);
    printf("Y:%d\n", tm->tm_year + 1900);
    fflush(stdout);
    close(fd[1]);
    close(fd[0]);
}
