/*
Documentation block
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>

//Global constants if needed

//Type declarations if needed


using namespace std;
//Function prototypes
void Game_over ( string name, int score );
string Get_answer ( ifstream &answers_bank );
int Randinex( int chosen_questions[], int max );
string Read_questions ( ifstream &question_bank );
string Read_answers( ifstream &question_bank);
void Show_question( string student, int q_num, string q_array[][5], int index );
void Show_question( string student, string choice, int q_num, string q_array[][5], int index );
bool Player_try( string answers_array[], int index, string choice );
void Play_game( ifstream &question_bank, ifstream &answers_bank, fstream &summary );
void Sort_score( string name, int score, fstream &summary );



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
        
        return -1;
    }
    
    fstream summary;
    
    summary.open("summary.txt", ios::in | ios::out);
    
    if ( ! summary )
    {
        cout << "***Program Terminated.***" << endl << endl
             << "Summary file failed to open." << endl;
        
        return -1;
    }
    
    Play_game(question_bank, answers_bank, summary);
    
    question_bank.close();
    answers_bank.close();
    summary.close();
    
    return 0;
}

void Game_over ( string name, int score )
{
    cout << "--- Game Over! ---" << endl;
    
    cout << name << " you scored " << score << " !" << endl
         << "Check summary.txt for your ranking!" << endl;
    
}

string Get_answer ( ifstream &answers_bank )
{
    string output;
    
    getline(answers_bank, output);
    
    return output;
}

bool Player_try ( string answers_array[], int index, string choice )
{
    string correct_choice = answers_array[index];
    
    bool output = false;
    
    cout << "The correct choice is " << correct_choice << endl;
    
    if( toupper(choice[0]) == toupper(correct_choice[0]) )
        output = true;
    
    return output;
}

void Play_game ( ifstream &question_bank, ifstream &answers_bank, fstream &summary )
{
    const int POINT_MULTIPLE = 10;
    const int POINT_MULTIPLE_HALF = 5;
    
    string q_array[50][5];
    string answers_array[50];
    string student;
    string choice;
    
    int chosen_questions[50];
    int q_num = 1;
    int score = 0;
    int total_ques = 0;
    int total_ans = 0;
    
    bool truth_value;
    
    cout << "What is your name?" << endl;
    getline(cin, student);
    
    cout << endl;
    
    //Question array creation
    for(int i = 0; i < 50; i++)
    {
        if( !question_bank.eof() )
        {
            total_ques++;
            total_ans++;
        }
        else
            break;
        
        for(int j = 0; j < 5; j++)
        {
            
            if(j == 0)
                q_array[i][j] = Read_questions( question_bank );
            
            else
                q_array[i][j] = Read_questions( question_bank );
        }
        
        
        answers_array[i] = Read_answers( answers_bank );
    }
    
    
    //Checks to ensure same numbers of
    if( total_ans > total_ques )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "There are more answers then there are questions." << endl;
        
        return;
    }
    
    else if ( total_ans < total_ques  )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "There are more questions then there are answers." << endl;
        
        return;
    }

    //Display questions and accept input from user
    while( q_num <= total_ques )
    {
        string retry_choice;
        
        int index = Randinex(chosen_questions, total_ques);

        //Display question first round
        Show_question( student, q_num, q_array, index );
        
        //Acquires answer choice from user
        cout << "Your choice? > ";
        cin >> choice;
        
        
        
        //Asses correctness of user choice
        truth_value = Player_try( answers_array, index, choice);
        
        cout << truth_value << endl;
        
        if( truth_value == false )
        {
            cout << "Would you try again? (Y/N)" << endl
                 << "> ";
            cin >> retry_choice;
            
            if ( toupper(retry_choice[0]) == toupper('Y'))
            {
                //Displays question for second attempt
                Show_question ( student, choice, q_num, q_array, index );
            
                //Acquires choice from user
                cout << "Your choice? > ";
                cin >> choice;
            
                //Asses correctness of user choice
                truth_value = Player_try( answers_array, index, choice);
            
                cout << truth_value << endl;
                
                if ( truth_value == true )
                {
                    if( score >= 1)
                        score *= 5;
                    else
                        score = 5;
                    cout << "The score is now " << score << endl;
                }
                
                else
                {
                    Game_over(student, score);
                    return;
                }
            }

        }
        
        else
        {
            
            if(score >= 1)
                score *= 10;
            else
                score = 10;
            cout << "The score is now " << score << endl;
        }
        
        chosen_questions[q_num-1] = index;
        
        q_num++;
    }
    
    Game_over(student, score);
    
}

int Randinex( int chosen_questions[], int max )
{
    bool unique_item = false;
    
    int rand_int;
    
    srand(time(NULL));
    
    do {
        unique_item = true;
        
        rand_int = rand() % (max-1) + 0;

        for( int cntr = 0; cntr < max; cntr++)
        {
            if( chosen_questions[cntr] == rand_int )
            {
                unique_item = false;
                break;
            }
        }
    } while( unique_item == false );
    
    return rand_int;
}

string Read_answers ( ifstream &answers_bank )
{
    string output;
    
    while ( getline(answers_bank, output) && (!answers_bank.eof()))
    {
        if (strlen(output.c_str()) == 1 || strlen(output.c_str()) == 0)
            continue;
        
        else
            break;
    }
    
    return output;
}

string Read_questions ( ifstream &question_bank )
{
    string output = "";
    
    while ( getline(question_bank, output) && (!question_bank.eof()) )
    {
        if (strlen(output.c_str()) == 1 || strlen(output.c_str()) == 0)
            continue;
        
        else
            break;
    }
    
    return output;
}

void Sort_score ( string name, int score, fstream &summary )
{
    int num_of_players = 0;
    string input;
    
    while( ! summary.eof() )
    {
        summary >> input;
        
        if (strlen(input.c_str()) == 1 || strlen(input.c_str()) == 0) {}
        
        else
            num_of_players++;
    }
    
    summary.close();
    
    summary.open("summary.txt", ios::in | ios::out);
    
    if ( ! summary )
    {
        cout << "***Program Terminated.***" << endl << endl
        << "Summary file failed to open." << endl;
        
        return;
    }
    
    
    string summary_entries[num_of_players+1][3];
    
    for( int i = 0; i <= num_of_players; i++ )
    {
        for( int j = 0; j < 3; j++)
        {
            summary >> input;
            
            if ( strlen(input.c_str()) == 1 || strlen(input.c_str()) == 0 ) {}
            
            else
                summary_entries[i][j] = input;
                
        }
    }
    
    for( int i = 0; i <= num_of_players; i++ )
    {
        if( stoi(summary_entries[i][2]) < score )
        {
            
        }
    }
    
    
}

void Show_question ( string student, int q_num, string q_array[][5], int index )
{
    string multipe_choice[4] = {"A", "B", "C", "D"};
    
    cout << student << " Here's Question Number " << q_num << endl
         << q_array[index][0] << endl;
    
    for( int i = 1; i < 5; i++)
        cout << multipe_choice[i-1] << ". " << q_array[index][i] << endl;
    
}

void Show_question( string student, string choice, int q_num, string q_array[][5], int index )
{
    string multipe_choice[4] = {"A", "B", "C", "D"};
    
    cout << student << " Here's Question Number " << q_num << " (second try)" << endl
         << q_array[index][0] << endl;
    
    for( int i = 1; i < 5; i++)
    {
        string current_index = multipe_choice[i-1];
        
        if( toupper( current_index[0] ) != toupper( choice[0] ) )
            cout << multipe_choice[i-1] << ". " << q_array[index][i] << endl;
        else {}
            
    }
}
