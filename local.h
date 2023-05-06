#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// Booleans
#define True 1
#define False 0
// Constants
#define NUM_CHILDREN 5
#define NUM_ROUNDS 5
int PIPE[2];
void handler_setup(int sig, void (*handler)(int));
