// Author: Noah del Angel
// Due Date: 2/15/2021
// Assignment Number: 2
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// Manipulation of two dimensional arrays

#include <iostream>
#include <vector>

using namespace std;


void menu( vector < vector<char> > & );
void printChart( vector < vector<char> >  );
void modifySeatingChart( char row, vector < vector<char> > & );
void initSeatingChart( vector < vector<char> > & );


int main ( )
{
    vector<char> initializerRow;

    vector<vector<char> > assignedSeats(0, initializerRow);

    cout << "Welcome to My Airline APP." << endl << endl;
    cout << "The purpose of this app is to assign seats for your reservation."
         << endl;
    cout << "This airplane has 13 rows. with six seats in each row." << endl
         << endl;
    cout << "     - Rows 1 and 2 are first class" << endl;
    cout << "     - Rows 3 and 7 are business class" << endl;
    cout << "     - Rows 8 through 13 are economy class " << endl << endl;

    initSeatingChart( assignedSeats );
    menu(assignedSeats);

    cout << "Thanks for using this APP." << endl;
    cout << "Noah del Angel" << endl;
    cout << "2 - 15 - 2021" << endl;
    return 0;
}

//**************************************************
// Populates array with random numbers
//
// seatingChart - Vector array that holds the seating
// chart for the Airline APP
//**************************************************
void menu( vector<vector<char> > &seatingChart )
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
        cout << "     5. Enter X to Exit the App.  ";

        cin >> inputClass;

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

//**************************************************
// Prints the seating chart to the console
//
// seatingChart - Vector array that holds the seating
// chart for the Airline APP
//**************************************************
void printChart( vector<vector<char> > seatingChart )
{
    cout << "        A   B   C   D   E   F" << endl << endl;
    for( int i = 0; i < 13; i++ )
    {
        cout << "Row " << i + 1;
        if( i < 9 )
            cout << "   ";
        else
            cout << "  ";
        for( int j = 0; j < 6; j++ )
            cout << seatingChart[i][j] << "   ";
        cout << endl;
    }
}

//**************************************************
// Assigns seats to the chart if there are available
// to 'X'
//
// seatingChart - Vector array that holds the seating
// chart for the Airline APP
//**************************************************
void modifySeatingChart( char row, vector<vector<char> > &seatingChart )
{
    // Variable declarations
    int stindex = 0, index, minRow, maxRow, rowNum;
    bool foundSeat = false,
         isInt = true;
    char rowChar, seatloc, charIndex;
    string possibleRows, inputRow;

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
        cin >> inputRow;

        cout << "Enter Seat ";
        cin >> seatloc;
        cout << endl;

        // Check each string of inputRow to determine
        // if it is a digit
        while( stindex < inputRow.length() )
        {
            if( ! isdigit( inputRow[stindex] ) )
                isInt = false;
            stindex++;

        }

        // Check if the rowChar is a digit
        if( isInt )
        {
            rowNum = stoi(inputRow);

            // Check if is in range
            if( rowNum - 1 >= minRow && rowNum - 1 <= maxRow )
                // Check if seat is within range
                if( seatloc >= 'A' && seatloc <= 'F' )
                {
                    // Determine the location of the seat
                    charIndex = 'A';
                    index = 0;
                    while( charIndex != seatloc )
                    {
                        charIndex++;
                        index++;
                    }

                    // Check if the seat is assigned
                    if( seatingChart[rowNum-1][index] != 'X' )
                    {
                        // Assign the position in the seating chart to X
                        seatingChart[rowNum-1][index] = 'X';

                        // End loop
                        foundSeat = true;

                        // Display assigned seat
                        cout << "Seat: Row " << inputRow << " Seat " << seatloc
                             << " is assigned" << endl;
                    }

                    else
                        cout << "This seat is already assigned" << endl << endl;

                }

                else
                    cout << "Invalid Seat" << endl << endl;

            else
                cout << "Invalid Row Number" << endl << endl;

        }

        else
            cout << "Invalid Row Number" << endl << endl;

        // Reset vars
        isInt = true;
        stindex = 0;
    }

}

//**************************************************
// Resize seating chart to the correct array
// then initialize all elements to '*'
//
// seatingChart - Vector array that holds the seating
// chart for the Airline APP
//**************************************************
void initSeatingChart( vector<vector<char> > &seatingChart )
{
    // Resize matrix
    seatingChart.resize( 13, vector<char>( 6 ) );

    for( int i = 0; i < 13; i++ )
        for( int j = 0; j < 6; j++ )
            seatingChart[i][j] = '*';
}

