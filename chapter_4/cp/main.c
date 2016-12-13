#include "headers.h"
#include <sys/stat.h>
#include <fcntl.h> // open
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{

    if (argc < 2) {
        exit(EXIT_SUCCESS);
    }

    // open file
    int inputFd;
    if ((inputFd = open(argv[1],O_RDWR)) == -1) {
        exit(EXIT_FAILURE);
    }

    /* creating test file
    char buffer[] = "This is my test file \n and second rot\n";
    int outputFd;
    if ((outputFd = open("test2.txt", O_RDWR)) != -1) {
        if (lseek(outputFd, 100, SEEK_SET) == -1) {
            exit(EXIT_FAILURE);
        }

        if (write(outputFd, buffer, strlen(buffer)) == -1) {
            printf("Err\n");
        }
    }
*/
    //lseek(inputFd, 10, SEEK_SET);
    
    ssize_t numRead;
    char buf[BUF_SIZE + 1];
    
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        //buf[numRead] = '\0';
        
        for (int i = 0; i < numRead; i++) {    
            if (buf[i] == '\0') {
                printf("Hole\n");
            } 
            else {
                printf("%c\n", buf[i]);
            }
            //if (write(STDOUT_FILENO, buf, numRead) != numRead) {
            //    exit(EXIT_FAILURE);
           // }
        }
    }

    if (close(inputFd) == -1) {
        exit(EXIT_FAILURE); 
    }
    
    exit(EXIT_SUCCESS);
}
