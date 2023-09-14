#include <stdio.h>

const char PATTERN[] = "rwxrwxrwx";

int
parse_rwx_permissions(const char *str)
{
    if (!str) {
        return -1;
    }
    int ans = 0;
    int i = 0;
    while (PATTERN[i]) {
        ans <<= 1;
        if (str[i] == PATTERN[i]) {
            ans++;
        } else if (str[i] != '-') {
            return -1;
        }
        i++;
    }
    if (str[i] != PATTERN[i]) {
        return -1;
    }
    return ans;
}
