#include "parent.h"

int main(int argc, char *argv[]) {
	sigset(SIGUSR1, ready_to_start);
	pid_t *children = create_children(5);
	write_range("range.txt", 1, 100);
	for (int i=0; i < 5; ++i) printf("[child] %d\n", children[i]);
	while(ready_counter < 5) pause(); // Wait until all children are ready (Note: without this line, the parent will send the signal before the children finish setting up their signal handlers)
	for (int i=0; i < 5; ++i) kill(children[i], SIGUSR1); // Send SIGUSR1 to all children (Start signal)
	while(wait(NULL) > 0); // Wait for all children to finish
	return 0;
}

pid_t * create_children(int num_children) {
	static pid_t children[5]; // static so that it doesn't get destroyed when the function returns
	for (int i = 0; i < num_children; i++) {
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
	printf("Received signal %d, ready counter: %d\n", sig, ready_counter);
}