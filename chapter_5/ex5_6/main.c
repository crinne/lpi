#include "headers.h"


int main(int argc, char *argv[]) {

    if (argc !=2 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd1, fd2, fd3;

    fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    fd2 = dup(fd1);
    fd3 = open(argv[1], O_RDWR);
    write(fd1, "Hello,", 6); //input is Hello,
    write(fd2, "world", 6); // input will be Hello,world
    lseek(fd2, 0, SEEK_SET); // set offset to 0 for fd1 and fd2
    write(fd1, "HELLO,", 6); // input will be HELLO,world
    write(fd3, "Gidday", 6); // Since fd donot share smae offset, Giddayworld


    exit(EXIT_SUCCESS);
}
