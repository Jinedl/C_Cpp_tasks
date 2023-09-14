#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

const char FILE_RANDOM[] = "/dev/urandom";

void
work(int semid, int self, int nproc) {
    while (semop(semid, (struct sembuf[]) {{self, -1, 0}}, 1) >= 0) {

        int val;
        if (scanf("%d", &val) < 0) {
            semctl(semid, 0, IPC_RMID);
            break;
        }

        printf("%d %d\n", self, val);
        fflush(stdout);

        semop(semid, (struct sembuf[]) {{(nproc + (val % nproc)) % nproc, 1, 0}}, 1);
    }
}

int
main(int argc, char *argv[])
{
    setbuf(stdin, NULL);

    errno = 0;
    char *eptr = NULL;
    long h = strtol(argv[1], &eptr, 10);
    if (errno || *eptr || eptr == argv[1] || (int) h != h) {
        exit(1);
    }
    int count = (int) h;

    int fd;
    if ((fd = open(FILE_RANDOM, O_RDONLY)) < 0) {
        exit(1);
    }
    unsigned long long name_digit;
    if (read(fd, &name_digit, sizeof(name_digit)) < 0) {
        exit(1);
    }
    close(fd);

    char file[NAME_MAX];
    if (snprintf(file, sizeof(file), "/tmp/%llu", name_digit) >= sizeof(file)) {
        exit(1);
    }
    fd = creat(file, 0);
    close(fd);

    key_t key;
    if ((key = ftok(file, rand())) < 0) {
        exit(1);
    }

    int semid = semget(key, count, 0600 | IPC_CREAT);

    for (int i = 0; i < count; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (!pid) {
            work(semid, i, count);
            _exit(0);
        }
    }
    semop(semid, (struct sembuf[]) {{0, 1, 0}}, 1);

    int status;
    while(wait(&status) > 0) {
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            exit(1);
        }
    }

    if (remove(file) < 0) {
        exit(1);
    }

}
