#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int
comparator(const void *s1, const void *s2)
{
    return(strcasecmp(*(char**) s1, *(char **) s2));
}

int
traversal(char *path, char *dir_name)
{
    char *dir_path = calloc(1, PATH_MAX);

    if (dir_name) {
        if (snprintf(dir_path, PATH_MAX, "%s/%s", path, dir_name) >= PATH_MAX) {
            free(dir_path);
            return 1;
        }
    } else {
        if (snprintf(dir_path, PATH_MAX, "%s", path) >= PATH_MAX) {
            free(dir_path);
            return 1;
        }
    }

    DIR *dir;
    if ((dir = opendir(dir_path))) {

        char **names = NULL;
        struct stat stb;
        struct dirent *object;

        if (dir_name) printf("cd %s\n", dir_name);

        int i = 0;
        while ((object = readdir(dir))) {
            if (!strcmp(object->d_name, ".") || !strcmp(object->d_name, ".."))
                continue;
            char object_path[PATH_MAX];
            if (snprintf(object_path, sizeof(object_path), "%s/%s", dir_path, object->d_name) >= sizeof(object_path)) {
                closedir(dir);
                free(dir_path);
                return 1;
            }
            if (lstat(object_path, &stb) < 0) {
                closedir(dir);
                free(dir_path);
                return 1;
            }
            if (S_ISDIR(stb.st_mode)) {
                names = (char**) realloc(names, (i + 1) * sizeof(char*));
                names[i] = (char*) calloc(1, NAME_MAX + 1);
                strncpy(names[i], object->d_name, NAME_MAX + 1);
                i++;
            }
        }
        closedir(dir);

        qsort(names, i, sizeof(char*), comparator);
        for (int j = 0; j < i; j++) {
            traversal(dir_path, names[j]);
            free(names[j]);
        }
        free(names);
        free(dir_path);

        if (dir_name) printf("cd ..\n");
        return 0;
    } else {
        free(dir_path);
        return 1;
    }
}

int
main(int argc, char *argv[])
{
    traversal(argv[1], NULL);
}
