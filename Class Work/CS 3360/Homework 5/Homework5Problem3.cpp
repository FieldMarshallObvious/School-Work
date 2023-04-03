#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <sys/time.h>


using namespace std;

#define ARRAYSIZE 1000000
#define ITERATIONS 1000

void generateRandomArray( int* randIntArray );
void performParallelComputation( int randIntArray [] );
void runExpirement( int expirementNum, double * averageComputationTime, timeval* beg, timeval* end, int randIntArray [], int num_threads );



int main( ) {
    // Providing a seed value
	srand((unsigned) time(NULL));

    // Create random array
    int randIntArray[ARRAYSIZE];

    // start time & end time
    timeval beg, end;

    // Average computation time
    double averageComputationTime[5];

    // Fill array with random numbers
    generateRandomArray(randIntArray);


    // Run expirement with 1 thread
    runExpirement(0, averageComputationTime, &beg, &end, randIntArray, 1);

    // Run expirement with 2 threads
    runExpirement(1, averageComputationTime, &beg, &end, randIntArray, 2);


    // Run expirement with 4 threads
    runExpirement(2, averageComputationTime, &beg, &end, randIntArray, 4);

    // Run expirement with 8 threads
    runExpirement(3, averageComputationTime, &beg, &end, randIntArray, 8);

    // Run expirement with 16 threads
    runExpirement(4, averageComputationTime, &beg, &end, randIntArray, 16);


    // Output Expirement results
    for(int i = 0; i < 5; i++ ) {
        cout << "Average service for expirement " << i + 1 << ": " << averageComputationTime[i] << endl;
    }

    return 0;
}

void generateRandomArray( int* randIntArray ) {

    // Generate 1 million random integers
    for( int i = 0; i < ARRAYSIZE; i++ )
    { 
        // Generate a random int 
        int randInt = rand();

        randIntArray[0] = randInt;
    }
}

void performParallelComputation( int randIntArray [] ) {
    // Iterate through each element of the array
    #pragma omp parallel for shared(randIntArray)
    for(int i = 0; i < ARRAYSIZE; i++ ) {
        int tempResult = 0;
        for(int j = 1; j < ITERATIONS; j++ ) {
            // Perform Computation
            tempResult = randIntArray[i] % j;
        }
    }
}

void runExpirement( int expirementNum, double * averageComputationTime, timeval* beg, timeval* end, int randIntArray [], int num_threads ) {
    // Set num threads
    omp_set_num_threads(num_threads);

    // Run Expirement 5 times
    for(int i = 0; i < 5; i++ ) { 
        gettimeofday(beg, NULL);

        performParallelComputation(randIntArray); 

        gettimeofday(end, NULL);

        averageComputationTime[expirementNum] += end->tv_sec - beg->tv_sec + (end->tv_usec - beg->tv_usec) / 1000000.0;
    }

    // Average results
    averageComputationTime[expirementNum] =  averageComputationTime[expirementNum]/5;
}
