// Author: Noah del Angel
// Due Date: 2/3/2021
// Assignment Number: 1
// Spring - 2016   -  CS 33SIZE8   -  2SIZE2
// Instructor:  Husain Gholoom
//
// Manipulation of two dimensional arrays
#include <iostream>
#include <time.h>

void populateArray( int[][5] );
void printArray( int[][5] );
void displayPrimeNums( int[][5] );
void sortArray( int[][5] );
void displayMathOperations( int[][5] );
void displayEvens( int[][5] );
void displayOdds( int[][5] );
int generateRanNum( );

using namespace std;

// Global vars
const int SIZE = 5;

int main()
{
    // Required statement
    cout << "This Program is Written by Noah del Angel" << endl;
    cout << endl;
    cout << "The program uses a SIZE by SIZE array to store a set of random numbers into array." << endl;
    cout << "The numbers are between 1 and 100. The program then displays on the screen" << endl;
    cout << "the numbers, sum, average, smallest, largest, even, odd, and prime of the" << endl;
    cout << "numbers. Finally, the program will display the array with the numbers are sorted" << endl;
    cout << "from lowest to highest." << endl;

    cout << endl;

    // Declare vars
    int randArray[7][SIZE];

    // Create seed
    srand(time(NULL));


    // Populate Array
    populateArray( randArray );

    // Display Array and manipulations
    cout << "The size of the array is = 5"<< endl ;
    cout << endl;

    cout << "The 5 x 5 array is " << endl;
    printArray(randArray);

    displayMathOperations( randArray );

    sortArray( randArray );

    cout << "The Smallest is: " << randArray[0][0] << endl;
    cout << "The Largest is: " << randArray[( SIZE - 1 )][( SIZE - 1 )] << endl;

    displayEvens( randArray );
    displayOdds( randArray );

    return 0;


}

void populateArray( int arr[][SIZE]  )
{
    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
            arr[i][j] = generateRanNum();
}

void printArray( int arr[][SIZE] )
{
    for( int i = 0; i < 7; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
                cout << arr[i][j] << "     ";
        cout << endl;
    }
}

void displayPrimeNums ( int arr[][SIZE] )
{


}

void sortArray ( int arr[][SIZE] )
{
    // Variable declarations
    int curItem,
        swapItem;
    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
        {
            curItem = arr[i][j];
            for( int z = 0; z < SIZE - 1; z++ )
                if( arr[i][j] > arr[i][z] )
                {
                    arr[i][j] = arr[i][z];
                    arr[i][z] = curItem;
                }
        }
}

void displayMathOperations ( int arr[][SIZE] )
{


}

void displayEvens ( int arr[][SIZE] )
{


}

void displayOdds ( int arr[][SIZE] )
{


}


int generateRanNum( )
{
    int output = (rand() % 99 ) + 2;
    return output;
}
