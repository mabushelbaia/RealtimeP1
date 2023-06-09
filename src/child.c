#include "child.h"

volatile sig_atomic_t confirmed_f = false;
int main(int argc, char *argv[]) {
    #ifdef CLI
    printf("[%d] Child %s process started\n", getpid(), argv[0]);
    #endif
	if (strcmp(argv[0], "4") == 0) {
        //printf("[%d] Coprocessor child process started\n", getpid());
        fd1 = atoi(argv[1]);
        fd2 = atoi(argv[2]);
        #ifdef CLI
        printf("[%d] Pipe1 file descriptor: %d\n", getpid(), fd1);
        printf("[%d] Pipe2 file descriptor: %d\n", getpid(), fd2);
        #endif
        handler_setup(SIGUSR1, &coprocessor);
	}
	else {
    	//printf("[%d] Child process started\n", getpid());
    	handler_setup(SIGUSR1, &start);
    	handler_setup(SIGUSR2, &confirmed);
	}
    while(true) pause();
    return 0;
}
void confirmed(int sig, siginfo_t *info, void *context) {
    confirmed_f = true;
    #ifdef CLI
    printf("[%d] Received confirmation signal\n", getpid());
    #endif
}

void start(int sig, siginfo_t *info, void *context) {
    #ifdef CLI
    printf("[%d] Received starting signal\n", getpid());
    #endif
    srand(getpid() * time(NULL));
    int min, max;
    read_range("./txt/range.txt", &min, &max);
    write_random_float_number(getpid(), min, max);
    while (!confirmed_f) {
        kill(getppid(), SIGUSR1);
        usleep(100000); // 100ms
    }
    confirmed_f = false;
}

void coprocessor(int sig, siginfo_t *info, void *context) {
    char buffer[100];
    read(fd1, buffer, 100);
    #ifdef CLI
    printf("[%d] Received message: %s\n", getpid(), buffer);
    #endif
    char* token = strtok(buffer, ",");
    float SUM1 = atof(token);
    token = strtok(NULL, ",");
    SUM1 += atof(token);
    token = strtok(NULL, ",");
    float SUM2 = atof(token);
    token = strtok(NULL, ",");
    SUM2 += atof(token);
    #ifdef CLI
    printf("sum1: %f, sum2: %f\n", SUM1, SUM2);
    #endif
    sprintf(buffer, "%f,%f", SUM1, SUM2);
    write(fd2, buffer, 100);
    #ifdef CLI
    printf("[%d] Sent message: %s\n", getpid(), buffer);
    #endif
    kill(getppid(), SIGWINCH);
}
