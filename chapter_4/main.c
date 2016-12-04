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
    
    int openFlags;
    int filePerms;
    /* rw-rw-rw */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; 
    if (flags) {
        openFlags = O_CREAT | O_WRONLY | O_APPEND;
    } else {
        openFlags = O_CREAT | O_WRONLY;
    }

    int list_of_files[1000];
    
    // Opening files
    for (int i = optind; i < argc; i++) {
        list_of_files[i] = open(argv[i], openFlags, filePerms);
        if (list_of_files[i] == -1) {
            exit(EXIT_FAILURE);
        }
    }

    char buffer[BUF_SIZE] = "hello Multifile\n";
    ssize_t numRead, numWritten;

    for (int i = optind; i < argc; i++) {
        numWritten = write(list_of_files[i], buffer, BUF_SIZE);
        if (numWritten == -1 ) {
            exit(EXIT_FAILURE);
        }
            
            
    }
    exit(EXIT_SUCCESS);
}
