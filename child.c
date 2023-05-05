#include "child.h"
#include "local.h"

int main(int argc, char *argv[]) {
    handler_setup(SIGUSR1, &start);
    kill(getppid(), SIGUSR1); // Send SIGUSR1 to parent (Ready signal)
    pause();
    return 0;
}

void start(int sig) {
    printf("Received starting signal [%d]\n", sig);
}

void handler_setup(int sig, void (*handler)(int)) {
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(sig, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
}
