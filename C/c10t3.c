#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int
mysys(const char *str)
{
    pid_t pid = fork();
    if (pid < 0) {
        return 0;
    } else if (!pid) {
        if (execlp(str, str, NULL) < 0) {
            _exit(1);
        }
    }
    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int
main(int argc, char *argv[])
{
    return !((mysys(argv[1]) || mysys(argv[2])) && mysys(argv[3]));
}
