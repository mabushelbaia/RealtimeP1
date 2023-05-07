#include "child.h"

volatile sig_atomic_t confirmed_f = false;
int main(int argc, char *argv[]) {
	if (strcmp(argv[1], "4") == 0) {
    	printf("[%d] Coprocessor child process started\n", getpid());
	}
	else {
    	printf("[%d] Child process started\n", getpid());
    	handler_setup(SIGUSR1, &start);
    	handler_setup(SIGUSR2, &confirmed);
    	pause();
    	return 0;
	}
}
void confirmed(int sig, siginfo_t *info, void *context) {
    confirmed_f = true;
    printf("[%d] Received confirmation signal\n", getpid());
}

void start(int sig, siginfo_t *info, void *context) {
    printf("[%d] Received starting signal\n", getpid());
    int min, max;
    read_range("./txt/range.txt", &min, &max);
    write_random_float_number(getpid(), min, max);
    while (!confirmed_f) {
        kill(getppid(), SIGUSR1);
    }
    confirmed_f = false;
}
