#ifndef INCLUDE_GEN_MATH_H
#define INCLUDE_GEN_MATH_H

class GenMath
{
    public: 
        static float interpolate( float a, float b,  float t );
        static float toRadians( float degress );
        static float toDegress( float radians );
};

#endif