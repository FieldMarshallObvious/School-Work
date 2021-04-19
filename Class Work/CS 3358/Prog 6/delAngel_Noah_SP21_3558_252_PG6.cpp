#include <iostream>
#include <time.h>


using namespace std;

void generateArray( char inputArr[], int inputSize );
void displayArray( char inputArr[], int inputSize );
void sequentialSearch( char inputArr[], int inputSize, char item );
void selectionSort( char inputArr[], int inputSize );
void insertionSort( char inputArr[], int inputSize );
void runQuickSort( char inputArr[], int left, int right, int inputSize );
void quickSort( char inputArr[], int left, int right, int &numCalls );
void copyArr( char originalArr[], char newArr[], int sizeOfArr );
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

        // Display Starting Array
        cout << "Array elements are: ";
        displayArray( originalArr, sizeArr );
        cout << endl;

        // Search using Sequential Search
        cout << endl << endl;
        cout <<  "Sequential Search" << endl << endl;
        cout << "Search for  Char " << (int) itemToFind << endl << endl;
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
        runQuickSort( originalArr, 0, sizeArr - 1, sizeArr );

        cout << endl << endl;
        cout << "Quick Sort - The next to last element as a pivot: " << endl
             << endl;
        runQuickSort( originalArr, sizeArr - 4, sizeArr - 1, sizeArr);




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
    if( inputSize > 20 )
        inputSize = 20;

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
    double duration;
    time_t start,
           finish;

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
    finish = clock();

    // Calculate the clock time
    duration = double(finish - start);

    cout << "Char " << itemToFind << " Was";

    if( foundItem == true )
        cout << " Not found." << endl;
    else
        cout << " found." << endl;

    cout << "Start Time  : " << double(start) << endl;
    cout << "End Time    : " << double(finish) << endl;
    cout << "Actual CPU Clock time : " << duration << endl;
    cout << "Total Number of char 80 : " << numOfOccurrences << endl;
    cout << "Array Elements : ";
    displayArray( inputArr, inputSize );
    cout << endl;

}

void selectionSort( char inputArr[], int inputSize )
{
    // Variable declarations
    char tempArr[inputSize];
    int minIndex,
        minItem,
        numOfSwaps = 0;
    char tempValue;
    double duration;
    time_t start,
           finish;

    // Create tempArr values
    copyArr( inputArr, tempArr, inputSize );

    // Log the start time of the function
    start = clock();

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
            cout << "New Arr ";
            displayArray(tempArr, inputSize);
            cout << endl;
        }
    }

    // Log end time
    finish = clock();

    // Calculate the clock time
    duration = double(finish - start);

    cout << "Start Time  : " << double(start) << endl;
    cout << "End Time    : " << double(finish) << endl;
    cout << "Actual CPU Clock time : " << duration << endl;
    cout << "Total Number of Swaps : " << numOfSwaps << endl;
    cout << "Sorted Elements : ";
    displayArray( tempArr, inputSize );
    cout << endl;

}

void insertionSort( char inputArr[], int inputSize )
{
    // Variable declarations
    char tempArr[inputSize];    // Holds temp array
    char minItem;
    int j,
        totalComps = 0;
    double duration;
    time_t start,
           finish;

    // Set temp array to original array
    copyArr( inputArr, tempArr, inputSize );
    // Log the start time of the function
    start = clock();

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
    finish = clock();

    // Calculate the clock time
    duration = double(finish - start);

    cout << "Start Time  : " << double(start) << endl;
    cout << "End Time    : " << double(finish) << endl;
    cout << "Actual CPU Clock time : " << duration << endl;
    cout << "Total Number of Comparisons : " << totalComps << endl;
    cout << "Sorted Elements: ";
    displayArray( tempArr, inputSize );
    cout << endl;

}

void runQuickSort( char inputArr[], int left, int right, int inputSize )
{
    // Variable declarations
    char tempArr[inputSize];    // Holds temp array
    double duration;
    time_t start,
           finish;
    int numOfRecursiveCalls = 0;

    // Set temp array to original array
    copyArr( inputArr, tempArr, inputSize );

    // Log start time
    start = clock();
    quickSort( tempArr, left, right, numOfRecursiveCalls );

    // Log finish time
    finish = clock();

    // Calculate duration
    duration = double(finish - start);

    // Quick Sort output block
    cout << "Start Time : " << start << endl;
    cout << "End Time   : " << finish << endl;
    cout << "Actual CPU Clock Time : " << duration << endl;
    cout << "Number of Recursive calls : " << numOfRecursiveCalls << endl;
    cout << "Sorted Elements: ";
    displayArray(tempArr, inputSize);

}
void quickSort( char inputArr[], int left, int right, int &numCalls )
{
    // Variable declarations
    int i = left,
        j = right,
        tmp,
        pivot = inputArr[(left + right)/2];


        while( i <= j )
        {
            while( inputArr[i] < pivot )
                i++;

            while( inputArr[j] > pivot )
                j--;

            if( i <= j )
            {
                tmp = inputArr[i];
                inputArr[i] = inputArr[j];
                inputArr[j] = tmp;
                i++;
                j--;
            }

            if( left < j )
            {
                quickSort( inputArr, left, j, numCalls );
                numCalls++;
            }
            if( i < right )
            {
                quickSort( inputArr, i, right, numCalls );
                numCalls++;
            }

        }
}

void copyArr( char originalArr[], char newArr[], int sizeOfArr )
{
    for( int i = 0; i < sizeOfArr; i++ )
        newArr[i] = originalArr[i];
}

char ranChar()
{
    char output = rand( ) % ( 126 - 65 ) + 65;
    return output;
}


