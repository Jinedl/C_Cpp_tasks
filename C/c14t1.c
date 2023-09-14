#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

enum { PMEM_SIZE = sizeof(int *) * 2, MULTIPLIES = 4 };

void
work(int semid, int shmid, int *pmem, int self, int nproc, int maxval) {
    while (semop(semid, (struct sembuf[]) {{self - 1, -1, 0}}, 1) >= 0) {
        printf("%d %d %d\n", self, pmem[0], pmem[1]);
        fflush(stdout);

        pmem[0]++;
        pmem[1] = self;

        if (pmem[0] > maxval) {
            semctl(semid, 0, IPC_RMID);
            shmctl(shmid, IPC_RMID, NULL);
            break;
        }

        int val = 1;
        for (int i = 0; i < MULTIPLIES; i++){
            val *= pmem[0];
            val %= nproc;
        }

        semop(semid, (struct sembuf[]) {{val, 1, 0}}, 1);
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
    int nproc = (int) h;

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
    int maxval = (int) h;

    int semid = semget(key, nproc, 0600 | IPC_CREAT);

    int shmid = shmget(key, PMEM_SIZE, 0600 | IPC_CREAT);
    int *pmem = shmat(shmid, NULL, 0);
    pmem[0] = 0;//val
    pmem[1] = 0;//sender

    for (int i = 1; i <= nproc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (!pid) {
            work(semid, shmid, pmem, i, nproc, maxval);
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

}
