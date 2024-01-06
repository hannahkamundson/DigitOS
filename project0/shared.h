#ifndef SHARED_H
#define SHARED_H

struct StringArrayAndSize {
  char** array; /** The string array */
  int size; /** The number of arguments */
};

/* Convenience struct for describing a command. Modify this struct as you see
 * fit--add extra members to help you write your code. */
struct Command {
  struct StringArrayAndSize args;      /* Argument array for the command */
  char *outputFile; /* Redirect target for file (NULL means no redirect) */
};

void write_error(char msg[]);

#endif /* SHARED_H */