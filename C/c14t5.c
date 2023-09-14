#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void
work(FILE *pfdr1, FILE *pfdr2, FILE *pfdw)
{
    int n1, n2;
    if (fscanf(pfdr1, "%d", &n1) < 0) {
        return;
    }
    if (fscanf(pfdr2, "%d", &n2) < 0) {
        return;
    }

    while (1) {
        if (n1 == n2) {
            fprintf(pfdw, "%d\n", n1);
            fflush(pfdw);
            if (fscanf(pfdr1, "%d", &n1) < 0) {
                break;
            }
            if (fscanf(pfdr2, "%d", &n2) < 0) {
                break;
            }
        } else if (n1 > n2) {
            if (fscanf(pfdr2, "%d", &n2) < 0) {
                break;
            }
        } else if (n1 < n2) {
            if (fscanf(pfdr1, "%d", &n1) < 0) {
                break;
            }
        }
    }
    return;
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        exit(0);
    }

    FILE *fd_file1 = fopen(argv[1], "r");

    if (argc > 2) {

        for (int i = 0; i < argc - 2; i++) {
            int pfd[2];
            if (pipe(pfd) < 0) {
                exit(1);
            }
            FILE *pfdr = fdopen(pfd[0], "r");
            FILE *pfdw = fdopen(pfd[1], "w");

            pid_t pid = fork();
            if (pid < 0) {

                exit(1);

            } else if (!pid) {

                fclose(pfdr);

                FILE *fd_file2 = fopen(argv[2 + i], "r");

                work(fd_file1, fd_file2, pfdw);
                fclose(fd_file1);
                fclose(fd_file2);
                fclose(pfdw);

                _exit(0);
            }
            fclose(fd_file1);
            fclose(pfdw);

            fd_file1 = pfdr;
        }

    }

    int status;
    while(wait(&status) > 0) {
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            exit(1);
        }
    }

    int n;
    while (fscanf(fd_file1, "%d", &n) > 0) {
        printf("%d ", n);
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);

    fclose(fd_file1);
}
