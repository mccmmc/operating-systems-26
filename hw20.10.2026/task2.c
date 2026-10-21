#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int first_sigint = 1;

void sigint_handler(int signum) {
    if (first_sigint) {
        printf("\nInterrupted!\n");
        first_sigint = 0;
    } else {
        signal(SIGINT, SIG_DFL);
        raise(SIGINT);
    }
}

void sigalrm_handler(int signum) {
    printf("\nChild process (PID: %d) received SIGALRM. Terminating...\n", getpid());
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);

    pid_t pid = fork();

    if (pid == 0) {
        signal(SIGALRM, sigalrm_handler);

        alarm(3);

        while (1) {
            printf("Hello world! (Child PID: %d)\n", getpid());
            sleep(1);
        }
    } else if (pid > 0) {
        wait(NULL);
        printf("Parent: Child process finished.\n");
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}
