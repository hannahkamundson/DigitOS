#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "util.h"

void signal_handler(int signal) {
    ssize_t bytes;
    const int STDOUT = 1;
    bytes = write(STDOUT, "Nice try.\n", 10);
    if(bytes != 10)
        exit(-999);
}

/*
 * First, print out the process ID of this process.
 *
 * Then, set up the signal handler so that ^C causes
 * the program to print "Nice try.\n" and continue looping.
 *
 * Finally, loop forever, printing "Still here\n" once every
 * second.
 */
int main(int argc, char **argv)
{
    pid_t current_pid = getpid();
    printf("%d\n", current_pid);
    struct sigaction sig_handler_info = {signal_handler, 0, SA_RESTART};

    sigaction(SIGINT, &sig_handler_info, NULL);
    struct timespec rqtp = {1, 0};
    struct timespec rmtp;
    int nano_status = 0;

    while(1) {
        if (nano_status == EINTR) {
            rqtp = rmtp;
        } else {
            printf("Still here\n");
            rqtp.tv_sec = 1;
            rqtp.tv_nsec = 0;
        }
        nano_status = nanosleep(&rqtp, &rmtp);
    }
    return 0;
}


