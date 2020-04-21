// This is the unoptimized solution of 4.2

#define _GNU_SOURCE
#include "../tlpi_hdr.h"
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

// Helper function
void populateFile(char *filePath) {
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
}

int sparse_copy(int argc, char *argv[]) {
  if (argc != 3) {
    usageErr("cp command needs source filepath and destination filepath. "
             "Example:\n./cp sourcepath destinationpath");
  }
  char buffer[BUF_SIZE];
  int fd;
  int fdd;
  int numRead;
  off_t seek;
  off_t endSeek;
  fd = open(argv[1], O_RDONLY);
  fdd = open(argv[2], O_RDWR | O_TRUNC | O_CREAT | O_APPEND,
             S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR);
  endSeek = lseek(fd, -1, SEEK_END);
  seek = lseek(fd, -1, SEEK_SET);
  while ((seek = lseek(fd, seek + 1, SEEK_SET)) != endSeek + 1) {
    numRead = read(fd, buffer, 1);
    write(fdd, buffer, 1);
  }

  exit(EXIT_SUCCESS);
}
