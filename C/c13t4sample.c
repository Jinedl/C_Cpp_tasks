#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

enum { LEFT_IDX = 1, RIGHT_IDX = 2, N_IDX = 3, F_IDX = 4 };

int
main(int argc, char *argv[])
{
    char file_path[] = "tmp_path.c";
    char exe_file_path[] = "tmp_path";

    int fd = open(file_path, O_WRONLY | O_TRUNC | O_CREAT, 0777);

    int stdout_cpy = dup(1);
    dup2(fd, 1);
    close(fd);
    printf("#include <stdio.h>\n"
    "#include <math.h>\n\n"
    "int main(void) {\n"
    "    double left = %s, right = %s;\n"
    "    int n = %s;\n"
    "    double dx = (right - left) / (double)n;\n"
    "    double s = 0.0;\n"
    "    for (int i = 0; i < n; i++) {\n"
    "        double x = left + i * dx;\n"
    "        s += (%s) * dx;\n"
    "    }\n"
    "    printf(\"%%.10g\\n\", s);\n"
    "    return 0;\n"
    "}", argv[LEFT_IDX], argv[RIGHT_IDX], argv[N_IDX], argv[F_IDX]);

    fflush(stdout);
    dup2(stdout_cpy, 1);
    close(stdout_cpy);

    pid_t pid = fork();
    if (pid < 0) {
        _exit(1);
    }
    else if (!pid) {
        execlp("gcc", "gcc", "-o", exe_file_path, file_path, "-lm", NULL);
        _exit(1);
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status)) {
        _exit(1);
    }
    if (remove(file_path)) {
        _exit(1);
    }
    execl(exe_file_path, exe_file_path, NULL);
    _exit(1);
}
