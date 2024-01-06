/*
  utcsh - The UTCS Shell

  <Put your name and CS login ID here>
*/

/* Read the additional functions from util.h. They may be beneficial to you
in the future */
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Global variables */
/* The array for holding shell paths. Can be edited by the functions in util.c*/
char shell_paths[MAX_ENTRIES_IN_SHELLPATH][MAX_CHARS_PER_CMDLINE];
static char prompt[] = "DigitOS> "; /* Command line prompt */
static char *default_shell_path[2] = {"/bin", NULL};
/* End Global Variables */


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

/* Here are the functions we recommend you implement */
struct Command read_user_input();
char* read_raw();
struct StringArrayAndSize tokenize_command_line(char *cmdline);
struct Command parse_command(struct StringArrayAndSize tokensAndSize);
void eval(struct Command *cmd);
int try_exec_builtin(struct Command *cmd);
void exec_external_cmd(struct Command *cmd);

/*
remembering pointers:

int number = 1;
printf("NUMBER: %d", number);
  utcsh> NUMBER: 1
printf("\nNUMBER&: %p", &number);
  utcsh> NUMBER&: 0x7ffec8a2660c

int* numberPointer = &number;
printf("\nPOINTER: %p", numberPointer);
  utcsh> POINTER: 0x7ffec8a2660c
printf("\nPOINTER*: %d", *numberPointer);
  utcsh> POINTER*: 1
printf("\nPOINTER POINTER: %p", &numberPointer);
  utcsh> POINTER POINTER: 0x7ffec8a26610% 

char* input = "This is my input";
printf("INPUT: %s", input);
  utcsh> INPUT: This is my input
printf("INPUT POINTER: %p", input);
  utcsh> INPUT POINTER: 0x56299a6d9004

*/

/* Main REPL: read, evaluate, and print. This function should remain relatively
   short: if it grows beyond 60 lines, you're doing too much in main() and
   should try to move some of that work into other functions. */
int main(int argc, char **argv) {
  set_shell_path(default_shell_path);

  /* These two lines are just here to suppress certain warnings. You should
   * delete them when you implement Part 1.4 */
  (void)argc;
  (void)argv;


  // while (1) {
    printf("%s", prompt);
    
    /* Read */
    struct Command command = read_user_input();

    /* Evaluate */
    eval(&command);

    /* Print (optional) */
  // }
  return 0;
}

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
