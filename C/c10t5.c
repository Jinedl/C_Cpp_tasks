#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>

const char FILE_RANDOM[] = "/dev/urandom";
const char LINE1[] = "#include <stdio.h>\n";
const char LINE2[] = " const char reject[] = \"reject\"; const char summon[] = \"summon\";";
const char LINE2_CONTINUE1[] = " const char disqualify[] = \"disqualify\";";
const char LINE2_CONTINUE2[] = " int main(void) { int x; while (scanf(\"%%u\", &x) != EOF) printf(\"%%s%%c\", ";
const char LINE2_END[] = ", 10);}";

int
main(int argc, char *argv[])
{
    int fd;
    unsigned long long name_digit;
    char name_file[NAME_MAX];
    char name_program[NAME_MAX];
    if ((fd = open(FILE_RANDOM, O_RDONLY)) < 0) {
        exit(1);
    }
    if (read(fd, &name_digit, sizeof(name_digit)) < 0) {
        exit(1);
    }
    if (snprintf(name_file, sizeof(name_file), "%llu", name_digit) >= sizeof(name_file)) {
        exit(1);
    }
    if (snprintf(name_program, sizeof(name_program), "%llu", ~name_digit) >= sizeof(name_program)) {
        exit(1);
    }
    close(fd);

    char file[PATH_MAX];
    if (snprintf(file, sizeof(file), "%s/%s.c",
        getenv("XDG_RUNTIME_DIR") ? getenv("XDG_RUNTIME_DIR") : (getenv("TMPDIR") ? getenv("TMPDIR") : "/tmp"),
            name_file) >= sizeof(file)) {

        exit(1);
    }

    char program[PATH_MAX];
    if (snprintf(program, sizeof(program), "%s/%s",
        getenv("XDG_RUNTIME_DIR") ? getenv("XDG_RUNTIME_DIR") : (getenv("TMPDIR") ? getenv("TMPDIR") : "/tmp"),
            name_program) >= sizeof(program)) {

        exit(1);
    }

    if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0500)) < 0) {
        exit(1);
    }
    int out = dup(1);
    dup2(fd, 1);
    if (printf(LINE1) < 0 ||
        printf(LINE2) < 0 ||
            printf(LINE2_CONTINUE1) < 0 ||
                printf(LINE2_CONTINUE2) < 0 ||
                    printf("%s", argv[1]) < 0 ||
                        printf(LINE2_END) < 0) {

        exit(1);
    }
    close(fd);

    fflush(stdout);
    dup2(out, 1);
    close(out);

    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (!pid) {
        if (execlp("gcc", "gcc", "-std=gnu18", "-O2", file, "-o", program, NULL) < 0) {
            _exit(1);
        }
    } else {
        if (wait(NULL) < 0) {
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (!pid) {
            if (execlp(program, program, NULL) < 0) {
                _exit(1);
            }
        }
        if (wait(NULL) < 0) {
            exit(1);
        }

        if (remove(file) < 0) {
            exit(1);
        }
        if (remove(program) < 0) {
            exit(1);
        }
    }
}
