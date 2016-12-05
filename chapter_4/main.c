#include "headers.h"
#include <sys/stat.h>
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

    char buffer[BUF_SIZE+1];
    ssize_t numRead;

    while ((numRead = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0) {
        buffer[numRead] = '\0';

        printf("%s", buffer);
        for (int i = optind; i < argc; i++) {
            if (write(list_of_files[i], buffer, numRead) != numRead) {
                exit(EXIT_FAILURE);
            }
        }
    }
    
    exit(EXIT_SUCCESS);
}
