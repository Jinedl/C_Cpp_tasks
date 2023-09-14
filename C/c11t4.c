#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void
delete_proc(pid_t *success_pid, int i)
{
    for(int j = 0; j < i; j++) {
        kill(success_pid[j], SIGKILL);
    }
    free(success_pid);
    while(wait(NULL) > 0) {}
}

int
main(int argc, char *argv[])
{
    pid_t *success_pid = calloc(argc - 1, sizeof(pid_t));
    int pfdr;
    pid_t pid;
    int i;
    for (i = 0; i < argc - 1; i++) {
        int pfd[2];
        if (i != argc - 2) {
            if (pipe(pfd) < 0) {
                delete_proc(success_pid, i);
                exit(1);
            }
        }
        pid = fork();

        if (pid < 0) {
            delete_proc(success_pid, i);
            exit(1);
        } else if (!pid) {
            if (i != 0) {
                dup2(pfdr, 0);
                close(pfdr);
            }
            pfdr = pfd[0];
            if (i != argc - 2) {
                close(pfd[0]);
                dup2(pfd[1], 1);
                close(pfd[1]);
            }
            execlp(argv[i + 1], argv[i + 1], NULL);
            _exit(1);
        }
        success_pid[i] = pid;
        if (i != 0) {
            close(pfdr);
        }
        pfdr = pfd[0];
        if (i != argc - 2) {
            close(pfd[1]);
        }
    }
    while (wait(NULL) > 0) {}
    free(success_pid);
    exit(0);
}
