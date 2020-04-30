//
//  file_filter.cpp
//  
//
//  Created by Noah del Angel on 4/29/20.
//


#include <cstdlib>
#include <cctype>
#include <cstring>
#include <fstream>
#include <string>
#include "DynQue.h"

using namespace std;

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
        
        cout << input << endl;
        
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
        
        cout << "the output is " << output << endl;
        
        cout << toupper(output) << endl;
        
        output = toupper(output);
        
        //Send upper case character to
        outputFile << output;
        
        //Reset the string
        output = ' ';
        
    }
}
