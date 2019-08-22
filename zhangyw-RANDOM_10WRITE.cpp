#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAXSIZE 65535
#define DEADTIME 20.0
#define THREADNUMBER 10
using namespace std;

void *thread_main(void *argc);
void writein(ofstream &out, int* index);
void *thread_wirte(void *argc);

int main(int argc, char const *argv[])
{
    timeval t_start, t_end;
    gettimeofday(&t_start, NULL);
    
    pthread_t *tid = new pthread_t;

    int	n;
    n = pthread_create(tid, NULL, thread_main, NULL);
    if (n != 0)
    {
        fprintf(stderr, "create main thread failed\n");
	pthread_exit((void *)1);
    }

    if (pthread_join(*tid, NULL) != 0)
    {
        fprintf(stderr, "main end fail\n");
	pthread_exit((void *)1);
    }
    
    gettimeofday(&t_end, NULL);
    double delta_t = (t_end.tv_sec-t_start.tv_sec) + 
                    (t_end.tv_usec-t_start.tv_usec)/1000000.0;
    cout << "all time : " << delta_t  << "s" << endl;

    delete tid;
    return 0;
}


void *thread_main(void * argc)
{   
    pthread_t *tid = new pthread_t[THREADNUMBER]();
    int *index = new int[THREADNUMBER]();
    for (int i = 0; i < THREADNUMBER ; i++)
    {
        int	n;
        index[i] = i;
        n = pthread_create(&tid[i], NULL, thread_wirte, &index[i]);
        if (n != 0)
        {
            fprintf(stderr, "create thread %d failed\n", i);
	    pthread_exit((void *)1);
        }
    }
    
    /* wait 10 thread terminated */
    for (int i = 0; i < THREADNUMBER ; i++)
    {
        if (pthread_join(tid[i], NULL) != 0)
        {
            fprintf(stderr, "thread %d end fail\n", i);
            pthread_exit((void *)1);
        }
    }

    delete []tid;
    delete []index;

    return NULL;
}

void *thread_wirte(void *argc)
{
    int* index = (int *) argc;

    string filename = "output" + to_string(*index);

    ofstream out;

    out.open(filename.c_str(), ios::out | ios::trunc | ios::binary);

    if (!out.is_open())
    {
        fprintf(stderr, "open file fail\n");
        pthread_exit((void *)1);
    }  

    writein(out, index);

    out.close();

    printf("tid = %d exit\n", *index);

    pthread_exit(0);
}

void writein(ofstream &out, int* index)
{
    time_t seed = time(NULL);
    srand(seed);

    int number;
    long int t;
    float total_time;
    float write_time;
    
    unsigned short int size = 0;

    total_time = 0;
    number = 0;
   
    while (total_time < DEADTIME)
    {
        t = (rand() % (1000 - 10 + 1)) + 10;
        size = rand() % MAXSIZE;
        ////////////////////////////////////////////////////////
        unsigned char * data = new unsigned char[size];
        ////////////////////////////////////////////////////////
        ++number;
        
        write_time = clock();
        
        /* write */
        ////////////////////////////////////////////////////////
        // pthread_mutex_lock(&printMutex);
        // while (true)
        // {
        //     pthread_cond_wait(&printCond, &printMutex);
        // }
        out.write((char *) &size, sizeof(size));
        out.write(",", sizeof(char));
        for (int i = 0; i < size - 1; ++i)
        {
            data[i] = rand() % 255; 
            out.write((char *)&data[i], sizeof(data[i]));    
        }
        out.write(",", sizeof(char));
        // pthread_cond_signal(&printCond);
        // pthread_mutex_unlock(&printMutex);
        /////////////////////////////////////////////////////////
        write_time = ((float)clock() - write_time) / CLOCKS_PER_SEC;

        /* wait zone */
        usleep(t * 1000);
        
        total_time += (((float)t / 1000)  + write_time);

        printf("tid = %d, waited %ld ms, writed %d char ,total time = %f\n", *index, t, size, total_time);

        delete[] data;
      
    } 
    printf("tid = %d, %d block has been writern\n", *index, number);
}





