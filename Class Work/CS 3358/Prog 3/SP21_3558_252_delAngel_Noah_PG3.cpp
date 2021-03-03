// Author: Noah del Angel
// Due Date: 3/3/2021
// Assignment Number: 3
// Spring - 2021 - CS 3358 - 252
// Instructor:  Husain Gholoom
//
// A simulated vending machine that
// uses classes
#include <iostream>
#include <vector>

using namespace std;

//**************************************************
// This class holds the cost and number of items available
// for a particular item
//
// Private Variables:
//      numOfItems - keeps track of the number of available
//                   for that item
//      cost - keeps track of the cost of the item
// Public Functions:
//      DispenserType() - default constructor initializes
//                         numOfItems to 3
//      returnNumOfItems() - returns the number of items for that object
//      setCost(input) - sets the cost for the item
//      returnCost() - returns the cost of the item
//      reduceNumOfItems() - reduces the number of available items
//**************************************************
class DispenserType
{
    private:
        int numOfItems,
            cost;
    public:
        DispenserType()
        {
            numOfItems = 3;
        }

        int returnNumOfItems()
        {
            return numOfItems;
        }

        void setCost( int input )
        {
            cost = input;
        }

        int returnCost()
        {
            return cost;
        }

        void reduceNumOfItems()
        {
            numOfItems -= 1;
        }
};

//**************************************************
// This class keeps track of all the money flowing
// in and out of the cash register
//
// Private Variables:
//      cashOnHand - Holds the amount of cash that the register has
// Public Functions:
//      CashRegister() - default constructor sets cashOnHand to 500
//      returnCash() - returns the cashOnHand for the register
//      receiveCash(int receiveCash, int cost,
//                  DispenserType &item) - Attempts to receive cash
//                  deposited by user. If the user inputs more cash then
//                  required the function will determine the change and tell
//                  the user to collect their change. However, if the user
//                  inputs less change than the request amount, it determines
//                  how much more is required and asks the user to deposit
//                  that amount. If the user still fails to input enough
//                  change, end the transaction.  If the user fails to input
//                  enough cash twice the the function returns false, otherwise
//                  the function returns true.
//**************************************************
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

        bool receiveCash( int receiveCash, int cost, DispenserType &item );
};

// Displays menu, and runs input loop for program
void menu( DispenserType[], CashRegister & );

// Initializes array to basic state
void populateMachine( DispenserType[]  );

int main( )
{
    // Variable declarations
    DispenserType DispenserItems[4];
    CashRegister Register;

    // Populate Array
    populateMachine( DispenserItems );

    // Initialize menu
    menu( DispenserItems, Register );

    return 0;
}

//**************************************************
// Attempts to receive cash deposited by user. If the
// user inputs more cash then required the function
// will determine the change and tell the user to collect
// their change. However, if the user inputs less change
// than the request amount, it determines how much more is
// required and asks the user to deposit that amount. If
// the user still fails to input enough change, end the transaction.
// If the user fails to input enough cash twice the the function
// returns false, otherwise the function returns true.
//
// receiveCash - integer that holds cash the user
// attempts to deposit
// cost - integer that holds the cost of the item
// item - A DispenserType Object that holds the
//        item
//**************************************************
bool CashRegister::receiveCash( int receiveCash, int cost, DispenserType &item )
{
    // Variable declarations
    bool enoughCash = true;
    int delta = cost - receiveCash,
        additionalCash = 0;

    cout << endl;

    // If the cash is not enough, add the cash
    if ( receiveCash < cost )
    {
        cout << "Please deposit another " << delta << " cents" << endl;
        cin >> additionalCash;
        cout << endl;

        // If more cash is still not added
        // return the program with a false bool
        if( additionalCash < delta )
        {
            cout << "The amount is not enough. Collect what you deposited."
                 << endl;
            cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl << endl;

            enoughCash = false;

            // Return success of function
            return enoughCash;
        }
    }

    cout << "Collect your item at the bottom and enjoy." << endl;

    // If the cash is more than requested provide change
    if( (receiveCash + additionalCash ) > cost )
    {
        delta = (receiveCash + additionalCash) - cost;

        cout << "Collect your change " <<delta << endl;
    }

    // Once all required cash is recieved, add it to
    // the register. And, reduce the number of items
    cashOnHand += cost;
    item.reduceNumOfItems();

    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl << endl;

    // Return success of function
    return enoughCash;
}

//**************************************************
// Displays menu, and runs input loop for program
//
// inputItems - Holds the available items
// inputRegister - Holds the cash register object
//**************************************************
void menu( DispenserType inputItems[3], CashRegister &inputRegister )
{
    // Variable declarations
    bool continueMenu = true, correctinput = false;
    int input, index, cost, deposit;


    // Header statement
    cout << "*** Welcome to Noah del Angel's Vending Machine ***" << endl;
    cout << endl;


    // Run menu until user specifies to exit
    while( continueMenu == true )
    {
        // Reset values
        input = 0;
        index = 0;
        cost = 0;
        correctinput = true;

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
            if( !cin || input > 9 || input < 1)
                throw input;

            cout << endl;
        }
        catch(...)
        {
            cout << endl;
            cout << "Invalid selection." << endl << endl;

            // Set input to false
            correctinput = false;

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

        // If the user wishes to continue get money
        // for the item they want
        if( continueMenu == true && correctinput == true)

            // If there is still items
            if( inputItems[index].returnNumOfItems() == 0 )
            {
                cout << "Sorry, this item is sold out." << endl;
                cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl << endl;
            }
            else
            {
                // Determine cost
                cost = inputItems[index].returnCost();

                cout << "Please deposit " << cost << " cents" << endl;


                    try
                    {
                        cin >> deposit;
                        // if input breaks throw error
                        if( !cin )
                            throw input;

                        inputRegister.receiveCash( deposit, cost,
                                                   inputItems[index] );

                    }
                    catch(...)
                    {
                        cout << endl;
                        // Clear items in the cin
                        cin.clear();
                        cin.ignore(256, '\n');
                    }


            }
    }

    // Footer statement
    cout << "*** Thank you for using Noah del Angel's Vending Machine ***"
         << endl;
}

//**************************************************
// Initializes vending machine objects cost
//
// inputItems - Holds the available items
//**************************************************
void populateMachine( DispenserType inputItems[3] )
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
