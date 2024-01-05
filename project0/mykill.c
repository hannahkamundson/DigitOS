#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: fib <num>\n");
        exit(-1);
    }

    char *process_id = argv[1];
    pid_t process_id_pid = (pid_t) atoi(process_id);
    int kill_value = kill(process_id_pid, SIGUSR1);

    if (kill_value == -1) {
        fprintf(stderr, "Kill command failed!\n");
        exit(-1);
    }
}
