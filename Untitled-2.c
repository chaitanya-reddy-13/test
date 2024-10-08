// G.Chaitanya Reddy CS22B1052
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main() {
    int pipefds[2];
    int returnstatus;
    pid_t pid;
    char writemessage[20];
    char readmessage[20];

    // Create pipe
    returnstatus = pipe(pipefds);
    if (returnstatus == -1) {
        printf("Unable to create pipe\n");
        return 1;
    }

    // Fork the process
    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid > 0) { // Parent process
        // Get message from user input
        printf("Parent Process: Enter a message to write to the pipe: ");
        scanf("%s", writemessage);

        // Write to the pipe
        close(pipefds[0]); // Close the read end
        write(pipefds[1], writemessage, strlen(writemessage) + 1);
        close(pipefds[1]); // Close the write end

        // Wait for child process to finish
        wait(NULL);
    }
    else if (pid == 0) { // Child process
        // Read from the pipe
        close(pipefds[1]); // Close the write end
        read(pipefds[0], readmessage, sizeof(readmessage));
        close(pipefds[0]); // Close the read end

        // Display the message
        printf("Child Process: Reading from pipe: %s\n", readmessage);
    }

    return 0;
}

/* 
Analysis:

1. If `close(pipefds[1])` is removed in the child process:
   - The child won't close the write end of the pipe. In this case, reading from the pipe will still function, but it could cause issues in a more complex scenario where further communication is needed.

2. If `close(pipefds[0])` is removed in the parent process:
   - The parent will not close the read end of the pipe. This may not impact writing, but it could lead to resource management problems, especially if the pipe is used further.

3. Closing both ends before reading or writing:
   - If both the read and write ends are closed before performing operations, the pipe will be created, but attempting to read or write will result in errors. Specifically:
     - Write operations will fail due to a bad file descriptor error.
     - Read operations will also return an error due to the same issue.

4. Reading and writing on the same pipe in the same process:
   - Performing both reading and writing in the same process without proper end management can result in unexpected behaviors, such as reading back what was written if the buffer still contains data.

5. Writing multiple times without reading:
   - If you write to the pipe repeatedly without reading, the buffer could overflow. Pipes have a limited buffer size, and when it's full, writing will be blocked until space becomes available by reading.

6. Other scenarios:
   - Buffer overflow: If too much data is written, the write will block until data is read from the pipe.
   - Blocking operations: In blocking mode, write operations pause if the buffer is full, and reads block if there's no data.
   - Interrupted system calls: Signals can interrupt reads or writes, resulting in system call failures.
*/
