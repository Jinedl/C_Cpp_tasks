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
work(int semid, unsigned self, unsigned health) {
    while (semop(semid, (struct sembuf[]) {{self + 1, -1, 0}}, 1) >= 0) {

        health--;

        printf("%u %u\n", self, health);
        fflush(stdout);

        semop(semid, (struct sembuf[]) {{0, 1, 0}}, 1);
        if (!health) {
            break;
        }
    }
}

int
main(int argc, char *argv[])
{
    setbuf(stdin, NULL);

    errno = 0;
    char *eptr = NULL;
    unsigned long h = strtoul(argv[1], &eptr, 10);
    if (errno || *eptr || eptr == argv[1] || (unsigned) h != h) {
        exit(1);
    }
    unsigned n = (unsigned) h;

    eptr = NULL;
    h = strtoul(argv[2], &eptr, 10);
    if (errno || *eptr || eptr == argv[2] || (unsigned) h != h) {
        exit(1);
    }
    unsigned health = (unsigned) h;

    unsigned healths[n];
    for (int j = 0; j < n; j++) {
        healths[j] = health;
    }

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

    int semid = semget(key, n + 1, 0600 | IPC_CREAT);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (!pid) {
            work(semid, i, health);
            _exit(0);
        }
    }

    unsigned shoot;
    while (scanf("%u", &shoot) > 0) {
        if (healths[shoot % n]) {
            healths[shoot % n]--;
            semop(semid, (struct sembuf[]) {{shoot % n + 1, 1, 0}}, 1);
            semop(semid, (struct sembuf[]) {{0, -1, 0}}, 1);
        }
    }

    unsigned alive = 0;
    for (int k = 0; k < n; k++) {
        if (healths[k]) {
            alive++;
        }
    }
    printf("%u\n", alive);
    fflush(stdout);

    semctl(semid, 0, IPC_RMID);

    int status;
    while (wait(&status) > 0) {
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            exit(1);
        }
    }

    if (remove(file) < 0) {
        exit(1);
    }
}
