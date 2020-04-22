#define _GNU_SOURCE
#include "lib/tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
#define MAX_READ 2000
#define MAX_WRITE 512
#define TEST

#define TEST_FILEPATH "/home/manash/testcpy/helloworld.txt"

int t_readv(int argc, char *argv[]) {
  int fd;
  struct iovec iov[2];
  struct stat myStruct;
  int x;
#define STR_SIZE 12
  char str[STR_SIZE];
  ssize_t numRead, totRequired;

  fd = open(TEST_FILEPATH, O_RDONLY);
  if (fd == -1) {
    errExit("open");
  }

  totRequired = 0;

  //  iov[0].iov_base = &myStruct;
  //  iov[0].iov_len = sizeof(myStruct);
  //  totRequired += iov[0].iov_len;

  iov[0].iov_base = &x;
  iov[0].iov_len = sizeof(x);
  totRequired += iov[0].iov_len;

  iov[1].iov_base = str;
  iov[1].iov_len = STR_SIZE;
  totRequired += iov[1].iov_len;

  numRead = readv(fd, iov, 3);
  if (numRead == -1) {
    errExit("readv");
  }

  if (numRead < totRequired) {
    printf("Read fewer bytes than requested\n");
  }

  printf("total bytes requested: %ld; bytes read: %d\n", (long)totRequired,
         (long)numRead);
  printf("%s\n", str);
  exit(EXIT_SUCCESS);
}
