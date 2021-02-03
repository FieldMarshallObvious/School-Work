// Author: Noah del Angel
// Due Date: 2/3/2021
// Assignment Number: 1
// Spring - 2016   -  CS 33SIZE8   -  2SIZE2
// Instructor:  Husain Gholoom
//
// Manipulation of two dimensional arrays

#include <iostream>
#include <time.h>
#include <string>


void populateArray( int[][5] );
void printArray( int[][5] );
void displayPrimeNums( int[][5] );
void sortArray( int[][5] );
void displayMathOperations( int[][5] );
void displayEvens( int[][5] );
void displayOdds( int[][5] );
std::string removeTail( std::string );
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

    sortArray( randArray );


    cout << endl;

    displayMathOperations( randArray );

    cout << endl;

    cout << "The Smallest is: " << randArray[0][0] << endl << endl;
    cout << "The Largest is: " << randArray[6][( SIZE - 1 )] << endl << endl;

    cout << "Even Numbers are : ";
    displayEvens( randArray );
    cout << endl;

    cout << "Odd Numbers are : ";
    displayOdds( randArray );
    cout << endl;

    cout << "All prime numbers are : ";
    displayPrimeNums( randArray );
    cout << endl;

    cout << "The Array after Sort : " << endl;
    printArray(randArray);

    return 0;



}

//**************************************************
// Populates array with random numbers
//
// arr[][SIZE]-input array to function
//**************************************************
void populateArray( int arr[][SIZE]  )
{
    // Populate each array element with a random num
    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
            arr[i][j] = generateRanNum();
}

//**************************************************
// Prints the passed array
//
// arr[][SIZE]-input array to function
//**************************************************
void printArray( int arr[][SIZE] )
{
    // Go through each element and print them out
    for( int i = 0; i < 7; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
                cout << arr[i][j] << "     ";
        // At the end of each row start a new line
        cout << endl;
    }
}

//**************************************************
// Finds and displays prime numbers
//
// arr[][SIZE]-input array to function
//**************************************************
void displayPrimeNums ( int arr[][SIZE] )
{
    // Variable declarations
    bool isPrime;
    string output = "";

    // Iterate through each element in the array
    // To see if it's prime
    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
        {
            // Reset bool value
            isPrime = true;

            // If the element is it is not prime
            if( arr[i][j] ==  1 )
                isPrime = false;

            // If the element is not one check
            else
            {
                // Iterate through all numbers less than
                // the element to check if it's divisible
                for( int y = 2; y <= arr[i][j] - 1; y++ )

                    if( (arr[i][j] % y) == 0 )
                        isPrime = false;

            }


            // If the element is prime
            // then add it to the string
            if( isPrime == true )
            {
                output += to_string(arr[i][j]) + ", ";
            }
        }

    // Prune tailing comma's
    output = removeTail(output);

    cout << output << endl;
}

//**************************************************
// Sorts the array from least to greatest
// using selection sort
//
// arr[][SIZE]-input array to function
//**************************************************
void sortArray ( int arr[][SIZE] )
{
    // Variable declarations
    int curMinRow,
        curMinCol,
        numMin;

    for( int i = 0; i < 7; i++ )
    {
        for( int j = 0; j < SIZE; j++ )
        {

            // Initialize min value
            curMinCol = i;
            curMinRow = j;
            numMin = arr[i][j];

            // Find a lower min value in the row
            for( int z = j+1; z < SIZE; z++ )
                if( arr[i][z] < numMin )
                {
                    curMinRow = i;
                    curMinCol = z;
                    numMin = arr[i][z];
                }

            // Check remaining rows for a lower value
            for( int z = i + 1; z < 7; z++ )
                for( int y = 0 ; y < SIZE; y++ )
                    if( arr[z][y] < numMin )
                    {
                        curMinRow = z;
                        curMinCol = y;
                        numMin = arr[z][y];
                    }

            // Swap elements with minium
            arr[curMinRow][curMinCol] = arr[i][j];
            arr[i][j] = numMin;

        }
    }
}

//**************************************************
// Performs operations average, sum,
// and subtraction
//
// arr[][SIZE]-input array to function
//**************************************************
void displayMathOperations ( int arr[][SIZE] )
{
    // Variable declarations
    int sum,
        average,
        iterations = 0;

    // Output the sum
    cout << "The Sum is : ";
    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
            sum += arr[i][j];
    cout << sum << endl << endl;

    // Output the average
    cout << "The Average is : ";
    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
        {
            iterations++;
            average+= arr[i][j];
        }
    average = average/iterations;
    cout << average << endl;
}

//**************************************************
// Finds and displays all even numbers in the
// array
//
// arr[][SIZE]-input array to function
//**************************************************
void displayEvens ( int arr[][SIZE] )
{
    // Variable declarations
    string evenNums = "";

    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
        {
            // Check each element to see if it
            // is even
            if( arr[i][j]%2 == 0 )
            {
                // add the element to
                // the string
                evenNums += to_string(arr[i][j]) += ", ";
            }

        }

    // Prune tailing commas
    evenNums = removeTail(evenNums);

    // Print evens
    cout << evenNums << endl;
}

//**************************************************
// Finds and displays all odd numbers in the
// array
//
// arr[][SIZE]-input array to function
//**************************************************
void displayOdds ( int arr[][SIZE] )
{
    // Variable declarations
    string oddNums = "";

    for( int i = 0; i < 7; i++ )
        for( int j = 0; j < SIZE; j++ )
        {
            // Check each element to see if it
            // is odd
            if( arr[i][j]%2 != 0 )
            {
                // Add the element to
                // the string
                oddNums += to_string(arr[i][j]) + ", ";
            }

        }

    // Prune tailing commas
    oddNums = removeTail(oddNums);

    // Print odds
    cout << oddNums << endl;

}

//**************************************************
// Removes comma tails from the end of
// string inputs
//
// input-string input
//
// returns altered string
//**************************************************
string removeTail( string input )
{
    // If the second to last
    // element is a comma remove
    // if from the string
    if( input[(input.length() - 2 )] == ',' )
        return input.substr(0, input.length() - 2);

    // Return otherwise
    return input;
}


//**************************************************
// Generates random integer between 100 and 1
//
// returns random integer
//**************************************************
int generateRanNum( )
{
    int output = (rand() % 101 ) + 1;
    return output;
}
