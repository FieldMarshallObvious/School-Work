/*
Documentation block
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

//Global constants if needed

//Type declarations if needed


using namespace std;
//Function prototypes
string Read_questions ( );
string Read_answers( );
void Show_question( );
bool Player_try( char choice, string q_array[], int correct_choice );
void Play_game( ifstream &question_bank, ifstream &answers_bank, ofstream &summary );
void Sort_score( );



int main ()
{
    //Create file in and out var
    ifstream question_bank;
    
    question_bank.open("questions.txt");
    
    if( ! question_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Question bank file failed to open." << endl;
        
        return -1;
    }
    
    ifstream answers_bank;
    
    answers_bank.open("questions.txt");
    
    if( ! answers_bank )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Answer bank file failed to open." << endl;
        
        return -2;
    }
    
    ofstream summary;
    
    summary.open("summary.txt");
    
    if ( ! summary )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Answer bank file failed to open." << endl;
        
        return -3;
    }
    
    question_bank.close();
    answers_bank.close();
    summary.close();
    
    return 0;
}

bool Player_try ( string choice, string q_array[], int correct_choice )
{
    if( toupper(choice) == q_array[correct_choice] )
    {
        
    }
    
    return false;
}

void Play_game ( ifstream &question_bank, ifstream &answers_bank, ofstream &summary )
{
    const int POINT_MULTIPLE = 10;
    const int POINT_MULTIPLE_HALF = 5;
    
    string q_array[4];
    string student;
    string choice;
    
    int correct_choice;
    
    cout << "What is your name?" << endl;
    cin >> choice;
    
    cout << endl;
    
    Show_question();
    
    cout << "Your choice? > ";
    cin >> choice;
}

string Read_answers ( )
{
    
    return " ";
}

string Read_questions ( )
{
    
    return " ";
}

void show_question ( string q_array[], int &correct_choice, ifstream &question_bank, ifstream &answers_bank)
{
    //Question existence check
    
    //Question answer loop check
    
    q_array[1] = Read_questions();
    q_array[3] = Read_answers();
    
    cout << q_array[0] << " Here's Question Number " << q_array[1]<< endl
         << q_array[2] << endl;
    
    //Question options loop - using delimeter for endls
}
