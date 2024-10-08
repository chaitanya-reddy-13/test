#include <stdio.h>
#include <signal.h>

void handle_sigint(int sig) {
    printf("Caught SIGINT signal\n");
}

int main() {
    // Register the SIGINT handler
    signal(SIGINT, handle_sigint);

    printf("Raising SIGINT signal...\n");
    
    // Send the SIGINT signal to the current process
    raise(SIGINT);

    printf("SIGINT handled, continuing execution\n");

    return 0;
}
