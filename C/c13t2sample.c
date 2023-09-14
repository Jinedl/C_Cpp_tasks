#include <stdio.h>
#include <inttypes.h>

int64_t
calc_max_size(int64_t block_size, int64_t block_num_size, int64_t inode_direct_block_count)
{
    /// максимальный теоретический размер файла исходя из размера числа для хранения номера блока диска в байтах:
    int64_t max_theoretical_size = block_size, deg = 1;
    if (__builtin_smulll_overflow(8, block_num_size, (long long int *) &deg)) {
        max_theoretical_size = -1;
    }
    else {
        for (int i = 0; i < deg; i++) {
            if (__builtin_smulll_overflow(2, max_theoretical_size, (long long int *) &max_theoretical_size)) {
                max_theoretical_size = -1;
                break;
            }
        }
    }

    /// максимальный размер файла исходя из размера блока системы
    int64_t max_system_size = inode_direct_block_count;
    int64_t num_links_indir_level = 1; // число ссылок в этом уровне косвенности
    int64_t d_nlil = block_size/block_num_size; // в результат будет входить слагаемые - первая, вторая и третья степени
    for (int i = 0; i < 3; i++) {
        if (__builtin_smulll_overflow(num_links_indir_level, d_nlil, (long long int *) &num_links_indir_level) ||
                __builtin_saddll_overflow(max_system_size, num_links_indir_level, (long long int *) &max_system_size)) {
            max_system_size = -1;
            break;
        }
    }
    if (max_system_size != -1
            && __builtin_smulll_overflow(max_system_size, block_size, (long long int *) &max_system_size)) {
        max_system_size = -1;
    }

    if (max_system_size == -1) return max_theoretical_size;
    if (max_theoretical_size == -1) return max_system_size;
    return max_theoretical_size < max_system_size ? max_theoretical_size : max_system_size;
}


int main() {
    int64_t block_size, block_num_size, inode_direct_block_count;
    scanf("%"PRId64"%"PRId64"%"PRId64, &block_size, &block_num_size, &inode_direct_block_count);

    printf("%"PRId64"\n", calc_max_size(block_size, block_num_size, inode_direct_block_count));

    int64_t max_size = 0, max_bns = 1;
    for (int i = 1; i <= block_size; i++) {
        int64_t cur = calc_max_size(block_size, i, inode_direct_block_count);
        if (cur > max_size || cur == -1) {
            max_size = cur;
            max_bns = i;
        }
        if (cur == -1) {
            break;
        }
    }
    printf("%"PRId64" %"PRId64"\n", max_bns, max_size);

    return 0;
}
