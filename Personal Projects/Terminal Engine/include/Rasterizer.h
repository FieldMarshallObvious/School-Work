#ifndef INCLUDE_RASTERIZER_H
#define INCLUDE_RASTERIZER_H

#include "Framebuffer.h"


class Vector2;
class Vector3;
class Vector4;
class Matrix44;

class Rasterizer
{
    private:
        Framebuffer* fb;
        void initializerFramebuffer( int width, int height );
        
    public:
        Rasterizer( int width, int height );
        ~Rasterizer();

        void rasterizeTriangle( const Vector2& v1, const Vector2& v2, const Vector2& v3 );

        inline Framebuffer* getFrameBuffer() const {return fb;};
        inline void presentFrame(int x, int y){ fb->print(x,y);}
        inline void clearFrame(){fb->clear(0);}
};

#endif