#include "parent.h"

int main(int argc, char *argv[]) {
	struct sigaction sa;
	sa.sa_handler = &ready_to_start;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
	pid_t *children = create_children(NUM_CHILDREN);

	write_range("range.txt", 1, 100);
	for (int i=0; i < NUM_CHILDREN; ++i) printf("[child] %d\n", children[i]);
	// #PROBLEM: Implement a queue to store the signals received from the children
	//while(ready_counter < 5) pause(); // Wait until all children are ready (Note: without this line, the parent will send the signal before the children finish setting up their signal handlers)
	for (int j=0; j < 5; ++j) kill(children[j], SIGUSR1); // Send SIGUSR1 to all children (Start signal)
	while(wait(NULL) > 0); // Wait for all children to finish
	return 0;
}

pid_t * create_children() {
	static pid_t children[NUM_CHILDREN]; // static so that it doesn't get destroyed when the function returns
	for (int i = 0; i < NUM_CHILDREN; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			if(execlp("./child.o","child", NULL) == -1) {
				perror("exec");
				exit(1);
			}
		} else if (pid > 0) {
			children[i] = pid;
		} else {
			perror("fork");
			exit(1);
		}
		pause(); // Wait for child to finish setting up its signal handler
	}
	return children;
}

void write_range(char * filename,int min, int max) {
	//write two comma-separated integer values  in a file called range.txt
	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}
	fprintf(fp, "%d,%d", min, max);
	fclose(fp);
}

void ready_to_start(int sig) {
	ready_counter += 1;
	printf("Received ready signal [%d], count=%d\n", sig, ready_counter);
}