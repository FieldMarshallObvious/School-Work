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
        Framebuffer* pFrame;
        Framebuffer* rFrame;
        Framebuffer* frameBuffers[2];
        int currentBuffer;

        bool(*renderCallback)();

        void initializerFramebuffer( int width, int height );
        
    public:
        Rasterizer( int width, int height );
        ~Rasterizer();

        void rasterizeTriangle( const Vector2& v1, const Vector2& v2, const Vector2& v3 );
        void presentFrame(int x, int y);
        
        inline void clearFrame(){rFrame->clear(0);}
        inline void swapBuffers()
        {
            currentBuffer ^= 1;
            pFrame = frameBuffers[currentBuffer];
            rFrame = frameBuffers[currentBuffer ^ 1];
        }
        inline void setRenderCB(bool(*rendercb)())
        {
            renderCallback = rendercb;
        }
};

#endif