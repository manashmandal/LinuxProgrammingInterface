// Solution to exercise 5.1
/*
Modify the program in Listing 5-3 to use standard file I/O system calls (open()
and lseek()) and the off_t data type. Compile the program with the
_FILE_OFFSET_BITS macro set to 64, and test it to show that a large file can be
successfully created.

Commands to check validity of large file:
./large_file /home/manash/testcpy/helloworld.txt 10111222333
ls -l /home/manash/testcpy/helloworld.txt
-rw-r--r-- 1 manash manash 10111222337 Apr 23 09:41
/home/manash/testcpy/helloworld.txt

*/

#define _FILE_OFFSET_BITS 64
#define _GNU_SOURCE
#include "../tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define TEST_FILEPATH "/home/manash/testcpy/helloworld.txt"

int large_file(int argc, char *argv[]) {
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
