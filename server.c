#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *message = "Hello from server";

    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {  // Use < 0 to check for errors
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Setting up address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Binding the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for client connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    // Accepting a client connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Reading message from client
    int valread = read(new_socket, buffer, 1024);
    if (valread < 0) {
        perror("Read failed");
    } else {
        printf("Message from client: %s\n", buffer);
    }

    // Sending message to client
    if (send(new_socket, message, strlen(message), 0) < 0) {
        perror("Send failed");
    } else {
        printf("Hello message sent\n");
    }

    // Closing the connected socket
    close(new_socket);

    // Closing the listening socket
    close(server_fd);

    return 0;
}
