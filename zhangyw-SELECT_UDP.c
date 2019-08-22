#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/select.h>


#define SERV_PORT 9877
#define MAXLINE 4096


void client_func(int sockfd, const struct sockaddr_in *addr, socklen_t len_t);


int main(int argc, char **argv) {
    
    int sockfd;
    struct	sockaddr_in addr;

    if (argc != 2)
    {
        fprintf(stderr, "type <IPaddress>");
        exit(1);
    }
    
    /* init */
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &addr.sin_addr);


    client_func(sockfd, (struct sockaddr_in*) &addr, sizeof(addr));

    return 0;
}


void client_func(int sockfd, const struct sockaddr_in *addr, socklen_t len_t)
{

    int maxfd_plus1;
    int n;
    fd_set readset;
    fd_set writeset;
    int m = 0;

    char sendbuf[MAXLINE];
    char recvbuf[MAXLINE];
    char sin_addr [16];
    uint16_t port_num ;

    /* init */
    FD_ZERO(&writeset);
    FD_ZERO(&readset);
    
    connect(sockfd, (struct sockaddr*) & addr, sizeof(addr));
    

    // inet_ntop(AF_INET, &addr->sin_addr, sin_addr, sizeof(sin_addr));
    // port_num = htons(addr->sin_port);
    // sprintf(sendbuf, "This is zhangyw (%s, %u)\n", sin_addr, port_num);



    for (;;)
    {   
        /* set descriptors */
        FD_SET(sockfd, &readset);
        FD_SET(sockfd, &writeset);

        maxfd_plus1 = sockfd + 1;
        select(maxfd_plus1, &readset, &writeset, NULL, NULL);

        /* socket buffer can write */
        if (FD_ISSET(sockfd, &writeset))
        {
            
            sendto(sockfd, sendbuf, strlen(sendbuf), 0, (struct sockaddr*)addr, len_t);

            


            sleep(1);
            // write(sockfd, sendbuf, strlen(sendbuf));
            // sleep(1);
        }

        /* socket buffer can read */
        if (FD_ISSET(sockfd, &readset) && m == 0)
        {
            socklen_t len;
            len = len_t;
            struct sockaddr_in recvser;
            n = recvfrom(sockfd, recvbuf, MAXLINE, 0, (struct sockaddr*)&recvser, &len);

            inet_ntop(AF_INET, &recvser.sin_addr, sin_addr, sizeof(sin_addr));
            port_num = htons(recvser.sin_port);
            sprintf(sendbuf, "This is zhangyw (%s, %u)\n", sin_addr, port_num);

            // n = read(sockfd, recvbuf, MAXLINE);
            if (n > 0)
                printf("%s", recvbuf); 

            ++m;
        }
    }
}
