#include "Rasterizer.h"

#include "defs.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>

bool renderStart, renderFinished, programRunning;

void renderThreadF(bool(**renderCB)())
{
    while(programRunning)
    {
        if(renderStart)
        {
            renderStart = false;
            renderFinished = false;

            if(*renderCB != nullptr)
            {
                (*renderCB)();
            }

            renderFinished = true;
        }
    }
}

inline static bool isPointInTriangle( int ptX, int ptY, const Vector2& v1, const Vector2& v2, const Vector2& v3)
{
    float wv1 = ((v2.getY() - v3.getY()) * (ptX - v3.getX()) +
                 (v3.getX() - v2.getX()) * (ptY - v3.getY())) /
                ((v2.getY() - v3.getY()) * (v1.getX() - v3.getX()) +
                 (v3.getX() - v2.getX()) * (v1.getY() - v3.getY()));

    float wv2 = ((v3.getY() - v1.getY()) * (ptX - v3.getX()) +
                 (v1.getX() - v3.getX()) * (ptY - v3.getY())) /
                ((v2.getY() - v3.getY()) * (v1.getX() - v3.getX()) +
                 (v3.getX() - v2.getX()) * (v1.getY() - v3.getY()));

    float wv3 = 1.0f - wv1 - wv2;

    int one = (wv1 < -0.001);
    int two = (wv2 < -0.001);
    int three = (wv3 < -0.001);

    return ((one == two) && (two == three));
}

Rasterizer::Rasterizer( int width, int height )
 :pFrame(nullptr), rFrame(nullptr), currentBuffer(0), renderCallback(nullptr)
{
    programRunning = true;
    renderStart = false;
    renderFinished = false;

    initializeFramebuffer( width, height );

    //renderThread = std::thread(renderThreadF, &renderCallback);
}

Rasterizer::~Rasterizer()
{
    delete frameBuffers[0];
    delete frameBuffers[1];
}

void Rasterizer::rasterizeTriangle( const Vector2& vv1, const Vector2& vv2, const Vector2& vv3, const Vector2& vv4, const Vector2& vv5, const Vector2& vv6, int colorPair, int colorPair2, int z1, int z2 )
{
    int minX,maxX;
    int minY, maxY;

    Framebuffer* fb = rFrame;

    int halfWidth = fb->getWidth() / 2,
        halfHeight = fb->getHeight() / 2;

    Vector2 v1 = Vector2( vv1.getX() * halfWidth + halfWidth, -vv1.getY() * halfHeight + halfHeight );
    Vector2 v2 = Vector2( vv2.getX() * halfWidth + halfWidth, -vv2.getY() * halfHeight + halfHeight );
    Vector2 v3 = Vector2( vv3.getX() * halfWidth + halfWidth, -vv3.getY() * halfHeight + halfHeight );

    Vector2 v4 = Vector2( vv4.getX() * halfWidth + halfWidth, -vv4.getY() * halfHeight + halfHeight );
    Vector2 v5 = Vector2( vv5.getX() * halfWidth + halfWidth, -vv5.getY() * halfHeight + halfHeight );
    Vector2 v6 = Vector2( vv6.getX() * halfWidth + halfWidth, -vv6.getY() * halfHeight + halfHeight );

    minX = MAX(0, MIN(v1.getX(), MIN(v2.getX(), v3.getX())));
    minY = MAX(0, MIN(v1.getY(), MIN(v2.getY(), v3.getY())));

    maxX = MIN(fb->getWidth(), MAX(v1.getX(), MAX(v2.getX(), v3.getX())) + 1);
    maxY = MIN(fb->getHeight(), MAX(v1.getY(), MAX(v2.getY(), v3.getY())) + 1);


    for( int j = minY; j < maxY; j++ )
    {
        for( int i = minX; i < maxX; i++ )
        {
            if( isPointInTriangle(i, j, v1, v2, v3) && !isPointInTriangle( i, j, v4, v5, v6 ) )
            {
                fb->setPixel( i, j, colorPair, 0);
            }

            else if ( !isPointInTriangle(i, j, v1, v2, v3) && isPointInTriangle( i, j, v4, v5, v6 ) )
            {
                fb->setPixel( i, j, colorPair2, 0);
            }

            else if ( isPointInTriangle(i, j, v1, v2, v3) && isPointInTriangle( i, j, v4, v5, v6 ) )
            {
                if( z1 > z2 )
                    fb->setPixel( i, j, colorPair, 0);
                if( z1 < z2 )
                    fb->setPixel( i, j, colorPair2, 0);
                else
                    fb->setPixel( i, j, colorPair, 0);
            }

            else
            {
                fb->setPixel( i, j, ' ', 0);
            }
            
        }
    }
}

void Rasterizer::presentFrame(int x, int y)
{ 
    //renderStart = true;
    if(renderCallback !=nullptr)
    {
        std::thread renderThread(renderCallback);
        pFrame->print(x,y);

        renderThread.join();
    }    

    //while(!renderFinished);
    //renderFinished = true;
}


void Rasterizer::initializeFramebuffer( int width, int height )
{
    frameBuffers[0] = new Framebuffer( width, height );
    frameBuffers[1] = new Framebuffer( width, height );
    swapBuffers();
}


