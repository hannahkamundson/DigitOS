#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int MAX = 13;

static void doFib(int n, int doPrint);

/*
 * unix_error - unix-style error routine.
 */
inline static void unix_error(char *msg) {
  fprintf(stdout, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main(int argc, char **argv) {
  int arg;
  int print = 1;

  if (argc != 2) {
    fprintf(stderr, "Usage: fib <num>\n");
    exit(-1);
  }

  arg = atoi(argv[1]);
  if (arg < 0 || arg > MAX) {
    fprintf(stderr, "number must be between 0 and %d\n", MAX);
    exit(-1);
  }

  doFib(arg, print);

  return 0;
}

/*
 * Recursively compute the specified number. If print is
 * true, print it. Otherwise, provide it to my parent process.
 *
 * NOTE: The solution must be recursive and it must fork
 * a new child for each call. Each process should call
 * doFib() exactly once.
 */
static void doFib(int n, int doPrint) {
    int answer;

    if (n == 0) {
        answer = 0;
    } else if (n == 1) {
        answer = 1;
    } else {
        pid_t first_child = fork();
        // If there is an error
        if (first_child == -1) {
            unix_error("Could not create fork!");
        // If this is the child process
        } else if (first_child == 0) {
            // Run Fib on 2 values back
            doFib(n-2, 0);
        // If it returns the child process ID (ie, it is the parent)
        } else {
            int status;
            wait(&status);
            // Store the value of 2 numbers back in the answer
            answer = WEXITSTATUS(status);

            // Then calculate the number 1 back
            pid_t second_child = fork();
            // if there is an error
            if (second_child == -1) {
                unix_error("Could not create fork!");
            // If it is the child, calculate the number before this one
            } else if (second_child == 0) {
                doFib(n-1, 0);

            // Otherwise, if it is the parent
            } else {
                // Wait for the 
                int second_status;
                wait(&second_status);
                answer += WEXITSTATUS(second_status);
            }
        }
    }

    if (doPrint == 1) {
        fprintf(stdout, "%d\n", answer);
    } else {
        exit(answer);
    }
}
