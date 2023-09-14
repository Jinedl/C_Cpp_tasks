#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int
mysys(const char *str)
{
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        int out = 0;
        waitpid(pid, &out, 0);
        if (WIFSIGNALED(out)) {
            return WTERMSIG(out) + 128;
        } else {
            return WEXITSTATUS(out);
        }
    }
}
