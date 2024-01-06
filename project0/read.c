#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Command read_user_input() {
  // Read the raw input
  char* raw = read_raw();
  printf("\nRAW: %s", raw);

  // Tokenize it and get it in a string array
  struct StringArrayAndSize tokenized = tokenize_command_line(raw);

  for (int i = 0; i < tokenized.size; i++) {
    printf("\nTOKENIZED %d: %s", i, tokenized.array[i]);
  }

  return parse_command(tokenized);
}

char* read_raw() {
    char *line = NULL;
    size_t linecap = 0;

    char result = getline(&line, &linecap, stdin);
    (void)result; // Just so we don't get a compiler issue

    return line;
}

/** Turn a command line into tokens with strtok
 *
 * This function turns a command line into an array of arguments, making it
 * much easier to process. First, you should figure out how many arguments you
 * have, then allocate a char** of sufficient size and fill it using strtok()
 */
struct StringArrayAndSize tokenize_command_line(char *cmdline) {
  // TODO
  (void)cmdline;

  int numberOfArgs = 2;

  // Get the array of strings (char*)
  char* localArray[] = { "cd", "examples" };

  // This holds the address of the array of strings we can actually return
  char** returnable = malloc(numberOfArgs * sizeof(char*));

  // For each argument, move it to the returnable
  for (int i = 0; i < numberOfArgs; i++) {
    returnable[i] = malloc(strlen(localArray[i]) + 1);
    strcpy(returnable[i], localArray[i]);
  }

  struct StringArrayAndSize output = { .array = returnable, .size = numberOfArgs };
  
  return output;
}

/** Turn tokens into a command.
 *
 * The `struct Command` represents a command to execute. This is the preferred
 * format for storing information about a command, though you are free to change
 * it. This function takes a sequence of tokens and turns them into a struct
 * Command.
 */
struct Command parse_command(struct StringArrayAndSize tokensAndSize) {
  // TODO
  struct Command dummy = {.args = tokensAndSize, .outputFile = NULL};
  return dummy;
}