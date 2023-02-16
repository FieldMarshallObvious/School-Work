#include <iostream>
#include <cstdlib>

using namespace std;

void unifRandInts( int* intArr, int size, int lower, int max );
void unifRandFloat( float* floatArr, int size, float lower, float max );
void specificRandFloat( float* floatArr, int size, double probA, 
                        double probB, float lower, float max  );
void outputArr( int* arr, int size );
void outputArr( float* arr, int size );

int main() {
    // Seed ranom num generator
    srand((unsigned) time(NULL));

    // Variable declarations
    int intArr[100];
    float floatArr[100];
    float floatArrSpecific[100];

    // Generate random numbers
    unifRandInts(intArr, 100, 0, 99);
    unifRandFloat(floatArr, 100, 0.25, 0.5);
    specificRandFloat(floatArrSpecific, 100, 0.5, 0.2, 3, 4);

    // Display Arrays
    cout << "Uniform Int Array: " << endl;
    outputArr(intArr, 100);

    cout << endl;

    cout << "Uniform Float Array: " << endl;
    outputArr(floatArr, 100);

    cout << endl;
    cout << "Specific Distribution Float Array: " << endl;
    outputArr(floatArrSpecific, 100);


}

// Generate random numbers between lower and max
void unifRandInts( int* intArr, int size, int lower, int max ) {
    for ( int i = 0; i  < size; i++ ) {
        intArr[i] = rand() % max + lower;
    }
}

// Generate random doubles between lower and max values
void unifRandFloat( float* floatArr, int size, float lower, float max ) {
    for ( int i = 0; i  < size; i++ ) {
        floatArr[i] = ( (float)rand() / RAND_MAX ) * ( max - lower ) + lower;
    }
}

void specificRandFloat( float* floatArr, int size, double probA, 
                        double probB, float lower, float max ) 
{
    for( int i = 0; i < 100; i++ ) {

        // Select the numbers one or two based on the probabilities
        // provided
        float oneTwoSelector = (float) rand() / RAND_MAX;

        if( oneTwoSelector < probA ) {
            floatArr[i] = 1; 
        } 
        // Select 2 using equivalent probability
        // on other side
        else if( oneTwoSelector > 1 - probB ) {
            floatArr[i] = 2;
        }

        // Otherwise generate a random float based on 
        // the passed low val & max
        else {
            floatArr[i] = ((float)rand() / RAND_MAX) * ( max - lower ) + lower;
        }
    }
}

void outputArr( int* arr, int size )
{
    for ( int i = 0; i < size; i++ ) {
        cout << arr[i];
        if( i < (size - 1) )
        {
            cout << ", ";
        }
        else 
        {
            cout << endl;
        }
    }
} 
void outputArr( float* arr, int size )
{
    for ( int i = 0; i < size; i++ ) {
        cout << arr[i];
        if( i < (size - 1) )
        {
            cout << ", ";
        }
        else 
        {
            cout << endl;
        }
    }
} 
