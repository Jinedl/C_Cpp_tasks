#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum { SIZE = 64 * (2 << 9), MULTIPLIER = 2, PAGE_OFFSET_BITS = 9, MASK = 0x1FF };

int
main(int argc, char *argv[])
{
    unsigned int begin_addr, addr, ph_addr;
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        exit(1);
    }
    struct stat stb;
    if (fstat(fd, &stb) < 0) {
        exit(1);
    }
    if (stb.st_size != SIZE) {
        exit(1);
    }
    sscanf(argv[2], "%x", &begin_addr);
    unsigned char *file;
    if ((file = mmap(NULL, stb.st_size, PROT_READ, MAP_SHARED, fd, 0)) < 0) {
        exit(1);
    }
    while (scanf("%x", &addr) > 0) {
        ph_addr = (*(unsigned short *) (file + begin_addr + MULTIPLIER * (addr >> PAGE_OFFSET_BITS))) | (addr & MASK);
        printf("%hu\n", *(unsigned short *) (file + ph_addr));
    }
    if (close(fd) < 0) {
        exit(1);
    }
}
