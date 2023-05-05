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
    FILE *fp = fopen("range.txt", "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fscanf(fp, "%d,%d", &min, &max);
    fclose(fp);
    srand(time(NULL) + getpid());
    //generate a random float number between min and max
    float random_number = (float)rand()/(float)(RAND_MAX/max);
    char filename[20];
    sprintf(filename, "%d.txt", getpid());
    fp = fopen(filename, "w");
    fprintf(fp, "%f", random_number);
    fclose(fp);

    printf("Child %d: %f\n", getpid(), random_number);
}
