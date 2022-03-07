#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h> 

int* findZeroFromCurrentLocation( int curLocation, int size, char *argv[] )
{
	int charLocation = -1;

	// Find location of 0 in array
    for( int j = (curLocation + 1); j < size; j++ )
    {
        if( argv[j] == 0 )
        {
            charLocation = j;
            break;
        }
        if( j == ( size - 1 ) )
            charLocation = size;
	}

	return charLocation;
}

main()

{

char *path, *argv[20], buf[80], n, *p;

int m, status, inword, continu;



while(1) {



inword = 0;

p = buf;

m = 0;

continu=0;



printf( "\nshhh> ");

while ( ( n = getchar() ) != '\n'  || continu ) {

	if ( n ==  ' ' ) { 

	    if ( inword ) {

		inword = 0;

		*p++ = 0;

	    } 

	}

	else if ( n == '\n' ) continu = 0;

	else if ( n == '\\' && !inword ) continu = 1;

	else {

	    if ( !inword ) {

		 inword = 1;

		 argv[m++] = p;

		 *p++ = n;

	     }

	     else 

		 *p++ = n;

	}

}

*p++ = 0;

argv[m] = 0;


// No need to change anything above. Your part should start from // here
if ( strcmp(argv[0],"exit") == 0 ) return 0;


int left_fd[2];
int right_fd[2];

int pipes = 0;

bool inputRedirection = false;
bool outputRedirection = false;

int charLocation = -1;
int oldCharLocation = 0;


// Replace characters with 0 
for( int i = 0; i < m; i++ )
{
	// Replace all information with related 0's
	if( *argv[i] == '<' )
	{
		inputRedirection = true;
		argv[i] = 0;
	}
	else if( *argv[i] == '>' )
	{
		outputRedirection = true;
		argv[i] = 0;
	}
	else if( *argv[i] == '|' )
	{
		pipes++;
		argv[i] = 0;
	}
}

for( int i = 0; i <= pipes; i++)
{
    // Create the right pipe, if this is not the last proccess
    // and a pipe is supposed to be created 
    if( pipes != 0 && i != pipes ) 
    {
        pipe(right_fd);
    }
    
    int pid = fork();
	oldCharLocation = charLocation + 1;
	charLocation = findZeroFromCurrentLocation(charLocation, m, argv);


    if( pid < 0 )
    {
        printf("Failed \n");
        return -1;
    }

    if( pid > 0 )
    {
		wait(&status);

		printf("i: %d\n", i);
        
        // Close left pipe
        if( i >= 0 )
        {
            close(left_fd[0]);
            close(left_fd[1]);
        }

        // Assign the left pipe to the right pipe
        left_fd[0] = right_fd[0];
        left_fd[1] = right_fd[1];

    }

    else
    {
		printf("child - proccess: %d \n", i);


		// If this is the first proccess 
		// and there is inputRedirection
        if( i == 0 && inputRedirection )
		{
			// Close standard input
			close(0);

			// Open file
			left_fd[0] = open(argv[charLocation+1], O_RDONLY);


			// Duplicate the input location
			dup(left_fd[0]);

			close(left_fd[0]);
			close(left_fd[1]);


			// Move to next 0
			charLocation = findZeroFromCurrentLocation(charLocation, m, argv);
		}

		// If there are pipes
		if( pipes != 0 )
		{
            // If first proccess
            if( i == 0 )
            {
                printf("First proccess \n");
                // Close standard output
                // and attach right pipe
                close(1);
                dup(right_fd[1]); // output end

                close(right_fd[1]);
                close(right_fd[0]);
            }

            // If is a middle proccess
            else if ( i < pipes )
            {
                printf("Middle process \n");
                // Close standard input & output
                // and attach left and right pipes
                
                close(0);
                dup(left_fd[0]);

                close(left_fd[0]);
                close(left_fd[1]);

                close(1);
                dup(right_fd[1]);

                close(right_fd[0]);
                close(right_fd[1]);
            }

            // If is last proccess
            else
            {
                printf("Last process \n");
                // Close standard input 
                // and attach left pipe
                close(0);
                dup(left_fd[0]); // input end

                close(left_fd[0]);
                close(left_fd[1]);
            }

		}

		// If there is output redirection, and is the last process
		if( i == pipes && outputRedirection )
		{
			printf("output redirection \n");


			// opening file 
			right_fd[1] = open(argv[charLocation+1], O_WRONLY|O_CREAT, 0666);

			// Close standard output 
			close(1);

			// Duplicate the output location
			dup(right_fd[1]);

			close(right_fd[0]);
			close(right_fd[1]);

			// Move to next 0
			charLocation = findZeroFromCurrentLocation(charLocation, m, argv);
		}

		printf("argc: %d \n", (charLocation - oldCharLocation) );
		printf("child - charLocation: %d \n", charLocation);
		printf("child - oldCharLocation: %d \n", oldCharLocation);
		printf("argv[oldCharLocation] %s \n", argv[oldCharLocation]);

        char *arrayCommand[charLocation - oldCharLocation];

        for( int j = 0; j < charLocation - oldCharLocation; j++ )
        {

            arrayCommand[j] = argv[oldCharLocation + j];
			printf("arrayCommand[j]: %s \n", arrayCommand[j]);
        }

		arrayCommand[charLocation - oldCharLocation] = 0;

		execvp(arrayCommand[0], &arrayCommand[0]);
    }


}
printf("we are done here \n");
wait(&status);

}

}

