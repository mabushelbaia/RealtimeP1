#include "child.h"
int main(int argc, char *argv[]) {
	struct sigaction sa;
	sa.sa_handler = &start;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
    printf("I sent a signal %d to my parent and got %d as a response\n", SIGUSR1,kill(getppid(), SIGUSR1));
    pause();
    return 0;
}

void start(int sig) {
    printf("Received starting signal [%d]\n", sig);
}
