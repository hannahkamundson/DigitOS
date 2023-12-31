#include "evaluate.h"
#include "commands.h"
#include <stdio.h>
#include <string.h>

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
    command_exit(cmd);
  } else if (strings_same("cd", program)) {
    printf("\n[cd] command executing.");
    command_cd(cmd);
    return 1;
  } else if (strings_same("path", program)) {
    printf("\n[path] command executing.");
    command_path(cmd);
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
