#include "../tlpi_hdr.h";
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
#define MAX_READ 512

int readUsingSeek(char *filepath, off_t seek){
    char buffer[BUF_SIZE];
    int openFd;
    off_t curr;
    ssize_t numRead;
    openFd = open(filepath, O_RDONLY);
    curr = lseek(openFd, seek, SEEK_CUR);
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
