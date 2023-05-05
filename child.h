#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

// Booleans
#define True 1
#define False 0

// Function prototypes
void start(int);
void read_range(char *, int *, int *);
float generate_random_float_number(int min, int max);
void write_random_float_number(float);
