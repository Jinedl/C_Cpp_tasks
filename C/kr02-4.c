#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

enum { APPEND = 1, READ = 2 };

int
sys(const char *prog, char *fdname)
{

    pid_t pid = fork();
    if (pid < 0) {

        return 0;

    } else if (!pid) {

        int fdw;
        if ((fdw = open(fdname, O_WRONLY | O_TRUNC, 0660)) < 0) {
            _exit(1);
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


    pid_t pid = fork();
    if (pid < 0) {

        exit(1);

    } else if (!pid) {

        sys(argv[1], argv[2]);
        _exit(0);

    }


    int status;
    waitpid(pid, &status, 0);
    exit(!(WIFEXITED(status) && !WEXITSTATUS(status)));
}
