#include <iostream>
#include "defs.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "GenMath.h"
#include "Rasterizer.h"


using namespace std;

int main(void) {
    //Setup ncurses window
    initscr();
    raw();
    noecho();

    Rasterizer rasterizer( WW, WH );

    float angle = 0;

    Matrix44 transformation;
    transformation.scale(Vector3(5, 1, 1));
    transformation.rotate(Vector3(0, 0, 1), GenMath::toRadians(400));

    Vector4 v1(10, -5, 1, 1);
    Vector4 v2(5, 15, 1, 1);
    Vector4 v3(50, 10, 1, 1);

    v1 = transformation * v1;
    v2 = transformation * v2;
    v3 = transformation * v3;
    
    rasterizer.clearFrame();

    rasterizer.rasterizeTriangle( Vector2(v1.getX(), v1.getY()), 
                                  Vector2(v2.getX(), v2.getY()), 
                                  Vector2(v3.getX(), v3.getY()) );
    rasterizer.presentFrame( 0, 0 );

    getch();
    clear();

    //Clear buffer stack

    endwin();

    return 0;
}