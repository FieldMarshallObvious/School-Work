#include "Vector3.h"
#include <math.h>

//Constructor
Vector3::Vector3( float x, float y, float z )
  //Initilization List
  :x( x ), y( y ), z( z )
{}

//Copy Constructor
Vector3::Vector3( const Vector3& oldVector )
    :x( oldVector.x ), y( oldVector.y ), z( oldVector.z )
{}

Vector3& Vector3::operator=( const Vector3& oldVector )
{
    x = oldVector.x;
    y = oldVector.y;
    z = oldVector.z;

    return *this;
}

Vector3::~Vector3(){}

float Vector3::length() const
{
    return sqrt( x * x + y * y + z * z );
}

void Vector3::add( const Vector3& left, const Vector3& right, Vector3& dest )
{
    dest.x = left.x + right.x;
    dest.y = left.y + right.y;
    dest.z = left.z + right.z;
}

void Vector3::subtract( const Vector3& left, const Vector3& right, Vector3& dest )
{
    dest.x = left.x - right.x;
    dest.y = left.y - right.y;
    dest.z = left.z - right.z;

}

void Vector3::multiply( const Vector3& left, const Vector3& right, Vector3& dest )
{
    dest.x = left.x * right.x;
    dest.y = left.y * right.y;   
    dest.z = left.z * right.z;

}

void Vector3::crossProduct( const Vector3& a, const Vector3& b, Vector3& dest )
{
    dest.x = (a.y * b.z) - ( a.z * b.y) ;
    dest.y = ( a.z + b.x ) - ( a.x + b.z );
    dest.z = ( a.x * b.y ) - ( a.y * b.x );
}

void Vector3::lerp(  const Vector3& a, const Vector3& b, float t, Vector3& dest  )
{
    dest.x = a.x + ( ( b.x - a.x ) * t );
    dest.y = a.y + ( ( b.y - a.y ) * t );
    dest.z = a.z + ( ( b.z - a.z) * t );
}


Vector3& Vector3::operator%=(const Vector3& right){
    Vector3::crossProduct(*this, right, *this);
   
   return *this;
}

Vector3& Vector3::operator+=(const Vector3& right)
{
    Vector3::add( *this, right, *this );

    return *this;
}
Vector3& Vector3::operator-=(const Vector3& right)
{
    Vector3::subtract( *this, right, *this );

    return *this;
}


Vector3 Vector3::operator+(const Vector3& right)
{
    Vector3 output;
    Vector3::add( *this, right, output );

    return output;
}
Vector3 Vector3::operator-(const Vector3& right)
{
    Vector3 output;
    Vector3::subtract( *this, right, output );

    return output;
}
Vector3 Vector3::operator%(const Vector3& right)
{
    Vector3 output;
    Vector3::crossProduct( *this, right, output );

    return output;
}
float Vector3::operator*(const Vector3& b)
{
    float output = Vector3::dotProduct( *this, b );

    return output; 
}

float Vector3::dotProduct( const Vector3& left, const Vector3& right )
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

float Vector3::angle( const Vector3& left, const Vector3& right )
{
    float dot = Vector3::dotProduct( left, right );

    return acos( dot/(left.length() *  right.length()));
}

float Vector3::distance( const Vector3& a, const Vector3& b )
{
    float xDiff = a.x - b.x;
    float yDiff = a.y - b.y;
    float zDiff = a.z - b.z;

    return sqrt( xDiff * xDiff + yDiff * yDiff  + zDiff * zDiff );
}

Vector3 Vector3::getNormalized( const Vector3& input )
{
    Vector3 ret(input);

    ret.normalize();

    return ret;
}

void Vector3::scale( float s )
{
    x += s;
    y += s;
    z += s;
}

void Vector3::normalize( )
{
    float mag = length( ); 

    x /= mag;
    y /= mag;
    z /= mag;
}