// Author: Noah del Angel
// Due Date: 3/3/2021
// Assignment Number: 3
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// Description of purpose of program
#include <iostream>
#include <vector>

using namespace std;

class CashRegister
{
    private:
        int cashOnHand;
    public:
        CashRegister()
        {
            cashOnHand = 500;
        }

        int returnCash()
        {
            return cashOnHand;
        }

        bool recieveCash( int recieveCash, int cost );
};

bool CashRegister::recieveCash( int recieveCash, int cost )
{
    // Variable declarations
    bool enoughCash = true;
    int delta = cost - recieveCash,
        additionalCash;

    // If the cash is not enough, add the cash
    if ( recieveCash != cost )
    {
        cout << "Please deposit another " << delta << " cents" << endl;
        cin >> additionalCash;

        // If more cash is still not added
        // return the program with a false bool
        if( additionalCash != delta )
        {
            cout << "The amount is not enough. Collect what you deposited."
                 << endl;
            cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl << endl;

            enoughCash = false;
            return recieveCash;
        }
    }

    // Once all required cash is recieved, add it to
    // the register.
    cashOnHand += cost;


    return recieveCash;
}

class DispenserType
{
    private:
        int numOfItems,
            cost;
    public:
        Dispenser()
        {
            numOfItems = 3;
        }

        int returnNumOfItems()
        {
            return numOfItems;
        }

        int setCost( int input )
        {
            cost = input;
        }

        int returnCost()
        {
            return cost;
        }

        int reduceNumOfItems()
        {
            numOfItems -= 1;
        }
};

void menu( DispenserType[], CashRegister & );
void populateMachine( DispenserType[]  );

int main( )
{
    // Variable declarations
    DispenserType DispenserItems[3];
    CashRegister Register;

    // Populate Array
    populateMachine( DispenserItems );

    // Initialize menu
    menu( DispenserItems, Register );

    return 0;
}

void menu( DispenserType inputItems[9], CashRegister &InputRegister )
{
    // Variable declarations
    bool continueMenu = true, correctinput = false;
    int input, index, cost, deposit;


    // Header statement
    cout << "*** Welcome to Noah del Angel's Vending Machine ***" << endl;


    // Run menu until user specifies to exit
    while( continueMenu == true )
    {
        // Reset values
        input = 0;
        index = 0;
        cost = 0;
        correctinput = false;

        cout << "Select One of the following" << endl << endl;
        cout << "     1 for Candy" << endl;
        cout << "     2 for Chips" << endl;
        cout << "     3 for Gum" << endl;
        cout << "     4 for Cookies" << endl;
        cout << "     9 to exit" << endl;
        cout << endl;


        // Catch non-integer inputs
        try
        {
            cin >> input;

            // if input breaks throw error
            if( !cin )
                throw input;
        }
        catch(...)
        {
            cout << "Invalid selection." << endl << endl;

            // Clear items in the cin
            cin.clear();
            cin.ignore(256, '\n');
        }

        // Determine input
        switch(input)
        {
            case 1:
                index = 0;
                break;

            case 2:
                index = 1;
                break;

            case 3:
                index = 2;
                break;

            case 4:
                index = 3;
                break;

            case 9:
                continueMenu = false;
                break;
        }

        if( inputItems[index].returnNumOfItems() == 0 )
        {
            cout << "Sorry, this item is sold out." << endl;
            cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
        }
        else
        {
            // Determine cost
            cost = inputItems[index].returnCost();

            cout << "Please deposit " << cost << " cents" << endl;

            while( correctinput == false )
            {
                try
                {
                    cin >> deposit;
                    // if input breaks throw error
                    if( !cin )
                        throw input;

                    correctinput = true;
                }
                catch(...)
                {
                    cout << "Please enter an integer" << endl << endl;

                    // Clear items in the cin
                    cin.clear();
                    cin.ignore(256, '\n');
                }

            }

            InputRegister.recieveCash( deposit, cost );

        }
    }

    // Footer statement
    cout << "*** Thank you for using Noah del Angel's Vending Machine ***"
         << endl;
}

void populateMachine( DispenserType inputItems[9] )
{
    // Initialize array
    for( int i = 0; i < 4; i++ )
    {
        switch ( i )
        {
        case 0:
            inputItems[i].setCost(50);
            break;

        case 1:
            inputItems[i].setCost(25);
            break;
        case 2:
            inputItems[i].setCost(45);
            break;
        case 3:
            inputItems[i].setCost(60);
            break;
        }
    }
}
