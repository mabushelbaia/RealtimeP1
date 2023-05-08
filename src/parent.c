#include "parent.h"


int main(int argc, char *argv[]) {
	create_pipe(fd1);
	create_pipe(fd2);
	handler_setup(SIGUSR1, &child_confirmations);
	create_children(fd1, fd2);
	close(fd1[0]);
	close(fd2[1]);
	sleep(1); // Wait for children to finish setting up their signal handlers
	write_range("./txt/range.txt", 1, 100);
	// Send SIGUSR1 to all children (Start signal)
	for (int j=0; j < NUM_CHILDREN - 1; ++j) kill(children[j], SIGUSR1);
	// Wait for all children to send SIGUSR1 (Confirm signal)
	while(ready_counter < NUM_CHILDREN - 1) pause();
	char buffer[100];
	get_numbers(buffer);
	send_message(fd1[1], buffer);
	sleep(1);
	kill(children[4], SIGUSR1);
	handler_setup(SIGWINCH, &judge);
	pause(); // Wait for coprocessor signal
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
			if (i == 4) {
				close(fd1[1]);
				close(fd2[0]);
			}
			char arg[10];
			int fd1_arg[20];
			int fd2_arg[20];
			sprintf(arg, "%d", i);
			sprintf(fd1_arg, "%d", fd1[0]);
			sprintf(fd2_arg, "%d", fd2[1]);
			if (execlp("./bin/child.o", arg, fd1_arg, fd2_arg, NULL) == -1)
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
	}
}

void child_confirmations(int signo, siginfo_t *info, void *context) {
	#ifdef CLI
	printf("[Parent]\n");
    printf("Received signal %d\n", signo);
    printf("Sender PID: %d\n", info->si_pid);
	#endif
	int index = getIndex(children, info->si_pid, NUM_CHILDREN); //info->si_pid - children[0];
	if (!confirmed[index]) {
		ready_counter += 1;
		kill(info->si_pid, SIGUSR2); // Send SIGUSR2 to child (Confirm signal)
		confirmed[index] = true;
	}
}

void get_numbers(char* buffer) {
    for (int i = 0; i < NUM_CHILDREN - 1; i++) {
        char filename[20];
        sprintf(filename, "./txt/%d.txt", children[i]);
        numbers[i] = read_number(filename);
        printf("Child %d: %f\n", children[i], numbers[i]);
        if (i == 0) {
            sprintf(buffer, "%f", numbers[i]);
        } else {
            sprintf(buffer, "%s,%f", buffer, numbers[i]);
        }
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

int send_message(int fd, char *message) {
    ssize_t bytes_written = write(fd, message, strlen(message));
	printf("Message sent: %s\n", message);
    if (bytes_written == -1) {
        perror("write");
        return -1;
    }
    return 0;
}

void judge(int signo, siginfo_t *info, void *context) {
	float sum1, sum2;
	char buffer[100];
	read(fd2[0], buffer, 100);
    char* token = strtok(buffer, ",");
    float SUM1 = atof(token);
    token = strtok(NULL, ",");
    float SUM2 = atof(token);
	printf("SUM1: %f\n", SUM1);
	printf("SUM2: %f\n", SUM2);
	if (SUM1 > SUM2) {
		printf("Winner: team 1\n");
	} else if (SUM1 < SUM2) {
		printf("Winner: team 2\n");
	} else {
		printf("Tie\n");
	}
}
