/*=====================================================================
 Program: Prog 5
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 5/1/20
 Description: This portion of the program uses the Dynque class to
              take input from the input.txt file, and convert all
              the chars to upper case. The program then outputs it
             all to output_filter.txt
 Input: input.txt
 Output: output_filter.txt
 Compilation instructions: This program requires the compilation of the
                           header file Dynque.h to run. One method of
                           compiling is listed below:
                           g++ file_filter.cpp Dynque.h
 Usage:
 Modifications:
 Date Comment: 29/4/20
 ----------------------------------------------------
 ======================================================================*/

#include <cstdlib>
#include <cctype>
#include <cstring>
#include <fstream>
#include "Dynque.h"

using namespace std;

/*=====================================================================
 Function: main
 Description: Creates a Dynque object, and enqueues chars from the input
              file to the que. Then dequeus that information. After
              converting those chars to upper case, they are written
              to the output file. 
 Parameters:
 ======================================================================*/
int main ( )
{
    //Variable declarations
    Dynque<char> que;
    ifstream inputFile;
    ofstream outputFile;
    char input = ' ',
         output = ' ';
    int cntr = 0;
    
    //Open the input file
    inputFile.open( "input.txt" );
    
    if ( !inputFile )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "Input file failed to open." << endl;
        
        return -1;
    }
    
    //Open the output file
    outputFile.open( "output_filter.txt" );
    
    if ( !outputFile )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "output file failed to open." << endl;
        
        return -1;
    }
    
    //Push file items to the stack
    while( ! inputFile.eof( ) )
    {
        //Get chars from file without skipping white space
        inputFile >> std::noskipws >> input;
        
        que.enqueue( input );
        
        //Reset the input string
        input = ' ';
        
        //Determine the total number words
        cntr++;
    }
    
    //Write the stack to the file
    for( int i = 0; i < cntr; i++ )
    {
        //Get word from stack
        que.dequeue(output);
        
        output = toupper(output);
        
        //Send upper case character to
        outputFile << output;
        
        //Reset the string
        output = ' ';
        
    }
}
