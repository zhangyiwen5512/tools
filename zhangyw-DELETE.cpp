#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define THREADNUMBER 3
#define FILENUMBER 10
using namespace std;

void *thread_main(void * argc);
void *thread_delete(void *argc);
void *DeleteFile(const char *name, int index);

struct fileName
{
    char *name;
    int start;
    int end;
};

int main(int argc, char const *argv[])
{     
    printf("prepare to delete\n");
    printf("3\n"); 
    sleep(1);
    printf("2\n"); 
    sleep(1);
    printf("1\n");
    sleep(1);

    pthread_t *tid = new pthread_t;

    int	n;
    n = pthread_create(tid, NULL, thread_main, NULL);
    if (n != 0)
    {  
        fprintf(stderr, "create main thread failed\n");
    }

    if (pthread_join(*tid, NULL) != 0)
    {
        fprintf(stderr, "main end fail\n");
    }

    return 0;
}

void *thread_main(void * argc)
{   
    printf("use %d thread to delete\n", THREADNUMBER);

    pthread_t *tid = new pthread_t[THREADNUMBER]();
    struct fileName *file = new  struct fileName[THREADNUMBER]();

    for (int i = 0; i < THREADNUMBER ; i++)
    {
        /* divide job */
        file[i].name = "output";
        if (i == 0)
        {
            file[i].start = 0;
        }
        else
        {
            file[i].start = file[i - 1].end + 1;
        }
        
        if (i == (THREADNUMBER - 1))
        {
            file[i].end = FILENUMBER - 1;
        }
        else if (i == 0)
        {
            file[i].end = int(FILENUMBER / THREADNUMBER) - 1;
        }
        else
        {
            file[i].end = int(FILENUMBER / THREADNUMBER) - 1 + file[i].start;
        }

        int	n;
        n = pthread_create(&tid[i], NULL, thread_delete, &file[i]);
        if (n != 0)
        {
            fprintf(stderr, "create thread %d failed\n", i);
        }
    }

    for (int i = 0; i < THREADNUMBER ; i++)
    {
        if (pthread_join(tid[i], NULL) != 0)
        {
            fprintf(stderr, "thread %d end fail\n", i);
        }
    }

    delete [] tid;
    //delete [] file; /* auto deleted */

    return NULL;
}


void *thread_delete(void *argc)
{
    struct fileName * file = (struct fileName *)argc;
    for (int i = file->start; i <= file->end ;i++)
    {
        string filename = file->name + to_string(i);
        DeleteFile(filename.c_str(), i);
    }
    
    pthread_exit(0);
}




void *DeleteFile(const char *name, int index)
{
    ifstream in(name, ios::in | ios::binary);
   
    if (!in.is_open())    
    {
        fprintf(stderr, "open file%d fail\n", index);
        return NULL;
    }

    unsigned short int size;
    char dot;
    int n = 0;
    timeval t_start, t_end;
    double delta_t;
    while (true)
    { 
        in.read((char *)&size, sizeof(size));
        in.read((char *)&dot, sizeof(dot));
        if (in)
        {
            ++n; 
            gettimeofday(&t_start, NULL);
            printf("file = %d, %d block size = %u\n", index, n, size);
            in.ignore(size);
            usleep(500000);    
        }
        
        if (!in) 
        {
            gettimeofday(&t_end, NULL);
            delta_t = (t_end.tv_sec-t_start.tv_sec) + 
                    (t_end.tv_usec-t_start.tv_usec) / 1000000.0;
            if (delta_t > 2.0)
                break;
        }     
    }

    in.close();
    if (remove(name) != 0)
    {
        fprintf(stderr, "file = %d remove file fail", index);
        return NULL;
    }
    printf("tid = %d remove succeed\n", index);
    return NULL;
}    