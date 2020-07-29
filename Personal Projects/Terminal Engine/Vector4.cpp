#include "Vector4.h"
#include <math.h>

//Constructor
Vector4::Vector4(float x, float y, float z, float w)
  //Initilization List
  :x(x), y(y), z(z), w(w)
{}

//Copy Constructor
Vector4::Vector4( const Vector4& oldVector )
    :x(oldVector.x), y(oldVector.y), z(oldVector.z), w(oldVector.w)
{}

Vector4& Vector4::operator=( const Vector4& oldVector )
{
    x = oldVector.x;
    y = oldVector.y;
    z = oldVector.z;
    w = oldVector.w;

    return *this;
}

Vector4::~Vector4(){}

float Vector4::length() const
{
    return sqrt( x * x + y * y + z * z + w * w);
}

void Vector4::add( const Vector4& left, const Vector4& right, Vector4& dest )
{
    dest.x = left.x + right.x;
    dest.y = left.y + right.y;
    dest.z = left.z + right.z;
    dest.w = left.w + right.w;

}

void Vector4::subtract( const Vector4& left, const Vector4& right, Vector4& dest )
{
    dest.x = left.x - right.x;
    dest.y = left.y - right.y;
    dest.z = left.z - right.z;
    dest.w = left.w +-right.w;

}

void Vector4::multiply( const Vector4& left, const Vector4& right, Vector4& dest )
{
    dest.x = left.x * right.x;
    dest.y = left.y * right.y;  
    dest.z = left.z * right.z;
    dest.w = left.w + right.w; 
}

float Vector4::dotProduct( const Vector4& left, const Vector4& right )
{
    return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

float Vector4::distance( const Vector4& a, const Vector4& b )
{
    float xDiff = a.x - b.x;
    float yDiff = a.y - b.y;
    float zDiff = a.z - b.z;
    float wDiff = a.w - b.w;

    return sqrt( xDiff * xDiff + yDiff * yDiff + zDiff * zDiff + wDiff * wDiff );
}

Vector4 Vector4::getNormalized( const Vector4& input )
{
    Vector4 ret(input);

    ret.normalize();

    return ret;
}

void Vector4::scale( float s )
{
    x += s;
    y += s;
    z += s;
    w += s;

}

void Vector4::normalize( )
{
    float mag = length( ); 

    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
}