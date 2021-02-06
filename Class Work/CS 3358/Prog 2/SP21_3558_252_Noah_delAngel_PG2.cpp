// Author: Noah del Angel
// Due Date: 2/15/2021
// Assignment Number: 2
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// Manipulation of two dimensional arrays

#include <iostream>
#include<vector>

void menu( char[][13] );
void printSeatRow( char[][13] );
void modifySeatingChart( char, char[][13] );
void initSeatingChart( char[][13] );

using namespace std;

int main ( )
{
    char seatingChar[6][13];
    menu(seatingChar);
    return 0;
}

void menu( char seatingChart[][13] )
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

        if( inputClass == 'F' || inputClass == 'B' || inputClass == 'E' )
        {
            modifySeatingChart(inputClass,seatingChart);
            passed = true;
        }

        else if( inputClass == 'X' )
            endApp = true;

        else
            cout << "Invalid Choice" << endl
                 << endl;

        if( passed == true )
        {
            endQ = false;
            while( endQ == false )
            {
                cout << "Would you like to Assign another seat? (Y/N) -- ";

                cin >> assignAnotherSeat;

                assignAnotherSeat = toupper(assignAnotherSeat);

                cout << endl;

                if( assignAnotherSeat == 'Y' )
                {
                    endApp = false;
                    endQ = true;
                }

                else if( assignAnotherSeat == 'N' )
                {
                    endApp = true;
                    endQ = true;
                }
            }



        }

        // Reset vars
        passed = false;
    }

}

void modifySeatingChart( char row, char seatingChart[][13] )
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
            maxRow = 6;
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
                    charIndex = 'A';
                    index = 0;
                    while( charIndex != seatloc )
                        charIndex++;
                        index++;
                    seatingChart[rowNum][index] = 'X';
                    foundSeat = true;

                    cout << "Seat: Row " << rowChar << " Seat " << seatloc
                         << " is assigned" << endl;

                }

                else
                    cout << "Invalid Seat" << endl;

            else
                cout << "Invalid Row Number2" << endl;

        }

        else
            cout << "Invalid Row Number1" << endl;
    }

}

