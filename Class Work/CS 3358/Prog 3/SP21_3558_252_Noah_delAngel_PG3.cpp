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
            cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*";

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
    bool continueMenu = true;

    while( continueMenu == true )
    {

    }

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
