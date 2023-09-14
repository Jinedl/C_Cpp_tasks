#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

enum { APPEND = 1, READ = 2 };

int
sys(const char *prog, int fdr, int fdw, char *fdname, int type)
{

    pid_t pid = fork();
    if (pid < 0) {

        return 0;

    } else if (!pid) {

        if (type == APPEND) {
            if ((fdw = open(fdname, O_WRONLY | O_CREAT | O_APPEND, 0660)) < 0) {
                _exit(1);
            }
        } else if (type == READ) {
            if ((fdr = open(fdname, O_RDONLY)) < 0) {
                _exit(1);
            }
        }

        if (fdr) {
            dup2(fdr, 0);
            close(fdr);
        }

        dup2(fdw, 1);
        close(fdw);

        execlp(prog, prog, NULL);
        _exit(1);
    }

    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int
main(int argc, char *argv[])
{

    int pfd[2];
    if (pipe(pfd) < 0) {
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {

        exit(1);

    } else if (!pid) {

        close(pfd[0]);
        if (sys(argv[1], 0, pfd[1], argv[4], READ)) {
            sys(argv[2], 0, pfd[1], NULL, 0);
        }
        close(pfd[1]);
        _exit(0);

    }

    close(pfd[1]);
    sys(argv[3], pfd[0], 0, argv[5], APPEND);
    close(pfd[0]);

    int status;
    waitpid(pid, &status, 0);
    exit(!(WIFEXITED(status) && !WEXITSTATUS(status)));
}
