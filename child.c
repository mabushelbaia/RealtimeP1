#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    printf("I am a child process with PID = %d\n", getpid());
    return 0;
}