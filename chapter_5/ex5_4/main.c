#include "headers.h"


int dup_test(int oldFd);
int dup2_test(int oldFd,int newFd);


int main(int argc, char *argv[]) {

    if (argc !=2 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    int inputFd = open(argv[1], O_RDWR);

    if(inputFd == -1) {
        fprintf(stderr, "Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    printf("File descriptor is: %d\n", inputFd);

    int newFd = dup(inputFd);
    if (newFd == -1) {
        fprintf(stderr, "failed to dub FD\n");
        exit(EXIT_FAILURE);
    }
    printf("Dublicated file descriptor is: %d\n", newFd);

    printf("Testing home made dup_test fn\n");

    int newFd1 = dup_test(inputFd);
    if (newFd1 == -1) {
        fprintf(stderr, "failed to dub FD\n");
        exit(EXIT_FAILURE);
    }
    printf("Dublicated file descriptor is: %d\n", newFd1);


    printf("Testing hme made dup2_test fn\n");

    int newFd2 = dup2_test(inputFd, newFd1);
    if (newFd2 == -1) {
        fprintf(stderr, "failed to dub FD\n");
        exit(EXIT_FAILURE);
    }
    printf("Dublicated file descriptor is: %d\n", newFd2);

    exit(EXIT_SUCCESS);
}


int dup2_test(int oldFd,int newFd) {
    // Check if oldFd is valid descriptor
    if (fcntl(oldFd, F_GETFL) == -1) {
        fprintf(stderr, "Old file descriptior is not valid\n");
        return -1;
    }

    if (oldFd == newFd) {
        return newFd;
    }

    if (close(newFd) ==-1) {
        fprintf(stderr, "Err closing file\n");
        exit(EXIT_FAILURE);
    }
    return fcntl(oldFd, F_DUPFD, newFd);
}

int dup_test(int oldFd) {
    /*Lowest numbered available descriptor greater than or equal to arg "10" */
    return fcntl(oldFd, F_DUPFD, 10);
}
