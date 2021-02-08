// Author: Noah del Angel
// Due Date: 2/15/2021
// Assignment Number: 2
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// Manipulation of two dimensional arrays

#include <iostream>
#include<vector>

void menu( char[][7] );
void printChart( char[][7] );
void modifySeatingChart( char, char[][7] );
void initSeatingChart( char[][7] );

using namespace std;

int main ( )
{
    char assignedSeats[13][7];

    cout << "Welcome to My Airline APP." << endl << endl;
    cout << "The purpose of this app is to assign seats for your reservation."
         << endl;
    cout << "This airplane has 13 rows. with six seats in each row." << endl
         << endl;
    cout << "     - Rows 1 and 2 are first class" << endl;
    cout << "     - Rows 3 and 7 are business class" << endl;
    cout << "     - Rows 8 through 13 are economy class " << endl << endl;

    initSeatingChart( assignedSeats);
    menu(assignedSeats);

    cout << "Thanks for using this APP." << endl;
    cout << "Noah del Angel" << endl;
    cout << "2 - 15 - 2021" << endl;
    return 0;
}

void menu( char seatingChart[][7] )
{
    // Variable declarations
    char inputClass,
         assignAnotherSeat;
    bool endApp = false,
         endQ = false,
         passed = false;

    while( endApp == false )
    {
        cout << "Enter Your Ticket Type" << endl << endl;

        cout << "     1. Enter D for Displaying the Seating Chart" << endl;
        cout << "     2. Enter F for First class" << endl;
        cout << "     3. Enter B for Business Class" << endl;
        cout << "     4. Enter E for Economy class" << endl;
        cout << "     5. Enter x to Exit the App.  ";

        cin >> inputClass;

        inputClass = toupper(inputClass);

        cout << endl;


        // Determine the option chosen by the menu
        if( inputClass == 'D' )
        {
            printChart( seatingChart );
            passed = true;
        }

        else if( inputClass == 'F' || inputClass == 'B' || inputClass == 'E' )
        {
            modifySeatingChart(inputClass,seatingChart);
            passed = true;
        }

        else if( inputClass == 'X' )
            endApp = true;

        else
            cout << "Invalid Choice" << endl
                 << endl;

        // If a seat assignment option has been chosen
        // Ask the user if they want to assign the seat again
        if( passed == true )
        {
            endQ = false;

            // Continue the loop until a valid option has been enterd
            while( endQ == false )
            {
                cout << "Would you like to Assign another seat? (Y/N) -- ";

                cin >> assignAnotherSeat;

                assignAnotherSeat = toupper(assignAnotherSeat);

                cout << endl;

                // If the user enters yes, break this loop
                // and continue the program
                if( assignAnotherSeat == 'Y' )
                {
                    endApp = false;
                    endQ = true;
                }

                // If the user enters no, break this loop
                // and end the program
                else if( assignAnotherSeat == 'N' )
                {
                    endApp = true;
                    endQ = true;
                }

                else
                {
                    cout << "Please enter a valid option." << endl << endl;
                }
            }



        }

        // Reset vars
        passed = false;
    }

}

void printChart( char seatingChart[][7] )
{
    for( int i = 0; i < 13; i++ )
    {
        cout << "Row " << i + 1;
        if( i < 9 )
            cout << "   ";
        else
            cout << "  ";
        for( int j = 0; j < 7; j++ )
            cout << seatingChart[i][j] << " ";
        cout << endl;
    }
}

void modifySeatingChart( char row, char seatingChart[][7] )
{
    // Variable declarations
    int index, minRow, maxRow, rowNum;
    bool foundSeat = false;
    char rowChar, seatloc, charIndex;
    string possibleRows;

    // Determine row
    switch(row)
    {
        case 'F':
            index = 0;
            possibleRows = "( 1 - 2 )";
            minRow = 0;
            maxRow = 1;
            break;

        case 'B':
            index = 2;
            possibleRows = "( 3 - 7 )";
            minRow = 2;
            maxRow = 7;
            break;

        case 'E':
            index = 7;
            possibleRows = "( 8 - 13 )";
            minRow = 7;
            maxRow = 12;
            break;
    }

    while( foundSeat == false )
    {
        cout << "Enter Row" << possibleRows << "and seat ( A - F ) " << endl;
        cout << "Enter Row ";
        cin >> rowChar;

        cout << "Enter Seat ";
        cin >> seatloc;
        cout << endl;

        // Convert seat location char to uppercase
        seatloc = toupper(seatloc);

        // Check if the rowChar is a digit
        if( isdigit( rowChar ) )
        {
            rowNum = (int)rowChar - 48;

            // Check if is in range
            if( rowNum - 1 >= minRow && rowNum - 1 <= maxRow )
                // Check if seat is within range
                if( seatloc >= 'A' && seatloc <= 'F' )
                {
                    // Determine the location of the seat
                    charIndex = 'A';
                    index = 0;
                    while( charIndex != seatloc )
                        charIndex++;
                        index++;

                    // Assign the position in the seating chart to X
                    seatingChart[rowNum-1][index-1] = 'X';

                    // End loop
                    foundSeat = true;

                    // Display assigned seat
                    cout << "Seat: Row " << rowChar << " Seat " << seatloc
                         << " is assigned" << endl;

                }

                else
                    cout << "Invalid Seat" << endl;

            else
                cout << "Invalid Row Number" << endl;

        }

        else
            cout << "Invalid Row Number1" << endl;
    }

}

void initSeatingChart( char seatingChart[][7] )
{
    for( int i = 0; i < 14; i++ )
        for( int j = 0; j < 7; j++ )
            seatingChart[i][j] = '*';
}

