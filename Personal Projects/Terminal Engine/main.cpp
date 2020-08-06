#include <iostream>
#include "defs.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "GenMath.h"
#include "Rasterizer.h"


using namespace std;

float angle = 0;
Rasterizer* rasterizer = nullptr;

bool renderCB()
{
        angle+=0.002f;
        Matrix44 transformation;
        transformation.scale(Vector3(0.5, 1, 1));
        transformation.rotate(Vector3(1, 1, 0), angle);

        Vector4 v1(-1, 1, 0, 1);
        Vector4 v2(1, 1, 0, 1);
        Vector4 v3(0, -1, 1, 1);

        v1 = transformation * v1;
        v2 = transformation * v2;
        v3 = transformation * v3;
        
        rasterizer->clearFrame();

        rasterizer->rasterizeTriangle( Vector2(v1.getX(), v1.getY()), 
                                    Vector2(v2.getX(), v2.getY()), 
                                    Vector2(v3.getX(), v3.getY()) );

        return true;
}

int main(void) {
    //Setup ncurses window
    initscr();
    raw();
    noecho();
    start_color();
    cbreak();
    curs_set(0);

    rasterizer = new Rasterizer(WW, HH);
    rasterizer->setRenderCB(renderCB);

    while(true)
    {

        rasterizer->presentFrame( 0, 0 );
        rasterizer->swapBuffers();

        refresh();
        erase();
    }

    getch();
    clear();

    //Clear buffer stack

    endwin();

    delete rasterizer;

    return 0;
}