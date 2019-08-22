#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


using namespace std;

void readin(ifstream &in);

int main(int argc, char const *argv[])
{
      
    ifstream in("output", ios::in | ios::binary);
   
    if (!in.is_open())    
    {
        fprintf(stderr, "open file fail");
        exit(1);
    }
          
    printf("prepare to read\n");
    printf("3\n"); 
    sleep(1);
    printf("2\n"); 
    sleep(1);
    printf("1\n");
    sleep(1);

    readin(in);

    in.close();

    return 0;
}


void readin(ifstream &in)
{
    unsigned short int size;
    char dot;
    int n = 0;
    float read_time;
    float total_time;

    while (true)
    { 
        in.read((char *)&size, sizeof(size));
        in.read((char *)&dot, sizeof(dot));
        if (in)
        {
            ++n; 
            read_time = clock();
            printf("%d block size = %u\n", n, size);
            in.ignore(size);
            usleep(500000);   
        }
        
        if (!in) 
        {
            total_time = ((float)clock() - read_time) / CLOCKS_PER_SEC;
            if (total_time > 2.0)
                break;
        }     
    }
    cout << n <<" bolcks has been read " << endl;
}