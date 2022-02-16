#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main ( int argc, char *argv[] )
{
    // Create fork
    int pid = fork();

    if ( argc < 1 )
    {
        printf("One argument expected.\n");
        return(-1);
    }

    argv[argc - 1] = NULL;

    // An error has occured 
    if( pid < 0 )
    {
        printf("Failed");
        return(-1);
    }

    else if( pid == 0 )
    {

        execvp(argv[0], argv);
        printf("Child proccess id is: %d\n", getpid());
    }

    else
    {        
        printf("Parent proccess id is: %d\n", getppid());
    }

    return 0;
}