#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main () 
{
    int inputPipe[2];    

    // Create pipe between outputs
    pipe(inputPipe);

    int pid = fork();

    // An error has occured 
    if( pid < 0 )
    {
        printf("Failed");
        return(-1);
    }
    if( pid == 0 )
    {
        // Duplicate the input end of the pipe
        dup(inputPipe[1]);

        // close the original
        close(inputPipe[0]); // don't need the read end
        close(inputPipe[1]); 

        execl("./pre", NULL);
    }
    else
    {
        // Open up the write end of the pipe
        dup(inputPipe[0]);

        // close the originals
        close(inputPipe[0]);
        close(inputPipe[1]); // don't need the write end 

        execl("./sort", NULL);
    }

    return 0;
}