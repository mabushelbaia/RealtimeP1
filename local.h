#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

// Booleans
#define True 1
#define False 0
// Constants
#define NUM_CHILDREN 5

void handler_setup(int sig, void (*handler)(int));
