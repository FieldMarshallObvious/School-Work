// Author: Noah del Angel
// Due Date: 4/12/2021
// Assignment Number: 5
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// A manipulation of linked
// lists using pointers
#include <iostream>
#include<time.h>

using namespace std;


void populateArray( int arr[], int sizeOfArr );
int * reverseArray( int arr[], int arrOriginal[], int sizeOfArr, int pos );
void displayArray( int arr[], int sizeOfArr );
void tableOfSquare( int sizeOfArr, int pos );
bool determinePrime( int num, int divisor );
int sumDigits( int input );
int generateRanNum();



int main ( )
{
    // Variable declarations
    int sizeOfArr;  // Holds the size of the array
    int *mainArr,   // Points to the first element of the main array
        *dupArr;    // Points to the first element of the duplicate array
    bool correctInput = false;

    // Header statements
    cout << "*** Welcome to My Recursion APP ***" << endl << endl;

    // Get size of array
    while(  correctInput == false )
    {
        cout << "Enter The array size.( Must be >= 5) - - > ";
        cin >> sizeOfArr;

        cout << endl;
        if( sizeOfArr < 5 )
        {
            cout << endl << endl;
            cout << "Invalid arrays size. Size must >= 5." << endl
                 << endl;
        }
        else
            correctInput = true;
    }

    // Create a array with that size
    mainArr = new int[sizeOfArr];
    dupArr = new int[sizeOfArr];

    // Create seed
    srand( time( NULL ) );

    // Populate array
    populateArray(mainArr, sizeOfArr - 1);

    // Display new generated array
    cout << "The generated array is : ";
    displayArray( mainArr, sizeOfArr );
    cout << endl << endl;

    // Reverse array
    mainArr = reverseArray(dupArr, mainArr, sizeOfArr - 1, 0);

    // Display Array in reverse
    cout << "Reversed Array is : ";
    displayArray( mainArr, sizeOfArr );
    cout << endl << endl;




    // Table of square values from 1 to N
    cout << "Table of square values from 1 to  " << sizeOfArr << " is : "
         << endl << endl;

    cout << "N      N Squared" << endl;
    tableOfSquare( sizeOfArr, sizeOfArr - 1 );

    cout << endl << endl;

    // Output sum of digits in first element
    cout << "Sum of " << mainArr[0] << " digits is : "
         << sumDigits( mainArr[0] ) << endl;

    cout << endl << endl;


    // Output last item of array
    cout << "Is " << mainArr[sizeOfArr - 1] << " Prime Number : "
         << mainArr[sizeOfArr - 1 ] << " is";

    // Determine if last item in array is prime
    if( determinePrime( mainArr[sizeOfArr - 1], 2 )  )
        cout << " a prime number " << endl;

    else
        cout << " not a prime number " << endl;

    // Footer Statement
    cout << endl << endl;
    cout << "Noah del Angel -Tweak Programming Director" << endl
         << "April 2021" << endl;

}

//**************************************************
// Recursively populates the array with random
// integers
//
// arr - Holds the to be populated
//**************************************************
void populateArray( int arr[], int sizeOfArr )
{
    // If there is still more items to add
    // add them
    if( sizeOfArr >= 0 )
    {
        // Generate random num
        arr[sizeOfArr] = generateRanNum(  );

        // Recursively move to next item
        populateArray( arr, sizeOfArr - 1 );
    }

    // If there is no more size remaining
    // return
    else if( sizeOfArr <= 0 )
        return;
}

//**************************************************
// Recursively reverses the original inputted
// array. Then returns that reversed that array
//
// arr - Holds the array
// arrOriginal - Holds the original array
// sizeOfArr - Holds the size of the array
// pos - Holds the current position in the new array
//
// returns a reversed array
//**************************************************
int * reverseArray(int arr[], int arrOriginal[], int sizeOfArr, int pos )
{

    // If there still more items in the array
    // continue recursively adding them to arr
    if( sizeOfArr >= 0 )
    {
        arr[pos] = arrOriginal[sizeOfArr];
        reverseArray( arr, arrOriginal, sizeOfArr - 1, pos + 1 );
    }

    // If not, exit recursive function
    // and return arr
    else
        return arr;
}

//**************************************************
// Display each item of the array via for loop
//
// arr - Holds the array
// sizeOfArr - Holds the size of the array
//**************************************************
void displayArray( int arr[], int sizeOfArr )
{
    // Iterate through the array
    // and output each element
    for( int i = 0; i < sizeOfArr; i++ )
        cout << arr[i] << " ";
}

//**************************************************
// Recursively creates a table of squares
// to N
//
// sizeOfArr - Holds the size of the array
// pos - Holds the position to be squared
//
// returns bool value if the number is prime or not
//**************************************************
void tableOfSquare( int sizeOfArr, int pos )
{
    // Variable declarations
    int curPos = sizeOfArr + ( -1 * pos );  // Determine the number
                                            // to be squared
    pos = pos - 1;

    if( pos == -2 )
        return;
    else
    {
        cout << curPos << "      " << ( curPos * curPos ) << endl;
        tableOfSquare( sizeOfArr, pos );
    }
}

//**************************************************
// Recursively determines whether the inputted
// number is prime based on the inputted divisor
//
// num - Holds the number that will be determined
//       to be prime or not
// divisor - Holds the divisor that the num
//           will be tested with
//
// returns bool value if the number is prime or not
//**************************************************
bool determinePrime( int num, int divisor )
{
    // If the inputted number is less than 2,
    // and it does not equal two, it is prime
    if( num <= 2 )
        return ( num == 2 ) ? true : false;

    // If inputted number modulo diviser
    // equals 0 it is not prime
    if( num % divisor == 0 )
        return false;

    // If the square of the divisor is
    // greater than the inputted number
    // it is prime
    if( divisor * divisor > num )
        return true;

    // Check next divisor
    return determinePrime( num, divisor + 1 );
}


//**************************************************
// Recursively sums the digits of the inputted
// integer
//
// input - Holds the digits that will be summed up
//
// returns the sum of the digits
//**************************************************
int sumDigits( int input )
{
    // Variable declarations
    int digit = 0; // Holds the sum of the digits

    // If the digit is greater than 10,
    // continue recursively till you get\
    // the digit
    if( input >= 10 )
        digit = sumDigits( input / 10 );

    // Set the digit equal to the digit plus
    // the digit from the input
    digit = digit + input % 10;

    // Exit the recursive function
    // and return the summed digit
    return digit;


}


//**************************************************
// Generates random integer between 100 and 5896
//
// returns random integer
//**************************************************
int generateRanNum()
{
    int output = rand( ) % 5896 + 100;
    return output;
}
