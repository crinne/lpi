#include "headers.h"
#include <sys/stat.h>
#include <fcntl.h> // open
#include <unistd.h>


#define BUF_SIZE 1024

int main(int argc, char *argv[])
{

    if (argc < 2)
        exit(EXIT_SUCCESS);
    
    // open file
    int inputFd = open(argv[1],O_RDWR);

    if (inputFd == -1)
        exit(EXIT_FAILURE);

    lseek(inputFd, 10, SEEK_SET);
    ssize_t numRead;
    char buf[BUF_SIZE + 1];
    
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        //buf[numRead] = '\0';
        if (write(STDOUT_FILENO, buf, numRead) != numRead) {
            exit(EXIT_FAILURE);
        }
    }

    if (close(inputFd) == -1)
        exit(EXIT_FAILURE); 

    exit(EXIT_SUCCESS);
}
