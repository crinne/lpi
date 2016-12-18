#define _LARGEFILE64_SOURCE
#include "headers.h"

int main(int argc, char *argv[])
{
        int fd;
        off64_t off;
        if (argc != 3 || strcmp(argv[1], "--help") == 0) {
            fprintf(stderr, "%s pathname offset\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        
        if (fd == -1) {
            fprintf(stderr, "open 64\n");
            exit(EXIT_FAILURE);
        }
        
        off = atoll(argv[2]);
        if (lseek64(fd, off, SEEK_SET) == -1) {
            fprintf(stderr, "lseek64\n");
            exit(EXIT_FAILURE);
        }

        if (write(fd, "test", 4) == -1) {
            fprintf(stderr, "write\n");
            exit(EXIT_FAILURE);
        }
        
        exit(EXIT_SUCCESS);
}
