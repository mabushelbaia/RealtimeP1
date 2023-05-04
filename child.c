#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    // Read range.txt and generate a random number in that range
    FILE *fp;
    int min, max, random;
    fp = fopen("range.txt", "r");
    fscanf(fp, "%d %d", &min, &max);
    fclose(fp);
    random = (rand() % (max - min + 1)) + min;

    // Write the random number to a file named after the process id
    char filename[20];
    sprintf(filename, "%d.txt", getpid());
    fp = fopen(filename, "w");
    fprintf(fp, "%d", random);
    fclose(fp);

    printf("I am a child process with PID = %d\n", getpid());
    return 0;
}
