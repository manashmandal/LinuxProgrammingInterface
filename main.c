#include "lib/tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
#define MAX_READ 512

int main(int argc, char *argv[]) {
  char *testfilepath = "/home/manash/KernelProgramming/helloworld.txt";
  char buff[BUF_SIZE];
  int fd;
  ssize_t numRead;

  fd = open(testfilepath, O_RDWR | O_TRUNC);

  if (fd == -1) {
    errMsg("open");
  }

  while (numRead = read(STDIN_FILENO, buff, MAX_READ)) {
    if (numRead == -1) {
      errMsg("read");
    }
    buff[numRead] = '\0';
    if (write(fd, buff, numRead) == -1) {
      errMsg("write");
    }
    printf("%s", buff);
  }
}
