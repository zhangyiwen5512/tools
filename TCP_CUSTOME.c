#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SERV_PORT 9877 /* port:0, selected by core */
#define MAXLINE 4096 /* buffer size*/

void client_func(int sockfd, const struct sockaddr_in *addr);


int main(int argc, char **argv) {

    if (argc != 2)
    {
        printf("type <IPaddress>");
        return -1;
    }

    int socketfd;
    struct sockaddr_in addr;


    /* init */
    socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (1 != inet_pton(AF_INET, argv[1], &addr.sin_addr))
    {
        printf("not a valid format!");
    }
    addr.sin_port = htons(SERV_PORT);

    /* mian */
    connect(socketfd, (struct sockaddr*) &addr, sizeof(addr));


    client_func(socketfd, (struct sockaddr_in*) &addr);


    return 0;
}

void client_func(int sockfd, const struct sockaddr_in *addr)
{
    char sendbuf[MAXLINE] ;
    char recvbuf[MAXLINE];
    char sin_addr [16];
    uint16_t port_num ;
    ssize_t n;
    inet_ntop(AF_INET, &addr->sin_addr, sin_addr, sizeof(sin_addr));
    port_num = htons(addr->sin_port);
  
    sprintf(sendbuf, "This is zhangyw (%s, %u)\n", sin_addr, port_num);
    if ((n = read(sockfd, recvbuf ,MAXLINE)) > 0)
    {
        printf("%s", recvbuf);
    }    
    for(;;)
    {
        write(sockfd, sendbuf, strlen(sendbuf));        
        sleep(1);    
    }
}