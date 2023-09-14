#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

enum { SICKLE = 29, GALLEON = 17 };
enum { INT = 4 };
enum { SEEK_RECORD = 20, SEEK_NAME = 16 };
enum { FST_BYTE = 0, SND_BYTE = 1, TRD_BYTE = 2, FTH_BYTE = 3 };
enum { FST_BYTE_SHIFT = 24, SND_BYTE_SHIFT = 16, TRD_BYTE_SHIFT = 8, FTH_BYTE_SHIFT = 0 };

int
main(int argc, char *argv[])
{
    int f;
    long long int len;
    unsigned int u_value;
    int flag = 0;
    long long int knut = LLONG_MIN;
    long long int max = LLONG_MIN;
    int knut_ans, sickle, value;
    unsigned char bytes[INT];
    for (int i = 1; i < argc; i++) {
        f = open(argv[i], O_RDONLY);
        len = lseek(f, 0, SEEK_END);
        for (long long j = 0; j < len; j += SEEK_RECORD) {
            lseek(f, j + SEEK_NAME, SEEK_SET);
            read(f, bytes, sizeof(bytes));
            u_value = bytes[FST_BYTE];
            u_value <<= FST_BYTE_SHIFT;
            u_value += (bytes[SND_BYTE] << SND_BYTE_SHIFT) +
                (bytes[TRD_BYTE] << TRD_BYTE_SHIFT) + (bytes[FTH_BYTE] << FTH_BYTE_SHIFT);
            value = u_value;
            if (max < value) {
                if (knut < max) {
                    flag = 1;
                    knut = max;
                }
                max = value;
            } else if (max != value && knut <= value) {

                flag = 1;
                knut = value;
            }
        }
        close(f);
    }
    if (flag) {
        if (knut < 0) {
            printf("-");
            knut = llabs(knut);
        }
        knut_ans = knut % SICKLE;
        knut /= SICKLE;
        sickle = knut % GALLEON;
        long long galleon = knut / GALLEON;
        printf("%lldg%02ds%02dk\n", galleon, sickle, knut_ans);
    }
}
