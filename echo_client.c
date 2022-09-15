#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER 100
#define PORT 22000
#define IP_ADDRESS "127.0.0.1"
 
int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[MAX_BUFFER];
    char recvline[MAX_BUFFER];
    struct sockaddr_in servaddr;
 
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
 
    inet_pton(AF_INET, IP_ADDRESS, &(servaddr.sin_addr));
 
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 
    while(1)
    {
        bzero( sendline, MAX_BUFFER);
        bzero( recvline, MAX_BUFFER);
        fgets(sendline,MAX_BUFFER,stdin); /*stdin = 0 , for standard input */
 
        write(sockfd,sendline,strlen(sendline)+1);
        read(sockfd,recvline,MAX_BUFFER);
        printf("%s",recvline);
    }
 
}
