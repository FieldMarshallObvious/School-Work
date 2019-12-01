/*
   File: prog6_nad73_aid7.cpp

   Author: Noah del Angel & Alyssa De La Cruz
   C.S.1428.001
   Lab Section: L32 & L06
   Program: #6
   Due Date: 12/02/19

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
   const string AUTHORS = "Noah del Angel & Alyssa De La Cruz",
                LAB_SECTION = "L32 & L06",
                DUE_DATE = "12/02/19";

   const int LECTURE_SECTION = 1,
             MAX_LENGTH_FN = 20;

   char input_filename[MAX_LENGTH_FN + 1] = "prog6_001inp.txt",
        output_filename[MAX_LENGTH_FN + 1] = "prog6_001out.txt";

   int employee[ROWS];          // employee ID#s

   double payroll[ROWS][COLS];  // payroll data

   ifstream fin;
   fin.open( input_filename );

    if ( !fin )
    {
        cout << endl << endl
             << "***Program Terminated.***" << endl << endl
             << "Input file failed to open." << endl;

        fin.close( );

        system("PAUSE>NUL");

        return 1; // Quit, but don't return a 0; send back a non-zero value.
    }

    ofstream fout;
    fout.open ( output_filename);

    if ( !fout )
    {
        cout << endl << endl
             << " ***Program Terminated.*** " << endl << endl
             << "Output file failed to open." << endl;

        fin.close( );

        system("PAUSE>NUL");

        return 2; // Quit, but don't return a 0, send back a non-zero value.
    }

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

    fin.close();
    fout.close();

   system("PAUSE>NUL");

   return 0;
}

/*
 Function: printIdInfo

 The function, printIdInfo, writes the team members' identifying
 information to the output file on four separate lines
 - AUTHORS
 - Class with one digit LECTURE_SECTION constant
 - "Lab Section: " with LAB_SECTION constant
 - program due data
 - one blank line after the due date.

 Sample Output:
 Authors' Names
 C.S.1428.?             // '?' represents three-digit lecture section #
 Lab Section: L? & L?   // '?' represents two-digit lab section #s
 --/--/--               // dashes represent due date, month/day/year
 <blank line>

 Recieves: output file variable(ostream),
 AUTHORS (string const), LECTURE_SECTION (int const),
 LAB_SECTION (const string), DUE_DATE (const string)
 Constants: AUTHORS, LECTURE_SECTION, LAB_SECTION, LAB_SECTION, DUE_DATE
 Returns: nothing; prints user's team identifying info to a file
*/
void printIdInfo ( ostream &out, const string AUTHORS,
                   const int LECTURE_SECTION, const string LAB_SECTION,
                   const string DUE_DATE )
{
    out << AUTHORS << endl
        << "C.S.1428.00" << LECTURE_SECTION << endl
        << "Lab Section: " << LAB_SECTION << endl
        << DUE_DATE << endl << endl;
}

/*
 Function: printReportHeadings

 The function, printReportHeadings, writes the output files
 headers on 4 seperate lines
 - writes "Monthly Payroll Report"
 - blank line
 - writes the first word for all the headers
 - Writes the second word for all the headers

 Sample Output:
                         Monthly Payroll Report
        <blank line>
     ID#     Hours    Hourly    Overtime   Gross    State   Federal    Net
            Worked     Rate       Hours     Pay      Tax      Tax      Pay
 Recieves: outputfile variable (ofstream)
 Constants: none
 Returns: nothing; writes results to a file
*/
void printReportHeadings ( ofstream &output_file )
{
    output_file << "                         Monthly Payroll Report" << endl
                << endl
                << " ID#     Hours    Hourly   Overtime    Gross     State    "
                << "Federal     Net  " << endl
                << "        Worked     Rate      Hours      Pay       Tax      "
                << " Tax       Pay" << endl;

}

/*
 Function: dataIn

 The function, dataIn, reads information from the input file then
 places this data into the approporiate arrays.
 - reads first value from input file than puts it into the employee array
 - Reads the second value and then places it into the HRS_WRKD collumn in the
 payroll array.
 - Reads the third value and then places it into the PAYRATE collumn in the
 payroll array

 Recieves: outputfile variable (ofstream)
 Constants: globally declared integers:
                ROWS - parallel arrays row dimension
                COLS - 2D array column dimension
                column designations in 2D array
                HRS_WRKD, PAYRATE
 Returns: nothing; reads from a file, and assigns read data to the approriate
 locations in the payroll and employee array
*/
void dataIn ( ifstream &input_file, int employee[],
              double (&payroll)[ROWS][COLS] )
{
    int inputId;
    double hoursWorked,
           hourlyRate;
    for ( int rows = 0; rows < ROWS; ++rows )
    {
        input_file >> inputId >> hoursWorked >> hourlyRate;
        employee[rows] = inputId;

        payroll[rows][HRS_WRKD] = hoursWorked;

        payroll[rows][PAYRATE] = hourlyRate;
    }
}

/*
 Function: overTime

 The function, overTime, determines wether the employee has any overtime.
 If the employee has any overtime the program will calculate how much

 Recieves: payroll array(double)
 Constants: globally declared integers:
                ROWS - parallel arrays row dimension
                COLS - 2D array column dimension
              column designations in 2D array
                OVERTIME, HRS_WRKD
                CUT_OFF - number if hours at which work is considered over time
 Returns: nothing; calculates the amount of overtime for each employee,
 then places it in the payroll array
*/
void overTime ( double (&payroll)[ROWS][COLS] )
{
    for(int id = 0; id < ROWS; ++id)
    {
        if ( payroll[id][HRS_WRKD] >= CUT_OFF )
            payroll[id][OVRTIME] = payroll[id][HRS_WRKD] - CUT_OFF;

        else
            payroll[id][OVRTIME] = 0;
    }
}

/*
 Function: grossPay

 The function, grossPay, calculates the pay with ours worked ant overtime hours.
 This is done without taking int oaccount any taxes.

 Recieves: payroll array(double)
 Constants: globally declared integers:
                ROWS - parallel arrays row dimension
                COLS - 2D array column dimension
              column designations in 2D array
                OVERTIME, HRS_WRKD, GROSS, PAYRATE
                CUT_OFF - number if hours at which work is considered over time
 Returns: nothing; calculates the gross pay for each employee,
 then places it in the payroll array
*/
void grossPay ( double (&payroll)[ROWS][COLS] )
{
    for ( int id = 0; id < ROWS; ++id )
    {
        if ( payroll[id][HRS_WRKD] > CUT_OFF )
            payroll[id][GROSS] = CUT_OFF * payroll[id][PAYRATE]
                                 + ( payroll[id][OVRTIME]
                                 * ( payroll[id][PAYRATE]
                                 + ( payroll[id][PAYRATE] * 0.5 )));

        else
              payroll[id][GROSS] = payroll[id][HRS_WRKD] * payroll[id][PAYRATE];



    }
}

/*
 Function: stateTax

 The function, stateTax, calculates the state tax for each employee's pay. In a
 for loop.

 Recieves: payroll array(double)
 Constants: globally declared integers:
                ROWS - parallel arrays row dimension
                COLS - 2D array column dimension
              column designations in 2D array
                OVERTIME, HRS_WRKD, GROSS, PAYRATE
            globally declared reals:
                STATE_TX_RATE - rate for state tax
 Returns: nothing; calculates the state tax for each employee,
 then places it in the payroll array
*/
void stateTax ( double (&payroll)[ROWS][COLS] )
{
    for( int id = 0; id < ROWS; ++id )
    {
        payroll[id][ST_TAX] = payroll[id][GROSS] * STATE_TX_RATE;

    }
}

/*
 Function: federalTax

 The function, federalTax, calculates the federal tax for each of the
 employee's gross pay. If the employee is above the cutoff limit calculates the
 amount over at the higher rate, and the amount under at the lower rate. If it
 falls below or equal to the limit, it calculates the lower tax rate.

 Recieves: payroll array(double)
 Constants: globally declared integers:
                ROWS - parallel arrays row dimension
                COLS - 2D array column dimension
              column designations in 2D array
                OVERTIME, HRS_WRKD, GROSS, PAYRATE
            globally declared reals:
                TAX_CUT_OFF - Amount at which income is considered to be taxed
                at a higher rate
                HI_TAX_RATE - High income tax rate
                LOW_TAX_RATE - Low income tax rate

 Returns: nothing; calculates the federal tax for each employee,
 then places it in the payroll array
*/
void federalTax ( double (&payroll)[ROWS][COLS] )
{
    for ( int id = 0; id < ROWS; ++id )
    {
        if ( payroll[id][GROSS] > TAX_CUT_OFF )
        {
            payroll[id][FED_TAX] = (( payroll[id][GROSS] - TAX_CUT_OFF)
                                      * HI_TAX_RATE) + ( TAX_CUT_OFF
                                      * LOW_TAX_RATE);
        }
        else
            payroll[id][FED_TAX] = payroll[id][GROSS] * LOW_TAX_RATE;
    }
}

/*
 Function: netPay

 The function, netPay, calculates the pay for each employee subtracting the
 state and federal tax.

 Recieves: payroll array(double)
 Constants: globally declared integers:
                ROWS - parallel arrays row dimension
                COLS - 2D array column dimension
              column designations in 2D array
                OVERTIME, HRS_WRKD, GROSS, PAYRATE, ST_TAX, FED_TAX, NETPAY
 Returns: nothing; calculates the net pay for each employee,
 then place it in the payroll array
*/
void netPay ( double (&payroll)[ROWS][COLS] )
{
    for ( int id = 0; id < ROWS; ++id )
    {
        payroll[id][NETPAY] = payroll[id][GROSS] -
                              (payroll[id][ST_TAX] + payroll[id][FED_TAX]);
    }
}

/*
 Function: printReportData

 The function, printReportData, prints the employee id, hours worked,
 hourly rate, over time hours, gross pay, state tax, federal tax, and net pay.
 After each employee's information is printed a new line is started.

 Sample Output:
    1000     51.00      6.55      11.00   370.07    22.20    74.02   273.86
    ...
    1002     26.00     15.00       0.00   390.00    23.40    78.00   288.60
    ...

 Recieves: output file variable (ofstream), employee array (const int),
 payroll array (const double)
 Constants: employee[], payroll[ROWS[COLS],
            globally declared integers:
                ROWS - parallel arrays row dimension
                COLS - 2D array column dimension
 Returns: nothing; writes the employee payroll information to the outputfile
*/
void printReportData ( ofstream &output_file, const int employee[],
                       const double (&payroll)[ROWS][COLS] )
{
    for ( int id = 0; id < ROWS; ++id )
    {
        output_file << employee[id] << fixed << setw(10) << setfill(' ');
        for ( int item = 0; item < COLS; ++item )
        {
            if ( item == 0 )
                output_file << fixed << setprecision(2) << payroll[id][item];
            else
            {
                output_file << fixed << setw(10) << setfill(' ')
                            << setprecision(2) << payroll[id][item];
            }
        }
        output_file << endl;
    }
}

/*
 Function: writeFileLocation

 The function, writeFileLocation, writes a message to the screen
 indicating to the user the name of the output file to which the
 results have been written.

 Sample Display:
 Program results have been written to prog6_001out.txt.

 Recieves: output_filename array (const char)
 Constants: output_filename[]
 Returns: nothing; displays the the location of the output file to the
 command line
*/
void writeFileLocation ( const char output_filename[] )
{
    cout << "Program reults have been written to " << output_filename << ".";
}
