#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

// Booleans
#define True 1
#define False 0
// Constants
#define NUM_CHILDREN 5
#define NUM_ROUNDS 5

// Constants and global variables

// Function prototypes
void start(int, siginfo_t *, void *);
void read_range(char *, int *, int *);
float generate_random_float_number(int min, int max);
void write_random_float_number(int pid, float number);
void handler_setup(int sig, void (*handler)(int, siginfo_t *, void *));
