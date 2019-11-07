//
//  DealOrNoDeal.cpp
//  
//
//  Created by Noah del Angel on 11/6/19.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

const int CASE_AMOUNT = 6;
const int RAND_PLACE_HOLDER = 1;

void pickCase ( );
void makeCases ( int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER] );
void drawCases (char (&casesOpened)[CASE_AMOUNT],
                int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER]);
void drawCase ( int index, int difference );
void drawCase ( int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER], int index, int difference );
bool inputCaseCheck ( );
int ranNumGen ( );



using namespace std;

int main ( )
{
    char casesOpened[CASE_AMOUNT];
    
    int casesList[CASE_AMOUNT][RAND_PLACE_HOLDER];
    
    makeCases(casesList);
    drawCases(casesOpened, casesList);
}

void pickCase ( char (&casesOpened)[CASE_AMOUNT],
                int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER] )
{
    
}

void makeCases ( int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER] )
{
    for ( int index = 0; index < CASE_AMOUNT; index++)
    {
        casesList[index][0] = ranNumGen( );
    }
}


void drawCases ( char (&casesOpened)[CASE_AMOUNT],
                 int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER] )
{
    int difference = 0;
    bool passed = false;
    

    
    for( int index = 0; index < CASE_AMOUNT; index++)
    {
        
        if ( passed == true )
        {
            difference = 3;
        }
        
        if ( casesOpened[index] == 'U')
        {
            if ( passed == true )
                passed = false;
            
            drawCase( index, difference );
        
            
        }
        else if (!(casesOpened[index] == 'y'))
        {
            if ( passed == true )
                passed = false;

            drawCase( index, difference );
        }
        else
        {
            if ( passed == true )
                passed = false;
           drawCase( casesList, index, difference );
        }
        
        if ( passed == false)
            difference = 0;
    
    }
}

void drawCase ( int index, int difference )
{
    cout << " .---[[__]]----. " << endl
    << ";-------------.|" << endl
    << "|             ||" << endl
    << "|             ||" << endl
    << "|      " << index + difference+1 << "      ||" << endl
    << "|             ||" << endl
    << "|_____________|/" << endl;
}
void drawCase ( int (&casesList)[CASE_AMOUNT][RAND_PLACE_HOLDER], int index, int difference )
{
    cout << " .---[[__]]----. " << endl
    << ";-------------.|" << endl
    << "|              |" << endl
    << "|              |" << endl
    << "|       $" << casesList[index+difference][0] << "      ||" << endl
    << "|              |" << endl
    << "|______________/" << endl
    << "/             /" << endl
    << "/            / " << endl
    << "/           /" << endl
    << "/          /" << endl
    << "___________" << endl;
}

int ranNumGen  ( )
{
    int randnum = 1;
    while ( !(randnum % 5 == 0) )
    {
        srand (time(NULL));
        randnum = rand() % 10000;
    }
    
    return randnum;
}
