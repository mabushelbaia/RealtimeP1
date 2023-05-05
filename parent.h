#include "local.h"

// Constants and global variables
volatile sig_atomic_t ready_counter = 0;

// Function prototypes
pid_t *create_children();
void write_range(char *filename, int min, int max);
void ready_to_start(int);