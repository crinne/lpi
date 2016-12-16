#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Error: usage %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char buffer[] = "This is my test";

    int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t filePerms = S_IRUSR | S_IWUSR| S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    int outputFd;
    outputFd = open(argv[1], openFlags, filePerms);
    if (outputFd == -1) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
    }

    if (lseek(outputFd, 10000, SEEK_SET) == -1) {
        fprintf(stderr, "Error: lseek\n");
        exit(EXIT_FAILURE);
    }

    if ((write(outputFd, buffer, strlen(buffer))) == -1) {
        fprintf(stderr, "Error writing file\n");
        exit(EXIT_FAILURE);
    }

    if (close(outputFd) == -1) {
        fprintf(stderr, "Error closing\n");
        exit(EXIT_FAILURE);
    }
                        
    exit(EXIT_SUCCESS);
}
