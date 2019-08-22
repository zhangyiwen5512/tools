#include <arpa/inet.h>
#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>
#include <sys/mman.h>
#include <semaphore.h>

#define MAXLINE 4096 
#define FIFOSEVER "./tmp/fifo.sever"
#define FIFOCLIENT "./tmp/fifo."
#define MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

volatile sig_atomic_t mqflag;

enum mode
{
    PIPE = 1,
    SIG = 2,
    MEN = 3,
    MESG = 4
};

typedef struct memory_t
{
    char message[20];
    int index;
    
}men_t;

sem_t *mutex;
sem_t *empty;
sem_t *full;

void sig_chld(int sig); /* handler child exit */
void sighandler(int signo, siginfo_t *info, void *ctx);

void childPipe();
void childSig();
void childMen(men_t *ptr);
void childMesg();

void fatherPipe();
void fatherSig(pid_t child[]);
void fatherMen(men_t *ptr);
void fatherMesg();

int main(int argc, const char** argv) 
{ 
    int i;
    int sw = 0;
    pid_t child[10];
    enum mode  m = atoi(argv[1]);
    if (argc != 2)
    {
        fprintf(stderr, "type 1 argument\n");
        exit(1);
    }
    
    signal(SIGCHLD, sig_chld);

    /* FIFO */
    
    /* signal */
  
    /* shared memory */
    men_t *ptr;
    
    /* message */
    
    for (i = 0; i < 10; i++)
    {   
        child[i] = fork();
        if (child[i] == 0 || child[i] == -1)
        {
            /* child */
            switch (m)
            {
                case MEN:
                    /* shared memory */
                    childMen(ptr);
                break;

                case PIPE:
                    /* pipe */
                    childPipe();
                break;

                case MESG:
                    /* message */
                    childMesg();
                break;

                default:
                    /* signal */
                    childSig();
                break;
            }
            sw = 1;
            break;
        }  
    }

    if (sw == 0)
    {
        /* father */
        switch (m)
        {
            case MEN:
                    /* shared memory */
                    fatherMen(ptr);                  
                break;

            case PIPE:
                    /* pipe */
                    fatherPipe();
                break;

            case MESG:
                    /* message */
                    fatherMesg();
                break;

            default:
                    /* signal */
                    fatherSig(child);
                break;
        }
        sleep(3);
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

void childPipe()
{
    /* father read child write */
    char file[MAXLINE];
    pid_t pid = getpid();
    snprintf(file, sizeof(file), "./tmp/fifo%d", pid);

    if ((mkfifo(file, MODE) < 0) && errno != EEXIST)
    {
        fprintf(stderr, "child mkfifo error\n");
        exit(1);
    }
   
    /* send FIFO name to father */
    int writefd = open(FIFOSEVER, O_WRONLY, 0);
    if (writefd < 0)
    {
        fprintf(stderr, "open FIFOSERVER error\n");
        exit(1);
    }

    if (write(writefd, file, strlen(file)) < 0)
    {
        fprintf(stderr, "write error\n");
        exit(1);
    }

    int readfd = open(file, O_RDONLY, 0);
    if (readfd < 0)
    {
        fprintf(stderr, "child open FIFOCLIENT error\n");
        exit(1);
    }

    /* read from father */
    int n;
    char buf[MAXLINE];
    int size = 0;
    while (1)
    {
        n = read(readfd, &buf, MAXLINE);
        if (n > 0)
        {
            printf("%s\n", buf);
            size += n;
        }
        if (errno == EINTR)
        {
            continue;
        }
        if (n < 0)
        {
            fprintf(stderr, "child read error\n");
            exit(1);
        }  
        if (size >= strlen("terminate now"))
            break;   
    }
    
    close(readfd);
    unlink(file); 
}

void childSig()
{
    sigset_t newset;
    if (sigemptyset(&newset) == -1)
    {
        fprintf(stderr, "sigemptyset error\n");
        exit(1);
    }
    if (sigaddset(&newset, SIGRTMAX) == -1)
    {
        fprintf(stderr, "sigaddset error\n");
        exit(1);
    }
    if (sigprocmask(SIG_BLOCK, &newset, NULL) == -1)
    {
        fprintf(stderr, "sigprocmask error\n");
        exit(1);
    }

    struct sigaction newact;
    struct sigaction oldact;

    newact.sa_sigaction = sighandler;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = SA_SIGINFO;//信息传递开关

    if (sigaction(SIGRTMAX, &newact, &oldact))
    {
        fprintf(stderr, "sigaction error\n");
        exit(1);
    }

    sleep(2);

    if (sigprocmask(SIG_UNBLOCK, &newset, NULL) == -1)
    {
        fprintf(stderr, "sigprocmask error\n");
        exit(1);
    }
    return;
}

void sighandler(int signo, siginfo_t *info, void *ctx)
{
    printf("child %d recvive using sig: %d\n",  getpid(), info->si_value.sival_int);
}

void childMen(men_t *ptr)
{
    int fd = shm_open("./shm", O_RDWR | O_CREAT, MODE);
    if (fd == -1)
    {
        fprintf(stderr, "shm_open error\n");
        exit(1);
    }
    if (ftruncate(fd, sizeof(men_t)) == -1)
    {
        fprintf(stderr, "ftruncate error\n");
        exit(1);
    }
    ptr = mmap(NULL, sizeof(men_t) , PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        fprintf(stderr, "mmap error\n");
        exit(1);
    }
    close(fd);
    mutex = sem_open("/mutex", O_CREAT, MODE, 1);
    if (mutex == SEM_FAILED)
    {
        fprintf(stderr, "sem_init mutex error\n");
        exit(1);
    }
    empty = sem_open("/empty", O_CREAT, MODE, 1);
    if (empty == SEM_FAILED)
    {
        fprintf(stderr, "sem_init empty error\n");
        exit(1);
    }
    full = sem_open("/full", O_CREAT, MODE, 0);
    if (full == SEM_FAILED)
    {
        fprintf(stderr, "sem_init full error\n");
        exit(1);
    }

    char mesg[20];
    if (sem_wait(full) == -1)
    {
        fprintf(stderr, "sem_wait full error\n");
        exit(1);
    }
    if (sem_wait(mutex) == -1)
    {
        fprintf(stderr, "sem_wait mutex error\n");
        exit(1);
    }
    
    memcpy(mesg, ptr->message, strlen(ptr->message));
    int i = ptr->index;

    if (sem_post(mutex) == -1)
    {
        fprintf(stderr, "sem_post mutex error\n");
        exit(1);
    }
    if (sem_post(empty) == -1)
    {
        fprintf(stderr, "sem_post empty error\n");
        exit(1);
    }
    
    printf("child %d recvive using men: %s %d\n", getpid(), mesg ,i);
    
    return ;
}

void childMesg()
{
    mqd_t mqd;

    struct mq_attr attr;
    char *buff;
    unsigned int prio;
    char name[] = "/mesg";

    mqd = mq_open(name, O_RDONLY | O_CREAT, MODE, NULL);
    if (mqd == -1)
    {
        fprintf(stderr, "mq_open error\n");
        exit(1);
    }
    
    if (mq_getattr(mqd, &attr) == -1)
    {
        fprintf(stderr, "mq_getattr error\n");
        exit(1);
    }
    buff = (char*)malloc(attr.mq_msgsize);
    if (buff == NULL)
    {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    if (mq_receive(mqd, buff, attr.mq_msgsize, &prio) == -1)
    {
        fprintf(stderr, "mq_receive error\n");
        exit(1);
    }

    printf("child %d recvive using mq: %s\n", getpid(), buff);
    free(buff);

    return;
}

void fatherPipe()
{
    /* father write child read */
    if ((mkfifo(FIFOSEVER, MODE) < 0) && errno != EEXIST)
    {
        fprintf(stderr, "father mkfifo error\n");
        exit(0);
    }
    int readfd = open(FIFOSEVER, O_RDONLY, 0);
    if (readfd < 0)
    {
        fprintf(stderr, "open FIFOSEVER error\n");
        exit(1);
    }

    int  n = 1;
    char file[MAXLINE];
    int size = 0;

    while (1)
    {     
        sleep(1);
        n = read(readfd, file, MAXLINE);
        if (n > 0)
        {
            size += n;
        }
		if (n == 0)
			break;
        if (n < 0)
        {
            fprintf(stderr, "child read error\n");
            exit(1);
        }  
        if (size >= 10 * strlen("./tmp/fifo%d"))
            break;
    }

    char filename[10][20];
    int i = 0;
    char *ptr;
    char *start = file;

    /* filename break */
    for (; i < 10; i++)
    {   
        ptr = strchr(start + 1, '.');
        if (ptr == NULL)
            break;
        memset(filename[i], 0, ptr - start + 1);
        memcpy(filename[i], start, ptr - start);
        printf("%s\n", filename[i]);
        start = ptr;
    }  
    memset(filename[i], 0, strlen(start) + 1); 
    memcpy(filename[i], start, strlen(start));
    printf("%s\n", filename[i]);

    printf("sleep 1s\n");
    sleep(1);
    char buf[MAXLINE];
    snprintf(buf, sizeof(buf), "terminate now");

    i = 0;   
    for (; i < 10; i++)
    {
        int writefd = open(filename[i], O_WRONLY, 0);
        if (writefd < 0)
        {
            fprintf(stderr, "father open writefd[%d] %d\n", i, writefd);
            exit(1);
        }
    
        if (write(writefd, buf, strlen(buf)) < 0)
        {
            fprintf(stderr, "write error\n");
            exit(1);
        }
        close(writefd);
    }
}

void fatherSig(pid_t child[])
{
    printf("father sleep 1s\n");
    sleep(1);
    union sigval val;
    
    int i = 0;
    for(;i < 10;i++)
    {
        val.sival_int = i;
        if (sigqueue(child[i], SIGRTMAX, val) == -1)
        {
            fprintf(stderr, "sigqueue error %d\n", child[i]);
            exit(1);
        }
    }
    return;  
}

void fatherMen(men_t *ptr)
{
    int fd = shm_open("./shm", O_RDWR | O_CREAT, MODE);
    if (fd == -1)
    {
        fprintf(stderr, "shm_open error\n");
        exit(1);
    }
    if (ftruncate(fd, sizeof(men_t)) == -1)
    {
        fprintf(stderr, "ftruncate error\n");
        exit(1);
    }
    ptr = mmap(NULL, sizeof(men_t) , PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        fprintf(stderr, "mmap error\n");
        exit(1);
    }
    close(fd);
    mutex = sem_open("/mutex", O_CREAT, MODE, 1);
    if (mutex == SEM_FAILED)
    {
        fprintf(stderr, "sem_init mutex error\n");
        exit(1);
    }
    empty = sem_open("/empty", O_CREAT, MODE, 1);
    if (empty == SEM_FAILED)
    {
        fprintf(stderr, "sem_init empty error\n");
        exit(1);
    }
    full = sem_open("/full", O_CREAT, MODE, 0);
    if (full == SEM_FAILED)
    {
        fprintf(stderr, "sem_init full error\n");
        exit(1);
    }


    printf("father sleep 1s\n");
    sleep(1);
    
    int i = 0;
    for (;i < 10;i++)
    {
        if (sem_wait(empty) == -1)
        {
            fprintf(stderr, "sem_wait empty error\n");
            exit(1);
        }
        if (sem_wait(mutex) == -1)
        {
            fprintf(stderr, "sem_wait mutex error\n");
            exit(1);
        }
        strcpy(ptr->message, "terminate now!");
        ptr->index = i;
        if (sem_post(mutex) == -1)
        {
            fprintf(stderr, "sem_post mutex error\n");
            exit(1);
        }   
        if (sem_post(full) == -1)
        {
            fprintf(stderr, "sem_post full error\n");
            exit(1);
        }  
    }
    return;
}

void fatherMesg()
{
    mqd_t mqd;

    char buff[] = "terminate now";
    unsigned int prio = 10;
    char name[] = "/mesg";
    int len;
    len = strlen(buff);

    mqd = mq_open(name, O_WRONLY | O_CREAT, MODE, NULL);
    if (mqd == -1)
    {
        fprintf(stderr, "mq_open error\n");
        exit(1);
    }
    
    printf("father sleep 1s\n");
    sleep(1);
    size_t i = 0;
    for (; i < 10; i++)
    {
        if (mq_send(mqd, buff, len, prio) == -1)
        {
            fprintf(stderr, "mq_send error\n");
            exit(1);
        }
    }
    
    return;
}
