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
void judge(int signo, siginfo_t *info, void *context);

// Constants and global variables
volatile sig_atomic_t ready_counter = 0;
pid_t children[NUM_CHILDREN];
bool confirmed[NUM_CHILDREN - 1] = {false};
float numbers[NUM_CHILDREN - 1] = {0.0};
int scores[2] = {0};
int round = 0;
int fd1[2];
int fd2[2];