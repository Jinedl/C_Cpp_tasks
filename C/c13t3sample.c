#include <malloc.h>
#include <memory.h>

double
***transpose(double ***arr)
{
    int dim_ext = 0; // число строк в исходном массиве
    while(NULL != arr[dim_ext]) {
        dim_ext++;
    }
    int *dim_internal = calloc(dim_ext, sizeof(int)); // число ссылок в каждой строке
    memset(dim_internal, 0, dim_ext * sizeof(int));

    int *dim_internal_copy = calloc(dim_ext, sizeof(int)); // число ссылок в каждой строке
    memset(dim_internal_copy, 0, dim_ext * sizeof(int));

    int res_dim_ext = 0; // число строк в результате равно длине самой большой строки
    for (int i = 0; i < dim_ext; i++) {
        while(NULL != arr[i][dim_internal[i]]) {
            dim_internal[i]++;
            dim_internal_copy[i]++;
        }
        if (dim_internal[i] > res_dim_ext) {
            res_dim_ext = dim_internal[i];
        }
    }

    double ***res = calloc(res_dim_ext + 1, sizeof(*res));

    for (int i = 0; i < res_dim_ext; i++) {
        int cur_len = 0;
        for (int j = 0; j < dim_ext; j++) {
            if (dim_internal[j] > 0) {
                dim_internal[j]--;
                cur_len = j + 1;
            }
        }
        res[i] = calloc(cur_len + 1, sizeof(*res[i]));
        for (int j = 0; j < cur_len; j++) {
            res[i][j] = calloc(1, sizeof(*res[i][j]));
            if (i < dim_internal_copy[j] && j < dim_ext) {
                res[i][j][0] = arr[j][i][0];
            }
            else {
                res[i][j][0] = 0;
            }
        }
        res[i][cur_len] = NULL;
    }
    res[res_dim_ext] = NULL;
    free(dim_internal);
    free(dim_internal_copy);
    return res;
}
