#include "parent.h"

int main(int argc, char *argv[])
{
	handler_setup(SIGUSR1, &ready_to_start);
	pid_t *children = create_children(NUM_CHILDREN);
	write_range("./txt/range.txt", 1, 100);
	while (ready_counter < 5)
		pause(); // Wait until all children are ready (Note: without this line, the parent will send the signal before the children finish setting up their signal handlers)
	for (int j = 0; j < NUM_CHILDREN; ++j)
		kill(children[j], SIGUSR1); // Send SIGUSR1 to all children (Start signal)
	while (wait(NULL) > 0)
		; // Wait for all children to finish
	return 0;
}

pid_t *create_children()
{
	static pid_t children[NUM_CHILDREN]; // static so that it doesn't get destroyed when the function returns
	for (int i = 0; i < NUM_CHILDREN; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			if (execlp("./bin/child.o", "child", NULL) == -1)
			{
				perror("exec");
				exit(1);
			}
		}
		else if (pid > 0)
		{
			children[i] = pid;
		}
		else
		{
			perror("fork");
			exit(1);
		}
		pause(); // Wait for child to finish setting up its signal handler
	}
	return children;
}

void write_range(char *filename, int min, int max)
{
	// write two comma-separated integer values  in a file called range.txt
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		perror("fopen");
		exit(1);
	}
	fprintf(fp, "%d,%d", min, max);
	fclose(fp);
}

void ready_to_start(int signo, siginfo_t *info, void *context)
{
	printf("[Parent]\n");
	printf("Received signal %d\n", signo);
	printf("Sender PID: %d\n", info->si_pid);
	ready_counter += 1;
}

void handler_setup(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction sa;
	sa.sa_handler = (void (*)(int))handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(sig, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
}

// void send_message_to_the_fifth_child_using_pipe(pid_t *children)
// {
// 	// write a message to the fifth child using a pipe (PIPE)
// 	close(PIPE[0]);
// 	char *message = "Hello, child!";
// 	size_t message_length = strlen(message) + 1;
// 	write(PIPE[1], message, message_length);
// 	kill(children[NUM_CHILDREN - 1], SIGUSR2);
// }