#include "headers.h"
#define BUF_LEN 1024

/*
 Write a program that opens an existing file for writing with the O_APPEND flag, and
 then seeks to the beginning of the file before writing some data. Where does the
 data appear in the file? Why?
 */

int main(int argc,char *argv[]) 
{
    if (argc !=2 || strcmp(argv[1], "--help") == 0) { 
        fprintf(stderr, "Usage: %s file-name\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int outputFd;

    outputFd = open(argv[1], O_WRONLY | O_APPEND);
    if (outputFd == -1) {
        fprintf(stderr, "Can't open file, make sure %s exists\n", argv[1]);
        exit(EXIT_FAILURE);
    }


    char buffer[1024+1];
    ssize_t numRead, numWritten;

    while ((numRead = read(STDIN_FILENO, buffer, BUF_LEN)) > 0) {
        if (lseek(outputFd, 0, SEEK_SET) == -1) {
            fprintf(stderr, "lseek\n");
            exit(EXIT_FAILURE);
        }
        numWritten = write(outputFd, buffer, numRead);
        if (numWritten == -1) {
            fprintf(stderr, "write\n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
