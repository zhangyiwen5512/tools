#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define SERV_PORT 9877 /* port, selected by core */
#define MAXLINE 4096 /* buffer size */
#define LISTENQ 1024

void sig_chld(int sig);
void response_func(int sockfd, const struct sockaddr_in *addr);


int main(void)
{
    int listen_socketfd;
    int connect_socketfd;
    pid_t pid;
    socklen_t client_len;

    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;

    /* init */
    listen_socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    if (-1 == bind(listen_socketfd, (struct sockaddr_in*) &server_addr, sizeof(server_addr)))
    {
        printf("faild to bind!");
    }


    /* main */
    listen(listen_socketfd, LISTENQ);
    signal(SIGCHLD, sig_chld);

    /* main loop */
    for (;;)
    {
        client_len = sizeof(client_addr);
        connect_socketfd = accept(listen_socketfd, (struct sockaddr*) &client_addr, &client_len);
        if (connect_socketfd < 0)
        {
            if (errno == EINTR)
            {   
                continue; /* restart the loop */
            } 
            else
            {
                printf("accept error");
                exit(1);
            }       
        }
        
        pid = fork();
        if (0 == pid)
        {
            close(listen_socketfd);
            response_func(connect_socketfd, (struct sockaddr_in*) &client_addr);
            exit(0);
        }
        close(connect_socketfd);
        
    }

    return 0;
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

void response_func(int sockfd, const struct sockaddr_in *addr)
{
    ssize_t n;
    char buf[MAXLINE];
    char ans[MAXLINE] = "Hellow zhangyw(";
    char sin_addr [16];
    uint16_t port_num ;
    inet_ntop(AF_INET, &addr->sin_addr, sin_addr, sizeof(sin_addr));
    port_num = htons(addr->sin_port);

    sprintf(ans, "Hellow zhangyw (%s, %u), You're welcome!\n", sin_addr, port_num);

    write(sockfd, ans, strlen(ans));

    for ( ; ; )
    {
        while ((n = read(sockfd,buf,MAXLINE)) > 0)
        {
            printf("%s", buf);
        }
        if (n < 0 && errno == EINTR)
        {
            continue;
        }
        else if (n < 0)
        {
            printf("read error");
            exit(1);
        }
        break;
    }
      
}