//
//  file_reverser.cpp
//  
//
//  Created by Noah del Angel on 4/29/20.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "DynStack.h"

using namespace std;

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
