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

// Function prototypes
pid_t *create_children();
void write_range(char *filename, int min, int max);
void ready_to_start(int, siginfo_t *, void *);
void handler_setup(int sig, void (*handler)(int, siginfo_t *, void *));

// Constants and global variables
volatile sig_atomic_t ready_counter = 0;

