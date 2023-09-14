#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { OK = 1, NEW = 1, UP_LEN = 3, STAY_LEN = 2 };

char*
normalize_path(const char *path, int is_cat)
{
    int len_path = strlen(path) + 1;
    char *mas = calloc(len_path, sizeof(char)); //"+ 1" for '\0'
    char *n_path = calloc(strlen(path) + 1, sizeof(char)); //"+ 1" for '\0'
    int new = NEW;
    int i, j;
    i = 0;
    while (path[i]) {
        if (new && path[i] == '.') {
            mas[i] = OK;
            new = !NEW;
            i++;
            if (path[i] == '/') {
                mas[i] = OK;
                for (j = i - 1; j >= i - STAY_LEN; j--) {
                    mas[j] = !OK;
                }
                new = NEW;
            } else if (path[i] == '\0') {
                mas[i] = OK;
                for (j = i - 1; j >= i - STAY_LEN; j--) {
                    mas[j] = !OK;
                }
                break;
            } else if (path[i] == '.') {
                mas[i] = OK;
                i++;
                if (path[i] == '/' || path[i] == '\0') {
                    mas[i] = OK;
                    for (j = i - 1; j >= i - UP_LEN; j--) {
                        mas[j] = !OK;
                    }
                    while (j >= 0 && !mas[j]) {
                        j--;
                    }
                    while (j >= 0 && path[j] != '/') {
                        mas[j] = !OK;
                        j--;
                    }
                    if (j >= 0) mas[j] = !OK;
                    if (path[i] == '\0') {
                        break;
                    } else {
                        new = NEW;
                    }
                } else {
                    mas[i] = OK;
                }
            } else {
                mas[i] = OK;
            }

        } else if (path[i] == '/') {
            mas[i] = OK;
            new = NEW;
        } else {
            mas[i] = OK;
            new = !NEW;
        }
        i++;
    }
    i = 0;
    j = 0;
    while (path[i]) {
        if (mas[i] == OK) {
            n_path[j] = path[i];
            j++;
        }
        i++;
    }
    free(mas);
    if (is_cat) {
        j--;
        while (n_path[j] != '/') {
            n_path[j] = '\0';
            j--;
        }
        if (j>=0) n_path[j] = '\0';
    }
    return n_path;
}


char*
relativize_path(const char *path1, const char *path2)
{
    char *r_path;
    char *n_path1 = normalize_path(path1, 1);
    char *n_path2 = normalize_path(path2, 0);

    if (n_path1[0] == '\0') {
        if (n_path2[1] == '\0') {
            r_path = calloc(STAY_LEN, sizeof(char));
            r_path[0] = '.';
            r_path[1] = '\0';
            free(n_path1);
            free(n_path2);
            return r_path;
        } else {
            r_path = calloc(strlen(n_path2), sizeof(char));
            strcpy(r_path, n_path2 + 1);
            free(n_path1);
            free(n_path2);
            return r_path;
        }
    }

    int j = 0, i = 0;
    while (n_path1[j + i] == n_path2[j + i]) {
        if (n_path1[j + i] == '/') {
            j += i;
            i = 1;
        } else if (n_path1[j + i] == '\0') {
            r_path = calloc(STAY_LEN, sizeof(char));
            r_path[0] = '.';
            r_path[1] = '\0';
            free(n_path1);
            free(n_path2);
            return r_path;
        } else {
            i++;
        }
    }

    int up, pos_down;
    if (n_path1[j + i] == '\0' && n_path2[j + i] == '/') {
        up = -1;
        pos_down = j + i + 1;
    } else if (n_path1[j + i] == '/' && n_path2[j + i] == '\0') {
        up = -1;
        pos_down = j + i;
    } else {
        up = 0;
        pos_down = j + 1;
    }

    while (n_path1[j]) {
        if (n_path1[j] == '/') up++;
        j++;
    }
    up *= UP_LEN; //now variable "up" is length of string for "up-signs" ("../")

    if (up > 0) {
        r_path = calloc(up, sizeof(char));
        for (j = 0; j < up; j += UP_LEN) {
            r_path[j] = '.';
            r_path[j + 1] = '.';
            r_path[j + 2] = '/';
        }
    } else {
        r_path = calloc(1, sizeof(char));
    }

    int down_len = strlen(n_path2 + pos_down);
    if (down_len) {
        if (up > 0) {
            r_path = realloc(r_path, up + down_len + 1); //"+ 1" for '\0'
        } else {
            r_path = calloc(down_len + 1, sizeof(char)); //"+ 1" for '\0'
        }
        i = 0;
        while (n_path2[pos_down + i]) {
            r_path[up + i] = n_path2[pos_down + i];
            i++;
        }
        r_path[up + i] = n_path2[pos_down + i];
    } else {
        if (up > 0) {
            r_path[up - 1] = '\0'; //"- 1" to get the last element in string
        } else {
            r_path = calloc(STAY_LEN, sizeof(char));
            r_path[0] = '.';
            r_path[1] = '\0';
            free(n_path1);
            free(n_path2);
            return r_path;
        }
    }
    free(n_path1);
    free(n_path2);
    return r_path;
}
