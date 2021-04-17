#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

void generateArray( char inputArr[], int inputSize );
void displayArray( char inputArr[], int inputSize );
void sequentialSearch( char inputArr[], int inputSize, char item );
void selectionSort( char inputArr[], int inputSize );
void insertionSort( char inputArr[], int inputSize );
void quickSort( char inputArr[], int midPoint );
char ranChar();

int main ( )
{
    // Variable declarations
    int sizeArr = 0;      // Holds the size of the array
    char itemToFind = 80; // Holds the char to find

    // Header statement
    cout << "Searching / Sorting Benchmark " << endl << endl;

    // Get size of arr from user
    cout << "Enter the size of the array : ";
    cin >> sizeArr;

    cout << endl << endl;
    // If size of Arr is less than one
    // end the program
    if( sizeArr < 4 )
    {
        cout << "*** Error - Invalid input - Size must be > 4 ***" << endl;
        cout << "4 - 2021" << endl
             << "Sorting / Searching Benchmark by : " << endl
             << "Noah del Angel" << endl;
        return 0;
    }
    else
    {

        // Create array
        char originalArr[sizeArr]; // Holds the original array of random
                                   // chars
        // Create seed
        srand( time( NULL ) );

        generateArray( originalArr, sizeArr );

        displayArray( originalArr, sizeArr );
    }
}

void generateArray( char inputArr[], int inputSize )
{
    for( int i = 0; i < inputSize; i++ )
    {
        inputArr[i] = ranChar();
    }
}


void displayArray( char inputArr[], int inputSize )
{
    for( int i = 0; i < inputSize; i++ )
    {
        cout << inputArr[i] << " ";
    }
}

void sequentialSearch( char inputArr[], int inputSize, char item )
{
    // Variable declarations
    int numOfOccurrences = 0;
    int itemToFind = item;
    bool foundItem = false;

    for( int i = 0; i < inputSize; i++ )
    {
        if( inputArr[i] == item )
        {
            numOfOccurrences++;
            foundItem = true;
        }
    }

    cout << "Char " << itemToFind << " Was";

    if( foundItem == true )
        cout << " Not found." << endl;
    else
        cout << " found." << endl;

    cout << "Start Time  : ";

}

char ranChar()
{
    char output = rand( ) % ( 126 - 65 ) + 65;
    return output;
}


