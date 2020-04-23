#define _GNU_SOURCE
#include "lib/tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
// Solution to Problem 5.2
/*
Write a program that opens an existing file for writing with the O_APPEND flag,
and then seeks to the beginning of the file before writing some data. Where does
the data appear in the file? Why?

Exaplanation:

Reference: https://linux.die.net/man/2/open

The file is opened in append mode. Before each write(2), the file offset is
positioned at the end of the file, as if with lseek(2).
*/

#include <unistd.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
#define MAX_READ 2000
#define MAX_WRITE 512
#define TEST

#define TEST_FILEPATH "/home/manash/testcpy/helloworld.txt"

int test_o_append(int argc, char *argv[]) {
  int fd;
  off_t offset = 0;
  off_t seek = 0;
  char *testString = "The Linux Programming Interface";

  fd = open(TEST_FILEPATH, O_APPEND | O_RDWR);
  if (fd == -1) {
    errExit("open");
  }

  seek = lseek(fd, offset, SEEK_SET);

  if (seek == -1) {
    errExit("seek");
  }

  if (write(fd, testString, strlen(testString)) == -1) {
    errExit("write");
  }

  if (close(fd) == -1) {
    errExit("close");
  }
}
