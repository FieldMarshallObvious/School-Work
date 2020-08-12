#ifndef INCLUDE_RASTERIZER_H
#define INCLUDE_RASTERIZER_H

#include "Framebuffer.h"
#include <thread>


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

        //std::thread renderThread;

        int currentBuffer;

        bool(*renderCallback)();

        void initializeFramebuffer( int width, int height );
        
    public:
        Rasterizer( int width, int height );
        ~Rasterizer();

        void rasterizeTriangle( const Vector2& vv1, const Vector2& vv2, const Vector2& vv3, const Vector2& vv4, const Vector2& vv5, const Vector2& vv6, int colorPair, int colorPair2, int z1, int z2  );
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