#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{

    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (!pid) {
        int fd = open(argv[2], O_RDONLY | O_CLOEXEC);
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 0) < 0) {
            _exit(42);
        }

        fd = open(argv[3], O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0660);
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 1)< 0) {
            _exit(42);
        }

        fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0660);
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 2) < 0) {
            _exit(42);
        }

        if (execlp(argv[1], argv[1], NULL) < 0) {
            _exit(42);
        }

        _exit(0);
    }
    int out;
    wait(&out);
    printf("%d\n", out);
    exit(0);
}
