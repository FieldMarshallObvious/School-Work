/* CS3339 Assignment 6 Problem 1
 * Handout code, compile using 'g++ -std=c++11 -O3 -Wall -o matrixOps MatrixOps.cpp'
 * Modified by [your name here]
 * Original and Copyright 2020  Lee B. Hinkle
 * Some references used: 
 *   https://software.intel.com/en-us/node/529735
 *   http://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
 *   https://www.techiedelight.com/dynamic-memory-allocation-in-c-for-2d-3d-array/
 * Timing code based off work by Dr. Martin Burtscher, Texas State University
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

#define R 10000
#define C 10000
int main()
{
    cout << "Project 6 Array Traversal: ";
    cout << "Integer Array size = " << "FIXME "  << " MegaBytes" << endl;
    int** A = new int*[R]; //allocate pointer for each row
    int** B = new int*[R]; //allocate pointer for each row

    for (int i=0; i<C; i++){
        A[i] = new int[R];//allocate each column
        B[i] = new int[R];//allocate each column
    }

    //initialize matrix - the destination matrix is not initialized, it won't be in the cache
    for (int r = 0; r < R; r++){
        for (int c = 0; c < C; c++){
            A[r][c] = (int)r*c+1;
        }
    }

    double runtime; // for time measurement
    struct timeval start, end;  // for time measurement
    
    gettimeofday(&start, NULL);  // start timer
    // perform matrix operation
    // FIXME -after recording original time, the performance is lousy!!!
    for (int j = 0; j < C; j++){
        for (int i = 0; i < R; i++){
            B[i][j] = 2*A[i][j];
        }
    }
    gettimeofday(&end, NULL);  //end timer
    //sanity check a single element
    if (B[3][4]/A[3][4] == 2){
       printf("B is 2X A, A[3][4] = %d B[3][4] = %d\n", A[3][4], B[3][4]);
    }
    else{
       printf("Error:  B is not 2X A\n");
    }
    //compute and display results
    runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
    printf("by column (FIXME) compute time: %.4f seconds ", runtime);
    printf("megabytes/sec: %.3f\n", R*C*sizeof(int)*0.000001 / runtime);
    
    //deallocate memory
    for (int i=0; i<C; i++){
        delete[] A[i];
        delete[] B[i];
    }
    delete[] A;
    delete[] B;
    return 0;
}
