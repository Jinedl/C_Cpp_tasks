#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int
proc(void)
{
    int pid = fork();
    if (!pid) {
        write(1, "1\n", 2);
    }
    return pid;
}

int
main(void)
{
//    for (int i = 0; i < 3; i++) proc();
//    proc();
  //  proc();
   // proc();
/*pid_t pid;
    if ((pid = fork()) < 0) {
        exit(1);
    } else if (!pid) {
        proc();
    } else {
        proc();
    }*/
    proc(), proc(), proc();
    while (wait(NULL) > 0) {}
}
