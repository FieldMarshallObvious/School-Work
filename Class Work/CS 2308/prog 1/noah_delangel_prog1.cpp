/*
Documentation block
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <random>

//Global constants if needed

//Type declarations if needed


using namespace std;
//Function prototypes
string Get_answer ( ifstream &answers_bank );
int Randinex( int chosen_questions[], int max );
string Read_questions ( ifstream &question_bank );
string Read_answers( ifstream &question_bank);
void Show_question( string student, int q_num, string q_array[][5], int index );
bool Player_try( string answers_array[], int index );
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
    
    answers_bank.open("answers.txt");
    
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
    
    Play_game(question_bank, answers_bank, summary);
    
    question_bank.close();
    answers_bank.close();
    summary.close();
    
    return 0;
}

string Get_answer ( ifstream &answers_bank )
{
    string output;
    
    getline(answers_bank, output);
    
    return output;
}

bool Player_try ( string answers_array[], int index )
{
    string correct_choice = answers_array[index];
    string choice;
    
    bool output = false;
    
    cout << "Your choice? > ";
    cin >> choice;
    
    if( toupper(choice[0]) == toupper(correct_choice[0]) )
        output = true;
    
    return output;
}

void Play_game ( ifstream &question_bank, ifstream &answers_bank, ofstream &summary )
{
    const int POINT_MULTIPLE = 10;
    const int POINT_MULTIPLE_HALF = 5;
    
    string q_array[50][5];
    string answers_array[50];
    string student;
    string input;
    
    int chosen_questions[50];
    int q_num = 1;
    int total_ques = 0;
    
    cout << "What is your name?" << endl;
    getline(cin, student);
    
    cout << endl;
    
    //Question array creation
    for(int i = 0; i < 50; i++)
    {
        if( !question_bank.eof() )
            total_ques++;
        
        for(int j = 0; j < 5; j++)
        {
            input = Read_questions( question_bank );
            if(j == 0 && ( strlen( input.c_str()) != 0 || strlen(input.c_str()) != 1 ) )
            {
                q_array[i][j] = input;
            }
            else if ( strlen(input.c_str()) != 0 || strlen(input.c_str()) != 1 )
            {
                q_array[i][j] = input;
            }
        }
        
        answers_array[i] = Read_answers( answers_bank );
    }
    
    cout << "Total questions is" << total_ques << endl;
    //Display questions and accept input from user
    while( q_num <= total_ques )
    {
        int index = 0;
        
        //Question existence check
        
        //Question answer loop check
        
        Show_question( student, q_num, q_array, index );
    
        cout << Player_try( answers_array, index) << endl;
        
        chosen_questions[q_num-1] = index;
        
        q_num++;
    }
    
    if( question_bank.eof() && (! answers_bank.eof()) )
    {
        cout << "***Program Terminated.***" << endl << endl
            << "There are more answers then there are questions." << endl;
        
        return;
    }
    
    else if ( (! question_bank.eof()) && answers_bank.eof() )
    {
        cout << "***Program Terminated.***" << endl << endl
            << "There are more questions then there are answers." << endl;
        
        return;
    }
    
}

int Randinex( int chosen_questions[], int max )
{
    bool unique_item = false;
    
    int rand_int;
    
    srand(time(NULL));
    
    do {
        unique_item = true;
        
        int rand_int = rand()%max + 0;
        
        for( int cntr = 0; cntr < max; cntr++)
        {
            if( chosen_questions[cntr] == rand_int )
            {
                unique_item = false;
                break;
            }
        }
    } while( unique_item == false );
    
    cout << "The rand int is " << rand_int << endl;
    return rand_int;
}

string Read_answers ( ifstream &answers_bank )
{
    string output;
    
    getline(answers_bank, output);
    
    cout << "The answer is: " << output << endl;
    
    return output;
}

string Read_questions ( ifstream &question_bank )
{
    string output = "";
    
    while ( getline(question_bank, output) && (!question_bank.eof()) )
    {
        if (strlen(output.c_str()) == 1 || strlen(output.c_str()) == 0) {
            cout << "Detected empty line" << endl;
            cout << "The line is: " << output << endl;
            continue;
        }
        
        else
        {
            cout << "Detected non-empty line" << endl;
            cout << "The line is: " << output << endl;
            break;
        }
    }
    
    cout << "End of loop" << endl;
    
    return output;
}

void Show_question ( string student, int q_num, string q_array[][5], int index )
{
    string multipe_choice[4] = {"A.", "B.", "C.", "D."};
    
    cout << student << " Here's Question Number " << q_num << endl
         << q_array[index][0] << endl;
    
    for( int i = 1; i < 5; i++)
        cout << multipe_choice[i] << " " << q_array[index][i] << endl;
    
}
