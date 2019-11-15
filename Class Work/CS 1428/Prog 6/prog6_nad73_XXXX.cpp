/*
   File: prog6_bb0000.cpp  // Remove this inline comment after replacing 'bb0000' with your account number.

   Author: Betty Boop      // Remove this inline comment after replacing Betty Boop with your first & last names.
   C.S.1428.?              // Remove this inline comment after replacing the '?' with your three-digit lecture section number.
   Lab Section: L?         // Remove this inline comment after replacing the '?' with your two-digit lab section number.
   Program: #6
   Due Date: --/--/--      // Remove this inline comment after replacing the dashes with the due date, in this format - month, day, year.

   This program prints to an output file a title and column headers for a
   payroll report. It then reads an employees work record from an input file.
   The number of overtime hours worked, gross pay, state tax, federal tax,
   and net pay are calculated for each employee. The authors' personal
   identification information followed by the company payroll report is
   printed to the output file. Monetary values are displayed to two decimal
   places.

   An attempt to avoid repetitive code is made.

   An appropriate message is displayed to the console screen if either the
   input or the output file fails to open.

   An appropriate message is written to the console screen informing the
   user of the output file name to which the results have been written.

   The client file (main) calls the following void functions to process
   the data:

	  - printIdInfo prints the authors' personal information - name(s),
        class/section number, lab section number(s), due date - on the first,
        second, third and fourth lines. Two blank lines are left after the
        due date. The lecture section number is displayed in a three-digit
        field with leading zeros shown. The lab section number is displayed
        in a two-digit field with leading zeros shown. The calling routine
        determines the output stream to which the information is directed.
        (Refer to sample output below.)
	  - printReportHeadings prints to the output file the title & column
        headings for the payroll report. One blank line is left after the
        centered report title. Column headers are displayed on two lines.
        (Refer to sample output below.)
      - dataIn reads the employee ID#, hours worked and pay rate from
        an input file storing the values read into parallel arrays. The
        employee ID# is stored in a 1D array of integers. The hours worked
        and the pay rate are stored in the first and second columns of a
        2D array of reals.
	  - overTime calculates the number of overtime hours worked by the
        employee based on a 40 hour work week.
	  - grossPay calculates the employee's gross pay for the week. If the
        employee worked 40 hours or less, gross pay is the hourly pay rate
        multiplied by the number of hours worked; otherwise, the employee
        worked more than 40 hours, and they are paid the regular hourly
        rate for the first 40 hours plus time and a half for any hours
        over 40.
	  - stateTax calculates state taxes owed by the employee, which is
        calculated at a straight 6% of the employee's weekly gross pay.
        (6% is a sample tax rate. The tax rate will vary with each state.)
	  - federalTax calculates federal taxes owed by the employee. If
        weekly gross pay is $400.00 or less, the tax rate is 20%; otherwise,
        the employee's weekly gross pay is more than $400.00, and the tax
        rate is calculated at 20% for the first $400.00 and 31% for any
        amount over $400.00.
        (These rates will vary based on current federal tax regulations.)
	  - netPay calculates the employee's net pay for the week.
        (gross pay minus calculated taxes both state & federal).
	  - printReportData prints to the output file the information for each
        employee in tabular form. Monetary values are displayed to two
        digits of precision. (Refer to sample output below.)
	  - writeFileLocation prints an appropriate message to the console
        screen indicating to the user the name of the output file to which
        the results have been written. The output file name is provided by
        the calling routine.(Refer to sample output below.)


   The following named constants are declared globally:
      - the number of hours in a normal work week (40.00)
      - the state tax rate (0.06)
      - the federal tax rates (0.20; 0.31)
      - the cut off at which federal taxes increase (400.00)
      - parallel array dimensions
      - names used to reference individual columns in the payroll array

   Locally declared named constants include:
      - a string to hold the authors' names
      - a string to hold the authors' lab section number(s)
      - a string to hold the project's due date
      - an integer to hold the lecture section number
      - an integer representing the maximum string length allowed for
        input and output file names which are stored in character arrays
        of that length

==========================================================================

Layout and content of the output are shown in the samples below.

Input (file - prog6_?inp.txt) // '?' represents three-digit lecture section #
       one record per employee / each record containing three numbers

       ID#(integer)  hours worked (real)  pay rate (real)
       ...

Constants: globally declared:
              integer: ROWS
                       COLS
                       {2D array column indices)
                           HRS_WRKD = 0,
                           PAYRATE = 1,
                           OVRTIME = 2,
                           GROSS = 3,
                           ST_TAX = 4,
                           FED_TAX = 5,
                           NETPAY = 6;

              double: CUT_OFF (hours in a work week)
                      STATE_TX_RATE
                      TAX_CUT_OFF (division @ which net pay is taxed higher)
	                  LOW_TAX_RATE
                      HI_TAX_RATE

Constants: locally declared:
              string:  AUTHORS
                       LAB_SECTION
                       DUE_DATE

              integer: LECTURE_SECTION
                       MAX_LENGTH_FN = ?  // filename's maximum length

Output (console):
    Sample Console Output

    Authors' Names
    C.S.1428.?        // '?' represents three-digit lecture section number
    Lab Section: L?   // '?' represents two-digit lab section numbet
    --/--/--          // dashes represent due date, month/day/year
         <blank line>
         <blank line>
    Program results have been written to prog6_?out.txt.

Output (file: prog6_?out.txt): // '?' represents three-digit lecture section #
    Sample File Output

    Authors' Names
    C.S.1428.?        // '?' represents three-digit lecture section number
    Lab Section: L?   // '?' represents two-digit lab section numbet
    --/--/--          // dashes represent due date, month/day/year
         <blank line>
         <blank line>
                         Monthly Payroll Report
         <blank line>
     ID#     Hours    Hourly    Overtime   Gross    State   Federal    Net
            Worked     Rate       Hours     Pay      Tax      Tax      Pay
    1000     51.00      6.55      11.00   370.07    22.20    74.02   273.86
    ...
    1002     26.00     15.00       0.00   390.00    23.40    78.00   288.60
    ...

    =======================================================================

    <Output will vary based on actual input values.>
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>     // 4 Code::Blocks

using namespace std;

const int ROWS = 10,    // number of employees
          COLS = 7;

          // 2D array (payroll) column indices
const int HRS_WRKD = 0,
          PAYRATE = 1,
          OVRTIME = 2,
          GROSS = 3,
          ST_TAX = 4,
          FED_TAX = 5,
          NETPAY = 6;

const double CUT_OFF = 40.00,      // work week
             STATE_TX_RATE = 0.06,
             TAX_CUT_OFF = 400.00, // earnings after which taxed at a higher rate
             LOW_TAX_RATE = 0.20,
             HI_TAX_RATE = 0.31;

// REPLACE THIS COMMENT WITH PROTOTYPES.
void printIdInfo ( ostream &out, const string AUTHORS,
                   const int LECTURE_SECTION, const string LAB_SECTION,
                   const string DUE_DATE );
void printReportHeadings ( ofstream &output_file );
void dataIn ( ifstream &input_file, int employee[],
              double (&payroll)[ROWS][COLS] );
void overTime ( double (&payroll)[ROWS][COLS] );
void grossPay ( double (&payroll)[ROWS][COLS] );
void stateTax ( double (&payroll)[ROWS][COLS] );
void federalTax ( double (&payroll)[ROWS][COLS] );
void netPay ( double (&payroll)[ROWS][COLS] );

void printReportData ( ofstream &output_file, const int employee[],
                       const double (&payroll)[ROWS][COLS] );
void writeFileLocation ( const char output_filename[] );

int main ( )
{
   const string AUTHORS = "...",       // REMOVE THIS COMMENT AFTER REPLACING ... WITH THE NAMES OF YOUR TEAM MEMBERS.
                LAB_SECTION = "L?",    // REMOVE THIS COMMENT AFTER REPLACING THE QUESTION MARK WITH A TWO-DIGIT LAB LECTURE_SECTION NUMBER.
                DUE_DATE = "--/--/--"; // REMOVE THIS COMMENT AFTER REPLACING --/--/-- WITH THE DUE DATE IN THIS FORMAT.

   const int LECTURE_SECTION = 1,
             MAX_LENGTH_FN = 20;

   char input_filename[MAX_LENGTH_FN + 1] = "...",  // REMOVE THIS COMMENT AFTER REPLACING ... WITH THE NAME OF THE INPUT FILE.
        output_filename[MAX_LENGTH_FN + 1] = "..."; // REMOVE THIS COMMENT AFTER REPLACING ... WITH THE NAME OF THE OUTPUT FILE.

   int employee[ROWS];          // employee ID#s

   double payroll[ROWS][COLS];  // payroll data

   ifstream fin;
   fin.open( input_filename );

    // REPLACE THIS COMMENT WITH CODE TO VERIFY THE INPUT FILE OPENS.
    // USE THE CODE FROM THE EXAMPLE PROVIDED ON THE ASSIGNMENTS PAGE.
    // ONLY MAKE NECESSARY ADJUSTMENTS, OR POINTS WILL BE DEDUCTED.

    ofstream fout;
    fout.open ( output_filename );

    // REPLACE THIS COMMENT WITH CODE TO VERIFY THE INPUT FILE OPENS.
    // USE THE CODE FROM THE EXAMPLE PROVIDED ON THE ASSIGNMENTS PAGE.
    // ONLY MAKE NECESSARY ADJUSTMENTS, OR POINTS WILL BE DEDUCTED.

   printIdInfo( fout, AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE );
   printReportHeadings ( fout );
   dataIn ( fin, employee, payroll );
   overTime ( payroll );
   grossPay ( payroll );
   stateTax ( payroll );
   federalTax ( payroll );
   netPay ( payroll );
   printReportData ( fout, employee, payroll );
   printIdInfo( cout, AUTHORS, LECTURE_SECTION, LAB_SECTION, DUE_DATE );
   writeFileLocation ( output_filename );

   // REPLACE THIS COMMENT WITH CODE TO CLOSE THE INPUT/OUTPUT FILES.

   system("PAUSE>NUL");

   return 0;
}

// REPLACE THIS COMMENT WITH DOCUMENTATION & CODE FOR THE FUNCTION DEFINITIONS.
/*

*/
void printIdInfo ( ostream &out, const string AUTHORS,
                   const int LECTURE_SECTION, const string LAB_SECTION,
                   const string DUE_DATE )
{


}

/*

*/
void printReportHeadings ( ofstream &output_file )
{

}

/*

*/
void dataIn ( ifstream &input_file, int employee[],
              double (&payroll)[ROWS][COLS] )
{

}

/*

*/
void overTime ( double (&payroll)[ROWS][COLS] )
{

}

/*

*/
void grossPay ( double (&payroll)[ROWS][COLS] )
{

}

/*

*/
void stateTax ( double (&payroll)[ROWS][COLS] )
{

}

/*

*/
void federalTax ( double (&payroll)[ROWS][COLS] )
{

}

/*

*/
void netPay ( double (&payroll)[ROWS][COLS] )
{

}

/*

*/
void printReportData ( ofstream &output_file, const int employee[],
                       const double (&payroll)[ROWS][COLS] )
{

}

/*

*/
void writeFileLocation ( const char output_filename[] )
{

}
