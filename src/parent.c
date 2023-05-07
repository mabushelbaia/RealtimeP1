#include "parent.h"

pid_t children[NUM_CHILDREN];
bool confirmed[NUM_CHILDREN - 1] = {false};
float numbers[NUM_CHILDREN - 1] = {0.0};
int main(int argc, char *argv[]) {
	int fd1[2], fd2[2];
	create_pipe(fd1);
	create_pipe(fd2);
	handler_setup(SIGUSR1, &child_confirmations);
	create_children(fd1, fd2);
	sleep(1); // Wait for children to finish setting up their signal handlers
	write_range("./txt/range.txt", 1, 100);
	for (int j=0; j < NUM_CHILDREN - 1; ++j) kill(children[j], SIGUSR1); // Send SIGUSR1 to all children (Start signal)
	kill(children[NUM_CHILDREN - 1], SIGPIPE); // Send SIGUSR2 (PIPE Child)
	while(ready_counter < NUM_CHILDREN - 1) pause(); // Wait for all children to send SIGUSR1 (Confirm signal)
	get_numbers();
	while(wait(NULL) > 0); // Wait for all children to finish
	return 0;
}

void create_children(int fd1[], int fd2[])
{
	for (int i = 0; i < NUM_CHILDREN; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			// Redirect read end of pipe to stdin
        	if (dup2(fd1[0], STDIN_FILENO) == -1 || dup2(fd2[1], STDOUT_FILENO) == -1) {
        	    perror("dup2");
        	    exit(EXIT_FAILURE);
        	}
			close(fd1[1]);
			close(fd2[0]);
			char arg[10];
			sprintf(arg, "%d", i);
			if (execlp("./bin/child.o", arg, NULL) == -1)
			{
				perror("exec");
				exit(1);
			}
		}
		else if (pid > 0)
		{
			children[i] = pid;
			close(fd1[0]);
			close(fd2[1]);
		}
		else
		{
			perror("fork");
			exit(1);
		}
	}
}

void child_confirmations(int signo, siginfo_t *info, void *context) {
	// printf("[Parent]\n");
    // printf("Received signal %d\n", signo);
    // printf("Sender PID: %d\n", info->si_pid);
	int index = getIndex(children, info->si_pid, NUM_CHILDREN); //info->si_pid - children[0];
	if (!confirmed[index]) {
		ready_counter += 1;
		kill(info->si_pid, SIGUSR2); // Send SIGUSR2 to child (Confirm signal)
		confirmed[index] = true;
	}
}

void get_numbers() {
	for (int i = 0; i < NUM_CHILDREN - 1; i++) {
		char filename[20];
		sprintf(filename, "./txt/%d.txt", children[i]);
		numbers[i] = read_number(filename);
		printf("Child %d: %f\n", children[i], numbers[i]);
	}
}

//create a pipe using an integer array f_des[]
int create_pipe(int f_des[2]) {
	int ret = pipe(f_des);
    if (ret == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    return ret;
}
