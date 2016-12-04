#include "headers.h"
#include <sys/stat.h>  // some statistic
#include <fcntl.h> // open

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int flags, opt;

    flags = 0;
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
        case 'a':
            flags = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-a] file\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    int outputFd;
    char buf[BUF_SIZE + 1];
    ssize_t numRead;

    // open file
    
    exit(EXIT_SUCCESS);
 }
