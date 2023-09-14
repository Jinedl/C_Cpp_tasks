#include <stdio.h>  
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    int f = open(argv[1], O_RDWR);
    unsigned char bytes[2];
    unsigned short value;
    unsigned short min = USHRT_MAX;
    while ((read(f, bytes, sizeof(bytes))) > 0) {
        value = (bytes[0] << 8) | bytes[1];
        if (!(value % 2) && value < min) {
            min = value;
        }
    }
    if (!(min % 2)) printf("%hu\n", min);
    close(f);
}
