#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <time.h>

//interrupt stop terminate kill SIGINT, 
//signal(SIGINT, myhand);  

void myhandler(int sig)
{

}


void main()
{
    //int ogPID = getpid();
    time_t T= time(NULL);
    struct tm tm = *localtime(&T); //tm.tm_hour, tm.tm_min
    
    signal(SIGINT, myhandler); 
    signal(SIGKILL, myhandler); 
    //signal(SIGSTOP, myhand); 
    signal(SIGTERM, myhandler); 

    time_t T= time(NULL);
    struct tm tm = *localtime(&T); //tm.tm_hour, tm.tm_min

    int* childPID = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *childPID = 0;

    printf("original PID: %i\n", getpid());
    fflush(0);

    if (fork() == 0)
    {
        printf("%i:%i\n");
        //folder

    }
    else
    {
        
    }
    
}