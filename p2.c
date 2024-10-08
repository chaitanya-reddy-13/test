#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig) {
    printf("Process 1 received SIGUSR1\n");
}

void handle_sigusr2(int sig) {
    printf("Process 1 received SIGUSR2\n");
}

int main() {
    // Register signal handlers
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    //pid_t pid = fork();

    if (pid == 0) {
        // This is the child process
        while (1) {
            sleep(2); // Wait before sending signals
            printf("Process 1 sending SIGUSR1 to parent (PID: %d)\n", getppid());
            kill(getppid(), SIGUSR1);
            sleep(2);
            printf("Process 1 sending SIGUSR2 to parent (PID: %d)\n", getppid());
            kill(getppid(), SIGUSR2);
        }
   /* } else if (pid > 0) {
        // This is the parent process
        while (1) {
            pause(); // Wait for signals
        }
    } else {
        perror("Fork failed");
        exit(1);
    }*/

    return 0;
}
