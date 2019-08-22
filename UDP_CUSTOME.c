#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>

#define SERV_PORT   9877 /* port, selected by core */
#define MAXLINE 4096 /* buffer size */

void client_func(int sockfd, const struct sockaddr *addr, socklen_t sock_len, char sendbuf[]);


int main(int argc, char **argv)
{
    
    if (2 != argc)
    {
        printf("type <IPaddress>");
        return -1;
    }

    int sockfd;
    struct sockaddr_in addr;

    char buf[MAXLINE] ;
    char sin_addr [16];
    uint16_t port_num ;

    /* init */
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &addr.sin_addr);
    
    inet_ntop(AF_INET, &addr.sin_addr, sin_addr, sizeof(sin_addr));
    port_num = htons(addr.sin_port);
    sprintf(buf, "This is zhangyw (%s, %u)\n", sin_addr, port_num);

    client_func(sockfd, (struct sockaddr*) &addr, sizeof(addr), &buf);

    return 0;
}


void client_func(int sockfd, const struct sockaddr *addr, socklen_t sock_len, char sendbuf[])
{
    socklen_t len;
    for(;;)
    { 
        sendto(sockfd, sendbuf, strlen(sendbuf), 0, addr, sock_len);
        sleep(1);
    }
}


