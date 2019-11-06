/*
   File: prog4_nad73_aid7.cpp

   Author: Noah del Angel & Alyssa De La Cruz
   C.S.1428.001
   Lab Section: L32 & L06
   Program: #4
   Due Date:10/30/19

   This program prompts the user for the number of items purchased. If no
   items were purchased, the program terminates after printing an appropriate
   message to the screen; otherwise, the program repeatedly prompts the
   user for the price of the specified number of items and calculates the
   total of all purchased items. It then calculates the shipping charge,
   discounted total, tax on the discounted total, and the total amount due.

   After all calculations are performed, the program prints the author's
   identifying information followed by the total of all purchased items,
   the discounted total, the tax rate, the tax on the discounted total,
   shipping charges and the total amount due as shown below. Output is
   written in receipt form to both the console and to an output file.

   With the exception of the tax rate, the numeric data is formatted to
   two decimal places. The tax rate is formatted to four decimal places.

   Input (keyboard): number of items purchased, integer
                     item price, double

   Constants:        discount amount, double (sample: 0.20)
                     cut off amount for free shipping, double
                     shipping charge, double
                     tax rate, double (sample: 0.0825)

   Output (console):
          Sample Console Output (These samples do not reflect prompts.)

          Author's Name
          C.S.1428.?        // '?' represents three-digit lecture section number
          Lab Section: L?   // '?' represents two-digit lab section number
          --/--/--          // dashes represent due date, month/day/year
               <blank line>
          Total Purchases:    $ ??.??
          Discounted Total:     ??.??
          Tax Rate:              ?.????
          Tax:                   ?.??
          Shipping:              ?.??
               <blank line>
          Total Amount Due:   $ ??.??
               <blank line>
               <blank line>
          A copy for your records can be found in prog4_00?out.txt.

   Output (file - prog4_?out.txt):

          Author's Name
          C.S.1428.?        // '?' represents three-digit lecture section number
          Lab Section: L?   // '?' represents two-digit lab section number
          --/--/--          // dashes represent due date, month/day/year
               <blank line>
          Total Purchases:    $ ??.??
          Discounted Total:     ??.??
          Tax Rate:              ?.????
          Tax:                   ?.??
          Shipping:              ?.??
               <blank line>
          Total Amount Due:   $ ??.??

          ================================================

          <Output will vary based on actual input values.>
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main ( )
{
    const double DISCOUNT = 0.2,
                 TAX_RATE = 0.0825,
                 SHIPPING_RATE = 8.5,
                 DISCOUNT_CUTOFF = 150;

    int items_purchased;
    double total_purchase = 0,
           price,
           discounted_tot,
           tax,
           owed,
           shipping;

    ofstream output_file;
    output_file.open("prog4_001.txt");

    if ( !output_file )
    {
        cout << endl << endl
        << "***Program Terminated.***" << endl << endl
        << "Output file failed to open!" << endl;

        system ("PAUSE>NUL");

        return 1;
    }

    cout << "Enter number of items purchased: ";
    cin >> items_purchased;
    cout << endl;

    if ( items_purchased == 0 )
        cout << "Come back again soon!";

    else
    {

        for ( int i = 0; i < items_purchased; ++i )
        {
            cout << "Enter the item price: ";
            cin >> price;
            total_purchase += price;
        }

        discounted_tot = total_purchase - ( total_purchase * DISCOUNT );

        if ( discounted_tot >= DISCOUNT_CUTOFF )
        {
            shipping = 0;
        }

        else
        {
            shipping = SHIPPING_RATE;
        }

        tax = discounted_tot * TAX_RATE;
        owed = discounted_tot + shipping + tax;


        output_file << "Noah del Angel & Alyssa De La Cruz" << endl
                    << "C.S.1428.001" << endl
                    << "Lab Section: L32 & L06" << endl
                    << "10/30/19" << endl << endl;

        output_file << fixed << setprecision(2)
                    << "Total Purchases:    $ " << setw(6) << total_purchase
                    << endl
                    << "Discounted Total:     " << setw(6) << discounted_tot
                    << endl
                    << "Tax Rate :            " << setprecision(4)
                    << setw(8) << TAX_RATE << endl
                    << "Tax:                  " << setprecision(2)
                    << setw(6) << tax << endl
                    << "Shipping:             " << setw(6) << shipping << endl
                    << endl
                    << "Total Amount Due :  $ " << setw(6) << owed << endl
                    << endl;

        cout << endl << endl << endl
             << "Noah del Angel & Alyssa De La Cruz" << endl
             << "C.S.1428.001" << endl
             << "Lab Section: L32 & L06" << endl
             << "10/30/19" << endl << endl;

        cout << fixed << setprecision(2)
             <<"Total Purchases:    $ " << setw(6) << total_purchase << endl
             << "Discounted Total:     " << setw(6) << discounted_tot << endl
             << "Tax Rate :            " << setprecision(4) << setw(8)
             << TAX_RATE << endl
             << "Tax:                  " << setprecision(2) << setw(6)
             << tax << endl
             << "Shipping:             " << setw(6)
             << shipping << endl << endl
             << "Total Amount Due : $ " << setw(6)
             << owed << endl << endl << endl

             << "A copy for your records can be found in prog4_aid7.txt."
             << endl;
    }

    output_file.close( );

    system("PAUSE>NUL");

    return 0;
}


