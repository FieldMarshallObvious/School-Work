
#include "Rasterizer.h"

#include "defs.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>

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
 :fb(nullptr)
{
    initializerFramebuffer( width, height );
}

Rasterizer::~Rasterizer()
{
    delete fb;
}

void Rasterizer::rasterizeTriangle( const Vector2& v1, const Vector2& v2, const Vector2& v3 )
{
    int minX,maxX;
    int minY, maxY;

    minX = MAX(0, MIN(v1.getX(), MIN(v2.getX(), v3.getX())));
    minY = MAX(0, MIN(v1.getY(), MIN(v2.getY(), v3.getY())));

    maxX = MIN(fb->width, MAX(v1.getX(), MAX(v2.getX(), v3.getX())) + 1);
    maxY = MIN(fb->height, MAX(v1.getY(), MAX(v2.getY(), v3.getY())) + 1);

    for( int j = minY; j < maxY; j++ )
    {
        for( int i = minX; i < maxX; i++ )
        {
            if( isPointInTriangle(i, j, v1, v2, v3) )
            {
                mvprintw( j, i, "#");
            }
            else
            {
                mvprintw( j, i, "." );
            }
            
        }
    }

}

void Rasterizer::initializerFramebuffer( int width, int height )
{
    fb = new Framebuffer( width, height );
}


