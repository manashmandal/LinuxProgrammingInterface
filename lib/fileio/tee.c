// Solution to exercise-4.1

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
#define MAX_READ 512
#define MAX_WRITE 512

int tee(int argc, char *argv[]) {
  Boolean append;
  char *cvalue = NULL;
  int c;
  int fd;
  char *filepath;
  char buffer[BUF_SIZE];
  ssize_t numRead;

  if (argc < 2 || argc > 3) {
    usageErr("tee needs at least one filepath argument. And optional append "
             "operation '-a'");
  }

  // Check for appending existing file option
  while ((c = getopt(argc, argv, "a")) != -1) {
    switch (c) {
    case 'a':
      append = TRUE;
      break;
    }
  }

  if (argc == 3 && append) {
    if ((fd = open(argv[2], O_RDWR | O_APPEND)) == -1) {
      errMsg("open");
    }
  } else {
    if ((fd = open(argv[1], O_RDWR | O_TRUNC)) == -1) {
      errMsg("open");
    }
  }

  while ((numRead = read(STDIN_FILENO, buffer, MAX_READ)) != -1) {
    buffer[numRead] = '\0';
    if (write(fd, buffer, numRead) == -1) {
      errMsg("write");
    }
    printf("%s", buffer);
  }

  if (numRead == -1) {
    errMsg("read");
  }

  exit(EXIT_SUCCESS);
}
