#include "evaluate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** Evaluate a single command
 *
 * Both built-ins and external commands can be passed to this function--it
 * should work out what the correct type is and take the appropriate action.
 */
void eval(struct Command *cmd) {
  // If it wasn't built in, 
  if (try_exec_builtin(cmd) == 0) {
    // Run it as an external command
    exec_external_cmd(cmd);
  }

  return;
}

int strings_same(char* string1, char* string2) {
  if (strcmp(string1, string2) == 0) {
    return 1;
  } else {
    return 0;
  }
}

void write_error(char msg[]) {
  int nbytes_written = write(STDERR_FILENO, msg, strlen(msg));

  if(nbytes_written != (int) strlen(msg)){
    exit(2);  // Shouldn't really happen -- if it does, error is unrecoverable
  }
}

/** Execute built-in commands
 *
 * If the command is a built-in command, execute it and return 1 if appropriate
 * If the command is not a built-in command, do nothing and return 0
 */
int try_exec_builtin(struct Command *cmd) {
  char* program = cmd->args.array[0];
  printf("\nSearching for command: %s", program);

  // Try to match the string
  if (strings_same("exit", program)) {
    printf("\n[exit] command executing.");
    exit(0);
  } else if (strings_same("cd", program)) {
    printf("\n[cd] command executing.");

    if (cmd->args.size != 2) {
      write_error("You must have exactly one directory.\n");
    }

    int result = chdir(cmd->args.array[1]);

    if (result != 0) {
      write_error("chdir had an error");
    }

    return 1;
  } else if (strings_same("path", program)) {
    printf("\n[path] command executing.");
    return 1;
  }

  // Otherwise return 0 so we can attempt to execute it externally
  printf("\nNo build in command found.");

  return 0;
}

/** Execute an external command
 *
 * Execute an external command by fork-and-exec. Should also take care of
 * output redirection, if any is requested
 */
void exec_external_cmd(struct Command *cmd) {
  (void)cmd;
  return;
}
