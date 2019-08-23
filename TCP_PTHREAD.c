#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <pthread.h>

#define SERV_PORT 9877 /* port, selected by core */
#define MAXLINE 4096 /* buffer size */
#define LISTENQ 1024


typedef struct TCP_PTHREAD
{
    struct sockaddr_in addr;
    int fd;

}TPH;



void sig_chld(int sig);
void response_func(int sockfd, const struct sockaddr_in *addr);
static void *doit(void*);//线程操作

int main(void)
{
    int listen_socketfd;
    int connect_socketfd;
    TPH* tph;
    pthread_t tid;
    //pid_t pid;
    socklen_t client_len;

    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;

    /* init */
    listen_socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socketfd < 0)
    {
        fprintf(stderr,"socket fault\n");
    }
    
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    if (-1 == bind(listen_socketfd, (struct sockaddr*) &server_addr, sizeof(server_addr)))
    {
        printf("faild to bind!");
    }


    /* main */
    if (listen(listen_socketfd, LISTENQ) == -1)
    {
        fprintf(stderr, "listen error\n");
    }

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
  /////////////////////////////////////////////////////////////////////////    
        tph->addr = client_addr;
        tph->fd = connect_socketfd;  
        pthread_create(&tid, NULL, &doit, tph);
    }

    return 0;
}


static void *doit(void*arg)
{
	TPH* tph = (TPH * )arg;
    int connect_socketfd = tph->fd;
    struct sockaddr_in client_addr = tph->addr;
	pthread_detach(pthread_self());	
//////////////////////////////////////////////////////////////////////    			
	response_func(connect_socketfd, (struct sockaddr_in*) &client_addr);
	close(connect_socketfd);							
	return NULL;
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

    if (write(sockfd, ans, strlen(ans)) == -1)
    {
        fprintf(stderr, "write error\n");
    }

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