#include "local.h"

void handler_setup(int sig, void (*handler)(int, siginfo_t *, void *)) {
	struct sigaction sa;
	sa.sa_handler = (void (*)(int)) handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(sig, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
}

int getIndex(int *array, int value, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

float read_number(char *filename)
{
	// read a float value from a file called <pid>.txt
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("fopen");
		exit(1);
	}
	float number;
	fscanf(fp, "%f", &number);
	fclose(fp);
	return number;
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

void write_random_float_number(int pid, int min, int max) {
    srand(time(NULL) + getpid());
    float number = (float)rand() / (float)(RAND_MAX / max);
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

void read_range(char *, int *, int *);
void write_random_float_number(int pid,int min,int max);
