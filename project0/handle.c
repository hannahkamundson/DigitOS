#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "util.h"
#include <sys/types.h>


void handleSIGINT(int signal) 
{
    ssize_t bytes;
    // Write to standout by directly calling to POSIX write vs using printf which is an interface that calls write
    bytes = write(1, "Nice try\n", 10);
    if(bytes != 10) 
    {
        exit(-999);
    }
}

void handleSIGUSR1(int signal)
{
    ssize_t bytes;
    bytes = write(1, "Exiting", 8);
    if(bytes != 10) 
    {
        exit(-999);
    }

    exit(1);
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
    pid_t processId = getpid();

    printf("%d\n", processId);

    struct sigaction actionOnSIGINT;
    actionOnSIGINT.sa_handler = handleSIGINT;

    struct sigaction actionOnSIGUSR1;
    actionOnSIGUSR1.sa_handler = handleSIGUSR1;

    sigaction(SIGINT, &actionOnSIGINT, NULL);
    sigaction(SIGUSR1, &actionOnSIGUSR1, NULL);
    
    const struct timespec requestedTime = { 1 /* second */, 0 /* nanoseconds */ };
    struct timespec remainingTime;
    // // Was it interrupted?
    // int interruptStatus = 0;

    while(true) {
        printf("Still here\n");
        nanosleep(&requestedTime, &remainingTime);
    }

    return 0;
}
