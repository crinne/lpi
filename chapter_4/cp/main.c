#include "headers.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{

    if (argc != 3 || strcmp(argv[1], "-help") == 0) {
        fprintf(stderr, "Usage: %s old-file new-file\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    int inputFd;
    if ((inputFd = open(argv[1],O_RDWR)) == -1) {
        fprintf(stderr, "Error: opening file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t filePerms = S_IRUSR | S_IWUSR| S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    ssize_t numRead;
    char buf[BUF_SIZE];

    int outputFd;
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        fprintf(stderr, "Error opening file %s\n", argv[2]);
    }
    

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        
        if ((write(outputFd, buf, numRead)) == -1) {
            fprintf(stderr, "Error: writing file\n");
            exit(EXIT_FAILURE);
        }
    }

    if (close(inputFd) == -1) {
        fprintf(stderr, "Error closing input\n");
        exit(EXIT_FAILURE); 
    }
    if (close(outputFd) == -1) {
        fprintf(stderr, "Error: closing output\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}
