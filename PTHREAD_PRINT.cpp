#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;

#define THREADNUMBER 10
#define MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

//#define SEM
//#define MUTEX
#define COND

#ifdef SEM
sem_t* sem;
#endif // SEM
#ifdef MUTEX
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif // MUTEX
#ifdef COND
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;
#endif // COND

int source = 0;

void *thread_main(void *argc);
void writein(FILE *out, int *index);
void *thread_wirte(void *argc);

int main(int argc, char const *argv[])
{
    pthread_t tid;

    if (pthread_create(&tid, NULL, thread_main, NULL) != 0)
    {
        fprintf(stderr, "create main thread failed\n");
	    pthread_exit((void *)1);
    }

    if (pthread_join(tid, NULL) != 0)
    {
        fprintf(stderr, "main end fail\n");
	    pthread_exit((void *)1);
    }
    
    return 0;
}


void *thread_main(void * argc)
{   
#ifdef SEM
    printf("using SEM\n");
    sem = sem_open("/sem", O_CREAT, MODE, 0);
    if (sem == SEM_FAILED)
    {
        fprintf(stderr, "sem_init mutex error\n");
        exit(1);
    }
    sem_post(sem);

#endif // SEM
#ifdef MUTEX
    printf("using MUTEX\n");
#endif // MUTEX
#ifdef COND
    printf("using COND\n");
#endif // COND

    pthread_t *tid = new pthread_t[THREADNUMBER]();
    int *index = new int[THREADNUMBER]();
    for (int i = 0; i < THREADNUMBER ; i++)
    {
        index[i] = i;
        printf("create thread %d\n", i);
#ifdef COND
    if (i == 5)
        ready = 1;
#endif // COND
        if (pthread_create(&tid[i], NULL, thread_wirte, &index[i]) != 0)
        {
            fprintf(stderr, "create thread %d failed\n", i);
	        pthread_exit((void *)1);
        }
    }
    
    sleep(3);
    delete []tid;
    delete []index;

    return NULL;
}

void *thread_wirte(void *argc)
{
    pthread_detach(pthread_self());
    int* index = (int *) argc;
    writein(stdout, index);

    pthread_exit(0);
}

void writein(FILE *out, int *index)
{

#ifdef SEM
    if (sem_wait(sem) == -1)
    {
        fprintf(stderr, "sem_wait %d failed\n", *index);
        sem_post(sem);
	    pthread_exit((void *)1);
    }
#endif // SEM
#ifdef MUTEX
    if (pthread_mutex_lock(&mutex) != 0)
    {
        fprintf(stderr, "pthread_mutex_lock %d failed\n", *index);
        pthread_mutex_unlock(&mutex);
	    pthread_exit((void *)1);
    }
#endif // MUTEX
#ifdef COND
    if (pthread_mutex_lock(&mutex) != 0)
    {
        fprintf(stderr, "pthread_mutex_lock %d failed\n", *index);
        pthread_mutex_unlock(&mutex);
	    pthread_exit((void *)1);
    }
    /* reverse  */
    while(ready == 0)
        pthread_cond_wait(&cond, &mutex);
    ready--;
       
#endif // COND
///////////////////////////////////////////////////////////////////////////////////////
    fprintf(out,"thread %d, tid = %ld, source = %d\n", *index, pthread_self(), source);
    source++;
///////////////////////////////////////////////////////////////////////////////////////
#ifdef SEM
    sem_post(sem);
#endif // SEM
#ifdef MUTEX
    pthread_mutex_unlock(&mutex);
#endif // MUTEX
#ifdef COND
    if (ready == 0)
        pthread_cond_signal(&cond);
    ready++;
    //fprintf(stderr, "error\n");
    pthread_mutex_unlock(&mutex);
#endif // COND
}




