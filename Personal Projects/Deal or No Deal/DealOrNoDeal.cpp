//
//  DealOrNoDeal.cpp
//  
//
//  Created by Noah del Angel on 11/6/19.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>

const int CASE_AMOUNT = 26;
const int RAND_PLACE_HOLDER = 1;

void pickCase ( char (&casesOpened)[CASE_AMOUNT],
                int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER]);
void createCases ( int possibleChoices[] ,int
                  (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER],
                  std::string (&casesPrint)[CASE_AMOUNT/2][2] );
void drawCases ( std::string (&casesPrint)[CASE_AMOUNT/2][2] );

std::string drawCase ( int index, int difference );
std::string drawCase ( int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER], int index, int difference );

bool inputCaseCheck ( char (&casesOpened)[CASE_AMOUNT], int input );

int ranNumGen ( int possibleChoices[], int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER]);

using namespace std;

int main ( )
{
    string casesPrint[CASE_AMOUNT/2][2];
    char casesOpened[CASE_AMOUNT];
    
    int casesList[CASE_AMOUNT][RAND_PLACE_HOLDER],
        possibleChoices[CASE_AMOUNT];
    
    double randomizeDollar[26] =
    {.01, 5.0, 25.0, 75.0, 200.0, 400.0, 750.0, 5000.0, 25000.0, 75000.0, 200000.0,
        400000.0, 750000.0, 1.0, 10.0, 50.0, 100.0, 300.0, 500.0, 1000.0, 10000.0,
        50000.0, 100000.0, 300000.0, 500000.0, 1000000.0};
    
    createCases( possibleChoices, casesList, casesPrint );
    drawCases(casesPrint);
}

void pickCase ( char (&casesOpened)[CASE_AMOUNT],
                int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER] )
{
    int input = -1;
    bool checker = false;

    while ( checker != true )
    {
        cout << "Please pick a case from the selection";
        cin >> input;
        
        checker = inputCaseCheck ( casesOpened, input );
        
    }
    
    
}

void createCases ( int possibleChoices[] ,int
                  (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER],
                  std::string (&casesPrint)[CASE_AMOUNT/2][2] )
{
    
    bool passed = false;
    
    int difference = 0;
    
    for ( int index = 0; index < CASE_AMOUNT; index++ )
    {
        casesList[index][0] = ranNumGen( possibleChoices, casesList );
    }
    
    for ( int row = 0; row < CASE_AMOUNT/2; row++)
    {
        if ( passed == true )
            difference = CASE_AMOUNT/3;
        for ( int col = 0; col < CASE_AMOUNT/3; col++ )
        {
            casesPrint[row][col] = drawCase(col, difference);
        }
        passed = true;
    }
}



void drawCases ( std::string (&casesPrint)[CASE_AMOUNT/2][2] )
{
    

    
    for ( int row = 0; row < CASE_AMOUNT/2; row++)
    {
 
        for ( int col = 0; col < CASE_AMOUNT/3; col++ )
        {
            cout <<  casesPrint[row][col];

        }
        
        cout << endl;
    }
}

std::string drawCase ( int index, int difference )
{\
    string output =  " [ " +  std::to_string(index + difference) + " ]";
    
    return output;
}
std::string drawCase ( int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER], int index, int difference )
{
    string output =   " [ " +  std::to_string(index+difference)  + ": " + std::to_string(casesList[index+difference][0]) +" ]";
    
    return output;
}

bool inputCaseCheck ( char (&casesOpened)[CASE_AMOUNT], int input )
{
    bool output = false;
    
    if (input <= 0 || input >= CASE_AMOUNT )
        cout << "Please enter a value between 1 and " << CASE_AMOUNT;
    else if ( casesOpened[input - 1] == 'u' )
        cout << "You already chose this case, please select a different one.";
    else if ( casesOpened[input-1] == 'U' )
        cout << "This case has already been opened, choose a different one.";
    else
        output = true;
    
    return output;
        
    
}

int ranNumGen  ( int possibleChoices[], int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER] )
{
    int randnum = 1;
    
    bool repeat = true;
    
    while ( repeat == true )
    {
        srand (time(NULL));
        randnum = rand() % 25;
        for ( int index = 0; index < CASE_AMOUNT; index++ )
        {
            if ( possibleChoices[randnum] == casesList[index][0])
            {
                repeat = true;
                break;
            }
            else
                repeat = false;
        }
    }
    
    return randnum;
}
