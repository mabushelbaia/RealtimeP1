#include "child.h"
int main(int argc, char *argv[]) {
    kill(getppid(), SIGUSR1);
    sigset(SIGUSR1, start);
    pause();
    printf("Just a check to see if the signal handler works\n");
    return 0;
}


void start(int sig) {
    printf("Received starting signal [%d]\n", sig);
}