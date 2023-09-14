#include <stdlib.h>

enum { A = 1103515245, C = 12345, MOD = 0x80000000 };

typedef struct RandomGenerator
{
    const struct RandomOperations *ops;
    int x;
} RandomGenerator;


typedef struct RandomOperations
{
    int (*next) (RandomGenerator*);
    void (*destroy) (RandomGenerator*);
} RandomOperations;

static int
next(RandomGenerator *rand_gen)
{
    rand_gen->x = ((unsigned) rand_gen->x * (unsigned) A +  (unsigned) C) % (unsigned) MOD;
    return rand_gen->x;
}

static void
destroy(RandomGenerator *rand_gen)
{
    if (rand_gen != NULL) {
        free(rand_gen);
    }
}

static const RandomGenerator for_size;
static const RandomOperations rand_ops = {next, destroy};

RandomGenerator*
random_create(int seed)
{
    RandomGenerator *new_rand_gen = calloc(1, sizeof(for_size));
    if (new_rand_gen == NULL) {
        return NULL;
    }
    new_rand_gen->ops = &rand_ops;
    new_rand_gen->x = seed;
    return new_rand_gen;
}
