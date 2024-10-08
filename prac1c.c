#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#include <time.h>
#define PORT 8080
#define MAX_BUFFER 1024
#define TIMEOUT 3
int main(){
    int sock;
    struct sockadd_in serv_addr;
    char buffer[1024]={0};
    char ack[1024]={0};
    srand(time(0));
    sock=socket(AF_INET,SOCK_STREAM,0);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<0){
        return -1;
    }
    int totalpackets,packetnumber=1;
    if(connect(sock,&serv_addr,sizeof(serv_addr))<0){
        return -1;
    }
    scanf("Enter total number of packets\n");
    while(packetnumber<=totalpackets){
        snprintf(buffer, MAX_BUFFER, "Packet %d", packetNumber);
        printf("\nSending packet %d: %s\n", packetNumber, buffer);
        send(sock,buffer,sizeof(buffer),0);
        fd_set readfds;
        int retval;
        struct timeval tv;
        tv.tv_sec=TIMEOUT;
        tv.tv_usec=0;
        FD_ZERO(&readfds);
        FD_SET(sock,&readfds);
        retval=select(sock+1,readfds,NULL,NULL,&tv);
        if (retval == -1) {
            perror("select() error");
            close(sock);
            return -1;
        }
        else if(retval==0){
            printf("Timeout, retransmitting %d...\n",packetnumber);
        } 
        else{
            
        }

    }

}