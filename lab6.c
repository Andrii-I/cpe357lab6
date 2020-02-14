#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

//interrupt stop terminate kill SIGINT (^C, ^D, and ^Z)
//signal(SIGINT, myhand);  

void myhandler(int sig)
{
    printf("\n\nCan't touch this!\n\n");
}

    //int* childPID = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    //*childPID = 0;
    
    //printf("Parent PID: %i", getpid());
    //fflush(0);

void main()
{  
    signal(SIGINT, myhandler); 
    signal(SIGKILL, myhandler); 
    signal(SIGSTOP, myhandler); 
    signal(SIGTSTP, myhandler);  
    signal(SIGTERM, myhandler); 

    struct dirent* dent;
    DIR* dir;
    char* buffer;
    int i = 0;

    while (1)
    {
        printf("\n\nParent PID: %i\n\n", getpid());
        fflush(0);

        if (fork() == 0)
        {
            while(1)
            {
                time_t T= time(NULL);
                struct tm tm = *localtime(&T); //tm.tm_hour, tm.tm_min
                
                printf("\n%i : %i", tm.tm_hour, tm.tm_min);
                
                strcpy(buffer, ".");
                dir = opendir(buffer);
                 printf("\n---\n");
                for (dent = readdir(dir); dent != NULL; dent = readdir(dir))
                {
                    printf("%s\n", dent->d_name);
                }
                printf("---\n");
                printf("Child PID: %i\n\n", getpid());
                closedir(dir);
                sleep(10);
            }
        }
        else
        {
            wait(0);
        }
    }
    
}