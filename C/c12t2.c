#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum { ADD = 1, MULTIPLY = 2 };

volatile sig_atomic_t flag = ADD;
void handlerI(int s)
{
    flag = ADD;
}

void handlerQ(int s)
{
    flag = MULTIPLY;
}

int main(void)
{
    sigaction(SIGQUIT, &(struct sigaction) { .sa_handler = handlerQ, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handlerI, .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);

    int n;
    unsigned sum = 0;

    while (1) {
        if (scanf("%d", &n) > 0) {
            if (flag == ADD) {
                sum += (unsigned) n;
            } else if (flag == MULTIPLY) {
                sum *= (unsigned) n;
            }
            printf("%d\n", sum);
            fflush(stdout);
        } else {
            exit(0);
        }
    }
}

