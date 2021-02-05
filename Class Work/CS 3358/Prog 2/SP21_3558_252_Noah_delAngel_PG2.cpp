// Author: Noah del Angel
// Due Date: 2/15/2021
// Assignment Number: 2
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// Manipulation of two dimensional arrays

#include <iostream>
#include<vector>

void menu( );
std::string printMainMenu( );
void printSeatRow( );
void seatingChart( );

using namespace std;

int main ( )
{
    menu();
    return 0;
}

void menu( )
{
    // Variable declarations
    char inputClass;
    bool endApp = false;

    while( endApp == false )
    {
        cout << "Enter Your Ticket Type" << endl << endl;

        cout << "     1. Enter D for Displaying the Seating Chart" << endl;
        cout << "     2. Enter F for First class" << endl;
        cout << "     3. Enter B for Business Class" << endl;
        cout << "     4. Enter E for Economy class" << endl;
        cout << "     5. Enter x to Exit the App.  ";
    }

}

string printMainMenu( )
{
    // Variable declarations
    char inputClass;

    cout << "Enter Your Ticket Type" << endl << endl;

    cout << "     1. Enter D for Displaying the Seating Chart" << endl;
    cout << "     2. Enter F for First class" << endl;
    cout << "     3. Enter B for Business Class" << endl;
    cout << "     4. Enter E for Economy class" << endl;
    cout << "     5. Enter x to Exit the App.  ";

    cin >> inputClass;

    return inputClass;
}
