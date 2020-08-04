#include <iostream>
#include "defs.h"

#include "Vector2.h"
#include "Rasterizer.h"


using namespace std;

int main(void) {
    //Setup ncurses window
    initscr();
    raw();
    noecho();

    Rasterizer rasterizer( WW, WH );
    Vector2 v1(10, 0);
    Vector2 v2(50, 10);
    Vector2 v3(100, 40);

    rasterizer.rasterizeTriangle( v1, v2, v3 );


    getch();

    //Clear buffer stack

    endwin();

    return 0;
}