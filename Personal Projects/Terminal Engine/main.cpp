#include "defs.h"
#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Rasterizer.h"
#include "Matrix44.h"
#include "GenMath.h"
#include "Camera.h"

float angle = 0;
Rasterizer* rasterizer = nullptr;
Camera* cam = nullptr;

Vector4 v1(-1, 1, 0, 1);
Vector4 v2(1, 1, 0, 1);
Vector4 v3(0, -1, 0, 1);

Vector4 v4(-1, 1, 1, 0);
Vector4 v5(1, 1, 1, 0);
Vector4 v6(0, -1, 1, 0);

Vector4 transformVertex( const Vector4& vertex, const  Matrix44& MVPMatrix){
    Vector4 f;

    f = MVPMatrix * vertex;
    f.setX( f.getX() / f.getW() );
    f.setY( f.getY() / f.getW() );
    f.setZ( f.getZ() / f.getW() );

    return f;
}

bool renderCB(){
    Matrix44 transformation;
    Matrix44 PVMatrix;
    Matrix44 finalMatrix;

    cam->calculateViewMatrix();
    
    PVMatrix = cam->getPVMatrix();

    angle += .001f;

    transformation.translate(Vector3(0, 0, -2));
    transformation.rotate(Vector3(0, 1, 0), angle);
    finalMatrix = PVMatrix * transformation;

    Vector4 fv1 = transformVertex(v1, finalMatrix);
    Vector4 fv2 = transformVertex(v2, finalMatrix);
    Vector4 fv3 = transformVertex(v3, finalMatrix);

    Vector4 fv4 = transformVertex(v4, finalMatrix);
    Vector4 fv5 = transformVertex(v5, finalMatrix);
    Vector4 fv6 = transformVertex(v6, finalMatrix);

    rasterizer->clearFrame();
    rasterizer->rasterizeTriangle(Vector2(fv1.getX(), fv1.getY()), 
                                  Vector2(fv2.getX(), fv2.getY()), 
                                  Vector2(fv3.getX(), fv3.getY()),
                                  Vector2(fv4.getX(), fv4.getY()), 
                                  Vector2(fv5.getX(), fv5.getY()), 
                                  Vector2(fv6.getX(), fv6.getY()), 1200, 1000, 2, -1);

    rasterizer->rasterizeTriangle(Vector2(fv4.getX(), fv4.getY()), 
                                  Vector2(fv5.getX(), fv5.getY()), 
                                  Vector2(fv6.getX(), fv6.getY()),
                                  Vector2(fv1.getX(), fv1.getY()), 
                                  Vector2(fv2.getX(), fv2.getY()), 
                                  Vector2(fv3.getX(), fv3.getY()), 1000, 1200, -1, 2);

    return true;
}

int main(void){
	initscr();
	raw();
	noecho();

    cbreak();
    curs_set(0);

    start_color();
    init_pair(1,COLOR_BLUE, COLOR_RED);

    rasterizer = new Rasterizer(WW, HH);
    cam = new Camera();
    cam->createProjection(1.21f, (WW / (float)2) / HH, .2f, 400);

    rasterizer->setRenderCB(renderCB);

    while(true){
        //attron(COLOR_PAIR(COLOR_PAIR(1)));

        rasterizer->presentFrame(0 , 0);
        rasterizer->swapBuffers();

        refresh();
        erase();
    }

    getch();
    clear();

    endwin();

    delete rasterizer;
    delete cam;

    return 0;
}