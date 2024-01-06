/*
  utcsh - The UTCS Shell

  <Put your name and CS login ID here>
*/

/* Read the additional functions from util.h. They may be beneficial to you
in the future */
#include "util.h"
#include "shared.h"
#include "evaluate.h"
#include "read.h"
#include <stdio.h>

/* Global variables */
/* The array for holding shell paths. Can be edited by the functions in util.c*/
char shell_paths[MAX_ENTRIES_IN_SHELLPATH][MAX_CHARS_PER_CMDLINE];
static char prompt[] = "DigitOS> "; /* Command line prompt */
static char *default_shell_path[2] = {"/bin", NULL};
/* End Global Variables */


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

