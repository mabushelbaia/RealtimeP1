#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

// Booleans
#define True 1
#define False 0

// Constants and global variables
static int ready_counter = 0;

// Function prototypes
pid_t * create_children(int num_children);
void write_range(char * filename, int min, int max);
void ready_to_start(int);
