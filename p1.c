#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
    int server_fd, new_socket;
    struct sockarr_in address;
    int opt=1;
    int addrelen=sizeof(address);
    char *message="Hello from server";
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<0){
        perror("Socket failed");

    }
    address.sin_family=AF_INET;
    address.sin_addt.s_addr=INADDR_ANY;
    address.sin_port=htons(8080);
    if(bind(server_fd,&address,sizeof(address))<0){
        perror("Bind failed");
        close(server_fd);
    }
    if(listen(serever_fd,3)<0){
        perror("Listen failed");
        close(serve_fd);

    }
    new_socket=accept(server_fd,&address,(socklen_t*)&addrlen);
    if(new_socket<0){
        perror("Accepte failed");
        close(server_fd);
    }
   int valread=read(new_socket,buffer,1024);
   printf("Message from client",buffer);
   if(send(new_socket,message,strlen(message),0)>=0){
    printf("Hello message sent\n");
   }
   close(new_socket);
   close(srver_fd);
    
}