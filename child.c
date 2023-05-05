#include "child.h"
int main(int argc, char *argv[])
{
    struct sigaction sa;
    sa.sa_handler = &start;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    printf("I sent a signal %d to my parent and got %d as a response\n", SIGUSR1, kill(getppid(), SIGUSR1));
    pause();
    return 0;
}

void start(int sig)
{
    printf("Received starting signal [%d]\n", sig);
    int min, max;
    read_range("range.txt", &min, &max);
    float number = generate_random_float_number(min, max);
    write_random_float_number(number);
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

float generate_random_float_number(int min, int max)
{
    srand(time(NULL) + getpid());
    return (float)rand() / (float)(RAND_MAX / max);
}

void write_random_float_number(float number)
{
    char filename[20];
    sprintf(filename, "child_%d.txt", getpid());
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fprintf(fp, "%f", number);
    fclose(fp);
}