#include <stdio.h>
#include <pthread.h>

// Pre-define functions
void *APrinter(); 
void *BPrinter(); 


int main() 
{
    // Create pthread
    pthread_t tid;

    // Create A printer 
    pthread_create(&tid, NULL, (void *(*)(void *))APrinter, NULL  );

    // Create B printer 
    pthread_create(&tid, NULL, (void *(*)(void *))BPrinter, NULL );


    pthread_exit(0);
}

void *APrinter() 
{
    int curHalf = 0;
    // print A(x5) 10 times
    for( int i = 0; i < 10; i++ )
    {
        //Determine current half
        if( i < 5 )
            curHalf = 1;
        else 
            curHalf = 2;
        printf("%d: AAAAA\n", curHalf);
    }
}

void *BPrinter() 
{
    int curHalf = 0;
    // print A(x5) 10 times
    for( int i = 0; i < 10; i++ )
    {
        // Determine current half
        if( i < 5 )
            curHalf = 1;
        else 
            curHalf = 2;
        printf("%d: BBBBB\n", curHalf);
    }
}