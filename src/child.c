#include "child.h"

int main(int argc, char *argv[]) {
    handler_setup(SIGUSR1, &start);
    kill(getppid(), SIGUSR1); // Send SIGUSR1 to parent (Ready signal)
    pause();
    return 0;
}

void start(int sig, siginfo_t *info, void *context) {
    printf("[%d] Received starting signal\n", getpid());
    int min, max;
    read_range("./txt/range.txt", &min, &max);
    float number = generate_random_float_number(min, max);
    write_random_float_number(getpid(), number);
}
void read_range(char *filename, int *min, int *max)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fscanf(fp, "%d,%d", min, max);
    fclose(fp);
}


float generate_random_float_number(int min, int max){
    srand(time(NULL) + getpid());
    return (float)rand() / (float)(RAND_MAX / max);
}

void handler_setup(int sig, void (*handler)(int, siginfo_t *, void *)) {
	struct sigaction sa;
	sa.sa_handler = (void (*)(int)) handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(sig, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
}

void write_random_float_number(int pid, float number) {
    char filename[20];
    sprintf(filename, "./txt/%d.txt", pid);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fprintf(fp, "%f", number);
    fclose(fp);
}