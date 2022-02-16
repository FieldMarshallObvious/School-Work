#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>


int main ( int argc, char *argv[] )
{
    // Create fork
    int pid = fork();

    int status;

    if ( argc < 1 )
    {
        printf("One argument expected.\n");
        return(-1);
    }


    // An error has occured 
    if( pid < 0 )
    {
        printf("Failed");
        return(-1);
    }

    else if( pid == 0 )
    {   
        printf("Child proccess id is: %d\n", getpid());

        // In case of error return a negative statement
        if(execvp(argv[1], argv + 1) < 0 )
        {
            printf("Command failed\n");
            return -2;
        }
    }

    else
    {   
        // Wait for the child proccess to complete
        while(wait(&status) != pid);

        printf("Parent proccess id is: %d\n", getppid());

    }

    return 0;
}