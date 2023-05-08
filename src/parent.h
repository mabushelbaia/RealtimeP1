#include "local.h"
// Constants
#define NUM_CHILDREN 5
#define NUM_ROUNDS 5

// Function prototypes
void create_children(int fd1[], int fd2[]);
void child_confirmations(int, siginfo_t *, void *);
void get_numbers(char* buffer);
int create_pipe(int f_des[]);
int send_message(int fd, char *message);

// Constants and global variables
volatile sig_atomic_t ready_counter = 0;
