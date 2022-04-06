#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Pre-define functions
void *APrinter(); 
void *BPrinter(); 

#define CAPACITY 1
#define ITEMSIZE 11


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
    int completedItems = 1;
    // print A(x5) 10 times
    while(completedItems != ITEMSIZE)
    {
        // If the buffer is full 
        // then wait
        while (buffer.size > 0)
        {
            pthread_cond_wait(&full_cond, &mutex);

        }

        pthread_mutex_lock(&mutex);
        for( int j = 0; j < 5; j++)
        {
            printf("%d: AAAAA\n", completedItems);
        }
        // Keep track of the number of completed items 
        completedItems++;

        // Open the buffer
        buffer.size++;

        printf("\n");

        pthread_cond_broadcast(&empty_cond);
        pthread_mutex_unlock(&mutex);

    }
}

void *BPrinter() 
{
    int completedItems = 1;

    // print B(x5) 10 times
    while(completedItems != ITEMSIZE)
    {
        while ( buffer.size < CAPACITY )
        {
            pthread_cond_wait(&empty_cond, &mutex);
        }

        pthread_mutex_lock(&mutex);
        for( int j = 0; j < 5; j++)
        {
            printf("%d: BBBBB\n", completedItems);
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