#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

// Signal handler for SIGFPE (Floating Point Exception)
void handle_sigfpe(int sig) {
    if (sig == SIGFPE) {
        printf("Signal handler called: Floating point error (Division by zero)\n");
        // Terminate the process using SIGKILL
        kill(getpid(), SIGKILL);
    }
}

// Signal handler for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("Signal handler called: SIGINT (Ctrl+C)\n");
    exit(EXIT_SUCCESS);  // Terminate the child process
}

// Signal handler for SIGUSR1 in the parent process
void handle_sigusr1(int sig) {
    printf("Parent received SIGUSR1 - terminating the process\n");
    exit(EXIT_SUCCESS);  // Terminate the parent process
}

int main() {
    pid_t p = fork();
    
    if (p > 0) { // Parent process
        // Setting up the handler for SIGUSR1
        signal(SIGUSR1, handle_sigusr1);
        wait(NULL);  // Wait for the child to complete
        printf("Parent process (PID: %d) waiting for signals\n", getpid());
        pause();  // Wait for signals indefinitely
    } 
    else if (p == 0) { // Child process
        pid_t p1 = fork();
        
        if (p1 > 0) { // Child process
            wait(NULL);  // Wait for the grandchild to complete
            // Setting up the handler for SIGINT (Ctrl+C)
            signal(SIGINT, handle_sigint);
            printf("Child process (PID: %d) waiting for Ctrl+C\n", getpid());
            while (1) {
                printf("Press CTRL+C to stop\n")
                sleep(1);  // Keep the process running until Ctrl+C is pressed
            }
        } 
        else if (p1 == 0) { // Grandchild process
            printf("In the grandchild process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            // Setting up the handler for SIGFPE (Floating Point Exception)
            signal(SIGFPE, handle_sigfpe);
            
            // Trigger a floating-point exception by dividing by zero
            int i = 10;
            int j = 0;
            i = i / j;  // This will cause a SIGFPE signal to be sent
        }
    }
    
    return 0;
}
