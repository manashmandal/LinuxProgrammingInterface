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

#define TEST_FILEPATH "/home/manash/testcpy/helloworld.txt"

int bad_exclusive_open(int argc, char *argv[]) {
  int fd;
  fd = open(TEST_FILEPATH, O_WRONLY);
  if (fd != -1) {
    printf("[PID %ld] File \"%s\" already exists\n", (long)getpid(),
           TEST_FILEPATH);
    close(fd);
  } else {
    if (errno != ENOENT) {
      errExit("open");
    } else {
      fd = open(TEST_FILEPATH, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
      if (fd == -1) {
        errExit("open");
      }
      printf("[PID %ld] Created file '%s' exclusively\n", (long)getpid(),
             TEST_FILEPATH);
    }
  }
  return 0;
}
