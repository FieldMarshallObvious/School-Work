#include <iostream>
#include <defs.h>


using namespace std;

int main(void) {
    //Setup ncurses window
    initscr();
    raw();
    noecho();

    
    printw("this a test of ncurses!");
    getch();

    //Clear buffer stack

    endwin();

    return 0;
}