#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Pre-define functions
void *APrinter(); 
void *BPrinter(); 

#define CAPACITY 1
#define ITEMSIZE 20


pthread_mutex_t mutex;
pthread_cond_t  full_cond;
pthread_cond_t  empty_cond;
struct Buffer buffer;

struct Buffer
{
  int item[ITEMSIZE];
  int size;
};

int main() 
{
    // Create pthread
    pthread_t tid;
    buffer.size = 0;

    pthread_setconcurrency(2);


    // Create A printer 
    pthread_create(&tid, NULL, (void *(*)(void *))APrinter, NULL  );

    // Create B printer 
    pthread_create(&tid, NULL, (void *(*)(void *))BPrinter, NULL );


    pthread_exit(0);
}

void *APrinter() 
{
    int curHalf = 0;
    int completedItems = 0;
    // print A(x5) 10 times
    while(completedItems != 2)
    {
        // If the buffer is full 
        // then wait
        if (buffer.size == CAPACITY)
        {
            pthread_cond_wait(&full_cond, &mutex);

        }
        else
        {
            pthread_mutex_lock(&mutex);
            for( int j = 0; j < 5; j++)
            {
                //Determine current half
                if( completedItems < 1 )
                    curHalf = 1;
                else 
                    curHalf = 2;
                printf("%d: AAAAA\n", curHalf);
            }
            // Keep track of the number of completed items 
            completedItems++;

            // Open the buffer
            buffer.size++;

            printf("\n");

            pthread_cond_broadcast(&empty_cond);
        }
    }
}

void *BPrinter() 
{
    int curHalf = 0;
    int completedItems = 0;

    // print B(x5) 10 times
    while(completedItems != 2)
    {
        if ( buffer.size == 0 )
        {
            pthread_cond_wait(&empty_cond, &mutex);
        }
        else 
        {
            pthread_mutex_lock(&mutex);
            for( int j = 0; j < 5; j++)
            {
                // Determine current half
                if( completedItems < 1 )
                    curHalf = 1;
                else 
                    curHalf = 2;
                printf("%d: BBBBB\n", curHalf);
            }
            // Keep track of the number of completed items 
            completedItems++;

            // Return the buffer to the A printer 
            buffer.size--;
            printf("\n");
            
            pthread_cond_broadcast(&full_cond);
            pthread_mutex_unlock(&mutex);
        }
    }
}