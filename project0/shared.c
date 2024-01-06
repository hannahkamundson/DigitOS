#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void write_error(char msg[]) {
  int nbytes_written = write(STDERR_FILENO, msg, strlen(msg));

  if(nbytes_written != (int) strlen(msg)){
    exit(2);  // Shouldn't really happen -- if it does, error is unrecoverable
  }
}