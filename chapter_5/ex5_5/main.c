#include "headers.h"

void print_activity();
void flush_input();
void openFlagTest(int fd, int dupFd);

int main(int argc, char *argv[]) {

    if (argc !=2 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    off_t offset, dupOffset; 
    int inputFd, dupInputFd;
    inputFd = open(argv[1], O_RDWR | O_SYNC);
    if (inputFd == -1) { fprintf(stderr, "Err: open\n"); exit(EXIT_FAILURE);}


    dupInputFd = dup(inputFd);
    char buffer[1024];
    ssize_t numWritten, numRead;
    int true = 1;
    int c;
    while(true) {
        print_activity();
        c = getchar();

        switch(c) {
            case '1':
                offset = lseek(inputFd, 0, SEEK_CUR);
                printf("current file offset : %ld \n", offset);
                dupOffset = lseek(dupInputFd, 0, SEEK_CUR);
                printf("dublicated file offset : %ld \n", dupOffset);

                break;
            case '2':

                if ((numRead = read(inputFd, buffer, 5)) != -1) {
                    buffer[5] = '\n';
                    if (write(STDOUT_FILENO, buffer, numRead+1) == -1) {
                        fprintf(stderr, "Err: write\n");
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            case '5':
                openFlagTest(inputFd, dupInputFd);
                break;
            case '9':
                true = 0;
                break;
            default:
                printf("wrong input: %c\n", c);
        }
        flush_input();
    }

    exit(EXIT_SUCCESS);
}

void print_activity() {
    printf("Activities:\n"
                    "1. Print file offset\n"
                    "2. Read char's\n"
                    "5. Test Open flags\n"
                    "9. Exit\n");
}

void openFlagTest(int fd, int dupFd) {
    int flags, dupFlags, accessMode, dupAccessMode;

    flags = fcntl(fd, F_GETFL);
    if (flags == 1) {
        fprintf(stderr, "Err: fcntl\n");
        exit(EXIT_FAILURE);
    }
    dupFlags = fcntl(dupFd, F_GETFL);
    if (dupFlags == 1) {
        fprintf(stderr, "Err: fcntl\n");
        exit(EXIT_FAILURE);
    }

    accessMode = flags & O_ACCMODE;
    dupAccessMode = dupFlags & O_ACCMODE;

    if (flags & O_SYNC && dupFlags & O_SYNC) {
        printf("Witesare synchronized\n");
    }

    if (accessMode == O_WRONLY || accessMode == O_RDWR) {
        printf("File is writibale\n");
    }

    if (dupAccessMode == O_WRONLY || dupAccessMode == O_RDWR) {
        printf("Dublicated File is writibale\n");
    }

}

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

