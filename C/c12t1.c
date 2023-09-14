#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t count = 0;
void handler(int s)
{
    printf("%d\n", count);
    fflush(stdout);
    count++;
}

int main(void)
{
    sigaction(SIGHUP, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);

    while (count < 5) {
        pause();
    }
    exit(0);
}
