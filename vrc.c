#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    char data[100];
    printf("Enter data to be transimitted\n");
    scanf("%s",data);
    int pt=0;;
    for(int i=0;i<strlen(data);i++){
        pt=(pt^(data[i]-'0'));
    }
    char trans[100];
    trans[0]=pt+'0';
    for(int i=0;i<strlen(data);i++){
        trans[i+1]=data[i];
    }
    trans[strlen(data)+1]='\0';
    printf("Data including parity\n%s\n",trans);
    char rec[100];
    printf("Enter data recieved\n");
    scanf("%s",rec);
    int x=0;
    for(int i=0;i<strlen(rec);i++){
        x=(x^(rec[i]-'0'));
    }
    if(x==0){
        printf("\nNO error\n");
    }
    else{
        printf("\nError\n");
    }
}