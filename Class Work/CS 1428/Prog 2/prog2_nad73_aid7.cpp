/*
   File: prog2_nad73_aid7.cpp

   Author: Noah del Angel & Alyssa De La Cruz
   C.S.1428.001
   Lab Section: L32 & L06
   Program: #2
   Due Date: 10/02/19

   This program prompts the user to enter the amount of a purchase (in cents).
   It then prompts the user to enter the amount received in payment (in cents).
   It calculates the amount of change due, printing the results to an output
   file. The author's identifying information is provided followed by the
   number of each coin to be given in change: the number of dollars, half
   dollars, quarters, dimes, nickels and pennies are listed in tabular form.
   Monetary amounts are displayed to two decimal places.

   An appropriate message is displayed to the console screen if the output
   file fails to open.

   An appropriate message is written to the console screen informing the
   user of the output file name to which the results have been written.
   The layout and content of the file output are shown in the sample below.

   Input (keyboard):
          purchase amount, integer (in cents)
          payment amount, integer (in cents)

   Constants: none

   Output (screen):

         Author's Name
         C.S.1428.?         // '?' represents three-digit lecture section number
         Lab Section: L?    // '?' represents two-digit lab section number
         --/--/--           // dashes represent due date, month/day/year
              <blank line>
              <blank line>
         <Appropriate message indicating the name of the output file.>

   Output (file - prog2_?out.txt): // '?' represents three-digit lecture sec #

         Author's Name
         C.S.1428.?         // '?' represents three-digit lecture section number
         Lab Section: L?    // '?' represents two-digit lab section number
         --/--/--           // dashes represent due date, month/day/year
              <blank line>
         Received ? for a purchase of ?
              <blank line>
            Change in coins:
         Coin           Number
         ---------------------
         Dollars          ?
         Half Dollars     ?
         Quarters         ?
         Dimes            ?
         Nickels          ?
         Pennies          ?

   ================================================

   <Output will vary based on actual input values.>
*/

#include<iostream>
#include<fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main ( )
{
    int price_recieved,
        purchase_amount,
        change,
        dollars,
        half_dollars,
        quarters,
        dimes,
        nickels;

    ofstream output_file;
    output_file.open("prog1_nad73_aid7out.txt");
    if ( !output_file )
    {
        cout << endl << endl
             << "***Program Terminated.***" << endl << endl
             << "Output file failed to open!" << endl;
        return 1;
    }

    cout << "Enter the amount of the purchase (in cents): ";
    cin >> purchase_amount;
    cout << endl;

    cout << "Enter the amount recieved in payment (in cents): ";
    cin >> price_recieved;
    cout << endl;

    change = price_recieved - purchase_amount;

    if ( change >= 100 )
    {
        dollars = change/100;
        change = change%100;
    }

    else
        dollars = 0;

    if ( change >= 50 )
    {
        half_dollars = change/50;
        change = change%50;
    }
    else
        half_dollars = 0;

    if ( change >= 25)
    {
        quarters = change/25;
        change = change%25;
    }
    else
        quarters = 0;

    if ( change >= 10 )
    {
        dimes = change/10;
        change = change%10;
    }
    else
        dimes = 0;

    if ( change >= 5 )
    {
        nickels = change/5;
        change = change%5;
    }
    else
        nickels = 0;

    output_file << fixed << "Noah del Angel & Alyssa De La Cruz" << endl
                << "C.S.1428.001              " << endl
                << "Lab Section: L32 & L06    " << endl
                << "10/02/19                  " << endl << endl
                <<"Received" << setw(6) << setprecision(2)
                << price_recieved / 100.0 <<" for a purchase of" << setw(6)
                << purchase_amount / 100.0 << "." << endl << endl
                << setprecision(0) << "   Change in coins:" << endl
                << "Coin           Number" << endl
                << "---------------------" << endl
                << "Dollars          " << setw(6) << dollars << endl
                << "Half Dollars     " << setw(6) << half_dollars << endl
                << "Quarters         " << setw(6) << quarters << endl
                << "Dimes            " << setw(6) << dimes << endl
                << "Nickels          " << setw(6) << nickels << endl
                << "Pennies          " << setw(6) << change << endl;

    cout << "Program results have been written to prog1_nad73_aid7out.txt.";
    output_file.close();


    system("PAUSE>NUL");

    return 0;
}
