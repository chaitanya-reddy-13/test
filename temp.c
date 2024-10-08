#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigtstp(int sig) {
    sleep(3);
    printf("1111");
    printf("\nReceived SIGTSTP (Ctrl + Z). The process will be paused.\n");
    
    // The process will be stopped by the default action of SIGTSTP.
}

int main() {
    // Register the signal handler for SIGTSTP
    signal(SIGTSTP, SIG_DFL);

    printf("Process is running... Press Ctrl+Z to pause.\n");

    while (1) {
        printf("Running...\n");
        sleep(1); // Simulate ongoing work
    }

    return 0;
}
