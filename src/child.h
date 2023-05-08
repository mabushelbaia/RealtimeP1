#include "local.h"
// Booleans
#define True 1
#define False 0
// Constants
#define NUM_CHILDREN 5
#define NUM_ROUNDS 5

// Constants and global variables
int fd1;
int fd2;

// Function prototypes
void start(int, siginfo_t *, void *);
void confirmed(int, siginfo_t *, void *);
void coprocessor(int sig, siginfo_t *info, void *context);
