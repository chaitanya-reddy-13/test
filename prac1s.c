#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8080
#define MAX_BUFFER 1024
#define PACKET_LOSS_PROBABILITY 20
int socketProb(){
    int randvalue=rand()%100;
    return (randvalue<PACKET_LOSS_PROBABILITY);
}
int main(){
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    char buffer[1024]={0};
    char ack[10]="ack";
    char cack[10]="cack";
    srand(time(0));
    server_fd=socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<=0){
        perror("Socket failed");
    }
    address.sin_family=AF_INET:
    address.sin_addr.s_addr=INADDR_ANY:
    address.sin_port=htons(PORT);
    if(bind(serevr_fd,(struct sockadd*)&address,sizeof(address))<0){
        perror("Bind failed");
    }
    if(listen(server_fd,0)<0){
        perror("listen failed");
    }
    printf("Server is listening from the port %d",PORT);
    if(new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t)&addrlen)<0){
        perror("Accept failed");
    }
    int packetnumber=1;
    while(1){
        memset(buffer,0,1024);
        int val=read(new_socket,buffer,1024);
        if(val<=0){
            perror("read failed");
        }
        printf("Revied packet %d : %s",packetnumber,buffer);
        if(socketProb()){
            int corrupt=rand()%2;
            if(corrupt==0){
                printf("Packet lost\n")
            }
            else{
                printf("Packet %d corrupted. Sending corrupted ACK...\n", packetNumber);
                send(new_socket,cack,strlen(cack),0);
            }

        }
        else{
            printf("Packet %d received successfully. Sending ACK...\n", packetNumber);
            send(new_socket,ack,strlen(ack),0);
        }
        packetnumber++;

        
    }
    close(server_fd);
    close(new_socket);
    return 0;

}