#include <stdio.h>
#include <sys/stat.h>

enum { U_SHIFT = 6, G_SHIFT = 3, O_SHIFT = 0 };

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int
gid(const struct stat *stb, const struct Task *task)
{
    for (int i = 0; i < task->gid_count; i++) {
        if (task->gids[i] == stb->st_gid) {
            return 1;
        }
    }
    return 0;
}

int
ok_access(int mode, int access, int shift)
{
    return ((mode >> shift) & access) == access;
}

int
myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (!task->uid) {
        return 1;
    }
    if (task->uid == stb->st_uid) {
        return ok_access(stb->st_mode, access, U_SHIFT);
    }
    if (gid(stb, task)) {
        return ok_access(stb->st_mode, access, G_SHIFT);
    }
    return ok_access(stb->st_mode, access, O_SHIFT);
}
