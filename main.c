#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lib/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
#define MAX_READ 512

int main(int argc, char* argv[])
{
    char buffer[BUF_SIZE];
    int openFd;
    off_t curr;
    ssize_t numRead;
    char *filepath = "/home/manash/test.txt";
    openFd = open(filepath, O_RDONLY);
    curr = lseek(openFd, 0, SEEK_SET);
    if (openFd == -1){
        errExit("open");
    }
    while (numRead = read(openFd, buffer, MAX_READ)){
        if (numRead == -1 ){
            errExit("read");
        }
    }
    buffer[numRead] = "\0";
    printf("Read %s", buffer);
    return 0;
}
