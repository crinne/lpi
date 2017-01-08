#include "headers.h"


int main(int argc, char *argv[]) {

    if (argc !=2 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd1, fd2, fd3;

    /* Open file for reading and writng, if it doesn't exists then create it, if
    file was not empty then turnacate it, and give read write rights to current user
    */
    fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    /* Dublicated fd1 file descriptor*/
    fd2 = dup(fd1);
    /* Open file for reading and writig*/
    fd3 = open(argv[1], O_RDWR);
    /* use fd1 descriptor to write Hello into file */
    write(fd1, "Hello,", 6);
    /* use fd2 descriptor to write world into file */
    write(fd2, "world", 6);
    /* use fd2 descriptor to set file offset in the begining of file*/
    lseek(fd2, 0, SEEK_SET);
    /* use fd1 descriptor to write HELLO to the file by overriding existing text*/
    write(fd1, "HELLO,", 6);
    /* use fd3 descriptor to write Gidday to the file by overriding existing text
    fd1 and fd2 share file offset and fd3 does not, and because if this Gidday will
    be written in the beginning of file by overriding the text that was written by fd1 and fd2
    */
    write(fd3, "Gidday", 6); // Since fd donot share smae offset, Giddayworld

    exit(EXIT_SUCCESS);
}
