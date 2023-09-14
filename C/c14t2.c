#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

enum { MAX_VAL = 10 };

/*
void
operation(int *data, int ind1, int ind2, int value)
{
    if (ind1 != ind2) {
        int tmp1 = data[ind1] - value;
        int tmp2 = data[ind2] + value;

        data[ind1] = tmp1;
        data[ind2] = tmp2;
    }
}
*/

int
new_rand(int max)
{
    double n = rand() / ((double) RAND_MAX + 1);
    return (int) (max * n);
}

void
work(int semid, int *pmem, int count, int iter_count) {
    for (int i = 0; i < iter_count; i++) {
        int ind1 = new_rand(count);
        int ind2 = new_rand(count);
        int val = new_rand(MAX_VAL);
        if (ind1 == ind2) {
            continue;
        }
        semop(semid, (struct sembuf[]) {{ind1, -1, 0}, {ind2, -1, 0}}, 2);
        operation(pmem, ind1, ind2, val);
        semop(semid, (struct sembuf[]) {{ind1, 1, 0}, {ind2, 1, 0}}, 2);
    }
}

int
main(int argc, char *argv[])
{
    errno = 0;
    long h;
    char *eptr;

    eptr = NULL;
    h = strtol(argv[1], &eptr, 10);
    if (errno || *eptr || eptr == argv[1] || (int) h != h) {
        exit(1);
    }
    int count = (int) h;

    eptr = NULL;
    h = strtol(argv[2], &eptr, 10);
    if (errno || *eptr || eptr == argv[2] || (int) h != h) {
        exit(1);
    }
    int key = (int) h;

    eptr = NULL;
    h = strtol(argv[3], &eptr, 10);
    if (errno || *eptr || eptr == argv[3] || (int) h != h) {
        exit(1);
    }
    int nproc = (int) h;

    eptr = NULL;
    h = strtol(argv[4], &eptr, 10);
    if (errno || *eptr || eptr == argv[4] || (int) h != h) {
        exit(1);
    }
    int iter_count = (int) h;

    int i;

    int semid = semget(key, count, 0600 | IPC_CREAT);

    int shmid = shmget(key, sizeof(int) * count, 0600 | IPC_CREAT);
    int *pmem = shmat(shmid, NULL, 0);
    for (i = 0; i < count; i++) {
        scanf("%d", &pmem[i]);
        semop(semid, (struct sembuf[]) {{ i, 1, 0 }}, 1);
    }

    for (i = 0; i < nproc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (!pid) {

            eptr = NULL;
            h = strtol(argv[5 + i], &eptr, 10);
            if (errno || *eptr || eptr == argv[5 + i] || (int) h != h) {
                _exit(1);
            }
            int seed = (int) h;
            srand(seed);

            work(semid, pmem, count, iter_count);
            _exit(0);
        }
    }

    int status;
    while(wait(&status) > 0) {
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            exit(1);
        }
    }

    for (i = 0; i < count; i++) {
        printf("%d\n", pmem[i]);
    }
    shmdt(pmem);
    semctl(semid, 0, IPC_RMID);
    shmctl(shmid, IPC_RMID, NULL);
}
