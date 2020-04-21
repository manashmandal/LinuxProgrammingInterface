#define _GNU_SOURCE
#include "lib/tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
#define MAX_READ 2000
#define MAX_WRITE 512
#define TEST

void populateFile() {
  char *filePath = "/home/manash/testcpy/source.txt";
  off_t seek1 = 0;
  off_t seek2 = 1000;
  off_t seek;
  char *firstString = "hello!";
  char *secondString = "world#";
  ssize_t numWrite;
  int fd;
  if ((fd = open(filePath, O_RDWR | O_TRUNC)) == -1) {
    errMsg("open");
  }

  seek = lseek(fd, seek1, SEEK_SET);
  if ((numWrite = write(fd, firstString, strlen(firstString))) == -1) {
    errMsg("write");
  }

  seek = lseek(fd, seek2, SEEK_SET);
  if ((numWrite = write(fd, secondString, strlen(secondString))) == -1) {
    errMsg("write");
  }

  seek = lseek(fd, 0, SEEK_SET);
}

int main(int argc, char *argv[]) {
  // Populate source file with holes
  char *sourcePath = "/home/manash/testcpy/source.txt";
  char *destinationPath = "/home/manash/testcpy/destination.txt";
  char buffer[BUF_SIZE];
  int fd;
  int fdd;
  int numRead;
  off_t seek;
  off_t endSeek;
  fd = open(sourcePath, O_RDONLY);
  fdd = open(destinationPath, O_RDWR | O_TRUNC | O_CREAT | O_APPEND);
  endSeek = lseek(fd, -1, SEEK_END);
  seek = lseek(fd, -1, SEEK_SET);
  while ((seek = lseek(fd, seek + 1, SEEK_SET)) != endSeek + 1) {
    numRead = read(fd, buffer, 1);
    write(fdd, buffer, 1);
    printf("seek : %s\n", buffer);
  }

  exit(EXIT_SUCCESS);
}
