#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>


#define MAXLINE 4096  
#define SERV_PORT 9877
#define LISTENQ 1024
#define max(a,b)    ((a) > (b) ? (a) : (b))


void sever_response(int listen_sockfd, int connect_sockfd, int udp_sockfd,\
                    const struct sockaddr_in *server_addr, const struct sockaddr_in *client_addr);

void sig_chld(int sig);

int main(int argc, char const *argv[])
{
    int listen_sockfd;
    int connect_sockfd;
    int udp_sockfd;
    const int on = 1;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;


    /* tcp init */         
    listen_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    /* allow reuse sockaddr */
    setsockopt(listen_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    bind(listen_sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    /* udp init */
    udp_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    bind(udp_sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));


    sever_response(listen_sockfd, connect_sockfd, udp_sockfd,\
                   (struct sockaddr *) &server_addr, (struct sockaddr_in *) &client_addr);


    return 0;
}


void sever_response(int listen_sockfd, int connect_sockfd, int udp_sockfd,\
                    const struct sockaddr_in *server_addr, const struct sockaddr_in *client_addr)
{
    int len;
    int maxfdp1;
    int nready;
    int n;
    pid_t pid;
    fd_set rset;

    
    char recvbuf[MAXLINE];
    char sendbuf[MAXLINE];
    char sin_addr [16];
    uint16_t port_num ;
   
    listen(listen_sockfd, LISTENQ);

    signal(SIGCHLD, sig_chld);
    FD_ZERO(&rset);
    maxfdp1 = max(listen_sockfd, udp_sockfd) + 1;


    for(;;)
    {
        FD_SET(listen_sockfd, &rset);
        FD_SET(udp_sockfd, &rset);

        if (select(maxfdp1, &rset, NULL, NULL, NULL) < 0)
        {
            if (errno == EINTR)
                continue;
            else
            {
                fprintf(stderr, "select error");
                exit(1);
            }   
        }


        /* tcp can read */
        if (FD_ISSET(listen_sockfd, &rset))
        {
            len = sizeof(client_addr);
            connect_sockfd = accept(listen_sockfd, (struct sockaddr *) &client_addr, &len);

            if (connect_sockfd < 0)
            {
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    sprintf(stderr, "accept error");
                    exit(0);
                }           
            }

            if ((pid = fork()) == 0)
            {
                close(listen_sockfd);
                /*  */
                for(;;)
                {
                    
                    write(connect_sockfd, sendbuf, strlen(sendbuf));
              
                    n = read(connect_sockfd, recvbuf, MAXLINE);
                    if (n > 0)
                    {
                        printf("message from tcp:\n");
                        printf("%s", recvbuf);
                    }
                }    
                /*  */   
                exit(0);
            }

            close(connect_sockfd);
        }

        /* udp can read */
         if (FD_ISSET(udp_sockfd, &rset))
        {
            len = sizeof(client_addr);
            n = recvfrom(udp_sockfd, recvbuf, MAXLINE, 0, (struct sockaddr *) &client_addr, &len);
            if (n > 0)
            {
                printf("message from udp:\n");
                printf("%s", recvbuf); 
            }
                
            
            inet_ntop(AF_INET, &server_addr->sin_addr, sin_addr, sizeof(sin_addr));
            port_num = ntohs(server_addr->sin_port);

            sprintf(sendbuf, "Hellow zhangyw (%s, %u), You're welcome!\n", sin_addr, port_num);
               
            sendto(udp_sockfd, sendbuf, strlen(sendbuf), 0, (struct sockaddr *) &client_addr, len);
        }
    }
}


void sig_chld(int sig)
{
    pid_t pid;
    int stat;
    
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("child %d ternimated\n", pid);
    }

    return;
}