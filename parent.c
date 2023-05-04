#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	pid_t children[5];
	for (int i = 0; i < 5; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			if(execlp("./child.o", NULL) == -1) {
				perror("exec");
				exit(1);
			}
		} else if (pid > 0) {
			children[i] = pid;
		} else {
			perror("fork");
			exit(1);
		}
	}
	for (int j = 0; j < 5; j++) {
		printf("[child] %d\n", children[j]);
	}

	//write two comma-separated integer values  in a file called range.txt
	FILE *fp = fopen("range.txt", "w");
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}
	fprintf(fp, "%d,%d", children[0], children[4]);
	fclose(fp);

	return 0;
}
