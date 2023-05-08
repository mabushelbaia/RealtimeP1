#include "child.h"

volatile sig_atomic_t confirmed_f = false;
int main(int argc, char *argv[]) {
    #ifdef CLI
    printf("[%d] Child process started\n", getpid());
    #endif
    srand(getpid() * time(NULL));
    handler_setup(SIGUSR1, &start);
    handler_setup(SIGUSR2, &confirmed);
    #ifdef DEBUG
    sleep(20);
    #endif
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
