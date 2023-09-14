#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

enum { FILE_OFFSET = 2 };

int
prog(const char *name)
{
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (!pid) {
        char prog[PATH_MAX];
        FILE *fd = fopen(name, "r");
        if (fscanf(fd, "%4096s", prog) < 0) {
            _exit(1);
        }
        fclose(fd);
        execl(prog, prog, NULL);
        _exit(1);
    }
    return 0;
}

int
check_prog(void)
{
    int status;
    wait(&status);
    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int
main(int argc, char *argv[])
{
    int n, i;
    unsigned long long success = 0;

    errno = 0;
    char *eptr = NULL;
    long n_l = strtol(argv[1], &eptr, 10);
    if (errno || *eptr || eptr == argv[1] || n_l != (int) n_l) {
        exit(1);
    }

    n = (int) (n_l > argc - FILE_OFFSET ? argc - FILE_OFFSET : n_l);

    for (i = 0; i < n; i++) {
        if (prog(argv[i + FILE_OFFSET]) < 0) {
            exit(1);
        }
    }
    for (i = 0; i < n; i++) {
        success += check_prog();
    }

    for (i = n; i < argc; i++) {
        if (prog(argv[i + FILE_OFFSET]) < 0) {
            exit(1);
        }
        success += check_prog();
    }
    printf("%llu\n", success);
}
