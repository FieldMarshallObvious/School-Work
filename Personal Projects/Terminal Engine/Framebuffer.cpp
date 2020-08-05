#include "Framebuffer.h"
#include <memory.h>

Framebuffer::Framebuffer( int width, int height )
    :width(width), height(height)
{
    reCreate(width, height);
} 

Framebuffer::~Framebuffer()
{
    delete[] depthbuffer;
    delete[] colorbuffer;
}

void Framebuffer::reCreate(int width, int height)
{
    this->width = width;
    this->height = height;

    colorbuffer = new colorbuffer_t[width * height];
    depthbuffer = new depthbuffer_t[width * height];
}


void Framebuffer::clear(int clearColor)
{
    memset(colorbuffer, clearColor, sizeof(colorbuffer_t) * width * height);
    memset(depthbuffer, MAX_DEPTH_VALUE, sizeof(depthbuffer_t) * width * height);
}

void Framebuffer::setPixel( int x, int y, colorbuffer_t pixelcolor, depthbuffer_t depth )
{
    int index = (y * width ) + x;

    if( depth < depthbuffer[index] )
    {
        colorbuffer[index] = pixelcolor;
        depthbuffer[index] = depth;
    }
}

void Framebuffer::print( int offsetX, int offsetY )
{
    for(int i = offsetX; i < width; i++){
        for(int j = offsetY; j < height; j++){
            int index = (width * j) + i;

            //if(!colorbuffer[index]) continue;

            int color = (char)(colorbuffer[index] >> 8);
            attron(COLOR_PAIR(color));

            mvprintw(j, i, "%c", (char)colorbuffer[index]);
        }
    }
}

colorbuffer_t Framebuffer::getColor( int x, int y )
{
    int index = ( y * width ) + x;
    return colorbuffer[index];
}

depthbuffer_t Framebuffer::getDepth( int x, int y )
{
    int index = ( y * width ) + x;
    return depthbuffer[index];
}
