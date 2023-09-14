#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

enum { TYPES = 3, INIT = -1 };

int
main(int argc, char *argv[])
{
    errno = 0;
    long h;
    char *eptr;

    eptr = NULL;
    h = strtol(argv[2], &eptr, 10);
    if (errno || *eptr || eptr == argv[2] || (int) h != h) {
        exit(1);
    }
    int cache_size = (int) h;

    eptr = NULL;
    h = strtol(argv[3], &eptr, 10);
    if (errno || *eptr || eptr == argv[3] || (int) h != h) {
        exit(1);
    }
    int block_size = (int) h;

    char command[TYPES];
    int addr = 0, misses = 0;

    int block_count = cache_size / block_size;
    int *cache_mas = calloc(block_count, sizeof(int));
    memset(cache_mas, INIT, block_count * sizeof(int));

    int size, value;
    while (scanf("%s%x%d%d", command, &addr, &size, &value) > 0) {
        int memory_block_num = addr / block_size;
        int cache_block_num  = memory_block_num % block_count;
        if (command[0] == 'R'
            && memory_block_num != cache_mas[cache_block_num]
                && INIT != cache_mas[cache_block_num]) {
            misses++;
        }
        if (cache_mas[cache_block_num] != memory_block_num) {
            cache_mas[cache_block_num] = memory_block_num;
        }
    }

    free(cache_mas);

    printf("%d\n", misses);
}
