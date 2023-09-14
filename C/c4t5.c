#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int f;
    if ((f = open(argv[1], O_RDWR)) == -1) {
        exit(errno);
    }
    long long value;
    long long min = LLONG_MAX;
    long long pos = 0;
    long long min_pos = 0;
    int err;
    while ((err = read(f, &value, sizeof(value))) > 0) {
        if (err != sizeof(value)) {
            exit(errno);
        }
        if (value < min) {
            min_pos = pos;
            min = value;
        }
        pos += sizeof(value);
    }
    if (pos) {
        if (min != LLONG_MIN) {
            min = -min;
        }
        if (lseek(f, min_pos, 0) == -1) {
            exit(errno);
        }
        if (write(f, &min, sizeof(min)) != sizeof(min)) {
            exit(errno);
        }
    }
    close(f);
}
