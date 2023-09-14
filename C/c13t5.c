#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signalfd.h>
#include <limits.h>

volatile sig_atomic_t flag = 0;
void handler(int s)
{
    flag = 1;
}

int
main(int argc, char *argv[])
{
    int pid1 = fork();
    if (pid1 < 0) {
        exit(1);
    } else if (!pid1) {

        sigset_t ss;
        sigemptyset(&ss);
        sigaddset(&ss, SIGUSR1);
        sigaddset(&ss, SIGUSR2);
        sigaddset(&ss, SIGIO);
        sigprocmask(SIG_BLOCK, &ss, NULL);
        int sfd = signalfd(-1, &ss, 0);

        char bit = 0, byte = 0;
        int num_bit = 0;

        while (1) {

            struct signalfd_siginfo sinfo;
            read(sfd, &sinfo, sizeof(sinfo));

            if (sinfo.ssi_signo == SIGIO) {
                if (num_bit) {
                    printf("%c", byte);
                    fflush(stdout);
                }
                break;
            } else if (sinfo.ssi_signo == SIGUSR1) {
                bit = 0;
            } else if (sinfo.ssi_signo == SIGUSR2) {
                bit = 1;
            }
            byte |= (bit << num_bit);
            num_bit++;

            if (num_bit == CHAR_BIT) {
                printf("%c", byte);
                fflush(stdout);
                byte = 0;
                num_bit = 0;
            }

            kill(sinfo.ssi_pid, SIGALRM);
        }
        close(sfd);
        _exit(0);
    }

    int pid2 = fork();
    if (pid2 < 0) {
        exit(1);
    } else if (!pid2) {

        sigset_t ss, s;
        sigemptyset(&ss);
        sigaddset(&ss, SIGALRM);
        sigprocmask(SIG_BLOCK, &ss, NULL);
        sigemptyset(&s);
        sigaction(SIGALRM, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);

        int fd = open(argv[1], O_RDONLY);
        char byte;
        int num_bit = CHAR_BIT;

        while (1) {

            if (num_bit == CHAR_BIT) {
                if (read(fd, &byte, sizeof(byte)) == 0) {
                    kill(pid1, SIGIO);
                    break;
                }
                num_bit = 0;
            }
            if ((byte >> num_bit) & 1) {
                kill(pid1, SIGUSR2);
            } else {
                kill(pid1, SIGUSR1);
            }

            num_bit++;

            flag = 0;
            while (!flag) {
                sigsuspend(&s);
            }
        }

        close(fd);
        _exit(0);
    }

    while (wait(NULL) > 0) {}
}
