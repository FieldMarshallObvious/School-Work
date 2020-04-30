/*=====================================================================
 Program: Prog 5
 Author: Noah del Angel
 Class: CS 2308
 Instructor: Zilliang Zong
 Date: 5/1/20
 Description: This portion of the program uses the Dynque class to
              take input from the input.txt file, and reverses the
              order of all the chars. The program then outputs it
              all to output_reverse.txt
 Input: input.txt
 Output: output_reverse.txt
 Compilation instructions: This program requires the compilation of the
                           header file Dynque.h to run. One method of
                           compiling is listed below:
                           g++ file_reverser.cpp DynStack.h
 Usage:
 Modifications:
 Date Comment: 29/4/20
 ----------------------------------------------------
 ======================================================================*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "DynStack.h"

using namespace std;


/*=====================================================================
 Function: main
 Description: Creates a DynStack object, and pushes chars from the input
              file to the stack. Then pops that information, and writes
              it to the output file.
 Parameters:
 ======================================================================*/
int main ( )
{
    //Variable declarations
    DynStack<char> stack;
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
    outputFile.open( "output_reverse.txt" );
    
    if ( !outputFile )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "output file failed to open." << endl;
        
        return -1;
    }

    //Push file items to the stack
    while( ! inputFile.eof( ) )
    {
        //Get string from file
        inputFile >> std::noskipws >> input;
        
        stack.push( input );
        
        //Reset the input string
        input = ' ';
        
        //Determine the total number words
        cntr++;
    }
    
    //Write the stack to the file
    for( int i = 0; i < cntr; i++ )
    {
        //Get word from stack
        stack.pop(output);
        
        //Send it to the outputfile
        outputFile << output;
        
        //Reset the string
        output = ' ';
        
    }
    
    return 0;
}
