#ifndef INCLUDE_RASTERIZER_H
#define INCLUDE_RASTERIZER_H

class Vector2;
class Vector3;
class Vector4;
class Matrix44;

struct Framebuffer
{
    Framebuffer( int width, int height )
    : width(width), height(height)
    {}

    int width, height;
};

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
};

#endif