//
//  tic_tac_toe.cpp
//  
//
//  Created by Noah del Angel on 10/16/19.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool winCheck ( char (&gameBoard)[3][3], int rows, int cols );
bool placeCheck ( char (&gameBoard)[3][3], int rows, int cols, char character, char enemy );
void createBoard ( char (&gameBoard)[3][3], int rows, int cols );
void drawBoard ( char gameBoard[3][3], int rows, int cols );
void compPlace ( char (&gameBoard)[3][3], char character, int rows, int cols );
void personPlace ( char (&gameBoard)[3][3], char character );


int main ( )
{
    const int ROWS = 3;
    const int COLS = 3;
    
    int rowPlace, colPlace;
    
    char gameBoard [ROWS][COLS];
    char characterChoice = ' ';
    createBoard ( gameBoard, ROWS, COLS);
    
    while ( characterChoice != 'X' && characterChoice != 'O' )
    {
        cout << "Please choose to place X's or O's:" << endl;
        cin >> characterChoice;
        cout << endl;
        
        if ( characterChoice != 'X' && characterChoice != 'x' && characterChoice != 'O' && characterChoice != 'o')
        {
            cout << "Please enter a character that is either X or O." << endl;
        }
        else
        {
            if ( characterChoice == 'x' || characterChoice == 'X')
                characterChoice = 'X';
            else
                characterChoice = 'O';
        }
    }
    
    while( winCheck( gameBoard, ROWS, COLS ) == false )
    {
        personPlace( gameBoard, characterChoice );
        drawBoard( gameBoard, ROWS, COLS );
        compPlace( gameBoard, characterChoice, ROWS, COLS );
        cout << endl;
        drawBoard ( gameBoard, ROWS, COLS);
    
        cout << winCheck( gameBoard, ROWS, COLS ) << endl;
    }
    
    return 0;
}

bool winCheck ( char (&gameBoard)[3][3], int rows, int cols )
{
    bool line = false;
    
    //Diagonal Line check
    if( line == false )
    {
        for ( int rowCur = 0; rowCur < rows; rowCur++ )
        {
            for ( int colCur =0; colCur < cols; colCur++ )
            {
                char first_layer = gameBoard[rowCur][colCur];
                char second_layer = gameBoard[rowCur+1][colCur+1];
                char third_layer = gameBoard[rowCur+2][colCur+2];
                
                if( first_layer != ' ')
                    if( first_layer == second_layer && first_layer == third_layer)
                        line = true;
            }
        }
    }
    
    //Reverse Diagonal Line check
    if ( line == false )
    {
        for ( int rowCur = 0; rowCur < rows; rowCur++ )
        {
            for ( int colCur =0; colCur < cols; colCur++ )
            {
                char first_layer = gameBoard[rowCur][colCur];
                char second_layer = gameBoard[rowCur+1][colCur-1];
                char third_layer = gameBoard[rowCur+2][colCur-2];
                
                if( first_layer != ' ' )
                    if( first_layer == second_layer && first_layer == third_layer)
                        line = true;
            }
        }
    }
    
    //Vertical Line Check
    if ( line == false )
    {
        for ( int colCur = 0; colCur < cols; colCur++ )
        {
            char first_layer = gameBoard[0][colCur];
            char second_layer = gameBoard[1][colCur];
            char third_layer = gameBoard[2][colCur];
            
            if(first_layer != ' ')
                if (first_layer == second_layer && first_layer == third_layer)
                    line = true;
        }
    }
    
    //Horizontal Line Check
    if ( line == false )
    {
        for ( int rowCur = 0; rowCur < rows; rowCur++ )
        {
            char first_layer = gameBoard[rowCur][0];
            char second_layer = gameBoard[rowCur][1];
            char third_layer = gameBoard[rowCur][2];
            
            if(first_layer != ' ')
            {
                if (first_layer == second_layer && first_layer == third_layer)
                    line = true;
            }
        }
    }
    
    return line;
}

bool placeCheck ( char (&gameBoard)[3][3], int rows, int cols, char character, char enemy )
{
    bool line = false;
    
    
    //Diagonal Line check
    if( line == false )
    {
        for ( int rowCur = 0; rowCur < rows; rowCur++ )
        {
            for ( int colCur =0; colCur < cols-1; colCur++ )
            {
                char first_layer = gameBoard[rowCur][colCur];
                char second_layer = gameBoard[rowCur+1][colCur+1];
                char third_layer = gameBoard[rowCur+2][colCur+2];
                
                if( first_layer == enemy && second_layer == enemy && third_layer != enemy )
                {
                    gameBoard[rowCur+2][colCur+2] = character;
                    cout << "The computer chose: " << rowCur + 2 << " " << colCur + 1;
                    line = true;
                }
                if ( first_layer != enemy && second_layer == enemy && third_layer == enemy )
                {
                    gameBoard[rowCur][colCur] = character;
                    cout << "The computer chose: " << rowCur + 1 << " " << colCur + 1;
                    line = true;
                    
                }
                if ( first_layer == enemy && second_layer != enemy && third_layer == enemy )
                {
                    gameBoard[rowCur+1][colCur+1] = character;
                    cout << "The computer chose: " << rowCur + 1 << " " << colCur + 1;
                    line = true;
                }
            }
        }
    }
    
    //Reverse Diagonal Line check
    if ( line == false )
    {
        for ( int rowCur = 0; rowCur < rows; rowCur++ )
        {
            for ( int colCur =0; colCur < cols-1; colCur+=2 )
            {
                char first_layer = gameBoard[rowCur][colCur];
                char second_layer = gameBoard[rowCur+1][colCur-1];
                char third_layer = gameBoard[rowCur+2][colCur-2];

                if( first_layer == enemy && second_layer == enemy && third_layer != enemy )
                {
                    gameBoard[rowCur+2][colCur-2] = character;
                    cout << "The computer chose: " << rowCur + 2 << " " << colCur + 1;
                    line = true;
                }
                if ( first_layer != enemy && second_layer == enemy && third_layer == enemy )
                {
                    gameBoard[rowCur][colCur] = character;
                    cout << "The computer chose: " << rowCur + 1 << " " << colCur + 1;
                    line = true;

                }
                if ( first_layer == enemy && second_layer != enemy && third_layer == enemy )
                {
                    gameBoard[rowCur+1][colCur-1] = character;
                    cout << "The computer chose: " << rowCur + 1 << " " << colCur + 1;
                    line = true;
                }
            }
        }
    }
    
    //Vertical Line Check
    if ( line == false )
    {
        for ( int colCur = 0; colCur < cols-1; colCur++ )
        {
            char first_layer = gameBoard[0][colCur];
            char second_layer = gameBoard[1][colCur];
            char third_layer = gameBoard[2][colCur];
            
            
            if ( first_layer == enemy && second_layer == enemy && third_layer != enemy )
            {
                gameBoard[2][colCur] = character;
                cout << "The computer chose: 3 " << colCur+1;
                line = true;
            }
            
            if ( first_layer == enemy && second_layer != enemy && third_layer == enemy )
            {
                gameBoard[1][colCur] = character;
                cout << "The computer chose: 2 " << colCur+1;
                line = true;
            }
            if ( first_layer != enemy && second_layer == enemy && third_layer == enemy )
            {
                gameBoard[0][colCur] = character;
                cout << "The computer chose: 1 " << colCur+1;
                line = true;
            }
            
            
            
        }
    }
    
    //Horizontal Line Check
    if ( line == false )
    {
        for ( int rowCur = 0; rowCur < rows; rowCur++ )
        {
            char first_layer = gameBoard[rowCur][0];
            char second_layer = gameBoard[rowCur][1];
            char third_layer = gameBoard[rowCur][2];
            
            if ( first_layer == enemy && second_layer == enemy && third_layer != enemy )
            {
                gameBoard[rowCur][2] = character;
                cout << " The computer chose: " << rowCur + 1  << " " << 3;
                line = true;
            }
            if ( first_layer == enemy && second_layer != enemy && third_layer == enemy )
            {
                gameBoard[rowCur][1] = character;
                cout << rowCur;
                cout << " The computer chose: " << rowCur + 1  << " " << 2;
                line = true;
            }
            if ( first_layer != enemy && second_layer == enemy && third_layer == enemy )
            {
                gameBoard[rowCur][1] = character;
                cout << " The computer chose: " << rowCur + 1  << " " << 1;
                line = true;
            }
            
        }
    }
    
    return line;
    
}

void createBoard ( char (&gameBoard)[3][3], int rows, int cols )
{
    for ( int rowCur = 0; rowCur < rows; rowCur++)
    {
        
        for ( int colCur = 0; colCur < cols; colCur++)
        {
            gameBoard[rowCur][colCur] = ' ';
        }
    }
}

void drawBoard ( char gameBoard[3][3], int rows, int cols )
{
    
    for ( int rowCur = 0; rowCur < rows; rowCur++)
    {
        
        for ( int colCur = 0; colCur < cols; colCur++)
        {
            if(colCur != cols - 1)
                cout << gameBoard[rowCur][colCur] << " | ";
            else
                cout << gameBoard[rowCur][colCur];
        }
        cout << endl;
    }
}

void compPlace ( char (&gameBoard)[3][3], char character, int rows, int cols )
{
    char compCharacter;
    bool lineplaced = false;
    int compRow, compCol;
    
    //Assign computer character
    if ( character == 'X')
        compCharacter = 'O';
    else
        compCharacter = 'X';
    
    //Place to finish computer line
    if( lineplaced == false )
        lineplaced = placeCheck(gameBoard, rows, cols, compCharacter, compCharacter);
    //Place to block player line
    if( lineplaced == false )
        lineplaced = placeCheck(gameBoard, rows, cols, compCharacter, character);
    //Place in a random sqaure
    if ( lineplaced == false )
    {
        while ( lineplaced == false)
        {
            srand(time(NULL));
            int compRow = (rand()%rows) + 1;
            srand(time(NULL));
            int compCol = (rand()%cols) + 1;
            
            if ( gameBoard[compRow][compCol] == ' ')
            {
                gameBoard[compRow][compCol] = compCharacter;
                cout << "Rand Choice";
                cout << " The computer chose: " << compRow + 1 << " " << compCol + 1;
                lineplaced = true;
            }
        }
    }
}

void personPlace ( char (&gameBoard)[3][3], char character)
{
    bool checker = false;
    int rowIn;
    int colIn;
    while ( checker != true )
    {
        cout << "Select a posistion to place an X in Row Col format: ";
        cin >> rowIn >> colIn;
        cout << endl;
        if ( gameBoard[rowIn - 1][colIn - 1] == ' ' )
        {
            gameBoard[rowIn - 1][colIn - 1] = character;
            checker = true;
        }
        else
        {
            cout << "That spot is already taken! Please pick another" << endl;
        }
    }
}
