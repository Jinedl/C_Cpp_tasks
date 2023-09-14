#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

void
matrice(int *file, int rows, int cols)
{
    int max = rows * cols;
    int i = 0, j = 0;
    int value = 1;
    while (1) {
        while (j < cols && !file[i * cols + j]) {
            file[i * cols + j] = value++;
            j++;
        }
        j--;
        i++;
        if (value - 1 == max) {
            break;
        }
        while (i < rows && !file[i * cols + j]) {
            file[i * cols + j] = value++;
            i++;
        }
        i--;
        j--;
        if (value - 1 == max) {
            break;
        }
        while (j >= 0 && !file[i * cols + j]) {
            file[i * cols + j] = value++;
            j--;
        }
        j++;
        i--;
        if (value - 1 ==  max) {
            break;
        }
        while (i >= 0 && !file[i * cols + j]) {
            file[i * cols + j] = value++;
            i--;
        }
        i++;
        j++;
        if (value - 1 == max) {
            break;
        }
    }
}

int
main(int argc, char *argv[])
{
    char *eptr;

    eptr = NULL;
    errno = 0;
    long rows = strtol(argv[2], &eptr, 10);
    if (errno || *eptr || eptr == argv[2] || (int) rows != rows) {
        exit(errno);
    }

    eptr = NULL;
    errno = 0;
    long cols = strtol(argv[3], &eptr, 10);
    if (errno || *eptr || eptr == argv[3] || (int) cols != cols) {
        exit(errno);
    }

    int test;
    if (__builtin_mul_overflow(rows, cols, &test)) {
        exit(1);
    }

    int fd;
    if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC,
        S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {

        exit(1);
    }

    if (__builtin_mul_overflow(rows * cols, sizeof(int), &test)) {
        exit(1);
    }

    if (ftruncate(fd, rows * cols * sizeof(int)) < 0) {
        exit(1);
    }

    struct stat stb;
    if (fstat(fd, &stb) < 0) {
        exit(1);
    }

    int *file;
    if ((file = mmap(NULL, stb.st_size, PROT_WRITE, MAP_SHARED, fd, 0)) < 0) {
        exit(1);
    }
    matrice(file, rows, cols);
    close(fd);
}
