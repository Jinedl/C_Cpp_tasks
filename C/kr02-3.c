

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    unsigned long long *file = mmap(NULL, fd, 0);
}
