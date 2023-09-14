#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

extern char **environ;

const char FILE_RANDOM[] = "/dev/urandom";
const char LINE1[] = "#! /usr/bin/python3\n";
const char LINE2[] = "from functools import reduce; from operator import mul; import sys; import os;";
const char LINE2_CONTINUE[] = " print(reduce(mul, [int(x) for x in sys.argv if x.isdigit()])); os.unlink('";
const char LINE2_END[] = "')";

int
main(int argc, char *argv[])
{
    int fd;
    unsigned long long name_digit;
    char name[NAME_MAX];
    if ((fd = open(FILE_RANDOM, O_RDONLY)) < 0) {
        exit(1);
    }
    if (read(fd, &name_digit, sizeof(name_digit)) < 0) {
        exit(1);
    }
    if (snprintf(name, sizeof(name), "%llu.py", name_digit) >= sizeof(name)) {
        exit(1);
    }
    close(fd);
    char file[PATH_MAX];
    if (snprintf(file, sizeof(file), "%s/%s",
        getenv("XDG_RUNTIME_DIR") ? getenv("XDG_RUNTIME_DIR") : (getenv("TMPDIR") ? getenv("TMPDIR") : "/tmp"),
            name) >= sizeof(file)) {

        exit(1);
    }
    if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0700)) < 0) {
        exit(1);
    }
    int out = dup(1);
    dup2(fd, 1);
    if (printf(LINE1) < 0 ||
        printf(LINE2) < 0 ||
            printf(LINE2_CONTINUE) < 0 ||
                printf("%s", file) < 0 ||
                    printf(LINE2_END) < 0) {

        exit(1);
    }

    close(fd);

    fflush(stdout);
    dup2(out, 1);
    close(out);

    if (execve(file, argv, environ) < 0) {
        exit(1);
    }
}
