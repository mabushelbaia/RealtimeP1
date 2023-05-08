#include "child.h"

volatile sig_atomic_t confirmed_f = false;
int main(int argc, char *argv[]) {
    printf("[%d] Child %s process started\n", getpid(), argv[0]);
	if (strcmp(argv[0], "4") == 0) {
        //printf("[%d] Coprocessor child process started\n", getpid());
        fd1 = atoi(argv[1]);
        fd2 = atoi(argv[2]);
        printf("[%d] Pipe1 file descriptor: %d\n", getpid(), fd1);
        printf("[%d] Pipe2 file descriptor: %d\n", getpid(), fd2);
        handler_setup(SIGUSR1, &coprocessor);
	}
	else {
    	//printf("[%d] Child process started\n", getpid());
    	handler_setup(SIGUSR1, &start);
    	handler_setup(SIGUSR2, &confirmed);
	}
    pause();
    return 0;
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

void coprocessor(int sig, siginfo_t *info, void *context) {
    char buffer[100];
    read(fd1, buffer, 100);
    printf("[%d] Received message: %s\n", getpid(), buffer);
    char* token = strtok(buffer, ",");
    float SUM1 = atof(token);
    token = strtok(NULL, ",");
    SUM1 += atof(token);
    token = strtok(NULL, ",");
    float SUM2 = atof(token);
    token = strtok(NULL, ",");
    SUM2 += atof(token);
    printf("sum1: %f, sum2: %f\n", SUM1, SUM2);
    sprintf(buffer, "%f,%f", SUM1, SUM2);
    write(fd2, buffer, 100);
    printf("[%d] Sent message: %s\n", getpid(), buffer);
    kill(getppid(), SIGWINCH);
}
