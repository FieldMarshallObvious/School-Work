//
//  shape_drawer.cpp
//  
//
//  Created by Noah del Angel on 10/29/19.
//

#include <iostream>
#include <string>
#include <iostream>

using namespace std;

void line ( int length, char space );
void verticalLine ( int length );
void rectanglge ( int width, int height, char space );
void uptriangle ( int init, int max, int increment );
void downtriangle ( int init, int max, int increment );
void usFlag ( );
void stars ( char space );
void stripes ( int length );
void inputAcquirer ( string &shape, string requestSentece, string correctInputUpper,
                    string correctInputLower, string correctInputUpper2,
                    string correctInputLower2);
void inputAcquirer ( int &length, string requestSentece );

bool validInputChecker ( string upperExpected, string lowerExpected, string input );


using namespace std;

int main ( )
{
    string shape = " ",
        shape_designation = " ",
        end_question = " ";
    bool input_Complete = false,
         end_Draw = false;
    int width,
        height,
        length;
    
    cout << "Welcome to the shape drawer!" << endl;
    
    do
    {
        while ( input_Complete == false)
        {
            cout << "Would you like to draw a line, rectangle, square, triangle, or the US Flag: ";
            cin >> shape;
            if ( validInputChecker ( "Line", "line", shape ) ||
                validInputChecker ( "Rectangle", "rectangle", shape ) ||
                validInputChecker ( "Square", "square", shape ) ||
                validInputChecker ( "Triangle", "triangle", shape ) ||
                validInputChecker ( "US", "us", shape ) ||
                validInputChecker ( "US Flag", "us flag", shape ) )
            {
                input_Complete = true;
            }
            else
            {
                cout << "Please enter a valid option.";
            }
            cout << endl << endl;
        }
    
        if ( validInputChecker ( "Line", "line", shape ) )
        {
        
            inputAcquirer ( shape, "Would you like to draw a horizontal line, or vertical line: ", "Horizontal", "horizontal", "Vertical", "vertical");
        
            if ( validInputChecker ( "Horizontal", "horizontal", shape_designation ) )
            {
 
                inputAcquirer ( shape_designation, "Would you like to draw the horizontal line with spaces?(Y/N) : ", "Y", "y", "N", "n");
            
                inputAcquirer ( length, "Enter the length of the line: " );
            
                if ( validInputChecker ( "Y", "y", shape_designation ) )
                    line( length, ' ');
                else
                    line( length, '\0');
            }
        
            else
            {
            
                inputAcquirer ( length, "Enter the length of the line: " );
            
                verticalLine( length );
            }
        
        }
    
        if ( validInputChecker ( "Rectangle", "rectangle", shape ) )
        {

            inputAcquirer ( shape_designation, "Would you like to draw the rectangle filled (Y/N) : ", "Y", "y", "N", "n");
        
            if ( validInputChecker ( "Y", "y", shape_designation ) )
            {
                inputAcquirer ( width, "Enter the width of the rectangle: ");
            
                inputAcquirer ( height, "Enter the height of the rectangle: ");
            
                rectangle ( width, height, '@');
            }
            else
            {
                inputAcquirer ( width, "Enter the width of the rectangle: ");

                inputAcquirer ( height, "Enter the height of the rectangle: ");
            
                rectangle ( width, height, ' ');
            }

        }
    
        if ( validInputChecker ( "Square", "square", shape ) )
        {

            inputAcquirer ( shape_designation, "Would you like to draw the square filled (Y/N) : ","Y", "y", "N", "n");
        
            if ( validInputChecker ( "Y", "y", shape_designation ) )
            {
            
                inputAcquirer ( width, "Enter the length of the Square: ");
            
                rectangle ( width, width, '@');

            }
            else
            {

                inputAcquirer ( width, "Enter the length of the Square: ");
            
                rectangle ( width, width, ' ');
            }
        }
    
        if( validInputChecker ( "Triangle", "triangle", shape ) )
        {

            inputAcquirer ( shape_designation, "Would you like to draw the triangle inverted (Y/N) : ","Y", "y", "N", "n");
        
            if ( validInputChecker ( "Y", "y", shape_designation ) )
            {
            
                inputAcquirer ( length, "Enter the max length of the triangle: ");
            
                downtriangle( length, 0, 1);
            
            }
            else
            {
            
                inputAcquirer ( length, "Enter the max length of the triangle: ");
            
                uptriangle( 0, length, 1);
            }
        }
        if (validInputChecker ( "US", "us", shape ) || validInputChecker ( "US Flag", "us flag", shape ))
        {
            usFlag();
        }
        
    inputAcquirer ( end_question, "Would you like to draw another shape(Y/N) : ","Y", "y", "N", "n");
    
    if (validInputChecker ( "N", "n", end_question ) )
    {
        end_Draw = true;
    }
        
    input_Complete = false;
        
    }while ( end_Draw == false );
    
    return 0;
}


void line ( int length, char space )
{
    for ( int cntr = 0; cntr < length; cntr++)
    {
        cout << "@" << space;
    }
    cout << endl;
}


void verticalLine ( int length )
{
    for ( int cntr = 0; cntr < length; cntr++ )
    {
        cout << "@" << endl;
    }
}


void rectangle ( int width, int height, char space )
{
    for ( int height_cntr = 0; height_cntr < height; height_cntr++ )
    {
        
        for ( int width_cntr = 0; width_cntr < width; width_cntr++ )
        {
            if( height_cntr == 0 || height_cntr == height -1 || width_cntr == width - 1 || width_cntr == 0)
                cout << "@" << " ";
            else
                cout << space << " ";
        }
        
        cout << endl;
    }
}


void uptriangle ( int init, int max, int increment )
{
    for ( int cntr = init; cntr <= max; cntr += increment)
    {
        for ( int inner_cntr = 0; inner_cntr < cntr; inner_cntr++)
            cout << "@ ";
        cout << endl;
    }
}


void downtriangle ( int init, int max, int increment )
{
    for ( int cntr = init; cntr >= max; cntr -= increment)
    {
        for ( int inner_cntr = 0; inner_cntr < cntr; inner_cntr++)
            cout << "@ ";
        cout << endl;
    }
}


void usFlag ( )
{
    for ( int cntr = 0; cntr < 13; cntr++)
    {
        if ( cntr < 7 )
        {
            if( cntr % 2 == 0)
            {
                //cout << "No Space" << endl;
                stars('\0');
                cout << " ";
                stripes(33);
                cout << endl;
            }
            else
            {
                //cout << "Space" << endl;
                stars(' ');
                cout << endl;
            }
        }
        
        else if( cntr % 2 == 0)
        {
            //cout << "No Space" << endl;
            stripes(46);
            cout << endl;
        }
        else
        {
            //cout << "Space" << endl;
            cout << endl;
        }
        
    }
}


void stars ( char space )
{
    cout << space;
    for ( int cntr = 0; cntr < 6; cntr++)
    {
        cout << "★";
        if(cntr <= 5)
            cout << " ";
    }
}


void stripes ( int length )
{
    for ( int cntr = 0; cntr < length; cntr++)
    {
        cout << "▀";
        if ( cntr < 50)
        {
            cout << "";
        }
    }
}


void inputAcquirer ( string &shape, string requestSentece, string correctInputUpper,
                     string correctInputLower, string correctInputUpper2,
                     string correctInputLower2)
{
    bool input_Complete = false;
    while ( input_Complete == false )
    {
        cout << requestSentece;
        cin >> shape;
        
        
        if ( validInputChecker ( correctInputUpper, correctInputLower, shape ) ||
            validInputChecker ( correctInputUpper2, correctInputLower2, shape ))
        {
            input_Complete = true;
        }
        else
        {
            cout << "Please enter a valid option.";
        }
        cout << endl << endl;
    }
}

void inputAcquirer ( int &length, string requestSentece  )
{
    bool input_Complete = false;
    
    while ( input_Complete == false)
    {
        cout << requestSentece;
        cin >> length;
        cout << endl;
        
        if( !cin )
        {
            cout << "Please enter a valid input";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        }
        else if ( length < 1)
        {
            cout << "Please enter a input greater than or equal to 1";
            cout << endl;
        }
        else
        {
            input_Complete = true;
        }
    }
}

bool validInputChecker ( string upperExpected, string lowerExpected, string input )
{
    bool checker = false;
    if ( input == upperExpected || input == lowerExpected )
        checker = true;
    
    return checker;
}
