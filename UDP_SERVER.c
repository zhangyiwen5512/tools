#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

#define SERV_PORT 9877 /* port, selected by core */
#define MAXLINE 4096 /* buffer size */
#define max(a,b)    ((a) > (b) ? (a):(b))


void anser_once(int sockfd, const struct sockaddr_in *addr, socklen_t sock_len);
void response_func(int sockfd, const struct sockaddr *addr, socklen_t sock_len);


int main() {

    int sockfd;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;

    

    /* init */
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);


    
    if (-1 == bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)))
    {
        fprintf(stderr, "faild to bind!");
        exit(1);
    }


    /* main */
    
   
    for(;;)
    {       
        //anser_once(sockfd, (struct sockaddr_in*) &client_addr, sizeof(client_addr));
        response_func(sockfd, (struct sockaddr*) &client_addr, sizeof(client_addr));
        
    }
    
    return 0;
}

void anser_once(int sockfd, const struct sockaddr_in *addr, socklen_t sock_len)
{
    char buf[MAXLINE] ;
    char sin_addr [16];
    uint16_t port_num ;

    inet_ntop(AF_INET, &addr->sin_addr, sin_addr, sizeof(sin_addr));
    port_num = htons(addr->sin_port);
    sprintf(buf, "Hellow zhangyw (%s, %u) You're welcome!\n", sin_addr, port_num);


    socklen_t len = sizeof(addr);
    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) &addr, len);  
}




void response_func(int sockfd, const struct sockaddr *addr, socklen_t sock_len)
{
    socklen_t len;
    int n;
    char buf[MAXLINE];
    
	len = sock_len;
	n = recvfrom(sockfd, buf, MAXLINE, 0,(struct sockaddr*) &addr, &len);					
    if (n > 0)
    {
        printf("%s", buf);
    } 
        
}