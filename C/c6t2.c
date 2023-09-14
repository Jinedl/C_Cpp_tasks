#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

const char SUFFIX[] = ".exe";
enum { SUFFIX_LEN = sizeof(SUFFIX) - 1 };

int
main(int argc, char *argv[])
{
    long long int count = 0;
    unsigned len;
    struct dirent *file;
    struct stat stb;
    DIR *dir = opendir(argv[1]);
    if (!dir) {
        exit(1);
    }
    while ((file = readdir(dir))) {
        len = strlen(file->d_name);
        if (len >= SUFFIX_LEN && !strcmp(file->d_name + len - SUFFIX_LEN, SUFFIX)) {
            char path[PATH_MAX];
            if (snprintf(path, sizeof(path), "%s/%s", argv[1], file->d_name) < sizeof(path)) {
                if (stat(path, &stb) >= 0 && (stb.st_mode & S_IFMT) == S_IFREG && !access(path, X_OK)) count++;
            }
        }
    }
    if (closedir(dir) < 0) exit(1);
    printf("%lld\n", count);
}
