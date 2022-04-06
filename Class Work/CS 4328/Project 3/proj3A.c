#include <stdio.h>
#include <pthread.h>

// Pre-define functions
void *APrinter(); 
void *BPrinter(); 

#define ITEMSIZE 11


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
    int completedItems = 1;
    // print A(x5) 10 times
    while(completedItems != ITEMSIZE)
    {

        for( int j = 0; j < 5; j++)
        {
            printf("%d: AAAAA\n", completedItems);
        }
        // Keep track of the number of completed items 
        completedItems++;

        printf("\n");
    }
}

void *BPrinter() 
{
    int completedItems = 1;

    // print B(x5) 10 times
    while(completedItems != ITEMSIZE)
    {
        for( int j = 0; j < 5; j++)
        {
            printf("%d: BBBBB\n", completedItems);
        }
        // Keep track of the number of completed items 
        completedItems++;

        printf("\n");
    }
}