#include <inttypes.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

enum { MSG_SIZE = sizeof(int64_t) * 2 };

typedef struct MsgBuf
{
    int msgtype;
    int64_t msgtext[2];
} MsgBuf;

void
work(int msgid, int self, int nproc, int64_t maxval) {
    MsgBuf msg;
    while (msgrcv(msgid, &msg, MSG_SIZE, self + 1, 0) >= 0) {
        uint64_t x3 = msg.msgtext[0] + msg.msgtext[1];
        printf("%d %" PRIu64 "\n", self, x3);
        fflush(stdout);

        if (x3 > maxval) {
            msgctl(msgid, IPC_RMID, NULL);
            break;
        }

        msg.msgtype = x3 % nproc + 1;
        msg.msgtext[0] = msg.msgtext[1];
        msg.msgtext[1] = (int64_t) x3;
        msgsnd(msgid, &msg, MSG_SIZE, 0);
    }
}

int
main(int argc, char *argv[])
{
    setbuf(stdin, NULL);

    errno = 0;
    long h;
    int64_t hll;
    char *eptr;

    eptr = NULL;
    h = strtol(argv[1], &eptr, 10);
    if (errno || *eptr || eptr == argv[1] || (int) h != h) {
        exit(1);
    }
    int key = (int) h;

    eptr = NULL;
    h = strtol(argv[2], &eptr, 10);
    if (errno || *eptr || eptr == argv[2] || (int) h != h) {
        exit(1);
    }
    int nproc = (int) h;

    eptr = NULL;
    hll = strtoll(argv[3], &eptr, 10);
    if (errno || *eptr || eptr == argv[3]) {
        exit(1);
    }
    int64_t value1 = hll;

    eptr = NULL;
    hll = strtoll(argv[4], &eptr, 10);
    if (errno || *eptr || eptr == argv[4]) {
        exit(1);
    }
    int64_t value2 = hll;

    eptr = NULL;
    hll = strtoll(argv[5], &eptr, 10);
    if (errno || *eptr || eptr == argv[5] || (int) h != h) {
        exit(1);
    }
    int64_t maxval = llabs(hll);

    int msgid = msgget(key, 0600 | IPC_CREAT);

    int fork_fail = 0;
    for (int i = 0; i < nproc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            fork_fail = 1;
            msgctl(msgid, IPC_RMID, NULL);
        } else if (!pid) {
            work(msgid, i, nproc, maxval);
            _exit(0);
        }
    }
    msgsnd(msgid, &(MsgBuf) {1, {value1, value2}}, MSG_SIZE, 0);

    int status;
    while(wait(&status) > 0) {
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            exit(1);
        }
    }
    exit(fork_fail);
}
