#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
int main() {
int sock = 0;
struct sockaddr_in serv_addr;
char *message = "Hello from client";
char buffer[1024] = {0};
// Creating socket
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0) {
printf("\n Socket creation error \n");
return -1;
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(8080);
// Convert IPv4 address from text to binary form
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
// Connect to server
connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
send(sock, message, strlen(message), 0);
printf("Hello message sent\n");
read(sock, buffer, 1024);
printf("Message from server: %s\n", buffer);
close(sock);
return 0;
}