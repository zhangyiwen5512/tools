#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#define MAXSIZE 65535
#define DEADTIME 20.0


using namespace std;

void writein(ofstream &out);


int main(int argc, char const *argv[])
{


    time_t t = time(NULL);
    srand(t);
      
    ofstream out;
    out.open("output", ios::out | ios::trunc | ios::binary);
   
    if (!out.is_open())
    {
        fprintf(stderr, "open file fail");
        exit(1);
    }  

    writein(out);

    out.close();

    return 0;
}


void writein(ofstream &out)
{
    int number;
    long int t;
    float total_time;
    float write_time;
    
    unsigned short int size;

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
        out.write((char *) &size, sizeof(size));
        out.write(",", sizeof(char));
        for (int i = 0; i < size - 1; ++i)
        {
            data[i] = rand() % 255; 
            out.write((char *)&data[i], sizeof(data[i]));    
        }
        out.write(",", sizeof(char));
        //out.write((char *)&data, strlen((char*)(data)));

        write_time = ((float)clock() - write_time) / CLOCKS_PER_SEC;

        /* wait zone */
        usleep(t * 1000);
        
       
        total_time += (((float)t / 1000)  + write_time);
        printf("waited %ld ms, writed %d char ,total time = %f\n", t, size, total_time);

        delete[] data;
      
    }
    printf("%d block has been writern\n", number);

}