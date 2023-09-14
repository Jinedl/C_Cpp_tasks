#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

enum { MASK_BIG = 0xf, MASK_LITTLE = 0xff, BYTE = 8, HALF_BYTE = 4 };

int
main(int argc, char *argv[])
{
    char bytes[4];
    unsigned int value;
    int f = creat(argv[1], 0600);
    while (scanf("%u", &value) == 1) {
        bytes[3] = MASK_LITTLE & value;
        value >>= BYTE;
        bytes[2] = MASK_BIG & value;
        value >>= HALF_BYTE;
        bytes[1] = MASK_LITTLE & value;
        value >>= BYTE;
        bytes[0] = MASK_BIG & value;
        write(f, bytes, 4);
    }
    close(f);
}
