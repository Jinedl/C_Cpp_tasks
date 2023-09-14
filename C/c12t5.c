#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum { SIG_MAX = 4 };

volatile __sig_atomic_t val = 0, count = 0;

void
handler(int s)
{
    if (s == SIGINT) {
        count++;
        if (count < SIG_MAX) {
            printf("%d\n", val);
            fflush(stdout);
        }
        else {
            exit(0);
        }
    }
    else if (s == SIGTERM) {
        exit(0);
    }
}

int
is_simple(int n)
{
    if (n <= 1) {
        return 0;
    }
    int i = 3;
    while (i <= n / i) {
        if (!(n % i)) {
            return 0;
        }
        i += 2;
    }
    return 1;
}

int main(void)
{
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGTERM, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);

    int low, high;
    if (scanf("%d%d", &low, &high) < 0) {
        exit(1);
    }
    int i = low % 2 ? low : low + 1;
    i = low == 2 ? low : i;
    val = 0;

    while (i < high) {
        val = is_simple(i) ? i : val;
        if (i == 1 || i == 2) {
            i++;
        } else {
            i += 2;
        }
    }
    printf("-1\n");
    fflush(stdout);
    exit(0);
}
