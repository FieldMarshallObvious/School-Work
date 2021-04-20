// Author: Noah del Angel
// Due Date: 4/21/2021
// Assignment Number: 6
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// Experimenting with various search
// and sort methods to determine
// the time it takes to execute
#include <iostream>
#include <time.h>


using namespace std;

void generateArray( char inputArr[], int inputSize );
void displayArray( char inputArr[], int inputSize );
void sequentialSearch( char inputArr[], int inputSize, char item );
void selectionSort( char inputArr[], int inputSize );
void insertionSort( char inputArr[], int inputSize );
void runQuickSort( char inputArr[], int inputSize, int givenCase  );
void quickSortMid( char inputArr[], int left, int right, int &numCalls );
void quickSortStart( char inputArr[], int left, int right, int &numCalls );
void quickSortSecondLast( char inputArr[], int left, int right, int &numCalls );
void copyArr( char originalArr[], char newArr[], int sizeOfArr );
char ranChar();

int main ( )
{
    // Variable declarations
    int sizeArr = 0,      // Holds the size of the array
        placeholder = 0;  // Placeholder var to satisfy
                          // parameter requirement
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

    // If not, continue the program
    else
    {

        // Create array
        char originalArr[sizeArr]; // Holds the original array of random
                                   // chars
        // Create seed
        srand( time( NULL ) );

        generateArray( originalArr, sizeArr );

        // Display Starting Array
        cout << "Array elements are: ";
        displayArray( originalArr, sizeArr );
        cout << endl;

        // Search using Sequential Search
        cout << endl << endl;
        cout <<  "Sequential Search" << endl << endl;
        cout << "Search for  Char " << ( int ) itemToFind << endl << endl;
        sequentialSearch( originalArr, sizeArr, itemToFind );

        // Test with selection sort

        cout << endl << endl;
        cout << "Selection Sort : " << endl << endl;
        selectionSort( originalArr, sizeArr );

        // Test with insertion sort
        cout << endl << endl;
        cout << "Insertion Sort : " << endl << endl;
        insertionSort( originalArr, sizeArr );

        // Test with quick sort with various pivot points
        cout << endl << endl;
        cout << "Quick Sort - The middle element as pivot: " << endl << endl;
        runQuickSort( originalArr, sizeArr, 0 );

        cout << endl << endl;
        cout << "Quick Sort - The next to last element as a pivot: " << endl
             << endl;
        runQuickSort( originalArr, sizeArr, 1 );

        cout << endl << endl;
        cout << "Quick Sort - First element as a pivot:  " << endl
             << endl;
        runQuickSort( originalArr, sizeArr, 3);

        // Perform a sequential search for char 80
        // on the sorted array
        cout << endl << endl;
        cout << "Sequential Search for Char " << ( int ) itemToFind << endl
             << " After Sort" << endl;

        // Sort the original array
        quickSortMid( originalArr, 0, sizeArr - 1, placeholder );

        // Search through the array
        sequentialSearch( originalArr, sizeArr, itemToFind );

        // Footer statement
        cout << endl;
        cout << "4 - 2021" << endl
             << "Sorting/Searching Benchmark by:" << endl
             << "Noah del Angel" << endl;
    }
}

//**************************************************
// Generates array with random characters
//
// inputArr - Holds the array to be populated with
//            random characters
// inputSize - Holds the desired size of the array
//**************************************************
void generateArray( char inputArr[], int inputSize )
{
    for( int i = 0; i < inputSize; i++ )
    {
        inputArr[i] = ranChar( );
    }
}

//**************************************************
// Displays each element of the inputted array
//
// inputArr - Holds the array to be populated with
//            random characters
// inputSize - Holds the desired size of the array
//**************************************************
void displayArray( char inputArr[], int inputSize )
{
    if( inputSize > 20 )
        inputSize = 20;

    for( int i = 0; i < inputSize; i++ )
    {
        cout << inputArr[i] << " ";
    }
}

//**************************************************
// Performs a sequential search through the given
//  array, to find the inputted item. Also
//  determines the time it took to execute the
//  function, number of occurrences of the requested
//  item, and displays the array.
//
// inputArr - Holds the array to be populated with
//            random characters
// inputSize - Holds the desired size of the array
//**************************************************
void sequentialSearch( char inputArr[], int inputSize, char item )
{
    // Variable declarations
    int numOfOccurrences = 0;   // Tracks the number of occurrences
                                // of the inputted char
    bool foundItem = false;     // Keeps track of the whether
                                // the item was found our not
    double duration;            // Holds the duration of the time it
                                // took to execute the algorithm
    time_t start,               // Holds the start time of the algorithim
           finish;              // Holds the finish time of the algorithim

    // Log the start time of the function
    start = clock();

    for( int i = 0; i < inputSize; i++ )
    {
        if( inputArr[i] == item )
        {
            numOfOccurrences++;
            foundItem = true;
        }
    }

    // Log end time
    finish = clock( );

    // Calculate the clock time
    duration = double(finish - start);

    cout << "Char " << (int)item << " Was";

    if( foundItem == true )
        cout << " Not found." << endl;
    else
        cout << " found." << endl;

    cout << "Start Time  : " << double( start ) << endl;
    cout << "End Time    : " << double( finish ) << endl;
    cout << "Actual CPU Clock time : " << duration << endl;
    cout << "Total Number of char 80 : " << numOfOccurrences << endl;
    cout << "Array Elements : ";
    displayArray( inputArr, inputSize );
    cout << endl;

}

//**************************************************
// Performs a sequential search through the given
//  array, to find the inputted item. Also
//  determines the time it took to execute the
//  function, number of swaps occured,
//  and displays the array.
//
// inputArr - Holds the array to be populated with
//            random characters
// inputSize - Holds the desired size of the array
//**************************************************
void selectionSort( char inputArr[], int inputSize )
{
    // Variable declarations
    char tempArr[inputSize];    // Holds the temporary array to
                                // be sorted
    int minIndex,               // Holds the min index found
        minItem,                // Holds the min item found
        numOfSwaps = 0;         // Tracks the number of swaps
                                // made
    char tempValue;             // Holds the temporary value
                                // to be switched
    double duration;            // Holds the duration of the time it
                                // took to execute the algorithm
    time_t start,               // Holds the start time of the algorithim
           finish;              // Holds the finish time of the algorithim

    // Create tempArr values
    copyArr( inputArr, tempArr, inputSize );

    // Log the start time of the function
    start = clock( );

    // Sort array
    for( int i = 0; i < inputSize - 1; i++ )
    {
        minIndex = i;
        minItem = tempArr[i];
        for( int j = i + 1; j < inputSize; j++ )
        {
            if( tempArr[j] < tempArr[minIndex] )
            {
                minIndex = j;
                minItem = tempArr[j];
            }
        }

        if( minItem != tempArr[i])
        {
            numOfSwaps++;
            // Swap items with the
            tempValue = tempArr[i];
            tempArr[i] = minItem;
            tempArr[minIndex] = tempValue;
        }
    }

    // Log end time
    finish = clock( );

    // Calculate the clock time
    duration = double( finish - start );

    cout << "Start Time  : " << double( start ) << endl;
    cout << "End Time    : " << double( finish ) << endl;
    cout << "Actual CPU Clock time : " << duration << endl;
    cout << "Total Number of Swaps : " << numOfSwaps << endl;
    cout << "Sorted Elements : ";
    displayArray( tempArr, inputSize );
    cout << endl;

}

//**************************************************
// Performs a insertion sort on the inputted array.
//  Also determines the time it took to execute the
//  function, number of comparisons made, and
//  displays the array.
//
// inputArr - Holds the array to be populated with
//            random characters
// inputSize - Holds the desired size of the array
//**************************************************
void insertionSort( char inputArr[], int inputSize )
{
    // Variable declarations
    char tempArr[inputSize];    // Holds temp array
    char minItem;               // Holds the min item found
    int j,                      // Holds the index for the internal
                                // while loop
        totalComps = 0;         // Holds the total number comparisons
    double duration;            // Holds the duration of the time it
                                // took to execute the algorithm
    time_t start,               // Holds the start time of the algorithim
           finish;              // Holds the finish time of the algorithim

    // Set temp array to original array
    copyArr( inputArr, tempArr, inputSize );

    // Log the start time of the function
    start = clock( );

    for( int i = 0; i < inputSize; i++ )
    {
        minItem = tempArr[i];
        j = i - 1;

        while( j >= 0 && tempArr[j] > minItem )
        {
            tempArr[j + 1] = tempArr[j];
            j--;
            totalComps++;
        }
        tempArr[j + 1] = minItem;
    }

    // Log end time
    finish = clock( );

    // Calculate the clock time
    duration = double(finish - start);

    cout << "Start Time  : " << double( start ) << endl;
    cout << "End Time    : " << double( finish ) << endl;
    cout << "Actual CPU Clock time : " << duration << endl;
    cout << "Total Number of Comparisons : " << totalComps << endl;
    cout << "Sorted Elements: ";
    displayArray( tempArr, inputSize );
    cout << endl;

}

//**************************************************
// Runs the quick sort program, as well as
// prints the execution time of the algorithm,
// and the number of recursive calls
//
// inputArr - Holds the array to be populated with
//            random characters
// inputSize - Holds the desired size of the array
// givenCase - Determines which quickSort function
//             to use
//**************************************************
void runQuickSort( char inputArr[], int inputSize, int givenCase )
{
    // Variable declarations
    char tempArr[inputSize];    // Holds temp array
    double duration;            // Holds the clock time
                                // of the algorithm
    time_t start,               // Holds the start time
                                // of the algorithm
           finish;              // Holds the finish time
                                // of the algorithm
    int numOfRecursiveCalls = 0;// Holds the number of recursive
                                // calls

    // Set temp array to original array
    copyArr( inputArr, tempArr, inputSize );

    // Log start time
    start = clock( );

    // Determine which quickSort function to run
    switch (givenCase)
    {
        case 0:
            quickSortMid( tempArr, 0, inputSize - 1, numOfRecursiveCalls );
            break;
        case 1:
            quickSortStart( tempArr, 0, inputSize - 1, numOfRecursiveCalls );
            break;
        case 3:
            // In case 3 sort the original array
            quickSortSecondLast( tempArr, 0, inputSize - 1,
                                 numOfRecursiveCalls );
    }

    // Log finish time
    finish = clock( );

    // Calculate duration
    duration = double( finish - start );

    // Quick Sort output block
    cout << "Start Time : " << start << endl;
    cout << "End Time   : " << finish << endl;
    cout << "Actual CPU Clock Time : " << duration << endl;
    cout << "Number of Recursive calls : " << numOfRecursiveCalls << endl;
    cout << "Sorted Elements: ";
    displayArray(tempArr, inputSize);

}

//**************************************************
// Performs a quick sort on the inputted array
// where the pivot is the middle
//
//
// inputArr - Holds the array to be populated with
//            random characters
// left - The left marker, used in the quick sort
// right - The right marker, used in the quick sort
// numCalls - Holds the number of recursive calls
//            done by the algorithim
//**************************************************
void quickSortMid( char inputArr[], int left, int right, int &numCalls )
{
    // Variable declarations
    int i = left,   // Holds the left position in the search
        j = right,  // Holds the right position in the search
        tmp,        // Holds the temporary value to be placed
        pivot = inputArr[((left + right)/2)];   // Holds the pivot value
                                                // to sort the array around

    // Continue iterating through until i has passed j
    while( i <= j )
    {

        // Increase i until it is at the pivot
        while( inputArr[i] < pivot )
            i++;

        // Decrease j until it is at the pivot
        while( inputArr[j] > pivot )
            j--;

        // If i is still <= to j swap the elements
        if( i <= j )
        {
            tmp = inputArr[i];
            inputArr[i] = inputArr[j];
            inputArr[j] = tmp;
            i++;
            j--;
        }

    };

    // Recursive call
    if( left < j )
    {
        quickSortMid( inputArr, left, j, numCalls );
        // Keep track of the number of calls
        numCalls++;
    }

    if( i < right )
    {
        quickSortMid( inputArr, i, right, numCalls );
        // Keep track of the number of calls
        numCalls++;
    }
}

//**************************************************
// Performs a quick sort on the inputted array
// where the pivot is the middle
//
//
// inputArr - Holds the array to be populated with
//            random characters
// left - The left marker, used in the quick sort
// right - The right marker, used in the quick sort
// numCalls - Holds the number of recursive calls
//            done by the algorithim
//**************************************************
void quickSortStart( char inputArr[], int left, int right, int &numCalls )
{
    // Variable declarations
    int i = left,   // Holds the left position in the search
        j = right,  // Holds the right position in the search
        tmp,        // Holds the temporary value to be placed
        pivot = inputArr[0];    // Holds the pivot value
                                // to sort the array around

    // Continue iterating through until i has passed j
    while( i <= j )
    {

        // Increase i until it is at the pivot
        while( inputArr[i] < pivot )
            i++;

        // Decrease j until it is at the pivot
        while( inputArr[j] > pivot )
            j--;

        // If i is still <= to j swap the elements
        if( i <= j )
        {
            tmp = inputArr[i];
            inputArr[i] = inputArr[j];
            inputArr[j] = tmp;
            i++;
            j--;
        }

    };

    // Recursive call
    if( left < j )
    {
        quickSortMid( inputArr, left, j, numCalls );
        // Keep track of the number of calls
        numCalls++;
    }

    if( i < right )
    {
        quickSortMid( inputArr, i, right, numCalls );
        // Keep track of the number of calls
        numCalls++;
    }
}

//**************************************************
// Performs a quick sort on the inputted array
// where the pivot is the second to last
// element
//
//
// inputArr - Holds the array to be populated with
//            random characters
// left - The left marker, used in the quick sort
// right - The right marker, used in the quick sort
// numCalls - Holds the number of recursive calls
//            done by the algorithim
//**************************************************
void quickSortSecondLast( char inputArr[], int left, int right, int &numCalls )
{
    // Variable declarations
    int i = left,   // Holds the left position in the search
        j = right,  // Holds the right position in the search
        tmp,        // Holds the temporary value to be placed
        pivot = inputArr[right - 2];    // Holds the pivot value
                                        // to sort the array around

    // Continue iterating through until i has passed j
    while( i <= j )
    {

        // Increase i until it is at the pivot
        while( inputArr[i] < pivot )
            i++;

        // Decrease j until it is at the pivot
        while( inputArr[j] > pivot )
            j--;

        // If i is still <= to j swap the elements
        if( i <= j )
        {
            tmp = inputArr[i];
            inputArr[i] = inputArr[j];
            inputArr[j] = tmp;
            i++;
            j--;
        }

    };

    // Recursive call
    if( left < j )
    {
        quickSortMid( inputArr, left, j, numCalls );
        // Keep track of the number of calls
        numCalls++;
    }

    if( i < right )
    {
        quickSortMid( inputArr, i, right, numCalls );
        // Keep track of the number of calls
        numCalls++;
    }
}

//**************************************************
// Copies all elements from the original
// array to the new array within the given
// size.
//
//
// originalArr - The original inputted array
// newArr - The new array to be copied over
// sizeOfArr - The desired size of the array
//**************************************************
void copyArr( char originalArr[], char newArr[], int sizeOfArr )
{
    for( int i = 0; i < sizeOfArr; i++ )
        newArr[i] = originalArr[i];
}

//**************************************************
// Generate a random character between A and }
//
//**************************************************
char ranChar( )
{
    char output = rand( ) % ( 126 - 65 ) + 65;
    return output;
}


