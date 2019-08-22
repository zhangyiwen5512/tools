#include <sys/socket.h>
#include <stdio.h>

int main(int argc, const char** argv) 
{
    pid_t pid;

    pid_t child;
    pid = getpid();
    child = fork();
    if (child != 0)
    {    
        printf("This is father (pid = %d, child pid = %d)\n", pid, child);
    }
    
    if (child == 0)
    {
        printf("This is child (ppid = %d, pid = %d)\n", pid, child);   
    }

    return 0;
}