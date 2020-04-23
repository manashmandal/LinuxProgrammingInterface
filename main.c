#define _FILE_OFFSET_BITS 64
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

int main(int argc, char *argv[]) {
  int fd;
  off_t off;

  if (argc != 3 || strcmp("argv[1]", "--help") == 0) {
    usageErr("%s pathname offset\n", argv[0]);
  }

  fd = open(TEST_FILEPATH, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    errExit("open64");
  }

  off = atoll(argv[2]);

  if (lseek(fd, off, SEEK_SET) == -1) {
    errExit("lseek64");
  }

  if (write(fd, "test", 4) == -1) {
    errExit("write");
  }

  exit(EXIT_SUCCESS);
}
