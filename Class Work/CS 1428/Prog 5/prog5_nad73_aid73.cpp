/*
 File: prog5_bb0000.cpp  // Remove this inline comment after replacing 'bb0000' with your account number.

 Author: Betty Boop      // Remove this inline comment after replacing Betty Boop with your first & last names.
 C.S.1428.?              // Remove this inline comment after replacing the '?' with your three-digit lecture section number.
 Lab Section: L?         // Remove this inline comment after replacing the '?' with your two-digit lab section number.
 Program: #5
 Due Date: --/--/--      // Remove this inline comment after replacing the dashes with the due date, in this format - month, day, year.

 This program reads an unknown number of simple binary expressions
 of the form 'operand1 operator operand2' from an input file. Each
 expression is evaluated. Real input values are allowed.

 A sentinel value read loop is used to process as described below:

 (Named constants to 'hold' CLASS ("C.S.1428") and DUE_DATE ("--/--/--")
 are declared in the calling routine (main).)

 - A void function, getName, is called to 'get' the team members' first & last
 names using two different prompts for each team member leaving a blank
 line between sets of prompts. Four strings, one to 'hold' the first name
 and one to 'hold' the last name for each team member, are declared in the
 calling routine. A blank line is left after the last prompt.
 - A typed function, getLectureSection, is called to 'get' the team members'
 three-digit lecture section number. A string to 'hold' the lecture
 section number is declared in the calling routine. A blank line is left
 after the prompt.
 - A void function, getLabSection, is called to 'get' the team members'
 two-digit lab section numbers using two separate prompts. Strings are
 declared in the calling routine to 'hold' the lab section numbers.
 - A void function, printIdInfo, is called to print the team members' personal
 identifying information to the output file. (Refer to the sample output
 below.)
 - A void function, readExpression, is called to read from an input file
 a binary expression in the form operand1 operator operand2. One read
 statement is used to "get" the parts of the expression.
 - While the operator in the expression read is not a question mark,
 the program processes as follows:
 - A void function, echoExpression, is called to echo (print)
 the expression to the output file.
 - A void function, evaluateExpression, is called. If the
 expression currently being evaluated is valid, the results
 are calculated and written to the output file; otherwise,
 an appropriate message is written to the output file. (See
 below. *) A switch is used in the solution.
 - The void function readExpression is called to read the next
 expression of the form operand1 operator operand2.
 - Two blank lines are written to the screen in the calling routine before
 the void function printIdInfo is called to print the team members' personal
 identifying information to the console. (Refer to the sample output
 below.)
 - A void function, writeFileLocation, is called to print an appropriate
 message to the screen indicating to the user the name of the output
 file to which the results have been written. (Refer to sample output
 below.)

 ==========================================================================

 *The expressions are checked for the addition (+), subtraction (-),
 multiplication (*), and division (/) operators. Included are a check for
 division by zero when the division operator is encountered and a check for
 an invalid operator (e.g. 134.6 ! 23.1). Since these are mutually exclusive
 events, a switch statement with a nested double-sided alternative for
 handling the division operator was used to evaluate the expressions.

 If division by zero is encountered, the original expression is echoed to
 the output file along with the message '   Division by zero produces an
 undefined result.' If an invalid operator is encountered, the original
 expression is echoed to the output file along with the message
 '   Encountered unknown operator.'

 Every attempt is made to eliminate repetitive code!

 Numeric values in output are NOT formatted!

 ==========================================================================

 The layout and content of the file input and the file output are shown in
 the samples below. An appropriate message is displayed to the screen if
 either the input file or the output file fails to open.

 Input (file - prog5_?inp.txt):  // '?' represents three-digit lecture number
 (contains an unknown number of binary expressions)

 operand1(double)  operator(char)  operand2(double)
 ...

 Constants: CLASS = "C.S.1428"    (string)
 DUE_DATE = "--/--/--" (string)

 Sample Screen Display:

 Enter your first name:
 Enter your last name:
 <blank line>
 Enter your team member's first name:
 Enter your team member's last name:
 <blank line>
 Enter your three-digit lecture section number:
 <blank line>
 Enter your two-digit lab section number:
 Enter your team member's two-digit lab section number:
 <blank line>
 <blank line>
 Authors' Names
 C.S.1428.?           // '?' represents three-digit lecture section number
 Lab Section: L? & L? // '?' represents two-digit lab section number
 --/--/--             // dashes represent due date, month/day/year
 <blank line>
 <Appropriate message indicating the name of the output file.>

 Sample File Output (prog5_?out.txt): //'?' represents three-digit lecture sec #

 Authors' Names
 C.S.1428.?             // '?' represents three-digit lecture section number
 Lab Section: L? & L?   // '?' represents two-digit lab section number
 --/--/--               // dashes represent due date, month/day/year
 <blank line>
 125 $ 28   Encountered unknown operator.
 123.5 + 59.3 = 182.8
 198.7 / 0   Division by zero produces an undefined result.
 ...

 ================================================

 <Output will vary based on actual input values.>
 */

#include <fstream>
#include <iostream>
#include <cstdlib>   // 4 Code::Blocks

using namespace std;

void getName ( string &first1, string &last1, string &first2, string &last2 );
void printIdInfo ( );
void printIdInfo ( ostream &output_file, string first1, string last1,
                  string first2, string last2, const string CLASS,
                  string section, string lab_section1, string lab_section2,
                   const string DUE_DATE );
void readExpression ( ifstream &input_file, double &operand1, char &operatr,
                     double &operand2);
void echoExpression ( ostream &output_file, double operand1, char operatr,
                     double operand2 );
void evaluateExpression ( ostream &output_file, double operand1, char operatr,
                         double operand2 );
void writeFileLocation ( );


string getLectureSection ( );
string getLabSection ( string &section1, string &section2 );

int main ( )
{
    const string CLASS = "C.S.1428",
    DUE_DATE = "11/13/19";

    string first1_name,
    last1_name,
    first2_name,
    last2_name,
    lecture_section,
    lab_section1,
    lab_section2;

    double operand1,
    operand2;

    char operatr;

    ifstream fin;
    fin.open("prog5_001inp.txt");

    // REPLACE THIS COMMENT WITH CODE TO VERIFY THE INPUT FILE OPENS.
    // USE THE CODE FROM THE EXAMPLE PROVIDED ON THE ASSIGNMENTS PAGE.
    // ONLY MAKE NECESSARY ADJUSTMENTS, OR POINTS WILL BE DEDUCTED.

    ofstream fout;
    fout.open("prog5_001out.txt");

    // REPLACE THIS COMMENT WITH CODE TO VERIFY THE OUTPUT FILE OPENS.
    // USE THE CODE FROM THE EXAMPLE PROVIDED ON THE ASSIGNMENTS PAGE.
    // ONLY MAKE NECESSARY ADJUSTMENTS, OR POINTS WILL BE DEDUCTED.

    getName ( first1_name, last1_name, first2_name, last2_name );
    lecture_section = getLectureSection ( );
    getLabSection ( lab_section1, lab_section2 );
    printIdInfo ( fout, first1_name, last1_name, first2_name, last2_name,
                 CLASS, lecture_section,
                 lab_section1, lab_section2, DUE_DATE );

    readExpression ( fin, operand1, operatr, operand2 );
    while ( operatr != '?' )
    {
        echoExpression ( fout, operand1, operatr, operand2 );
        evaluateExpression ( fout, operand1, operatr, operand2 );
        readExpression ( fin, operand1, operatr, operand2 );
    }

    cout << endl << endl;
    printIdInfo ( cout, first1_name, last1_name, first2_name, last2_name,
                 CLASS, lecture_section, lab_section1, lab_section2, DUE_DATE );
    writeFileLocation ( );

    fin.close();
    fout.close();

    system("PAUSE>NUL");

    return 0;
}

/*
 Function: getName

 The function, getName, uses two separate prompts to 'get' the user's first
 and last names, leaves one blank line then repeats the process to obtain
 the first and last names of the user's team member.

 Sample Screen Display:
 Enter your first name:
 Enter your last name:
 <blank line>
 Enter your team member's first name:
 Enter your team member's last name:
 <blank line>

 Receives: first1, last1, first2, last2 (strings); in this order
 Constants: none
 Returns: first & last names of team members
 */
void getName ( string &first1, string &last1, string &first2, string &last2 )
{
    cout << "Enter your first name: ";
    cin >> first1;

    cout << endl;

    cout << "Enter your last name: ";
    cin >> last1;

    cout << endl;

    cout << "Enter your team member's first name: ";
    cin >> first2;

    cout << endl;

    cout << "Enter your team member's last name: ";
    cin >> last2;

    cout << endl << endl;
}

/*
 Function: getLectureSection

 The function, getLectureSection, prompts the user for the three-digit
 lecture section number and returns it to the calling routine.

 Sample Screen Display:
 Enter your three-digit lecture section number:
 <blank line>

 Receives: nothing
 Constants: none
 Returns: lecture section number
 */

string getLectureSection ( )
{
    string sectionInput;

    cout << "Enter your three-digit lecture section number: ";
    cin >> sectionInput;

    return sectionInput;
}

/*
 Function: getLabSection

 The function, getLabSection, prompts the user for his/her two-digit lab
 section number. It then prompts for the two-digit lab section number of
 the user's team member.

 Sample Screen Display:
 Enter your two-digit lab section number:
 Enter your team member's two-digit lab section number:

 Receives: section1, section2 (string); in this order
 Constants: none
 Returns: team members' lab section numbers
 */

string getLabSection ( string &section1, string &section2 )
{
    cout << "Enter your two-digit lab section number: ";
    cin >> section1;

    cout << endl << endl;

    cout << "Enter your team member's two digit lab section number: ";
    cin >> section2;
}

/*
 Function: printIdInfo

 The function, printIdInfo, writes the team members' identifying
 information to the output file on four separate lines
 - firstname1 lastname1 & firstname2 lastname2
 - class & three-digit lecture section number
 - "Lab Section: L"labsection1" & L"labsection2
 - program due date.
 One blank line is left after the due date.

 Sample Output:
 Authors' Names
 C.S.1428.?             // '?' represents three-digit lecture section #
 Lab Section: L? & L?   // '?' represents two-digit lab section #s
 --/--/--               // dashes represent due date, month/day/year
 <blank line>

 Receives: output file variable,
 first1, last1, first2, last2, (strings)
 CLASS (string constant), section (string),
 lab_section1, lab_section2 (strings)
 DUE_DATE (string constant); in this order
 Constants: CLASS, DUE_DATE
 Returns: nothing; prints user's team identifying info to a file
 */

void printIdInfo ( ostream &output_file, string first1, string last1,
                  string first2, string last2, const string CLASS,
                  string section, string lab_section1, string lab_section2,
                   const string DUE_DATE )
{
    output_file << first1 << " " << last1 << " & " << first2 << " " << last2
                << endl
                << CLASS << "." << section << endl
                << "Lab Section: " << "L" << lab_section1 << " & " << "L"
                << lab_section2 << endl
                << DUE_DATE << endl << endl;
}

/*
 Function: readExpression

 The function, readExpression, uses one statement to read a binary
 expression of the form operand1 operator operand2 from an input file

 Receives: input file variable,
 operand1 (double), operatr (char), operand2 (double);
 in this order
 Constants: none
 Returns: operand1 (double), operatr (char), operand2 (double)
 */

void readExpression ( ifstream &input_file, double &operand1, char &operatr,
                      double &operand2)
{
    input_file >> operand1 >> operatr >> operand2;
}

/*
 Function: echoExpression

 The function, echoExpression, echoes the binary expression to an output
 file.

 Sample Output:
 123.5 + 59.3
 ...

 Receives: output file variable,
 operand1 (double), operatr (char), operand2 (double);
 in this order
 Constants: none
 Returns: nothing; writes expression to a file
 */

void echoExpression ( ostream &output_file, double operand1, char operatr,
                      double operand2 )
{
    output_file << operand1 << " " << operatr << " " << operand2 << " ";
}

/*
 Function: evaluateExpression

 The function, evaluateExpression, evaluates the expression to determine
 whether or not it is valid. Valid expressions are evaluated and the
 results written to a file; otherwise, an appropriate message
 is written to the file.

 Sample Output:
 125 $ 28   Encountered unknown operator.
 123.5 + 59.3 = 182.8
 198.7 / 0   Division by zero produces an undefined result.
 ...

 Receives: output file variable,
 operand1 (double), operatr (char), operand2 (double);
 in this order
 Constants: none
 Returns: nothing; writes results to a file
 */

void evaluateExpression ( ostream &output_file, double operand1, char operatr,
                          double operand2 )
{
    switch ( operatr )
    {
        case '+':
            output_file << "= " << operand1 + operand2;
            break;
        case '-':
            output_file << "= " <<  operand1 - operand2;
            break;
        case '*':
            output_file << "= " << operand1 * operand2;
            break;
        case '/':
            if ( operand2 == 0 )
                output_file << "Division by zero produces an undefined result.";
            else
                output_file << operand1 / operand2;
            break;
        default:
            output_file << "Encountered unknown operator.";
    }

    output_file << endl;
}

/*
 Function: writeFileLocation

 The function, writeFileLocation, writes a message to the screen
 indicating to the user the name of the output file to which the
 results have been written.

 Sample Display:
 Program results have been written to prog5_00?out.txt.
 (The actual file name may differ.)

 Receives: nothing
 Constants: none
 Returns: nothing; writes a message to the screen
 */

void writeFileLocation ( )
{
    cout << "Program results have been written to prog5_001out.txt."
         << endl;
}
