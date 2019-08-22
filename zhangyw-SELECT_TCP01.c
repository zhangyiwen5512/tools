#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/select.h>


#define SERV_PORT 9877
#define MAXLINE 4096
#define max(a,b)    ((a) > (b) ? (a) : (b))


void client_func(int sockfd, const struct sockaddr_in *addr);


int main(int argc, char **argv) {
    
    int sockfd;
    struct sockaddr_in addr;

    if (argc != 2)
    {
        fprintf(stderr, "type <IPaddress>");
        exit(1);
    }

    /* init */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = SERV_PORT;
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    //connect(sockfd, (struct sockaddr*) &addr, sizeof(addr));

    client_func(sockfd, (struct sockaddr_in*) &addr);
    fprintf(stderr, "close");
    
    close(sockfd);
    fprintf(stderr, "close");
    return 0;
}


void client_func(int sockfd, const struct sockaddr_in *addr)
{

    int maxfd_plus1;
    int stdin_eof;
    int n;
    fd_set readset;
    fd_set writeset;

    char sendbuf[MAXLINE];
    char recvbuf[MAXLINE];
    char sin_addr [16];
    uint16_t port_num ;

    /* init */
    stdin_eof = 0; 
    FD_ZERO(&readset);
    FD_ZERO(&writeset);

    inet_ntop(AF_INET, &addr->sin_addr, sin_addr, sizeof(sin_addr));
    port_num = htons(addr->sin_port);
    sprintf(sendbuf, "This is zhangyw (%s, %u)\n", sin_addr, port_num);


    for(;;)
    {
        connect(sockfd, (struct sockaddr*) &addr, sizeof(addr));
        
        /* if allow, add a descriptor to read in*/
        FD_SET(sockfd, &readset);
        FD_SET(sockfd, &writeset);
        

        maxfd_plus1 = sockfd + 1;
        select(maxfd_plus1, &readset, &writeset, NULL, NULL);

        /* socket buffer can write */
        if (FD_ISSET(sockfd, &writeset))
        {
            //////////////////////////////////////////
            write(sockfd, sendbuf, strlen(sendbuf));
            sleep(1);
            fprintf(stderr, "writeset");
        }


        /* socket buffer can read */
        if (FD_ISSET(sockfd, &readset))
        {
            fprintf(stderr, "readset");

            n = read(sockfd, recvbuf, MAXLINE);
            if (n > 0)
            {
                printf("%s", recvbuf);
                fprintf(stderr, "out2\n");
            }
            else if (n == 0)
            {  
                if (stdin_eof == 1)
                {
                    fprintf(stderr, "out4");
                    return;
                }
                else
                {
                    fprintf(stderr, "server ternimated");
                    exit(1);
                }             
            }
            else
            {
                fprintf(stderr, "out3\n");
                continue;
            }   
        }
    }
}
