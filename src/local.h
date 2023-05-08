#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


void handler_setup(int sig, void (*handler)(int, siginfo_t *, void *));
int getIndex(int *array, int value, int size);
void write_range(char *filename, int min, int max);
float read_number(char *filename);
void read_range(char *filename, int *min, int *max);
void write_random_float_number(int pid, int min, int max);
void read_pipe(int);
