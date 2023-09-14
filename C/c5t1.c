#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

enum { KIBIBYTE = 0x3FF, ONLY_ONE = 1 };

int
main(int argc, char *argv[]) {
    unsigned long long sum = 0;
    struct stat stb;
    for (int i = 1; i < argc; i++) {
        if (!(lstat(argv[i], &stb)) &&
            !(stb.st_size & KIBIBYTE) &&
            (stb.st_mode & S_IFMT) == S_IFREG &&
            stb.st_nlink == ONLY_ONE) {

            sum += stb.st_size;
        }
    }
    printf("%llu\n", sum);
}
