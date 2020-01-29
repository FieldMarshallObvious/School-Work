/*
Documentation block
*/

#include <iostream>
#include <ifstream>

//Global constants if needed

//Type declarations if needed

//Function prototypes
void read_questions ( );
void read_answers( );
void show_question( );
void player_try( );
void play_game( );
void sort_score( );

using namespace std;

int main ()
{
    //Create file in and out var
    
    return 0;
}

void player_try ( )
{
    
    if( toupper(choice) == q_array[correct_choice] )
    {
        
    }
}

void play_game( )
{
    const int POINT_MULTIPLE = 10;
    const int POINT_MULTIPLE_HALF = 5;
    
    string q_array[6];
    string student;
    
    char choice;
    
    int correct_choice;
    
    //Question existence check
    
    //Question answer loop check
    
    //Question existence check
    
    //Question answer loop check
    
    show_question();
    
    cout << "Your choice? > "
    cin >> choice;
}

void read_answers( )
{
    //Question options loop
}

void read_questions ( )
{
    //Question display logic
    
    cout << student << " Here's Question Number " << q_num<< endl
    << question << endl;
}

void show_question ( )
{
    read_questions();
    read_answers();
}
